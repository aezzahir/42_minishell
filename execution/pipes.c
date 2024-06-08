#include "../minishell.h"

int create_unique_temp_file(char *template, int num)
{
    char final_file[256];
    int fd;
    sprintf(final_file, "%s%05d", template, num);

    fd = open(final_file, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd == -1 && errno == EEXIST) {
        return create_unique_temp_file(template, num + 1);
    }

    if (fd == -1) {
        perror("open unique final heredoc temp file");
        exit(EXIT_FAILURE);
    }

    strcpy(template, final_file);
    return fd;
}

static void handle_redirections(t_cmd *cmd, char **envp)
{
    t_list *current;
    char final_file_template[] = "/tmp/minishell_final_heredoc";
    current = cmd->in_files;
    while (current && current->content)
    {
        handle_input_redirection((char *)current->content);
        current = current->next;
    }
    if (cmd->her_docs)
    {
        int final_fd = create_unique_temp_file(final_file_template, 0);
        close(final_fd);
        concatenate_files(final_file_template, cmd->her_docs, envp);
        int fd = open(final_file_template, O_RDONLY);
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
        unlink(final_file_template);
    }
    current = cmd->out_files;
    if (current && current->content)
    {
        while (current->next)
        {
            handle_output_redirection((char *)current->content);
            current = current->next;
        }
        handle_output_redirection((char *)current->content);
    }
    current = cmd->out_files_app;
    if (current && current->content)
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
        // return;
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