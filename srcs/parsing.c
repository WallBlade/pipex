/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:09:03 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/04 19:44:43 by zel-kass         ###   ########.fr       */
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

void	get_cmds(char **argv, t_cmds **cmds, t_data *data)
{
	int	i;

	i = 1;
	while (argv[i] && i++ < data->cmd_count)
		ft_lstadd_back(cmds, ft_lstnew(argv[i], ft_split(argv[i], ' ')));
}

void	check_access(t_data *data, t_cmds *cmds)
{
	int	i;
	
	while (cmds)
	{
		printf("test\n");
		cmds = cmds->next;
		if (access(cmds->cmd, F_OK | X_OK) == -1)
		{
			i = 0;
			while (data->paths[i])
			{
				cmds->abs_path = ft_strjoin(data->paths[i], cmds->options[0]);
				if (access(cmds->abs_path, F_OK | X_OK) == 0)
					return ;
				free(cmds->abs_path);
			}
		}
		else if (access(cmds->cmd, F_OK | X_OK) == 0)
			cmds->abs_path = cmds->cmd;
	}
}

// char	*check_access(t_data *data)
// {
// 	int		i;
// 	int		j;
// 	char	*good_path;
// 	char	**options;
	
// 	i = 0;
// 	while (data->cmd[i] && i < data->cmd_count)
// 	{
// 		options = ft_split(data->cmd[i], ' ');
// 		if (!options)
// 			return (NULL);
// 		if (access(data->cmd[i], F_OK | X_OK) == -1)
// 		{
// 			j = 0;
// 			while (data->paths[j])
// 			{
// 				good_path = ft_strjoin(data->paths[j], options[0]);
// 				if (access(good_path, F_OK | X_OK) == 0)
// 					return (good_path);
// 				free(good_path);
// 				j++;
// 			}
// 		}
// 		i++;
// 	}
// 	return (good_path);
// }