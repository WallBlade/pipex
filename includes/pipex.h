/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:14:23 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/15 00:32:48 by zel-kass         ###   ########.fr       */
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
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
	int		status1;
	int		status2;
	int		cmd_count;
	char	**paths;
}	t_data;

typedef	struct s_cmds
{
	char			*cmd;
	char			*abs_path;
	char			**options;
	struct s_cmds	*next;
}	t_cmds;


//------------------    UTILS   ------------------//

char	*ft_strjoin(char *s1, char *s2);
int		ft_countwords(char const *str, char sep);
int		ft_wordlen(char const *str, char sep, int i);
void	ft_freetab(char **s);
char	**ft_split(char const *s, char c);

//------------------    UTILS1   ------------------//

int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strnstr(const char *str, const char *to_find, int n);
char	*ft_strdup(char *src);
void	ft_putstr_fd(char *s, int fd);

//------------------    LIST   ------------------//

t_cmds	*ft_lstnew(char *cmd, char **options);
void	ft_lstadd_back(t_cmds **lst, t_cmds *new);
void	ft_freelst(t_cmds **cmds);

//------------------    PARSING   ------------------//

int		get_paths(char **envp, t_data *data);
void	get_cmds(char **argv, t_cmds **cmds, t_data *data);
int		check_access(t_data *data, t_cmds *cmds);

//------------------    CHILD   ------------------//

void	first_child(t_data *data, t_cmds *cmds, char **envp);
void	second_son(t_data *data, t_cmds *cmds, char **envp);
void	exec(t_data *data, t_cmds *cmds, char **envp);

//------------------    ERROR   ------------------//

void	file_error(char *file);

#endif