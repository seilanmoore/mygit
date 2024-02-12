/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:08:18 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/07 14:27:00 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_stack
{
	size_t			index;
	int				number;
	int				indexed;
	struct s_stack	*next;
}					t_stack;

//	divide
size_t	get_median(t_stack *stack);
int		pushable(t_stack **stack_b, t_stack **stack_a, size_t range);
void	divide(t_stack **stack_a, t_stack **stack_b);
size_t	get_pos_target(t_stack *stack_a, size_t index);
size_t	cost_a(t_stack *stack_a, size_t index, size_t steps, int move, size_t *index_a);
size_t	total_cost(t_stack *stack_a, t_stack *stack_b, size_t index, size_t *index_a);
size_t	cost(t_stack **stack_a, t_stack **stack_b, size_t *index_a);
void	move_both(t_stack **stack_a, t_stack **stack_b, size_t a_p, size_t b_p);
void	move_a(t_stack **stack_a, t_stack **stack_b, size_t a_p);
void	moves(t_stack **stack_a, t_stack **stack_b);

// FEW_CASE

//	few_case
void	sort_three(t_stack **stack);
void	push_min_b_few(t_stack **stack_a, t_stack **stack_b);
void	sort_five(t_stack **stack_a, t_stack **stack_b);
void	sort_few(t_stack **stack_a, t_stack **stack_b);

// CHECKS

//	checks
long	ft_atol(const char *str);
int		sorted(t_stack *stack_a);
int		ft_error(int argc, char **argv);

// INITIALATION

//	init
void	init_stack_a(t_stack **stack_a, int argc, char **argv);
void	index_stack(t_stack **stack_a);

// POSITIONS

//	get_positions
size_t	get_node_pos(t_stack *stack, int number);
size_t	get_index(t_stack *stack);
size_t	get_min(t_stack *stack);
size_t	get_max(t_stack *stack);
size_t	get_min_pos(t_stack *stack);
size_t	get_max_pos(t_stack *stack);

// LIST FUNCTIONS

//	lst_utils_1
t_stack	*new_node(int number);
t_stack	*lst_last(t_stack *lst);
void	lst_add_back(t_stack **lst, t_stack *new);
void	lst_clear(t_stack **lst);
size_t	lst_size(t_stack *lst);

//	lst_utils_2
t_stack	*get_node(t_stack *stack, size_t position);
size_t	get_node_position(t_stack *stack, size_t index);

// RULES MOVES

//	swap_mv
void	swap_a(t_stack **stack_a, int both_stacks);
void	swap_b(t_stack **stack_b, int both_stacks);
void	swap_a_b(t_stack **stack_a, t_stack **stack_b);

//	push_mv
void	push_a(t_stack **stack_a, t_stack **stack_b);
void	push_b(t_stack **stack_b, t_stack **stack_a);

//	rotate_mv
void	rotate_a(t_stack **stack_a, int both_stacks);
void	rotate_b(t_stack **stack_b, int both_stacks);
void	rotate_a_b(t_stack **stack_a, t_stack **stack_b);

//	rev_rotate_mv
void	reverse_rotate_a(t_stack **stack_a, int both_stacks);
void	reverse_rotate_b(t_stack **stack_b, int both_stacks);
void	reverse_rotate_a_b(t_stack **stack_a, t_stack **stack_b);