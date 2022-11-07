/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:09:17 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/07 18:27:56 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int	len;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[++j])
		dest[i++] = s2[j];
	dest[i] = '\0';
	return (dest);
}

int	ft_countwords(char const *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] && str[i] != sep)
		{
			count++;
			while (str[i] && str[i] != sep)
				i++;
		}
	}
	return (count);
}

int	ft_wordlen(char const *str, char sep, int i)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != sep)
	{
		i++;
		len++;
	}
	return (len);
}

char	**ft_freetab(char **s, int n)
{
	while (n >= 0)
	{
		free(s[n]);
		n--;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int	i;
	int	j;
	int	k;
	char	**split;

	split = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < ft_countwords(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		k = 0;
		split[j] = (char *)malloc(sizeof(char) * (ft_wordlen(s, c, i) + 1));
		if (!split[j])
			return (ft_freetab(split, j), NULL);
		while (s[i] && s[i] != c)
			split[j][k++] = s[i++];
		split[j][k] = '\0';
	}
	split[j] = 0;
	return (split);
}