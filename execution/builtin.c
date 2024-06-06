
#include "../minishell.h"
#include <string.h>

void cd(char *path)
{
    if (chdir(path) != 0)
    {
        perror("cd");
    }
}

void echo(char *args[]) {
    bool newline = true;
    int i = 1;

    if (args[1] && args[1][0] == '-') {
        bool all_n = true;
        for (int j = 1; args[1][j] != '\0'; j++) {
            if (args[1][j] != 'n') {
                all_n = false;
                break;
            }
        }
        if (all_n) {
            newline = false;
            i++;
        }
    }

    for (; args[i] != NULL; i++) {
        if (i > 1) {
            printf(" ");
        }
        printf("%s", args[i]);
    }
    if (newline) {
        printf("\n");
    }
}


void pwd()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("pwd");
    }
}

int check_name(const char *name)
{
    int j = 0;
    while (name[j])
    {
        if (!ft_isalnum((int)name[j]) && name[j] != '_')
        {
            fprintf(stderr, "Invalid variable name\n");
            return 1;
        }
        j++;
    }
    return 0;
}

void export_env(char *var)
{
    char *value;
    char *name;
    char *var_copy;
    int i;

    if (var == NULL || strchr(var, '=') == NULL)
    {
        fprintf(stderr, "export: invalid format\n");
        return;
    }
    i = 0;
    while (var[i] && var[i] != '=')
        i++;
    name = strndup(var, i);
    if (name == NULL)
    {
        perror("export");
        return;
    }
    if (check_name(name))
    {
        free(name);
        return;
    }
    value = ft_strdup(var + i + 1);
    if (value == NULL)
    {
        perror("export");
        free(name);
        return;
    }
    var_copy = malloc(strlen(name) + strlen(value) + 2);
    if (var_copy == NULL)
    {
        perror("export");
        free(name);
        free(value);
        return;
    }
    sprintf(var_copy, "%s=%s", name, value);
    if (putenv(var_copy) != 0)
    {
        perror("export");
        free(var_copy);
    }
    free(name);
    free(value);
}

void unset_env(char *var)
{
    if (var == NULL || *var == '\0' || strchr(var, '=') != NULL)
    {
        fprintf(stderr, "unset: invalid variable name\n");
        return;
    }

    if (unsetenv(var) != 0)
    {
        perror("unset");
    }

}

void exit_shell(int status)
{
    exit(status);
}

void env()
{
    extern char **environ;
    for (char **env = environ; *env != 0; env++)
    {
        printf("%s\n", *env);
    }
}


void execute_builtin(char *args[])
{
    if (ft_strcmp(args[0], "cd") == 0)
    {
        cd(args[1]);
    }
    else if (ft_strcmp(args[0], "echo") == 0)
    {
        echo(args);
    }
    else if (ft_strcmp(args[0], "pwd") == 0)
    {
        pwd();
    }
    else if (ft_strcmp(args[0], "export") == 0)
    {
        export_env(args[1]);
    }
    else if (ft_strcmp(args[0], "unset") == 0)
    {
        unset_env(args[1]);
    }
    else if (ft_strcmp(args[0], "env") == 0)
    {
        env();
    }
    else if (ft_strcmp(args[0], "exit") == 0)
    {
        int status = args[1] ? ft_atoi(args[1]) : 0;
        exit_shell(status);
    }
}