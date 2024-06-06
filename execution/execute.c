#include "../minishell.h"

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
        unlink(final_file); // Remove the final temporary file after use
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
static void ft_pipe_exec(t_cmd *cmd, int *pipefd, int prev_pipe_out, char **envp)
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
        ft_exit("execve");
    }
    else if (pid < 0)
    {
        signal(SIGINT, ignore);
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
        t_cmd *cmd = curr->content;
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
            t_list *new_in_file = malloc(sizeof(t_list));
            if (!new_in_file)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            new_in_file->content = ft_strdup(final_file);
            if (!new_in_file->content)
            {
                perror("strdup");
                exit(EXIT_FAILURE);
            }
            new_in_file->next = cmd->in_files;
            cmd->in_files = new_in_file;
            t_list *tmp;
            while (cmd->her_docs)
            {
                tmp = cmd->her_docs;
                cmd->her_docs = cmd->her_docs->next;
                // free(tmp->content);
                free(tmp);
            }
        }
        curr = curr->next;
    }
    curr = cmds;
    while (curr)
    {
        if (curr->next)
        {
            if (pipe(pipefd) < 0)
                ft_exit("pipe");
        }
        else
            pipefd[0] = pipefd[1] = -1;
        ft_pipe_exec(curr->content, pipefd, prev_pipe_out, envp);

        if (prev_pipe_out >= 0)
            close(prev_pipe_out);
        if (curr->next)
        {
            prev_pipe_out = pipefd[0];
            close(pipefd[1]);
        }
        curr = curr->next;
    }

    return 0;
}