/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:00:43 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/04 19:43:50 by zel-kass         ###   ########.fr       */
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
	// while (cmds->next)
	// {
	// 	cmds = cmds->next;
	// 	printf("cmd = %s\toptions = %s\n", cmds->cmd, cmds->options[1]);
	// }
	// printf("options = %s\n", cmds->options[0]);
	check_access(&data, cmds);
	while (cmds)
	{
		printf("%s\n", cmds->abs_path);
		cmds = cmds->next;
	}
	return (0);
}
