#include "../minishell.h"

extern int g_status;

int ft_exec(t_list *cmds, char **envp)
{
    t_list *curr;
    int pipefd[2];
    int prev_pipe_out = -1;
    t_list *new_in_file;
    t_list *tmp;

    curr = cmds;
    while (curr)
    {
        t_cmd *cmd = curr->content;
        if (cmd->her_docs)
        {
            char final_file[] = "/tmp/minishell_final_heredocXXXXXX";
            int final_fd = mkstemp(final_file);
            if (final_fd == -1)
                ft_err("mkstemp");
            close(final_fd);
            concatenate_files(final_file, cmd->her_docs, envp);
            new_in_file = malloc(sizeof(t_list));
            if (!new_in_file)
                ft_err("malloc");
            new_in_file->content = ft_strdup(final_file);
            if (!new_in_file->content)
                ft_err("strdup");
            new_in_file->next = cmd->in_files;
            cmd->in_files = new_in_file;
            while (cmd->her_docs)
            {
                tmp = cmd->her_docs;
                cmd->her_docs = cmd->her_docs->next;
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
                ft_err("pipe");
        }
        else
            pipefd[0] = pipefd[1] = -1;
        if (curr->content)
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

int create_unique_temp_file(char *template, int num)
{
    char final_file[256];
    int fd;

    sprintf(final_file, "%s%05d", template, num);
    fd = open(final_file, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd == -1 && errno == EEXIST)
        return create_unique_temp_file(template, num + 1);
    if (fd == -1)
        ft_err("open unique final heredoc temp file");
    strcpy(template, final_file);
    return fd;
}

static void handle_redirections(t_cmd *cmd, char **envp)
{
    t_list *current;

    current = cmd->in_files;
    while (current)
    {
        handle_input_redirection((char *)current->content);
        current = current->next;
    }
    if (cmd->her_docs)
    {
        char final_file[] = "/tmp/minishell_final_heredocXXXXXX";
        int final_fd = mkstemp(final_file);
        if (final_fd == -1)
            ft_err("mkstemp");
        close(final_fd);
        concatenate_files(final_file, cmd->her_docs, envp);
        int fd = open(final_file, O_RDONLY);
        if (fd < 0)
            ft_err("open final heredoc temp file");
        if (dup2(fd, STDIN_FILENO) < 0)
            ft_err("dup2 heredoc");
        close(fd);
        unlink(final_file);
    }
    current = cmd->out_files;
    while (current)
    {
        handle_output_redirection((char *)current->content);
        current = current->next;
    }
    current = cmd->out_files_app;
    while (current)
    {
        handle_append_redirection((char *)current->content);
        current = current->next;
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
        return;  // Return to avoid fork if it's a builtin
    }

    pid = fork();
    if (pid == 0)
    {
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
        ft_err("execve");
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    if (pipefd[1] != -1)
        close(pipefd[1]);
    if (prev_pipe_out != -1)
        close(prev_pipe_out);

    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        g_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        g_status = 128 + WTERMSIG(status); // Common convention for signal exits
}
