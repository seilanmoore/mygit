/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/05 13:53:34 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* 	ptr = data->input.tokens;
	if (ptr && !ft_strncmp(ptr->token, "env", ft_strlen(ptr->token)))
		data->exit_code = env_builtin(data);
	else if (ptr && !ft_strncmp(ptr->token, "pwd", ft_strlen(ptr->token)))
		data->exit_code = pwd_builtin(data);
	else if (ptr && !ft_strncmp(ptr->token, "echo", ft_strlen(ptr->token)))
		data->exit_code = echo_builtin(data, ptr);
	else if (ptr && !ft_strncmp(ptr->token, "cd", ft_strlen(ptr->token)))
		data->exit_code = cd_builtin(data, ptr);
	else if (ptr && !ft_strncmp(ptr->token, "export", ft_strlen(ptr->token)))
		data->exit_code = export_builtin(data);
	else if (ptr && !ft_strncmp(ptr->token, "unset", ft_strlen(ptr->token)))
		data->exit_code = unset_builtin(data);
	else if (ptr && !ft_strncmp(ptr->token, "loc", ft_strlen(ptr->token)))
		print_locals(data);
	else if (ptr && !ft_strncmp(ptr->token, "exit", ft_strlen(ptr->token)))
		data->exit_code = exit_builtin(data); */

void	parser(t_data *data)
{
	parse_environment(data);
	parse_tokens(data);
	add_l_variables(data);
	expand(data);
	assign_opt_arg(data);
	parse_cmd_opt(data);
	//print_cmd_array(data);
	//print_types(data);
}
