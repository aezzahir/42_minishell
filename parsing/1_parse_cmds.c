#include "../minishell.h"


int ft_what_is_in_node(char *node_content)
{
    if (!node_content)
        return (-1);
    else if (ft_strncmp(node_content, "|", ft_strlen(node_content)) == 0)
        return (1);
    else if (ft_strncmp(node_content, "<", ft_strlen(node_content)) == 0)
        return (2);
    else if (ft_strncmp(node_content, ">", ft_strlen(node_content)) == 0)
        return (3);
    else if (ft_strncmp(node_content, ">>", ft_strlen(node_content)) == 0)
        return (4);
    else if (ft_strncmp(node_content, "<<", ft_strlen(node_content)) == 0)
        return (5);
    else
        return (0);
}

int ft_get_args_num(t_list *node)
{
    int num_of_args;

    num_of_args = 0;
    while (node && ft_what_is_in_node((char *)(node->content)) != 1)
    {
        if (ft_what_is_in_node((char *)(node->content)) == 0)
            num_of_args++;
        else
        {
            if (!(node->next) || ft_what_is_in_node((char *)(node->next->content)) != 0)
                printf("parse error near %s\n", (char *)(node->content));
            else
                node = node->next;
        }
        node = node->next;
    }
    return (num_of_args);
}

char **ft_fill_cmd_args(t_list *node, int num_of_args)
{
    int i;
    char **cmd_args;

    cmd_args = (char **)malloc((num_of_args + 1) * sizeof(char *));
    i = 0;
    while (node && ft_what_is_in_node((char *)(node->content)) != 1 && i < num_of_args)
    {
        if (ft_what_is_in_node((char *)(node->content)) == 0)
            cmd_args[i++] = (char *)(node->content);
        node = node->next;
    }
    cmd_args[i] = NULL;
    return (cmd_args);
}

t_prompt *ft_parse_cmds(t_list **tokens_list)
{
    t_list *node;
    int num_of_cmds;
    int num_of_args;
    t_prompt *prompt;
    t_cmd   cmd;

    if (!tokens_list)
    {
        printf("tokens list is empty!\n");
    }
    num_of_args = 0;
    num_of_cmds = 0;
    node = *tokens_list;
    prompt = (t_prompt *)malloc(sizeof(t_prompt));
    if(!prompt)
        return (NULL); // exit failaire exit(1)
   
    while (node)
    {
        if (num_of_cmds == 0)
        {
            num_of_args = ft_get_args_num(node);
            (cmd->content)
            printf("cmd (%d): num of args = %d\n", num_of_cmds, num_of_args);
        }
        else if (ft_what_is_in_node((char *)(node->content)) == 1)
        {
            if (!(node->next) || ft_what_is_in_node((char *)(node->next->content)) != 0)
            {
                printf("parse error near %s\n", (char *)(node->content));
            }
            node = node->next;
            num_of_args = ft_get_args_num(node);
            num_of_cmds++;
            printf("cmd (%d): num of args = %d\n", num_of_cmds, num_of_args);
        }
        node = node->next;
    }
}

// here I should firts creat a malloc for cmd then fill it with args and the eventual files discriptors then go to the next node or inside the fill args I should instead do fill cmd and fill the cmd automaticcally
I have to do a malloc for the cmd then a malloc for the args fill the args then cmd->args =  args ... I should review and rethink about the logic cause i see a lot of repeated stuff 