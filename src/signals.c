/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:36:29 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 19:21:20 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_boolhere(int i)
{
	static int	boole = 0;

	if (i != 0)
		boole = i;
	return (&boole);
}

void	ft_hered_sig_handler(int sig)
{
	struct termios	term;

	if (sig == SIGINT)
	{
		ft_boolhere(1);
		printf("\n");
		close(STDIN_FILENO);
		g_exitcode = 1;
	}
	tcgetattr(1, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSANOW, &term);
}

void	ft_main_sig_handler(int sig)
{
	struct termios	term;

	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_exitcode = 1;
	}
	tcgetattr(1, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSANOW, &term);
}

void	ft_exec_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exitcode = 130;
	}
	if (sig == SIGQUIT)
	{
		ft_printf_fd(2, "^\\Quit : 3\n");
		g_exitcode = 131;
	}
}
