/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:54:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/12 23:00:45 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

int	is_redir(int c)
{
	if (c && (\
	c == '<' || \
	c == '>' || \
	c == '|'))
		return (1);
	return (0);
}

int	is_space(int c)
{
	if (c && (\
	c == ' ' || \
	c == '\t' || \
	c == '\n' || \
	c == '\r' || \
	c == '\f' || \
	c == '\v'))
		return (1);
	return (0);
}

int	is_cmd(int c)
{
	if (c && (\
	(c >= 'a' && c <= 'z') || \
	(c >= 'A' && c <= 'Z') || \
	(c >= '0' && c <= '9') || \
	c == '$' || \
	c == '*' || \
	c == '/' || \
	c == '.' || \
	c == '-' || \
	c == '_' || \
	c == '\\'))
		return (1);
	return (0);
}

char	*cwd_compress(t_data *data)
{
	char	*short_cwd;
	char	*home;
	int		len;

	short_cwd = NULL;
	if (!data->envp_cpy)
		home = get_envp_var(data->envp, "HOME=");
	else
		home = get_envp_var(data->envp_cpy, "HOME=");
	len = ft_strlen(home);
	if (!ft_strncmp(data->cwd, home, len))
		short_cwd = str_replace(data->cwd, home, "~");
	return (short_cwd);
}

void	print_msg(t_data *data, char *msg, int status)
{
	ft_putendl_fd(msg, 2);
	data->status = status;
}

void	print_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
	{
		printf("%s", array[i]);
		if (array[i + 1])
			printf(" ");
	}
}

char	*type_to_char(int type)
{
	if (type == CMD)
		return ("CMD");
	if (type == OPTION)
		return ("OPTION");
	if (type == ARG)
		return ("ARGUMENT");
	if (type == PIPE)
		return ("PIPE");
	if (type == LEFT)
		return ("<");
	if (type == RIGHT)
		return (">");
	if (type == LEFTT)
		return ("<<");
	if (type == RIGHTT)
		return (">>");
	if (type == FILE)
		return ("FILE");
	if (type == HERE)
		return ("HEREDOC");
	if (type == LOCAL)
		return ("LOCAL");
	return ("NO_TYPE");
}

void	print_types(t_data *data)
{
	t_token	*head;
	t_token	*aux;

	head = data->input.tokens;
	while (head)
	{
		printf("TOKEN: \"%s\"	TYPE: %s(%d)\n", \
		head->token, type_to_char(head->type), head->type);
		aux = head->opt;
		if (aux)
			printf("\t--> OPTIONS:");
		while (aux && aux->type == OPTION)
		{
			printf(" %s", aux->token);
			aux = aux->next;
		}
		printf("\n");
		aux = head->arg;
		if (aux)
			printf("\t--> ARGS:");
		while (aux && aux->type == ARG)
		{
			printf(" %s", aux->token);
			aux = aux->next;
		}
		printf("\n");
		head = head->next;
	}
}

void	print_cmd_array(t_data *data)
{
	t_cmd	*head;

	head = data->input.command;
	while (head)
	{
		if (!(head->builtin))
		{
			printf("CMD_PATH: \"%s\" ARGUMENTS: ", head->cmd);
			print_array(head->args);
			printf("\n");
		}
		head = head->next;
	}
}

int	valid_char(char c)
{
	if (!c)
		return (0);
	if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && \
	(c < '0' || c > '9') && c != '_')
		return (0);
	return (1);
}

int	valid_ident(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != '_' && *str != '$' && \
			(*str < 'A' || *str > 'Z') && (*str < '0' || *str > '9'))
			return (0);
		str++;
	}
	return (1);
}

char	**split_token(char *token)
{
	char	**array;
	int		i;

	array = ft_calloc(3, sizeof(char *));
	i = -1;
	if (token[0] == '=')
	{
		array[0] = ft_strdup(token);
		return (array);
	}
	while (token[++i])
	{
		if (token[i] == '=')
		{
			array[0] = ft_substr(token, 0, i);
			array[1] = ft_strdup(&token[++i]);
			return (array);
		}
	}
	return (NULL);
}

char	*rev_split(char **array)
{
	char	*str;
	char	*prev_str;
	char	*aux;
	int		i;

	i = 0;
	str = ft_strdup(array[i]);
	while (array[++i])
	{
		prev_str = str;
		aux = ft_strjoin(str, " ");
		str = ft_strjoin(aux, array[i]);
		free(aux);
		free(prev_str);
		if (!str)
			break ;
	}
	return (str);
}

char	*get_envp_var(char **envp, char *var)
{
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (!ft_strncmp(*envp, var, ft_strlen(var)))
			return (ft_strchr(*envp, '=') + 1);
		envp++;
	}
	return (NULL);
}

char	*str_replace(char *haystack, char *needle, char *replace)
{
	char	*str;
	char	*ptr;
	char	*aux;
	int		len;

	if (!haystack || !needle)
		return (ft_strdup(haystack));
	ptr = ft_strnstr(haystack, needle, ft_strlen(haystack));
	len = ptr - haystack;
	str = ft_substr(haystack, 0, len);
	if (!str)
		return (NULL);
	ptr = ptr + ft_strlen(needle);
	aux = str;
	str = ft_strjoin(str, replace);
	if (!str)
		return (NULL);
	free (aux);
	aux = str;
	str = ft_strjoin(str, ptr);
	free(aux);
	if (!str)
		return (NULL);
	return (str);
}
