/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:00:43 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/08 14:00:36 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_cmds	*cmds;

	if (argc >= 5)
		data.cmd_count = argc - 2;
	else
		return (-1);
	get_paths(envp, &data);
	get_cmds(argv, &cmds, &data);
	check_access(&data, cmds);
	
	while (cmds)
	{
		printf("cmd = %s\toption = %s\tabs_path = %s\n", cmds->cmd, cmds->options[1], cmds->abs_path);
		cmds = cmds->next;
	}
	return (0);
}
