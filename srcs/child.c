/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:42:57 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/15 18:41:21 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_data *data, t_cmds *cmds, char **envp)
{
	if (check_access(data, cmds) == 0)
	{
		data->infile_fd = open("infile", O_RDONLY);
		if (data->infile_fd == -1)
			file_error("infile");
		dup2(data->fd[1], STDOUT_FILENO);
		dup2(data->infile_fd, 0);
		close(data->fd[0]);
		close(data->fd[1]);
		execve(cmds->abs_path, cmds->options, envp);
	}
}

void	second_son(t_data *data, t_cmds *cmds, char **envp)
{
	if (check_access(data, cmds->next) == 0)
	{
		data->outfile_fd = open("outfile", O_TRUNC | O_CREAT | O_RDWR, 0664);
		if (data->outfile_fd == -1)
			file_error("outfile");
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->outfile_fd, 1);
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
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}