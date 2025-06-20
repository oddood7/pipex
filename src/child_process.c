/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:57:42 by lde-mais          #+#    #+#             */
/*   Updated: 2023/07/13 12:06:54 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	has_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*get_command(char **paths, char *cmd)
{
	char	*command;
	char	*tmp;

	if (!paths || !cmd)
		return (NULL);
	if (has_char(cmd, '/'))
	{
		if (access(cmd, 0) == 0)
			return (cmd);
		return (NULL);
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

int	is_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 33 && str[i] < 126)
			return (1);
		i++;
	}
	return (0);
}

void	first_child(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
	{
		close_fd(&pipex);
		free_parent(&pipex);
		error_print(argv[1]);
	}
	dup2(pipex.pipefd[1], 1);
	close(pipex.pipefd[0]);
	dup2(pipex.infile, 0);
	close(pipex.infile);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = get_command(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		close(1);
		close(0);
		close_fd(&pipex);
		free_child(&pipex);
		error_msg(argv[2], &pipex);
		free_parent(&pipex);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	second_child(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.outfile < 0)
	{
		close_fd(&pipex);
		free_parent(&pipex);
		error_print(argv[4]);
	}
	dup2(pipex.pipefd[0], 0);
	close(pipex.pipefd[1]);
	dup2(pipex.outfile, 1);
	close(pipex.outfile);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = get_command(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		close(1);
		close(0);
		close_fd(&pipex);
		free_child(&pipex);
		error_msg(argv[3], &pipex);
		free_parent(&pipex);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}
