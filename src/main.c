/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:16 by bnaji             #+#    #+#             */
/*   Updated: 2021/12/29 04:10:42 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * TODO: don't forget to clear the history before you exit the program
 */
int	main(int ac, char **av, char **ev)
{
	struct sigaction	sig_sig;

	(void) ac;
	(void) av;
	g_data.environ = ev;
	g_data.exit_status = 0;
	g_data.c_exit_flag = 0;
	sig_sig.sa_flags = 0;
	sig_sig.sa_mask = 0;
	sig_sig.sa_sigaction = &sig_handler;
	sigaction(SIGINT, &sig_sig, NULL);
	sigaction(SIGQUIT, &sig_sig, NULL);
	initialize();
	printf(CLEAR_SCREEN);
	while (1)
	{
		g_data.cmdline = readline(MAC_PROMPT);
		// g_data.cmdline = "echo hi > 1 > 2 > 3";
		if (!g_data.cmdline)
			exit_shell(0);
		if (g_data.cmdline && *g_data.cmdline)
			add_history(g_data.cmdline);
		ultimate_3d_split();
		check_cmd();
		free_all();
	}
}
