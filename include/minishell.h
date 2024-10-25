/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:24:24 by armitite          #+#    #+#             */
/*   Updated: 2024/10/23 19:32:54 by armitite         ###   ########.fr       */
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
# include "../Libft/libft.h"

typedef struct s_outfiles
{
	int					checker;
	char				*last_append;
	char				*last_outfile;
	int					append;
	int					outfile;
}	t_outfiles;

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
	int					checker;
	int					infile;
	int					outfile;
	int					append;
	int					pid;
	int					fd[2];
	int					pipe_number;
	//struct s_outfiles	*outfiles;
	struct s_pipe_chain	*next;
	struct s_pipe_chain	*prev;
}	t_pipe_chain;

// Parsing part :

//quote_checking
int		quote_checker(char *rl);

//pipe_parsing fonctions
int		pipe_noding(char *rl, char **envp);
int		ft_ispipe(char *str);
void	pipe_parsing(t_pipe_chain **stack);
int		token_checker(t_pipe_chain **stack);
int		stack_len(t_pipe_chain *stack);

//file_parsing fonctions
void	stock_file(t_pipe_chain *checker_node, int h, int j, int redirect);
int		ft_is_bash_char(int c);

//Heredoc
void	display_line(t_pipe_chain *checker_node);

//cmd_parsing fonctions
int		cmd_check(t_pipe_chain *checker_node, int *i, int h);

//execution
int		shell_exec2(t_pipe_chain *exec_nodes);
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

#endif