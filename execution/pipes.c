#include "../minishell.h"

static void handle_redirections(t_cmd *cmd, char **envp)
{
    t_list *current;

    // Handle input redirections
    current = cmd->in_files;
    while (current)
    {
        handle_input_redirection((char *)current->content);
        current = current->next;
    }

    // Handle heredocs
    if (cmd->her_docs)
    {
        char final_file[] = "/tmp/minishell_final_heredocXXXXXX";
        int final_fd = mkstemp(final_file);
        if (final_fd == -1)
        {
            perror("mkstemp");
            exit(EXIT_FAILURE);
        }
        close(final_fd);

        concatenate_files(final_file, cmd->her_docs, envp);

        int fd = open(final_file, O_RDONLY);
        if (fd < 0)
        {
            perror("open final heredoc temp file");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDIN_FILENO) < 0)
        {
            perror("dup2 heredoc");
            exit(EXIT_FAILURE);
        }
        close(fd);
        unlink(final_file);
    }
    current = cmd->out_files;
    if (current)
    {
        while (current->next)
        {
            handle_output_redirection((char *)current->content);
            current = current->next;
        }
        handle_output_redirection((char *)current->content);
    }
    current = cmd->out_files_app;
    if (current)
    {
        while (current->next)
        {
            handle_append_redirection((char *)current->content);
            current = current->next;
        }
        handle_append_redirection((char *)current->content);
    }
}

void ignore()
{
    printf("\n");
}
void ft_pipe_exec(t_cmd *cmd, int *pipefd, int prev_pipe_out, char **envp)
{
    pid_t pid;

    if (is_builtin(cmd->cmd_args[0]))
    {
        execute_builtin(cmd->cmd_args);
        return;
    }
    signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        if (prev_pipe_out != -1)
        {
            dup2(prev_pipe_out, STDIN_FILENO);
            close(prev_pipe_out);
        }
        if (pipefd[1] != -1)
        {
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);
        }
        handle_redirections(cmd, envp);
        execve(cmd->cmd_path, cmd->cmd_args, envp);
        // ft_exit("execve");
    }
    else if (pid < 0)
    {
        signal(SIGINT, ignore);
        // ft_exit("fork");
    }

    waitpid(pid, NULL, 0);
}