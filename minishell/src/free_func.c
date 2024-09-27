/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:02:07 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/27 14:15:58 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	free_local(t_data *data)
{
	t_l_variable	*tmp;

	while (data->local)
	{
		free(data->local->variable);
		data->local->variable = NULL;
		free(data->local->value);
		data->local->value = NULL;
		tmp = data->local;
		data->local = data->local->next;
		free(tmp);
	}
}

void	free_environment(t_data *data)
{
	t_environment	*tmp;

	while (data->env)
	{
		free(data->env->variable);
		data->env->variable = NULL;
		free(data->env->value);
		data->env->value = NULL;
		tmp = data->env;
		data->env = data->env->next;
		free(tmp);
	}
	free_array(data->envp_cpy);
	data->envp_cpy = NULL;
}

void	free_tokens(t_data *data)
{
	t_tokens	*tmp;

	while (data->input.tokens)
	{
		free(data->input.tokens->token);
		data->input.tokens->token = NULL;
		tmp = data->input.tokens;
		data->input.tokens = data->input.tokens->next;
		free(tmp);
	}
}

void	free_data(t_data *data)
{
	int				i;
	int				j;
	t_environment	*env_head;
	t_l_variable	*local_head;
	char			**env_ptr;
	char			*aux;

	aux = data->prev_exit_code;
	env_head = data->env;
	env_ptr = data->envp_cpy;
	local_head = data->local;
	free(data->prompt);
	free(data->input.raw_line);
	free(data->history);
	free(data->process);
	free_tokens(data);
	i = -1;
	if (data->input.command)
	{
		while (data->input.command[++i].cmd)
			free(data->input.command[i].cmd);
		free(data->input.command);
	}
	free_array(data->paths);
	i = data->status;
	j = data->exit_code;
	init_data(data, data->argc, data->argv, data->envp);
	data->env = env_head;
	data->envp_cpy = env_ptr;
	data->local = local_head;
	data->status = i;
	data->exit_code = j;
	free(data->prev_exit_code);
	data->prev_exit_code = aux;
}