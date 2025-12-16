/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */ /*                                                                            */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:55:59 by mcombeau          #+#    #+#             */
/*   Updated: 2025/12/16 20:10:12 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* is_n_flag:
*	Checks whether an arg is an -n option flag.
*	Returns true if the arg is some variation of -n, -nnnn, -nn, etc.
*	Returns false if it contains anything other than - and n (ex. --n -nnnm -n1234)
*/
static bool	is_n_flag(char *arg)
{
	int		i;

	if (!arg || arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i] && arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

/* echo_print_args:
*	Prints the given array of aruments to STDOUT.
*/
static void	echo_print_args(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

/* echo_builtin:
*	Executes the echo builtin command: prints the given strings
*	and adds a \n character or not depending on the -n option.
*	Returns EXIT_SUCCESS on completion.
*/
int	echo_builtin(t_data *data, char **args)
{
	int		i;
	bool	n_flag;

	(void)data;
	n_flag = false;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	echo_print_args(args, i);
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
