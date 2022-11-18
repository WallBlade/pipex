/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:09:03 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/18 17:52:47 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5)
	{
		ft_putstr_fd("Error: wrong arguments number\n", 2);
		exit(EXIT_FAILURE);
	}
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 0)
		{
			ft_putstr_fd("Error: enter valid arguments\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

char	**get_paths(char **envp)
{
	int		i;
	char	*path_var;
	char	**env_path;

	i = 0;
	env_path = NULL;
	while (envp[i])
	{
		path_var = ft_strnstr(envp[i], "PATH=", 6);
		if (path_var)
		{
			env_path = ft_split(path_var, ':');
			break ;
		}
		i++;
	}
	i = -1;
	while (env_path[++i])
		env_path[i] = ft_strjoin(env_path[i], "/");
	return (env_path);
}

void	get_cmds(char *av, t_pip *pip, int i)
{
	char		**cmd;

	cmd = ft_split(av, ' ');
	if (!cmd)
		return ;
	pip[i].cmd = cmd[0];
	pip[i].options = cmd;
	pip[i].abs_path = NULL;
}

void	search_abs_path(t_data *data, t_pip *pip, int n)
{
	int		i;
	char	*abs;

	i = 0;
	while (data->paths && data->paths[i])
	{
		abs = ft_strjoin(ft_strdup(data->paths[i]), pip[n].options[0]);
		if (access(abs, F_OK | X_OK) == 0)
			break ;
		free(abs);
		abs = NULL;
		i++;
	}
	pip[n].abs_path = abs;
}

int	check_access(t_data *data, t_pip *pip, int n)
{
	search_abs_path(data, pip, n);
	if (!data->paths || !pip[n].abs_path)
	{
		if (access(pip[n].options[0], X_OK) == 0)
		{
			pip[n].abs_path = pip[n].options[0];
			data->is_abs = 1;
		}
	}
	if (access(pip[n].options[0], F_OK) == 0
		&& access(pip[n].options[0], X_OK) == -1)
		exit(126);
	if (!pip[n].abs_path)
	{
		free_struct(data, pip);
		exit(127);
	}
	return (0);
}