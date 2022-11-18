/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:00:43 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/18 17:22:09 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_pip	*pip;
	char	**env_path;
	int		wpid;

	env_path = NULL;
	check_args(argc, argv);
	if (envp && envp[0])
		env_path = get_paths(envp);
	data = init_data_struct(argc, argv, env_path);
	pip = init_pip_struct(argv, data);
	if (!pip)
		return (-1);
	exec(data, pip, envp);
	wpid = WEXITSTATUS(data->wpid);
	free_struct(data, pip);
	return (wpid);
}
