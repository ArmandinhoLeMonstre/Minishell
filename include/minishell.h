/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:24:24 by armitite          #+#    #+#             */
/*   Updated: 2024/11/26 21:07:33 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <fcntl.h>
# include <unistd.h>
//# include "../libft/include/libft.h"
# include "../Libft/libft.h"
#include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
#include <stdbool.h>
#include <stdarg.h>
#include <signal.h>
#include <termios.h>
#include <string.h>

int g_exitcode;

//#define ECHOCTL  0001000  /* Echo control characters as ^(X) notation. */


typedef struct s_env
{
	struct s_env	*next;
	char			*name;
	char			*value;
	bool			equal;
}	t_env;

typedef struct s_built
{
	t_env				*env_oldpwd;
	t_env				*env_pwd;
	t_env				*env_home;
	const char			*path;
	char				*tmp;
	DIR					*dir;
}						t_built;


typedef struct s_clean_string_data
{
	char *string2;
	int	i;
	int	h;
	int	verif;
}	t_clean_string_data;

typedef struct s_get_tab_data
{
	int	i;
	int	index;
}	t_get_tab_data;

typedef struct s_change_pipe_data
{
	int	i;
	int	index;
	char *rl2;
}	t_change_pipe_data;

typedef struct s_change_space_data
{
	int	i;
	int	index;
	char *rl2;
}	t_change_space_data;


typedef struct s_expander_data
{
	int	i;
	int	x;
	int	j;
	int	total;
	int	verif;
	char *user;
}	t_expander_data;

typedef struct s_strdup2_data
{
	int		total;
	int		index;
	int	i;
	int	x;
}	t_strdup2_data;

typedef struct s_pipe_chain
{
	char				**envp;
	char				*pipe_string;
	char				**cmd;
	char				*cmd_path;
	char				*last_infile;
	char				*last_outfile;
	char				*last_append;
	char				*heredoc_chars;
	char				*cmd_string;
	int					checker;
	int					infile;
	int					outfile;
	int					append;
	int					pid;
	int					fd[2];
	int					pipe_number;
	int					gv_fd[2];
	//struct s_outfiles	*outfiles;
	struct s_pipe_chain	*next;
	struct s_pipe_chain	*prev;
}	t_pipe_chain;

//Signals
void	ft_exec_sig_handler(int sig);
void	ft_main_sig_handler(int sig);

// Builtins part :
char	**build_env(t_env **env);
void	unset(char **token, t_env **env);
int	ft_builtins(char **token, t_env **env, int fd[2], int keycode);
void	exit_built(char **token);
void	pwd(t_env **env);

//export 
t_env	*make_envlist(char **env);
int	listlen(t_env *list);
void	free_list(t_env *list);
int	ft_printf_fd(int fd, const char *format, ...);
void	sort_env(t_env *top);
void	append_list(t_env **env_list, char *str);
void	export(char **token, t_env **env);
void	free_node(t_env *node);
int	check_identifier(char *str);

//cd
void	cd(char **token, t_env **env);
int	ft_isbuiltin(char *str);
t_env	*ft_findnode(t_env *env, char *name);
void	cd_home(t_built *var);
void	cd_oldpwd(t_built *var);
void	cd_dir(t_built *var);
int	diff_dir(const char *path);

// Parsing part :

//quote_checking
int		quote_checker(char *rl);

//Pipe in "" and ''
char	*reput_pipe(t_pipe_chain *checker_node, int *tab);
int		*get_tab(const char *rl, int *tab);
int		pipe_numbers(const char *rl);
char	*change_pipe(char *rl, int *tab);
char	*ft_strdup2(t_pipe_chain *checker_node, int *tab, int j);

//Expander
void	expander(t_pipe_chain *checker_node, t_env **env);
char	*get_user(t_pipe_chain *checker_node);
char	*clean_string(t_pipe_chain *checker_node, t_env **env, int total, char *user);
int     check_dollars(t_pipe_chain *checker_node, int i, t_env **env);

//Clean_space
int	space_numbers(const char *rl);
char *change_space(char *rl);
int *get_tab_space(const char *rl, int *tab);
char	**ft_strdup3(char **cmd);

//pipe_parsing fonctions
int	pipe_noding(t_pipe_chain **stack, t_env **env, char *rl, char **envp);
int		pipe_split(t_pipe_chain *stack, char *rl, char **envp, int *tab);
void	append_node(t_pipe_chain **stack, char *rl, char **envp);
int		ft_ispipe(char *str);
void	pipe_parsing(t_pipe_chain **stack, int *tab, t_env **env);
int	token_checker(char *rl);
int		stack_len(t_pipe_chain *stack);
char	*get_paths(t_pipe_chain *checker_node);
int		cmd_check_commas(t_pipe_chain *checker_node, int *i, int h, int	keycode);

//file_parsing fonctions
void	stock_file(t_pipe_chain *checker_node, int h, int j, int redirect);
int		ft_is_bash_char(int c);

//Heredoc
void	display_line(t_pipe_chain *checker_node);
int	ft_strcmp(const char *s1, const char *s2);

//cmd_parsing fonctions
int		cmd_check(t_pipe_chain *checker_node, int *i, int h);

//execution
int	shell_exec2(t_pipe_chain **s, int j);
int		get_outfile_number(t_pipe_chain *exec_nodes);
void	pid_exec_output(t_pipe_chain *exec_nodes, int fd[2]);
void	pid_exec_outfile(t_pipe_chain *exec_nodes, int fd[2]);
void	pid_exec(t_pipe_chain *exec_nodes, int fd[2]);

//free
void	ft_free2(char **strs);
void	free_nodes(t_pipe_chain **a);

//panic
int		panic_parsing(t_pipe_chain *checker_node, int error_code);
void	files_error(t_pipe_chain *checker_node, int c);


//extern char *readline PARAMS((const char *));
#endif