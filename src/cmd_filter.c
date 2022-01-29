/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 00:36:24 by bnaji             #+#    #+#             */
/*   Updated: 2022/01/29 13:19:22 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * save_exit_status() function is used to let the parent process wait 
 * 		for the child process, then after the child process die
 * 		the parent process check the exit status for the child process only.
 * 		(the exit status for the other commands that doesn't need child process
 * 		will be checked insided the functions' themselves)
 * TODO: check the exit status for export, unset and cd for all conditions and save their exit status in g_data.exit_status
 */
void	save_exit_status(void)
{
	int		status;
	int		i;

	i = 0;
	if (g_data.wait_n == 1)
	{
		wait(&status);
		if (g_data.c_pid != 0)
		{
			if (!g_data.c_exit_flag)
				g_data.exit_status = WEXITSTATUS(status);
			g_data.c_exit_flag = 0;
		}
	}
	else
	{
		//wait_n--;
		while(i < g_data.wait_n)
		{
			//write(2, "test\n", 5);
			int res = wait(&status);
			if (g_data.c_pid != 0)
			{
				if (!g_data.c_exit_flag && (g_data.c_pid == res))
					g_data.exit_status = WEXITSTATUS(status);
				g_data.c_exit_flag = 0;
			}
			i++;
		}
	}
	g_data.wait_n = 1;
}

/**
 * This function should be called from cmd_checker function
 * It should be called for each command
 * It will not return anything but it will change the value of g_data.cmd_path
 * g_data.cmd_path is a variable that contain the path joined with the command.
 * 		if there the first arg in the cmd is not a path and it's not included
 * 		in $PATH g_data.cmd_path will be NULL
 * * ft_strjoin has been modified to not free the second string (g_data.cmd[i][0])
 **/
void	cmd_filter(int i)
{
	char	**path;
	int		j;
	char	*temp;

	path = NULL;
	if (g_data.cmd_path)
	{
		free(g_data.cmd_path);
		g_data.cmd_path = NULL;
	}
	if (!g_data.cmd[i][0])
		return ;
	if (g_data.cmd[i][0][0] == '/' || g_data.cmd[i][0][0] == '.')
		g_data.cmd_path = ft_strdup(g_data.cmd[i][0]);
	else
	{
		temp = get_expnd_val("PATH");
		path = ft_split(temp, ':');
		free(temp);
		j = 0;
		while (path[j])
		{
			path[j] = ft_strjoin(path[j], "/");
			path[j] = ft_strjoin(path[j], g_data.cmd[i][0]);
			if (!access(path[j], F_OK))
			{
				g_data.cmd_path = ft_strdup(path[j]);
				free_2d(&path);
				return ;
			}
			j++;
		}
		free_2d(&path);
	}
}
