/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:17:59 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/14 14:56:18 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmds	*ft_lstnew(char *cmd, char **options)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	cmds->cmd = cmd;
	cmds->options = options;
	cmds->abs_path = NULL;
	cmds->next = NULL;
	return (cmds);
}

void	ft_lstadd_back(t_cmds **lst, t_cmds *new)
{
	t_cmds	*tmp;

	tmp = *lst;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_lstsize(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

void	ft_freelst(t_cmds **cmds)
{
	int		len;
	t_cmds	*tmp;

	len = ft_lstsize(*cmds);
	while (len > 0)
	{
		tmp = (*cmds)->next;
		free(*cmds);
		(*cmds) = tmp;
		len--;
	}
}
