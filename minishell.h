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

// Tokens :
typedef enum e_token_type {
    TOKEN_WORD,           // Regular word/command/ arg
    TOKEN_PIPE,           // |
    TOKEN_REDIRECT_IN,    // <
    TOKEN_REDIRECT_OUT,   // >
    TOKEN_APPEND,         // >>
    TOKEN_HEREDOC,        // <<
	TOKEN_IGNORE,			// <>
    TOKEN_ENV_VAR,        // $VAR
    TOKEN_SINGLE_QUOTE,   // '
    TOKEN_DOUBLE_QUOTE,   // "
    HERDOC_DELIM,            // DELIM
    
} t_token_type;

typedef struct s_token {
    char *value;
    t_token_type type;
} t_token;

// --------------------------------------------------------------------------
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
void ft_add_token(t_list **tokens_list, char *value, t_token_type type);
t_token *new_token(char *value, t_token_type type);
int ft_token_type(char *token);
char *ft_expand_variable(char *token, char **envp);
void ft_expand_variables(t_list *tokens_list, char **envp);
char *ft_remove_quotes(char *str);
void ft_handle_heredoc(t_list **tokens_list);
void ft_remove_quotes_from_tokens(t_list *tokens_list);
void ft_add_node(t_list **tokens_list, char *content);
// 1.1 - handles herdoc quotes and enviremental variables


// -------------------- Handles Syntax Errors ---------------------------|
int check_syntax_errors(t_list *tokens);                              // |
int is_redirection(t_token_type type);                                // |
int	         unclosed_qoutes(char *input);                            // |
int syntax_error(char *token);                                        // |
//------------------------------------------------------------------------


char *ft_strndup(const char *s, size_t n);



// parsing files && cmd args ...
void ft_initialize_cmd(t_cmd *cmd);
void ft_parse_files(t_cmd *cmd, t_list *token);
void ft_parse_cmd_args(t_cmd *cmd, t_list *head, int n_args);
t_cmd *ft_parse_cmds(t_list *head, char **envp);
t_list *get_cmds_list(t_list *head, char **envp);








//
void	free_split(char **str);

char 	*get_path(char *cmd, char **envp);
char	*find_path(char **arge);
int ft_is_special_char(char c);

/// Excution part :-)



// utility functions 
int ft_iswhitespace(char c);
int ft_is_file(t_token *token);
char *remove_quotes(char *delim);




void ft_print_nodes(void *content);
void ft_print_prompt(void *content);

#endif