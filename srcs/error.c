/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:58:47 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/18 17:53:35 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	file_error(char *file)
{
	if (access(file, F_OK) == -1)
	{	
		free(file);
		exit(126);
	}
	else if (access(file, X_OK) == -1)
	{
		free(file);
		exit(1);
	}
}

void	cmd_error(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	check_status(int wpid, char *cmd, char *file)
{
	if (wpid == 127)
		cmd_error(cmd);
	if (wpid == 126 && access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": permission denied\n", 2);
	}
	else if (wpid == 126)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (wpid == 1 && open(file, O_RDWR) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": permission denied\n", 2);
	}
}

void	wait_for_all(t_data *data, t_pip *pip)
{
	int		i;
	char	*file;

	i = 0;
	while (i < data->cmd_count)
	{
		if (i == 0)
			file = data->infile;
		else if (i == 1)
			file = data->outfile;
		waitpid(data->pid[i], &data->wpid, 0);
		check_status(WEXITSTATUS(data->wpid), pip[i].options[0], file);
		i++;
	}
}

void	free_struct(t_data *data, t_pip *pip)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		if (pip && pip[i].options)
			ft_freetab(pip[i].options);
		if (pip[i].abs_path && data->is_abs == 0)
			free(pip[i].abs_path);
		i++;
	}
	free(pip);
	if (data->infile)
		free(data->infile);
	if (data->outfile)
		free(data->outfile);
	if (data->pid)
		free(data->pid);
	if (data->paths)
		ft_freetab(data->paths);
	free(data);
}
