#include "minishell.h"


int main(int argc, char **argv, char *envp[])
{
    char *cmd_line;
    char *prompt = "mini ~$ ";

    (void)argc;
    (void)argv;
    (void)envp;
    while (TRUE)
    {
        cmd_line = readline(prompt);
        ft_split_args(cmd_line);
        // printf("%s\n", cmd_line);
    }
    return (0);
}