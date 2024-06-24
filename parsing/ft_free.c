#include "../minishell.h"
extern int	g_status;
void	free_str_array(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
		free(str);
	str = NULL;
}
void free_token(void *ptr)
{
    t_token *token;

    token = (t_token *)ptr;
    if (token)
    {
        if (token->value)
            free(token->value);
        free(token);
    }
}
void    free_cmd(void *ptr)
{
	t_cmd *cmd;

	cmd = (t_cmd *)ptr;	
	if (cmd)
	{
		if (cmd->cmd_args) // the args themselves we did already freed them in tokens  the same for the others because we are usig pointer
			free(cmd->cmd_args);
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		if (cmd->her_docs)
			free(cmd->her_docs);
		if (cmd->ignored_files)
			free(cmd->ignored_files);
		if (cmd->in_files)
			free(cmd->in_files);
		if (cmd->out_files)
			free(cmd->out_files);
		if (cmd->out_files_app)
			free(cmd->out_files_app);
		free(cmd);
	}
}
