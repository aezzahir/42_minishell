#include "../../minishell.h"


void echo(char *args[]) {
    bool newline = true;
    int i = 1;
    int j = 1;
    if (args[1] && args[1][0] == '-') {
        bool all_n = true;
  
    while (args[1][j] != '\0') {
        if (args[1][j] != 'n') {
            all_n = false;
            break;
        }
        j++;
    }

        if (all_n) {
            newline = false;
            i++;
        }
    }

  while (args[i] != NULL) {
    if (i > 1) {
        printf(" ");
    }
    printf("%s", args[i]);
    i++;
}

    if (newline) {
        printf("\n");
    }
}
