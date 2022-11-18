/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:05:56 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/18 17:52:07 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

t_data	*init_data_struct(int ac, char **av, char **env_path)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->cmd_count = ac - 3;
	data->pid = malloc(sizeof(int) * data->cmd_count);
	if (!data->pid)
		return (NULL);
	data->paths = env_path;
	data->infile = ft_strdup(av[1]);
	data->outfile = ft_strdup(av[ac - 1]);
	data->is_abs = 0;
	return (data);
}
