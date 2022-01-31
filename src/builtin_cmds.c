/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:15:01 by bnaji             #+#    #+#             */
/*   Updated: 2022/02/01 02:46:17 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * TODO: add errors and make it for any n of commands
 */
void	ft_cd(void)
{
	int		i;
	char	*tmp;

	if (!getcwd(g_data.pwd_dir_path, sizeof(g_data.pwd_dir_path)))
		ft_putendl_fd("failure in updating the environment variable: OLDPWD", 2);
	i = chdir(g_data.cmd[g_data.y][1]);
	if (!i)
	{
		tmp = ft_strjoin_moa("OLDPWD=", g_data.pwd_dir_path);
		ft_export(ft_strdup(tmp));
		free(tmp);
		if (!getcwd(g_data.pwd_dir_path, sizeof(g_data.pwd_dir_path)))
			ft_putendl_fd("failure in updating the environment variable: PWD", 2);
		tmp = ft_strjoin_moa("PWD=", g_data.pwd_dir_path);
		ft_export(ft_strdup(tmp));
		printf("cd: %s\n", g_data.pwd_dir_path);
		free(tmp);
	}
	else if (i == -1)
	{
		ft_putstr_fd("BnM bash: cd: ", 2);
		ft_putstr_fd(g_data.cmd[g_data.y][1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		g_data.exit_status = 1;
		return ;
	}
	g_data.exit_status = 0;
}

void	ft_echo(void)
{
	int	n_flag;
	int	j;
	int	i;

	n_flag = 0;
	if (!g_data.cmd[g_data.y][1])
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	j = 1;
	while (g_data.cmd[g_data.y][j][0] == '-')
	{
		i = 1;
		while (g_data.cmd[g_data.y][j][i] == 'n')
			i++;
		if (i > 1 && !g_data.cmd[g_data.y][j][i])
		{
			n_flag = 1;
			j++;
		}
		else
			break ;
	}
	while (g_data.cmd[g_data.y][j])
	{
		ft_putstr_fd(g_data.cmd[g_data.y][j], 1);
		if (g_data.cmd[g_data.y][j + 1])
			ft_putchar_fd(' ', 1);
		j++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	g_data.exit_status = 0;
}

void	ft_pwd(void)
{
	char	*ret;

	ret = getcwd(g_data.pwd_dir_path, sizeof(g_data.pwd_dir_path));
	if (ret)
		printf("%s\n", g_data.pwd_dir_path);
	else
	{
		ft_putstr_fd("pwd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		g_data.exit_status = 1;
		return ;
	}
	g_data.exit_status = 0;
}

/**
 * TODO: fix it to search for the environmental variable and replace it
 */
void	ft_env(void)
{
	int	x;
	int	k;
	char *v;

	k = 1;
	while (g_data.cmd[g_data.y][k])
	{
		v = ft_strdup(g_data.cmd[g_data.y][k]);
		if ((size_t)ft_chrindex(v, '=') >= ft_strlen(v))
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(g_data.cmd[g_data.y][k], 2);
			ft_putstr_fd(": No such file or directory", 2);
			ft_putchar_fd('\n', 2);
			g_data.exit_status = 1;
			free(v);
			return ;
		}

		ft_export(v);
		k++;
	}
	x = 0;
	printf("test3\n");
	while (g_data.environ[x])
	{
		printf("%s\n", g_data.environ[x]);
		x++;
	}
	g_data.exit_status = 0;
}
