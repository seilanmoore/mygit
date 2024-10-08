/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:21:13 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/03 15:24:41 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_prev_token(t_data *data)
{
	t_token	*head;
	t_token	*prev;

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
	var->aux = ft_substr(var->aux1, 0, var->i);
	if (var->aux1[var->i])
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
	var->aux = ft_substr(var->aux1, 0, var->i);
	if (var->aux1[var->i])
		var->i++;
	add_back_token(&(data->input.tokens), new_token(var->aux, 0, D_QUOTE));
}

static void	characters(t_data *data, t_var *var)
{
	while (var->aux1[var->i] && \
		var->aux1[var->i] != ' ' && \
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

void	parse_tokens(t_data *data)
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
		if (*var.aux1 && *var.aux1 == '\'' && *(var.aux1 + 1))
			single_quote(data, &var);
		else if (*var.aux1 && *var.aux1 == '\"' && *(var.aux1 + 1))
			double_quote(data, &var);
		else if (*var.aux1)
			characters(data, &var);
		var.aux1 = var.aux1 + var.i;
	}
	set_prev_token(data);
	assign_types(data);
	remove_equal(data);
}
