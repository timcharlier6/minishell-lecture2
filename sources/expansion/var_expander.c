/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 02:35:14 by alexa             #+#    #+#             */
/*   Updated: 2022/11/07 17:03:43 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void update_status(t_token **token_node, char c) {
  if (c == '\'' && (*token_node)->status == DEFAULT)
    (*token_node)->status = SQUOTE;
  else if (c == '\"' && (*token_node)->status == DEFAULT)
    (*token_node)->status = DQUOTE;
  else if (c == '\'' && (*token_node)->status == SQUOTE)
    (*token_node)->status = DEFAULT;
  else if (c == '\"' && (*token_node)->status == DQUOTE)
    (*token_node)->status = DEFAULT;
}

static bool is_next_char_a_sep(char c) {
  if (c == '$' || c == ' ' || c == '=' || c == '\0')
    return (true);
  else
    return (false);
}

//  echo "The price is "$"5.00"
static bool dollar_between_quotes(char *str, int i) {
  if (i > 0) {
    if (str[i - 1] == '\"' && str[i + 1] == '\"')
      return (true);
    else
      return (false);
  }
  return (false);
}

int var_expander(t_data *data, t_token **token_lst) {
  t_token *temp;
  int i;
  char *var_value;

  temp = *token_lst;
  while (temp) {
    if (temp->type == VAR) {
      i = 0;
      while (temp->str[i]) {
        update_status(&temp, temp->str[i]);
        if (temp->str[i] == '$' &&
            is_next_char_a_sep(temp->str[i + 1]) == false &&
            dollar_between_quotes(temp->str, i) == false &&
            (temp->status == DEFAULT || temp->status == DQUOTE))
        {
            var_value = get_var_value(temp, temp->str + i, data);
            if (replace_var(&temp, var_value, i) == FAILURE)
              return (FAILURE);
        }
        else
          i++;
      }
    }
    temp = temp->next;
  }
  return (SUCCESS);
}

/* var_expander_heredoc:
 *	Heredoc variant of var_expander. Replaces a string containing an
 *	environment variable, like $USER with its corresponding value.
 *	Returns the replaced string. May return NULL on error.
 */
char *var_expander_heredoc(t_data *data, char *str) {
  int i;

  i = 0;
  while (str[i]) {
    if (str[i] == '$' && is_next_char_a_sep(str[i + 1]) == false &&
        dollar_between_quotes(str, i) == false)
      str = replace_str_heredoc(str, get_var_value(NULL, str + i, data), i);
    else
      i++;
  }
  return (str);
}
