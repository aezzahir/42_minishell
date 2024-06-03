#include "../minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int g_status;

static void ft_exit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

bool is_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0 ||
            ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 ||
            ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 ||
            ft_strcmp(cmd, "exit") == 0);
}

static void handle_redirections(t_cmd *cmd)
{
    if (cmd->in_files)
    {
        handle_input_redirection((char *)cmd->in_files->content);
    }
    if (cmd->out_files)
    {
        handle_output_redirection((char *)cmd->out_files->content);
    }
    if (cmd->out_files_app)
    {
        handle_append_redirection((char *)cmd->out_files_app->content);
    }
}

static void ft_pipe_exec(t_cmd *cmd, int *pipefd, int prev_pipe_out, char **envp)
{
    pid_t pid;

    if (is_builtin(cmd->cmd_args[0]))
    {
        execute_builtin(cmd->cmd_args);
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        // Handle input from the previous pipe
        if (prev_pipe_out != -1)
        {
            dup2(prev_pipe_out, STDIN_FILENO);
            close(prev_pipe_out);
        }

        // Handle output to the next pipe
        if (pipefd[1] != -1)
        {
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);
        }

        // Handle redirections if any
        if (cmd->in_files || cmd->out_files || cmd->out_files_app)
        {
            handle_redirections(cmd);
        }

        execve(cmd->cmd_path, cmd->cmd_args, envp);
        ft_exit("execve");
    }
    else if (pid < 0)
    {
        ft_exit("fork");
    }

    waitpid(pid, NULL, 0);
}

int ft_exec(t_list *cmds, char **envp)
{
    t_list *curr;
    int pipefd[2];
    int prev_pipe_out = -1;

    curr = cmds;
    while (curr)
    {
        if (curr->next)
        {
            if (pipe(pipefd) < 0)
            {
                ft_exit("pipe");
            }
        }
        else
        {
            pipefd[0] = pipefd[1] = -1;
        }

        ft_pipe_exec(curr->content, pipefd, prev_pipe_out, envp);

        if (prev_pipe_out >= 0)
        {
            close(prev_pipe_out);
        }

        if (curr->next)
        {
            prev_pipe_out = pipefd[0];
            close(pipefd[1]);
        }

        curr = curr->next;
    }

    return 0;
}
