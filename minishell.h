#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>
//
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include <stdbool.h>

#include <errno.h>
#include <string.h> // Include this header for strerror
//
#define TRUE 1
#define FALSE 0


typedef struct s_prompt
{
	t_list	*cmds; // linked list of cmds ... 
	char	**envp;
	pid_t	pid;
}		t_prompt;

typedef struct s_cmd
{
	char			**cmd_args;
	char			*cmd_path;
	t_list	    	*in_files;
	t_list	    	*her_docs;
	t_list	    	*out_files;
	t_list	    	*out_files_app;
	t_list	    	*ignored_files;

}		t_cmd;

typedef struct s_env {
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_mini {
    t_env *env;
} t_mini;

// 1 - tokenazing strings
void 		ft_split_tokens(t_list **tokens_list, char *input, char **envp);
void 		ft_add_token(t_list **tokens_list, char *token);


// 1.1 - handles herdoc quotes and enviremental variables
char		*ft_handle_envar(char *token, char **envp);
void ft_handle_heredoc(t_list **tokens_list, char *input, int *end);
void concatenate_files(char *final_file, t_list *her_docs, char **envp);

int ft_handle_quote(t_list **tokens_list, char **envp, char *input, int *start, int *end, char quote);
char 		*ft_exit_status(char *token);
int 		ft_handle_syntax_errors(t_list **tokens_list);
int		unclosed_qoutes(char *input);

char		*ft_substrdup(const char *str, int *start, int *end);






// 1 - parsing commandes
t_cmd   *ft_parse_cmds(t_list *token, char **envp);
t_list *get_cmds_list(t_list *token, char **envp);
//
void	free_split(char **str);

char 	*get_path(char *cmd, char **envp);
char	*find_path(char **arge);
int ft_is_special_char(char c);

/// Excution part :-)

int ft_exec(t_list *cmds, char **envp);
void execute_builtin(char *args[]);

// redirections
void handle_input_redirection(char *input_file);
void handle_output_redirection(char *output_file);
void handle_append_redirection(char *output_file);

// builtins
void cd(char *path);
void echo(char *args[]);
void env();
void exit_shell(char *arg);
void export_env(char *var);
void pwd();
void unset_env(char **vars);
bool is_builtin(char *cmd);

void ft_pipe_exec(t_cmd *cmd, int *pipefd, int prev_pipe_out, char **envp);

void setup_default_env(void);


int is_number(const char *str);
void print_env_vars(void);
void print_error(const char *msg, const char *arg);
// signals
typedef struct s_signal_context
{
    int pid;
    int exit_status;
    int sigint;
    int sigquit;
} t_signal_context;


// utility functions 
int ft_iswhitespace(char c);
int ft_is_special_token(t_list *token); // is it a PIPE APPEND OR WHAT
int ft_special_token_is_a_file(t_list *token);
char *remove_quotes(char *delim);
char *remove_multiple_whitespaces(char *str);
int ft_in_quote(char *str, char *address);



void ft_print_nodes(void *content);
void ft_print_prompt(void *content);

#define EMPTY 0
#define	PIPE  1
#define INFILE 2
#define TRUNC 3
#define APPEND 4
#define HERDOC 5
#define IGNORE 7
#define NORMAL 6

#endif