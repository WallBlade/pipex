/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:14:23 by zel-kass          #+#    #+#             */
/*   Updated: 2022/10/31 17:55:19 by zel-kass         ###   ########.fr       */
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
	char	**cmd_1;
	char	**cmd_2;
	char	**paths;	
}	t_data;


//------------------    UTILS   ------------------//

char	**ft_split(char const *s, char c);
size_t	ft_countwords(char const *str, char sep);
size_t	ft_wordlen(char const *str, char sep, int i);
char	**ft_freetab(char **s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

//------------------    UTILS1   ------------------//

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *str, const char *to_find, size_t n);

//------------------    PARSING   ------------------//

int		get_paths(char **envp, t_data *data)

#endif