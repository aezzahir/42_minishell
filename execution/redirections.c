#include "../minishell.h"

void handle_input_redirection(char *input_file)
{
    int fd;
    
    fd = open(input_file, O_RDONLY);
    if (fd < 0)
            ft_err("open input file");
    if (dup2(fd, STDIN_FILENO) < 0)
        ft_err("dup2 input file");
    close(fd);
}

void handle_output_redirection(char *output_file)
{
    int fd;
    
    fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);  //0644 -> Owner can read and write, group and others can just read
    if (fd < 0)
        ft_err("open output file");
    if (dup2(fd, STDOUT_FILENO) < 0)
        ft_err("dup2 output file");
    close(fd);
}

void handle_append_redirection(char *output_file)
{
    int fd;
    
    fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
        ft_err("open append file");
    if (dup2(fd, STDOUT_FILENO) < 0)
        ft_err("dup2 append file");
    close(fd);
}

