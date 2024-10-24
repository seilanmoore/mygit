/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:14:41 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/23 20:26:11 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_option_arg(t_data *data, t_token *ptr, int i)
{
	if (ptr->quote == NO_QUOTE && \
		ptr->token[0] == '-' && \
		data->in_cmd && data->in_arg == 0)
		return (access_to_types(data, i, OPTION), 1);
	if (data->in_cmd)
	{
		data->in_arg = 1;
		return (access_to_types(data, i, ARG), 1);
	}
	return (0);
}

int	check_cmds(t_data *data, t_token *ptr, int i)
{
	if (check_option_arg(data, ptr, i))
		return (1);
	data->n_cmd++;
	data->in_cmd = 1;
	data->in_arg = 0;
	access_to_types(data, i, CMD);
	return (1);
}
