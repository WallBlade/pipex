/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:42:57 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/17 16:35:55 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_data *data, t_pip *pip, char **envp)
{
	if (check_access(data, pip, 0) == 0)
	{
		data->infile_fd = open(data->infile, O_RDONLY);
		if (data->infile_fd == -1)
		{
			free_struct(data, pip);
			file_error(data->infile); 
		}
		dup2(data->fd[1], STDOUT_FILENO);
		dup2(data->infile_fd, 0);
		close(data->fd[0]);
		close(data->fd[1]);
		execve(pip[0].abs_path, pip[0].options, envp);
	}
}

void	second_son(t_data *data, t_pip *pip, char **envp)
{
	if (check_access(data, pip, 1) == 0)
	{
		data->outfile_fd = open(data->outfile, O_TRUNC | O_CREAT | O_RDWR, 0664);
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->outfile_fd, 1);
		close(data->fd[0]);
		close(data->fd[1]);
		execve(pip[1].abs_path, pip[1].options, envp);
	}
}

void	exec(t_data *data, t_pip *pip, char **envp)
{
	int	i;

	i = 0;
	if (pipe(data->fd) == -1)
		return ;
	while (i < data->cmd_count)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return ;
		else if (data->pid[i] == 0 && i == 0)
			first_child(data, pip, envp);
		else if (data->pid[i] == 0 && i == 1)
			second_son(data, pip, envp);
		i++;
	}
	close(data->fd[0]);
	close(data->fd[1]);
	wait_for_all(data, pip);
}