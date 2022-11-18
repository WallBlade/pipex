/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:14:23 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/18 17:47:16 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef	struct s_data
{
	int		is_abs;
	char	*infile;
	char	*outfile;
	int		i_fd;
	int		o_fd;
	int		fd[2];
	int		cmd_count;
	int		wpid;
	int		*pid;
	char	**paths;
}	t_data;

typedef	struct s_pip
{
	char	*cmd;
	char	*abs_path;
	char	**options;
}	t_pip;


//------------------    UTILS   ------------------//

char	*ft_strjoin(char *s1, char *s2);
int		ft_countwords(char const *str, char sep);
int		ft_wordlen(char const *str, char sep, int i);
void	ft_freetab(char **s);
char	**ft_split(char const *s, char c);

//------------------    UTILS1   ------------------//

int		ft_strlen(char *s);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strnstr(char *str, char *to_find, int n);
char	*ft_strdup(char *src);
void	ft_putstr_fd(char *s, int fd);

//------------------    PARSING   ------------------//

void	check_args(int argc, char **argv);
char	**get_paths(char **envp);
void	get_cmds(char *av, t_pip *pip, int i);
int		check_access(t_data *data, t_pip *pip, int n);

//------------------    CHILD   ------------------//

void	first_child(t_data *data, t_pip *pip, char **envp);
void	second_son(t_data *data, t_pip *pip, char **envp);
void	exec(t_data *data, t_pip *pip, char **envp);

//------------------    INIT   ------------------//

t_pip	*init_pip_struct(char **argv, t_data *data);
t_data	*init_data_struct(int ac, char **av, char **env_path);

//------------------    ERROR   ------------------//

void	file_error(char *file);
void	cmd_error(char *cmd);
void	check_status(int wpid, char *cmd, char *file);
void	wait_for_all(t_data *data, t_pip *pip);
void	free_struct(t_data *data, t_pip *pip);

#endif