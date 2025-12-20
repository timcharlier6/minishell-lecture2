/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:26:14 by mcombeau          #+#    #+#             */
/*   Updated: 2022/11/07 16:26:15 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	var_is_not_null(t_data *data, char *var)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, len) == 0)
			return (true);
		i++;
	}
	return (false);
}

static char	*search_env_var(t_data *data, char *var)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, len) == 0)
			break ;
		i++;
	}
	str = ft_strdup(data->env[i] + len);
	if (!str)
		return (NULL);
	return (str);
}

// Special exit status variable
//
char	*get_var_value(t_token *token, char *str, t_data *data)
{
	char	*value;
	char	*key;

	key = get_var_key(str);
	if (key && var_is_not_null(data, key) == true)
	{
		if (token != NULL)
			token->var_is_not_null = true;
		value = search_env_var(data, key);
	}
	else if (key && key[0] == '?')
		value = ft_itoa(g_last_exit_code);
	else
		value = NULL;
	free_ptr(key);
	return (value);
}
