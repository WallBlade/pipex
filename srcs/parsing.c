/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:09:03 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/16 18:27:51 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envp)
{
	int		i;
	char	*path_var;
	char	**env_path;

	i = 0;
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

int	check_access(t_data *data, t_pip *pip, int n)
{
	int	i;

	i = 0;
	while (data->paths[i])
	{
		pip[n].abs_path = ft_strjoin(data->paths[i], pip[n].options[0]);
		if (access(pip[n].abs_path, F_OK | X_OK) == 0)
			break ;
		free(pip[n].abs_path);
		pip[n].abs_path = NULL;
		i++;
	}
	if (!pip[n].abs_path)
		exit(127);
	return (0);
}

t_pip	*init_pip_struct(char **argv, t_data *data)
{
	int		i;
	t_pip	*pip;

	pip = malloc(data->cmd_count * sizeof(t_pip));
	if (!pip)
		return (NULL);
	i = 0;
	while (i < data->cmd_count)
	{
		get_cmds(argv[i + 2], pip, i);
		i++;
	}
	return (pip);
}

t_data	*init_data_struct(int ac, char **av, char **envp)
{
	t_data	*data;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->cmd_count = ac - 3;
	data->pid = malloc(sizeof(int) * data->cmd_count);
	if (!data->pid)
		return (NULL);
	data->paths = get_paths(envp);
	if (!data->paths)
		return (NULL);
	data->infile = ft_strdup(av[1]);
	data->outfile = ft_strdup(av[ac - 1]);
	return (data);
}
