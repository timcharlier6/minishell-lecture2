/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:14:08 by alexa             #+#    #+#             */
/*   Updated: 2022/11/04 12:32:48 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_valid_var_name(char c) {
  if (ft_isalnum(c) || c == '_')
    return (true);
  return (false);
}

/*
 *   `$?`: The exit status of the last executed command.
 *   `$#`: The number of positional parameters (arguments passed to a script or
 * function).
 *   `$*` and `$@`: Represent all positional parameters.
 *   `$$`: The process ID (PID) of the current shell.
 */
int var_len(char *str) {
  int var_len;
  int i;

  var_len = 0;
  i = 0;
  while (str[i] != '$')
      i++;
  i++;
  if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?') {
    var_len = 1;
    return (var_len);
  }
  while (str[i]) {
    if (is_valid_var_name(str[i]) == false)
      break;
    var_len++;
    i++;
  }
  return (var_len);
}

char *get_var_key(char *str) {
  char *var;
  char *tmp;
  int start;
  int len;
  int i;

  i = 0;
  start = 0;
  while (str[i]) {
    if (str[i] == '$') {
      start = i + 1;
      break;
    }
    i++;
  }
  len = var_len(str);
  var = ft_substr(str, start, len);
  if (!var)
    return (NULL);
  tmp = ft_strjoin(var, "=");
  if (!tmp) {
    free_ptr(var);
    return (NULL);
  }
  free_ptr(var);
  var = tmp;
  return (var);
}
