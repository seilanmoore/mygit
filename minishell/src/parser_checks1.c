/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:13:34 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/23 20:38:51 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_redirections(t_data *data, t_token *ptr, int i)
{
	if (ptr->quote != NO_QUOTE)
		return (0);
	if (ft_strlen(ptr->token) == 1)
	{
		if (ptr->token[0] == '|')
		{
			data->n_pipe++;
			data->in_cmd = 0;
			return (access_to_types(data, i, PIPE), 1);
		}
		else if (ptr->token[0] == '<')
			return (access_to_types(data, i, LEFT), 1);
		else if (ptr->token[0] == '>')
			return (access_to_types(data, i, RIGHT), 1);
	}
	else if (ft_strlen(ptr->token) == 2)
	{
		if (!ft_strcmp(ptr->token, ">>"))
			return (access_to_types(data, i, RIGHTT), 1);
		else if (!ft_strcmp(ptr->token, "<<"))
			return (access_to_types(data, i, LEFTT), 1);
	}
	return (0);
}

static int	check_files(t_data *data, t_token *ptr, int i)
{
	if (ptr->prev)
	{
		if (ptr->prev->type == LEFTT)
			return (access_to_types(data, i, HERE), 1);
		if (ptr->prev->type == LEFT || \
		ptr->prev->type == RIGHT || \
		ptr->prev->type == RIGHTT)
			return (access_to_types(data, i, FILE), 1);
	}
	return (0);
}

static int	check_locals(t_data *data, t_token *ptr, int i)
{
	t_token	*prev;
	int		prev_len;

	if (data->in_cmd)
		return (0);
	prev = ptr->prev;
	if (prev)
		prev_len = ft_strlen(prev->token);
	if (prev && prev->type == LOCAL && \
	prev->token[prev_len - 1] == '=' && prev->end_space == 0)
		return (access_to_types(data, i, LOCAL_VAL), 1);
	else if (ft_strchr(ptr->token, '='))
		return (access_to_types(data, i, LOCAL), 1);
	return (0);
}

void	type_checks(t_data *data, t_token *ptr, int i)
{
	if (check_redirections(data, ptr, i))
		return ;
	if (check_files(data, ptr, i))
		return ;
	if (check_locals(data, ptr, i))
		return ;
	check_cmds(data, ptr, i);
}
