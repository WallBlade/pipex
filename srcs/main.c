/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:00:43 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/02 17:32:18 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	if (argc >= 5)
		data.cmd_count = argc - 3;
	get_paths(envp, &data);
	get_cmds(argv, &data);
	int i = 0;
	while (data.paths[i])
	{
		printf("%s\n", data.paths[i]);
		i++;
	}
	return (0);
}
