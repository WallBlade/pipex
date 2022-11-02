/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:14:23 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/02 20:29:47 by zel-kass         ###   ########.fr       */
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

typedef	struct s_data
{
	int		cmd_count;
	char	**cmd;
	char	**paths;	
}	t_data;


//------------------    UTILS   ------------------//

char	**ft_split(char const *s, char c);
int		ft_countwords(char const *str, char sep);
int		ft_wordlen(char const *str, char sep, int i);
char	**ft_freetab(char **s, int n);
char	*ft_strjoin(char *s1, char *s2);

//------------------    UTILS1   ------------------//

int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strnstr(const char *str, const char *to_find, int n);
char	*ft_strdup(char *src);

//------------------    PARSING   ------------------//

int		get_paths(char **envp, t_data *data);
int		get_cmds(char **argv, t_data *data);
char	*check_access(t_data *data);

#endif