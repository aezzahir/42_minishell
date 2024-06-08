#include "../minishell.h"

#define HEREDOC_LIMIT 16

void handle_heredoc(char *delimiter, char *tmp_file, int remove_tabs, char **envp)
{
    char *line;
    int quoted_delim;
    char *tmp;
    int fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open temp file");
        exit(EXIT_FAILURE);
    }
    quoted_delim = FALSE;
    if (!(ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\'')))
        quoted_delim = TRUE;
    delimiter = remove_quotes(delimiter); 
    while (1)
    {
        line = readline("heredoc> ");
        if (quoted_delim)
            line = ft_handle_envar(line, envp);
        if (line == NULL || ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        tmp = line;
        if (remove_tabs)
        {
            while (*tmp == '\t')
                tmp++;   
            write(fd, tmp, ft_strlen(tmp));
        }
        else
            write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    free(delimiter);
    close(fd);
}

void concatenate_files(char *final_file, t_list *her_docs, char **envp)
{
    t_list *current = her_docs;
    char buffer[1024];
    ssize_t bytes_read;

    int heredoc_count = 0;
    while (current)
    {
        heredoc_count++;
        current = current->next;
    }

    if (heredoc_count > HEREDOC_LIMIT)
    {
        fprintf(stderr, "Error: too many heredocs, maximum allowed is %d\n", HEREDOC_LIMIT);
        exit(EXIT_FAILURE);
    }

    current = her_docs;
    int final_fd = open(final_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (final_fd < 0)
    {
        perror("open final temp file");
        exit(EXIT_FAILURE);
    }

    while (current->next)
    {
        current = current->next;
    }

    char tmp_file[] = "/tmp/minishell_heredocXXXXXX";
    int tmp_fd = mkstemp(tmp_file);
    if (tmp_fd == -1)
    {
        perror("mkstemp");
        exit(EXIT_FAILURE);
    }
    close(tmp_fd);
    handle_heredoc((char *)current->content, tmp_file, 0, envp);

    int fd = open(tmp_file, O_RDONLY);
    if (fd < 0)
    {
        perror("open heredoc temp file");
        exit(EXIT_FAILURE);
    }
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
        write(final_fd, buffer, bytes_read);
    close(fd);
    unlink(tmp_file); 

    close(final_fd);
}
