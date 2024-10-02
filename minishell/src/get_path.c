/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:15:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/02 12:42:34 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* static void	cmd_not_found(t_data *data)
{
	int	fail;
	int	i;

	i = -1;
	fail = 0;
	if (!data->input.command)
		return ;
	while (data->input.command[++i].cmd)
	{
		if (data->input.command[i].cmd == NULL)
		{
			printf(MS "%s: " NOT_FOUND, data->input.command[i].cmd);
			fail = 1;
		}
	}
	if (fail)
		data->exit_code = 127;
} */

static void	append_slash(t_data *data)
{
	char	*tmp;
	int		i;

	i = -1;
	while (data->paths[++i])
	{
		tmp = data->paths[i];
		data->paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
	}
}

/* static void	assign_paths(t_data *data)
{
	char	*cmd;
	int		i;
	int		j;

	i = -1;
	if (!data->input.command)
		return ;
	while (data->input.command[++i])
	{
		j = -1;
		cmd = data->cmd[i].opt[0];
		while (data->paths[++j])
		{
			if (data->cmd[i].path == NULL)
			{
				data->cmd[i].path = ft_strjoin(data->paths[j], cmd);
				if (access(data->cmd[i].path, F_OK | X_OK) == ERROR)
				{
					free(data->cmd[i].path);
					data->cmd[i].path = NULL;
				}
			}
		}
	}
} */

void	get_env_paths(t_data *data)
{
	char	*line;
	int		i;

	line = NULL;
	i = -1;
	while (data->envp_cpy[++i] && ft_strncmp("PATH=", data->envp_cpy[i], 5))
		;
	if (!ft_strncmp("PATH=", data->envp_cpy[i], 5))
	{
		line = &(data->envp_cpy[i][5]);
		if (line[0] == '\0')
			printf(MS EMPTY_PATH NL);
		data->paths = ft_split(line, ':');
	}
	else
		printf(MS NO_PATH NL);
	append_slash(data);
}
