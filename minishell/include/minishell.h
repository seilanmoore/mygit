/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:44 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/24 20:44:58 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>

// ANSI color codes
# define RED	"\x1b[31m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[33m"
# define BLUE	"\x1b[34m"
# define WHITE	"\x1b[0m"

# define HISTORY_FILE ".history"

# define NL "\n"
# define MS "minishell: "
# define EMPTY_PATH "PATH variable is empty"
# define NO_PATH "PATH variable not found"
# define NOT_FOUND "command not found"
# define ERROR "error "
# define PATH_EXIST "No such a file or directory"
# define PERMIT "Permission denied"
# define IS_DIR "Is a directory"
# define NOT_DIR "Not a directory"

# define EXPORT "export: "
# define EXPORT_ID "not a valid identifier"

# define CD "cd: "
# define CD_OPT "no options allowed"
# define CD_ARG "too many arguments"
# define CD_HOME "HOME not set"

# define ECHO "echo: "
# define ECHO_OPT "not valid option"
# define ECHO_OPTS "too many options"

# define CMD 100		// cmd
# define OPTION 101		// cmd option
# define ARG 102		// argument
# define PIPE 103 		// |
# define LEFT 104 		// <
# define RIGHT 105 		// >
# define LEFTT 106 		// <<
# define RIGHTT 107 	// >>
# define FILE 108		// file
# define HERE 109 		// heredoc
# define LOCAL 110 		// variable=value
# define LOCAL_VAL 111	// " value "
# define NO_QUOTE 120
# define S_QUOTE 121 	// ''
# define D_QUOTE 122 	// ""

extern int	g_signal;

void	signal_handler(int sig);

typedef struct s_command
{
	char				*cmd;
	char				**args;
	int					builtin;
	struct s_command	*next;
}	t_cmd;

typedef struct s_tokens
{
	char				*token;
	int					type;
	int					quote;
	int					end_space;
	struct s_tokens		*opt;
	struct s_tokens		*arg;
	struct s_tokens		*prev;
	struct s_tokens		*next;
}	t_token;

typedef struct s_input
{
	char		*raw_line;
	//char		*file_name;
	t_token		*tokens;
	t_cmd		*command;
}	t_input;

typedef struct s_var
{
	char	*aux;
	char	*aux1;
	int		i;

}	t_var;

typedef struct s_environment
{
	char					*variable;
	char					*value;
	struct s_environment	*next;
}	t_env;

typedef struct s_pipe
{
	int	fd[2];
}	t_pipe;

typedef struct s_data
{
	int		fd[2];
	char	**envp;
	char	**paths;
	char	*user;
	char	*cwd;
	char	*prompt;
	char	*history;
	int		n_cmd;
	int		n_pipe;
	int		n_files;
	int		in_cmd;
	int		in_arg;
	int		in_local;
	int		status;
	int		exit_code;
	char	*prev_exit_code;
	char	*process;
	pid_t	pid;
	t_env	*locals;
	t_env	*env;
	t_pipe	*pipes;
	t_input	input;
}	t_data;

// init
void	init_data(t_data *data, char **envp);

// free_func
void	free_tokens(t_data *data);
void	free_local(t_data *data);
void	free_env_lst(t_data *data);
void	free_environment(t_data *data);
void	free_array(char ***array);
void	free_data(t_data *data);

//environment
void	envp_to_lst(t_data *data);
void	envp_to_array(t_data *data);

//env_utils
t_env	*get_env(t_env *l_variables, char *l_variable);
t_env	*get_env_var(t_env *env, char *variable);
t_env	*new_variable(char *variable, char *value);
t_env	*last_variable(t_env *lst);
void	del_env(t_env *env, char *variable);

// locals
void	print_locals(t_data *data);
void	locals(t_data *data);

//parser
void	parser(t_data *data);
void	access_to_types(t_data *data, int target, int type);
void	type_checks(t_data *data, t_token *ptr, int i);

//command
void	parse_cmd_opt(t_data *data);

//command_path
void	assign_paths(t_data *data);

//command_utils
void	add_back_cmd(t_cmd **lst, t_cmd *node);
t_cmd	*new_cmd(void *command, char **arguments, int builtin);
t_cmd	*last_cmd(t_cmd *lst);

//syntax
void	syntax_msg(char *wildcard);
int		is_redirection(int type);
int		is_word(int type);
int		syntax_error(t_data *data);

//syntax_circles
int		circle_1(t_token *token);
int		circle_2(t_token *token, t_token *prev);
int		circle_3(t_token *token, t_token *prev);
int		circle_4(t_token *token, t_token *prev);

//executer
int		execute(t_data *data);

// tokenizer
void	tokenizer(t_data *data);
//tokenizer_utils
void	set_prev_token(t_data *data);
t_token	*new_token(void *token, int type, int quote, int end_space);
t_token	*last_token(t_token *lst);

// parser_checks2
int		check_cmds(t_data *data, t_token *ptr, int i);

// types
void	assign_types(t_data	*data);
void	remove_equal(t_data *data);
void	assign_opt_arg(t_data *data);

// expand_utils

char	*get_dollar_value(t_data *data, char *variable);
char	*extract_id(char *token);

// expand
void	expand(t_data *data);

//builtin
int		export_builtin(t_data *data, t_token *args);
char	*variable_append(t_token **args);
char	*value_append(t_token **args);

int		exit_builtin(t_data *data);
int		unset_builtin(t_data *data, t_cmd *cmd);
int		cd_builtin(t_data *data, t_token *token);
int		echo_builtin(t_data *data, t_token *token);
int		pwd_builtin(t_data *data);
int		env_builtin(t_data *data);

char	*cwd_compress(t_data *data);

int		lst_size(t_token *lst);

void	add_back_token(t_token **lst, t_token *node);

void	add_back_variable(t_env **lst, t_env *node);
int		env_size(t_env *lst);

void	upd_env(t_data *data);
void	print_env(t_data *data);

// utils
int		ft_strcmp(const char *str1, const char *str2);
void	print_types(t_data *data);
void	print_cmd_array(t_data *data);
char	*str_replace(char *haystack, char *needle, char *replace);
void	print_msg(t_data *data, char *msg, int status);
char	*rev_split(char **array);
void	print_array(char **array);
int		valid_char(char c);
int		valid_ident(char *str);
char	*get_envp_var(char **envp, char *var);
int		is_redir(int c);
int		is_space(int c);
int		is_cmd(int c);
void	print_locals(t_data *data);
char	**split_token(char *token);
void	check_new_var(t_env **lst, t_env *new_var, char *var, char *value);


// path_checks

int		dir_f_check(char *path);
int		dir_r_check(char *path);
int		dir_w_check(char *path);
int		path_f_check(char *path);
int		path_r_check(char *path);
int		path_w_check(char *path);

// handle_error
int		handle_errno(char *wildcard);

#endif
