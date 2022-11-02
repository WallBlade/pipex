/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:09:03 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/02 22:26:20 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_paths(char **envp, t_data *data)
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
			break;
		}
		i++;
	}
	data->paths = malloc(sizeof(char *) * (i + 1));
	if (!data->paths)
		return (-1);
	i = -1;
	while (env_path[++i])
		data->paths[i] = ft_strjoin(env_path[i], "/");
	return (ft_freetab(env_path, i), 0);
}

int	get_cmds(char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	data->cmd = malloc(sizeof(char *) * (data->cmd_count + 1));
	if (!data->cmd)
		return (-1);
	while (argv[j] && i < data->cmd_count)
	{
		data->cmd[i] = argv[j];
		i++;
		j++;
	}
	data->cmd[i] = 0;
	return (0);
}

char	*check_access(t_data *data)
{
	int		i;
	int		j;
	char	*good_path;
	char	**options;
	
	i = 0;
	while (data->cmd[i] && i < data->cmd_count)
	{
		options = ft_split(data->cmd[i], ' ');
		if (!options)
			return (NULL);
		if (access(data->cmd[i], F_OK | X_OK) == -1)
		{
			j = 0;
			while (data->paths[j])
			{
				good_path = ft_strjoin(data->paths[j], options[0]);
				if (access(good_path, F_OK | X_OK) == 0)
					return (good_path);
				free(good_path);
				j++;
			}
		}
		i++;
	}
	return (good_path);
}