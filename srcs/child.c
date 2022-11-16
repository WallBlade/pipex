/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:42:57 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/16 18:44:50 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_data *data, t_pip *pip, char **envp)
{
	if (check_access(data, pip, 0) == 0)
	{
		data->infile_fd = open("infile", O_RDONLY);
		if (data->infile_fd == -1)
			file_error("infile");  
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
		data->outfile_fd = open("outfile", O_TRUNC | O_CREAT | O_RDWR, 0664);
		if (data->outfile_fd == -1){
			printf("jes suis la ?\n");
			file_error("outfile");
		}
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
	i = 0;
	while (i < data->cmd_count)
	{
		char	*file;
		if (i == 0)
			file = data->infile;
		else if (i == 1)
			file = data->outfile;
		waitpid(data->pid[i], &data->wpid, 0);
		if (WEXITSTATUS(data->wpid) == 127)
			cmd_error(pip[i].options[0]);
		if (WEXITSTATUS(data->wpid) == 126)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		if (WEXITSTATUS(data->wpid) == 1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd(": permission denied\n", 2);
		}
		i++;
	}
}