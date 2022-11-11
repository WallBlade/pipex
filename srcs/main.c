/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:00:43 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/11 17:35:15 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_cmds	*cmds;
	// int		pid;

	if (argc >= 5)
		data.cmd_count = argc - 2;
	else
		return (-1);
	get_paths(envp, &data);
	get_cmds(argv, &cmds, &data);
	check_access(&data, cmds);
	
	int pid = fork();
	if (pid == 0)
	{
		printf("I am child, my pid inside the fork is = %d\n", pid);
		printf("I am child, my absolute pid is = %d\n", getpid());
		printf("I am child, the pid of my parent = %d\n", getppid());
	}
	wait(NULL);
	printf("\npid = %d\n", pid);
	printf("I am parent, my pid is = %d\n", getpid());
	return (0);
}
