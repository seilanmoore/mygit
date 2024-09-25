/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/25 15:50:57 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>
#include <time.h>

char	*get_dollar_value(t_data *data, char *variable)
{
	t_environment	*env_var;
	t_l_variable	*local_head;

	env_var = get_env_var(data->env, variable);
	if (env_var)
		return (env_var->value);
	local_head = get_l_var(data->local, variable);
	if (local_head)
		return (local_head->value);
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

//terminar implementacion de expansion de variables

void	replace_dollar(t_data *data)
{
	char	*token;
	char	**tmp;
	int		i;
	char	*dollar_value;
	char	*aux;

	token = data->input.tokens->token;
	tmp = ft_split(data->input.tokens->token, ' ');
	i = -1;
	while (tmp[++i])
	{
		if (ft_strrchr(tmp[i], '$') && ft_strlen(tmp[i]) > 1 && !ft_strnstr(tmp[i], "\\$", 2))
		{
			dollar_value = get_dollar_value(data, ft_strrchr(tmp[i], '$') + 1);
			aux = tmp[i];
			if (dollar_value &&)
				tmp[i] = ft_strdup(dollar_value);
			else
				tmp[i] = ft_strdup("");
			free(aux);
		}
	}
	data->input.tokens->token = rev_split(tmp);
	free(token);
	free_array(tmp);
}

void	check_dollar(t_data *data)
{
	t_tokens	*token_head;
	char		*tmp;
	char		*dollar_value;

	token_head = data->input.tokens;
	while (data->input.tokens)
	{
		if (data->input.tokens->quote == NO_QUOTE && \
			data->input.tokens->token[0] == '$')
		{
			tmp = data->input.tokens->token;
			dollar_value = get_dollar_value(data, data->input.tokens->token + 1);
			if (dollar_value)
				data->input.tokens->token = ft_strdup(dollar_value);
			else
				data->input.tokens->token = ft_strdup("");
			free(tmp);
		}
		else if (data->input.tokens->quote == D_QUOTE)
			replace_dollar(data);
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = token_head;
}

static void	set_prev_token(t_data *data)
{
	t_tokens	*head;
	t_tokens	*prev;

	head = data->input.tokens;
	prev = head;
	if (!data->input.tokens)
		return ;
	data->input.tokens = data->input.tokens->next;
	while (data->input.tokens)
	{
		data->input.tokens->prev = prev;
		prev = data->input.tokens;
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
}

static void	single_quote(t_data *data, t_var *var)
{
	var->aux1++;
	while (var->aux1[var->i] && var->aux1[var->i] != '\'')
		var->i++;
	if (var->aux1[var->i] && var->aux1[var->i] == '\'')
		var->aux = ft_substr(var->aux1, 0, var->i);
	var->i++;
	add_back_token(&(data->input.tokens), new_token(var->aux, 0, S_QUOTE));
}

static void	double_quote(t_data *data, t_var *var)
{
	var->aux1++;
	while (var->aux1[var->i] && \
		(var->aux1[var->i] != '\"' || \
		(var->aux1[var->i] == '\"' && var->aux1[var->i - 1] == '\\')))
		var->i++;
	if (var->aux1[var->i] && var->aux1[var->i] == '\"')
		var->aux = ft_substr(var->aux1, 0, var->i);
	var->i++;
	add_back_token(&(data->input.tokens), new_token(var->aux, 0, D_QUOTE));
}

static void	characters(t_data *data, t_var *var)
{
	while (var->aux1[var->i] && \
		var->aux1[var->i] != ' ' && \
		var->aux1[var->i] != '\'' && \
		var->aux1[var->i] != '\"' && \
		var->aux1[var->i] != '=' && \
		var->aux1[var->i] != '\n')
		var->i++;
	if (var->aux1[var->i] == '=')
		var->i++;
	var->aux = ft_substr(var->aux1, 0, var->i);
	add_back_token(&(data->input.tokens), new_token(var->aux, 0, NO_QUOTE));
	if (var->aux1[var->i] && var->aux1[var->i] == '\n')
		var->i++;
}

static void	parse_tokens(t_data *data)
{
	t_var	var;

	var = (t_var){0};
	var.aux1 = data->input.raw_line;
	while (*var.aux1)
	{
		var.i = 0;
		var.aux = NULL;
		while (*var.aux1 && \
			(*var.aux1 == ' ' || *var.aux1 == '\t' || *var.aux1 == '\n'))
			var.aux1++;
		if (*var.aux1 && *var.aux1 == '\'')
			single_quote(data, &var);
		else if (*var.aux1 && *var.aux1 == '\"')
			double_quote(data, &var);
		else if (*var.aux1)
			characters(data, &var);
		var.aux1 = var.aux1 + var.i;
	}
	data->n_token = lst_size(data->input.tokens);
}

void	access_to_types(t_data *data, int target, int type)
{
	t_tokens	*head;
	int			i;

	head = data->input.tokens;
	i = -1;
	while (++i != target)
		data->input.tokens = data->input.tokens->next;
	if (data->input.tokens)
		data->input.tokens->type = type;
	data->input.tokens = head;
}

int	check_redirections(t_data *data, t_tokens *ptr, int i)
{
	if (ptr->quote != NO_QUOTE)
		return (0);
	if (ft_strlen(ptr->token) == 1)
	{
		if (ptr->token[0] == '|')
			return (access_to_types(data, i, PIPE), 1);
		else if (ptr->token[0] == '<')
			return (access_to_types(data, i, LEFT), 1);
		else if (ptr->token[0] == '>')
			return (access_to_types(data, i, RIGHT), 1);
	}
	else if (ft_strlen(ptr->token) == 2)
	{
		if (!ft_strncmp(ptr->token, ">>", 2))
			return (access_to_types(data, i, RIGHTT), 1);
		else if (!ft_strncmp(ptr->token, "<<", 2))
			return (access_to_types(data, i, LEFTT), 1);
	}
	return (0);
}

int	check_files(t_data *data, t_tokens *ptr, int i)
{
	if (ptr->prev && \
		(ptr->prev->type == LEFT || \
		ptr->prev->type == RIGHT || \
		ptr->prev->type == RIGHTT))
		return (access_to_types(data, i, FILE), 1);
	return (0);
}

int	check_local_variables(t_data *data, t_tokens *ptr, int i)
{
	if (!ptr->prev && ptr->quote == NO_QUOTE && \
		ptr->token[ft_strlen(ptr->token) - 1] == '=')
		return (access_to_types(data, i, L_VARIABLE), 1);
	if (ptr->prev && ptr->prev->type == L_VARIABLE)
		return (access_to_types(data, i, L_VALUE), 1);
	return (0);
}

int	check_variables(t_data *data, t_tokens *ptr, int i)
{
	if (ptr->quote == NO_QUOTE && \
		ptr->token[ft_strlen(ptr->token) - 1] == '=')
		return (access_to_types(data, i, VARIABLE), 1);
	if (ptr->prev && ptr->prev->type == VARIABLE)
		return (access_to_types(data, i, VALUE), 1);
	return (0);
}

int	check_heredoc(t_data *data, t_tokens *ptr, int i)
{
	if (ptr->prev && ptr->prev->type == LEFTT)
		return (access_to_types(data, i, HERE), 1);
	return (0);
}

int	check_cmds(t_data *data, t_tokens *ptr, int i)
{
	if (ptr->prev)
	{
		if (ptr->quote == NO_QUOTE && \
			ptr->token[0] == '-' && \
			(ptr->prev->type == CMD || ptr->prev->type == OPTION))
			return (access_to_types(data, i, OPTION), 1);
		if (ptr->prev->type == CMD || \
			ptr->prev->type == OPTION || \
			ptr->prev->type == ARG)
			return (access_to_types(data, i, ARG), 1);
	}
	return (access_to_types(data, i, CMD), 1);
}

int	type_checks(t_data *data, t_tokens *ptr, int i)
{
	if (check_redirections(data, ptr, i))
		return (1);
	if (check_files(data, ptr, i))
		return (1);
	if (check_local_variables(data, ptr, i))
		return (1);
	if (check_variables(data, ptr, i))
		return (1);
	if (check_heredoc(data, ptr, i))
		return (1);
	return (check_cmds(data, ptr, i));
}

void	assign_types(t_data	*data)
{
	t_tokens	*ptr;
	int			i;

	ptr = data->input.tokens;
	i = 0;
	while (ptr)
	{
		type_checks(data, ptr, i);
		ptr = ptr->next;
		i++;
	}
}

char	*type_to_char(int type)
{
	if (type == 100)
		return ("CMD");
	if (type == 101)
		return ("OPTION");
	if (type == 102)
		return ("ARGUMENT");
	if (type == 103)
		return ("PIPE");
	if (type == 104)
		return ("<");
	if (type == 105)
		return (">");
	if (type == 106)
		return ("<<");
	if (type == 107)
		return (">>");
	if (type == 108)
		return ("FILE");
	if (type == 109)
		return ("HEREDOC");
	if (type == 110)
		return ("VARIABLE");
	if (type == 111)
		return ("VALUE");
	if (type == 112)
		return ("LOCAL VARIABLE");
	if (type == 113)
		return ("LOCAL VALUE");
	if (type == 114)
		return ("SINGLE QUOTES");
	if (type == 115)
		return ("DOUBLE QUOTES");
	if (type == 116)
		return ("NO QUOTES");
	return ("NO_TYPE");
}

void	print_types(t_data *data)
{
	t_tokens	*head;

	head = data->input.tokens;
	while (head)
	{
		printf("TOKEN: \"%s\"	TYPE: %s\n", head->token, type_to_char(head->type));
		head = head->next;
	}
}

void	remove_equal(t_data *data)
{
	t_tokens	*head;
	char		*tmp;

	if (!data->input.tokens)
		return ;
	head = data->input.tokens;
	while (data->input.tokens)
	{
		if (data->input.tokens->type == VARIABLE || \
			data->input.tokens->type == L_VARIABLE)
		{
			tmp = data->input.tokens->token;
			data->input.tokens->token = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
			free(tmp);
		}
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
}

void	parser(t_data *data)
{
	t_tokens	*ptr;

	parse_environment(data);
	get_env_paths(data);
	parse_tokens(data);
	set_prev_token(data);
	assign_types(data);
	remove_equal(data);
	add_l_variables(data);
	check_dollar(data);
	print_types(data);
	ptr = data->input.tokens;
	if (ptr && !ft_strncmp(ptr->token, "env", ft_strlen(ptr->token)))
		env_builtin(data);
	if (ptr && !ft_strncmp(ptr->token, "export", ft_strlen(ptr->token)))
		export_builtin(data);
	if (ptr && !ft_strncmp(ptr->token, "exit", ft_strlen(ptr->token)))
		exit_builtin(data);
	if (ptr && !ft_strncmp(ptr->token, "loc", ft_strlen(ptr->token)))
		print_locals(data);
}
