/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:00:43 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/17 15:00:22 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_pip	*pip;
	int		wpid;

	if (argc < 5)
		return (-1);
	data = init_data_struct(argc, argv, envp);
	pip = init_pip_struct(argv, data);
	if (!pip)
		return (-1);
	exec(data, pip, envp);
	wpid = WEXITSTATUS(data->wpid);
	free_struct(data, pip);
	return (wpid);
}
