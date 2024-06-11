#include "../minishell.h"

extern int g_status;

int ft_exec(t_list *cmds, char **envp)
{
    t_list *curr;
    int pipefd[2];
    int prev_pipe_out = -1;
    char final_file[] = "/tmp/minishell_final_heredocXXXXXX";
    t_list *new_in_file;
    t_list *tmp;

    curr = cmds;
    while (curr)
    {
        t_cmd *cmd = curr->content;
        if (cmd->her_docs)
        {
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
                ft_err("pipe");
        }
        else
            pipefd[0] = pipefd[1] = -1;
        if(curr->content)
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
