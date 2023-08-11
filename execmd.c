/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:30:25 by jmarks            #+#    #+#             */
/*   Updated: 2023/08/02 15:54:31 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char const *currentPath, char const *cmd)
{
	char	*rtn;

	if (*cmd == '/')
		rtn = ft_strdup(cmd);
	if (cmd[0] == '/')
	{
		if (execve(&cmd[0], g_program.token, g_program.envp) == -1)
			error_and_exit("command cannot be executed", 126);
	}
	else if (!ft_strncmp(cmd, "./", 2))
		rtn = ft_strjoin((find_env(g_program.envar, "PWD")->value),
				ft_strjoin("/", cmd));
	else
		rtn = ft_strjoin(currentPath, ft_strjoin("/", cmd));
	return (rtn);
}

char	**get_full_path(void)
{
	char			**env_paths;
	t_envar const	*path;

	path = find_env(g_program.envar, "PATH");
	if (path)
		env_paths = ft_split(path->value, ':');
	else
		env_paths = NULL;
	return (env_paths);
}

char	*get_path_for_cmd(char **env_paths, char const *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (env_paths[i])
	{
		path = get_path(env_paths[i], cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	execmd(void)
{
	char	**paths;
	char	*exec_path;
	char	*cmds;
	pid_t	pid;
	int		status;

	pid = fork();
	cmds = g_program.token[0];
	if (pid == 0)
	{
		paths = get_full_path();
		exec_path = get_path_for_cmd(paths, &cmds[0]);
		if (!paths || !exec_path)
			error_and_exit("command not found", 127);
		if (execve(exec_path, g_program.token, g_program.envp) == -1)
			error_and_exit("command cannot be executed", 126);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_program.exit_status = WEXITSTATUS(status);
}
