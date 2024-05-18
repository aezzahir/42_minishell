#include "../minishell.h"
static void	ft_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
static void ft_pipe_exec(t_cmd *cmd, int *pipefd, char **envp)
{
    pid_t pid;
    // int saved_in, saved_out;

    // saved_in = dup(STDIN_FILENO);
    // saved_out = dup(STDOUT_FILENO);

    // if (cmd->in_fd >= 0)
    // {
    //     dup2(cmd->in_fd, STDIN_FILENO);
    //     close(cmd->in_fd);
    // }
    // else if (pipefd[0] >= 0)
    //     dup2(pipefd[0], STDIN_FILENO);

    // if (cmd->out_fd >= 0)
    // {
    //     dup2(cmd->out_fd, STDOUT_FILENO);
    //     close(cmd->out_fd);
    // }
    // else if (pipefd[1] >= 0)
    //     dup2(pipefd[1], STDOUT_FILENO);

    pid = fork();
    if (pid == 0)
    {
        execve(cmd->cmd_path, cmd->cmd_args, envp);
        ft_exit("execve");
    }
    else if (pid < 0)
        ft_exit("fork");

    // dup2(saved_in, STDIN_FILENO);
    // dup2(saved_out, STDOUT_FILENO);
    // close(saved_in);
    // close(saved_out);
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
                ft_exit("pipe");
        }
        else
            pipefd[0] = pipefd[1] = -1;
        ft_pipe_exec(curr->content, pipefd, envp);

        if (prev_pipe_out >= 0)
            close(prev_pipe_out);

        if (curr->next)
            prev_pipe_out = pipefd[1];

        close(pipefd[0]);
        close(pipefd[1]);
        curr = curr->next;
    }

    return 0;
}
