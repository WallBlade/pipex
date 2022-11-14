/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:42:57 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/14 18:30:57 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_data *data, t_cmds *cmds, char **envp)
{
	if (check_access(data, cmds) != 0)
	{
		if (open("infile", O_RDONLY) == -1)
			return ;
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
		execve(cmds->abs_path, cmds->options, envp);
	}
}

void	second_son(t_data *data, t_cmds *cmds, char **envp)
{
	if (check_access(data, cmds) != 0)
	{
		if (open("outfile", O_TRUNC | O_CREAT | O_RDWR, 0666) == -1)
			return ;
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
		execve(cmds->next->abs_path, cmds->next->options, envp);
	}
}

void	exec(t_data *data, t_cmds *cmds, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(data->fd) == -1)
		return ;
	pid1 = fork();
	if (pid1 < 0)
		return ;
	else if (pid1 == 0)
		first_child(data, cmds, envp);
	pid2 = fork();
	if (pid2 < 0)
		return ;
	else if (pid2 == 0)
		second_son(data, cmds, envp);
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(pid1, data->status1, 0);
	waitpid(pid2, data->status2, 0);
}