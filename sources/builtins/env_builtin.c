/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 22:17:54 by ticharli          #+#    #+#             */
/*   Updated: 2025/12/16 22:42:27 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_data *data, char **args)
{
	int	i;

	if (args[1])
	{
		if (args[1][0] == '-')
			return (errmsg_cmd("env", args[1], "invalid option", 125));
		return (errmsg_cmd("env", args[1], "No such file or directory", 127));
	}
	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
		ft_putendl_fd(data->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
