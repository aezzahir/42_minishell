#include "../minishell.h"


int ft_is_what(t_list *token)
{
	char *token_content;


	if (!token)
		return (-1);
	token_content = (char *)(token->content);
	if (!token_content)
		return (-1);
	if (ft_strncmp(token_content, "|", ft_strlen(token_content)) == 0)
		return (0);
	else if (ft_strncmp(token_content, "<", ft_strlen(token_content)) == 0)
		return (2);
	else if (ft_strncmp(token_content, ">", ft_strlen(token_content)) == 0)
		return (3);
	else if (ft_strncmp(token_content, ">>", ft_strlen(token_content)) == 0)
		return (4);
	else if (ft_strncmp(token_content, "<<", ft_strlen(token_content)) == 0)
		return (5);
	else
		return (1);
}

void ft_add_arg_to_cmd(t_cmd **cmd, t_list *token, int args_num)
{
	int i;


	(*cmd)->cmd_args = (char **)malloc((args_num + 1) * sizeof(char *));
	if (!(*cmd)->cmd_args)
		return;
	i = 0;
	while (ft_is_what(token) >= 1 && i < args_num)
	{
		if (ft_is_what(token) == 1)
		{
			(*cmd)->cmd_args[i] = (char *)(token->content);
			i++;
		}
		token = token->next;
	}
	(*cmd)->cmd_args[i] = NULL;
}


void ft_handle_special_tok(t_cmd *cmd, t_list *token)
{
	int fd;

	if (token && ft_is_what(token) == 2 && token->next && token->next->content)
	{
		fd = open((char *)token->next->content, O_RDONLY);
		if (fd < 0)
			return;
		cmd->in_fd = fd;
	}
	else if (token && ft_is_what(token) == 3 && token->next && token->next->content)
	{
		fd = open((char *)token->next->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0)
			return;
		cmd->out_fd = fd;
	}
	else if (token && ft_is_what(token) == 4 && token->next && token->next->content)
	{
		fd = open((char *)token->next->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return;
		cmd->out_fd = fd;
	}
	else if (token && ft_is_what(token) == 5 && token->next && token->next->content)
	{
		// handle herdoc 
		return;
	}
}
t_list *get_cmds_list(t_list *token)
{
	t_list *cmds;
	int piping;

	piping = 0;
	cmds = NULL;
	while (token)
	{
		if (piping == 0 && ft_is_what(token) == 1)
		{
			ft_lstadd_back(&cmds, ft_lstnew((void *)ft_parse_cmds(token)));
			piping = 1;
		}
		else if (ft_is_what(token) == 0)
		{
			token = token->next;
			ft_lstadd_back(&cmds, ft_lstnew((void *)ft_parse_cmds(token)));
		}

		token = token->next;
	}
	return (cmds);
}
void ft_initilize(t_cmd *cmd)
{
	cmd->cmd_args = NULL;
	cmd->cmd_path = NULL;
	cmd->in_fd = 0;
	cmd->out_fd = 1;
}
t_cmd   *ft_parse_cmds(t_list *token)
{
	t_list  *tmp_tok;
	t_cmd   *cmd;
	int args_num;

	if (!token)
	{
		printf("tokens list is empty!\n");
	}
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if(!cmd)
		return (NULL);
	ft_initilize(cmd);
	args_num = 0;
	tmp_tok = token;
	while (ft_is_what(tmp_tok) >= 1)
	{
		if (ft_is_what(tmp_tok) == 1)
			args_num++;
		else if (ft_is_what(tmp_tok) >= 2)
		{
			ft_handle_special_tok(cmd, tmp_tok);
			tmp_tok = tmp_tok->next;
		}
		tmp_tok = tmp_tok->next;
	}
	ft_add_arg_to_cmd(&cmd, token, args_num);
	return (cmd);
}

// here I should firts creat a malloc for cmd then fill it with args and the eventual files discriptors then go to the next token or inside the fill args I should instead do fill cmd and fill the cmd automaticcally
// I have to do a malloc for the cmd then a malloc for the args fill the args then cmd->args =  args ... I should review and rethink about the logic cause i see a lot of repeated stuff 
