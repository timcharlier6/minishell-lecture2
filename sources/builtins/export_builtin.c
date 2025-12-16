/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 22:17:54 by ticharli          #+#    #+#             */
/*   Updated: 2025/12/16 22:42:44 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int	partition(char **tab, int low, int high)
{
	char	*pivot;
	int		i;
	int		j;

	pivot = tab[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (ft_strcmp(tab[j], pivot) < 0)
		{
			i++;
			swap_strings(&tab[i], &tab[j]);
		}
		j++;
	}
	swap_strings(&tab[i + 1], &tab[high]);
	return (i + 1);
}

static void	quicksort_recursive(char **tab, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition(tab, low, high);
		quicksort_recursive(tab, low, pi - 1);
		quicksort_recursive(tab, pi + 1, high);
	}
}

static char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	tmp = malloc(sizeof *tmp * (2 + 1));
	tmp[0] = ft_substr(arg, 0, eq_pos - arg);
	tmp[1] = ft_substr(eq_pos, 1, ft_strlen(eq_pos));
	tmp[2] = NULL;
	return (tmp);
}

static void	print_variable(char *var)
{
	char	*eq_pos;

	ft_putstr_fd("export ", STDOUT_FILENO);
	eq_pos = ft_strchr(var, '=');
	if (eq_pos)
	{
		write(STDOUT_FILENO, var, eq_pos - var + 1);
		ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putstr_fd(eq_pos + 1, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
	}
	else
		ft_putendl_fd(var, STDOUT_FILENO);
}

static int	print_sorted_env(t_data *data)
{
	char	**sorted_env;
	int		count;
	int		i;

	count = env_var_count(data->env);
	sorted_env = ft_calloc(count + 1, sizeof(char *));
	if (!sorted_env)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < count)
		sorted_env[i] = data->env[i];
	quicksort_recursive(sorted_env, 0, count - 1);
	i = 0;
	while (i < count)
		print_variable(sorted_env[i++]);
	free(sorted_env);
	return (EXIT_SUCCESS);
}

static int	process_export_arg(t_data *data, char *arg)
{
	char	**tmp;

	if (!is_valid_env_var_key(arg))
	{
		errmsg_cmd("export", arg, "not a valid identifier", false);
		return (EXIT_FAILURE);
	}
	if (ft_strchr(arg, '=') != NULL)
	{
		tmp = get_key_value_pair(arg);
		set_env_var(data, tmp[0], tmp[1]);
		free_str_tab(tmp);
	}
	else if (get_env_var_index(data->env, arg) == -1)
		set_env_var(data, arg, NULL);
	return (EXIT_SUCCESS);
}

int	export_builtin(t_data *data, char **args)
{
	int	i;
	int	ret;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (print_sorted_env(data));
	while (args[i])
	{
		if (process_export_arg(data, args[i]) == EXIT_FAILURE)
			ret = EXIT_FAILURE;
		i++;
	}
	return (ret);
}
