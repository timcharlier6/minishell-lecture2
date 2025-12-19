/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexa <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:34:40 by alexa             #+#    #+#             */
/*   Updated: 2022/09/20 12:35:02 by alexa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int save_separator(t_token **token_lst, char *str, int index, int type) {
  int i;
  char *sep;

  i = 0;
  if (type == APPEND || type == HEREDOC) {
    sep = malloc(sizeof(char) * 3);
    if (!sep)
      return (FAILURE);
    while (i < 2)
      sep[i++] = str[index++];
    sep[i] = '\0';
    lst_add_back_token(token_lst, lst_new_token(sep, NULL, type, DEFAULT));
  } else {
    sep = malloc(sizeof(char) * 2);
    if (!sep)
      return (FAILURE);
    sep[i++] = str[index++];
    sep[i] = '\0';
    lst_add_back_token(token_lst, lst_new_token(sep, NULL, type, DEFAULT));
  }
  return (SUCCESS);
}

int save_word(t_token **token_lst, char *str, int index, int start) {
  int i;
  char *word;

  i = 0;
  word = malloc(sizeof(char) * (index - start + 1));
  if (!word)
    return (FAILURE);
  while (start < index) {
    word[i] = str[start];
    start++;
    i++;
  }
  word[i] = '\0';
  lst_add_back_token(token_lst,
                     lst_new_token(word, ft_strdup(word), WORD, DEFAULT));
  return (SUCCESS);
}

int is_separator(char *str, int i) {
  if (((str[i] > 8 && str[i] < 14) || str[i] == 32))
    return (SPACES);
  else if (str[i] == '|')
    return (PIPE);
  else if (str[i] == '<' && str[i + 1] == '<')
    return (HEREDOC);
  else if (str[i] == '>' && str[i + 1] == '>')
    return (APPEND);
  else if (str[i] == '<')
    return (INPUT);
  else if (str[i] == '>')
    return (TRUNC);
  else if (str[i] == '\0')
    return (END);
  else
    return (0);
}

int set_status(int status, char *str, int i) {
  if (str[i] == '\'' && status == DEFAULT)
    status = SQUOTE;
  else if (str[i] == '\"' && status == DEFAULT)
    status = DQUOTE;
  else if (str[i] == '\'' && status == SQUOTE)
    status = DEFAULT;
  else if (str[i] == '\"' && status == DQUOTE)
    status = DEFAULT;
  return (status);
}

int save_word_or_sep(int *i, char *str, int start, t_data *data) {
  int type;
  int is_word;

  is_word = 0;
  type = is_separator(str, (*i));
  if (type != is_word) {
    if ((*i) != 0 && is_separator(str, (*i) - 1) == 0)
      save_word(&data->token, str, (*i), start);
    if (type == APPEND || type == HEREDOC || type == PIPE || type == INPUT ||
        type == TRUNC || type == END) {
      save_separator(&data->token, str, (*i), type);
      if (type == APPEND || type == HEREDOC)
        (*i)++;
    }
    start = (*i) + 1;
  }
  return (start);
}

int begins_with_sep(t_token *token) {
  if (token->type == PIPE || token->type == HEREDOC || token->type == APPEND ||
      token->type == INPUT || token->type == TRUNC || token->type == END) {
    errmsg("syntax error near unexpected token", token->str, true);
    return (true);
  }
  return (false);
}
