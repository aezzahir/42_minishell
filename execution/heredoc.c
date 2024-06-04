// #include "../minishell.h"

// void handle_heredoc(char *delimiter, char *tmp_file)
// {
//     char *line;
//     int fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd < 0)
//     {
//         perror("open temp file");
//         exit(EXIT_FAILURE);
//     }

//     while (1)
//     {
//         line = readline("> ");
//         if (line == NULL || strcmp(line, delimiter) == 0)
//         {
//             free(line);
//             break;
//         }
//         write(fd, line, strlen(line));
//         write(fd, "\n", 1);
//         free(line);
//     }

//     close(fd);
// }
