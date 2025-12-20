/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexa <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:52:09 by alexa             #+#    #+#             */
/*   Updated: 2022/11/10 00:52:18 by alexa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_var(char *new_str, char *var_value, int *j)
{
	int	i;

	i = 0;
	while (var_value[i])
	{
		new_str[*j] = var_value[i];
		i++;
		(*j)++;
	}
}

char	*get_new_token_string(char *oldstr, char *var_value,
		int newstr_size, int var_index)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * newstr_size);
	if (!new_str)
		return (NULL);
	while (oldstr[i])
	{
		if (oldstr[i] == '$' && i == var_index)
		{
			expand_var(new_str, var_value, &j);
			i = i + var_len(oldstr + var_index) + 1;
			if (oldstr[i] == '\0')
				break ;
		}
		new_str[j++] = oldstr[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}
