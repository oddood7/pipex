/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:05:38 by lde-mais          #+#    #+#             */
/*   Updated: 2023/06/08 14:59:10 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	close_fd(t_pipex *pipex)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
}

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

void	error_print(char *error)
{
	perror(error);
	exit (1);
}

void	error_msg(char *s, t_pipex *pipex)
{
	if (!ft_strncmp(s, "cd", ft_strlen(s)))
		return ;
	if (pipex->paths[0] == ' ')
		write(2, "No such file or directory : ", 28);
	else
		write(2, "command not found:  ", 20);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
}

void	free_child(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd);
}
