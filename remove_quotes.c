// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   remove_quotes.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/13 18:23:48 by mesenyur          #+#    #+#             */
// /*   Updated: 2024/03/28 18:02:18 by mesenyur         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// // expansion function

// t_token	*expand_variable(t_token *token, t_env *envp, char quotes, int flag)
// {
// 	char	*joker;
// 	char	*new;
// 	char	*value;
// 	char	*tmp_i;
// 	char	*tmp;
// 	int		len;
// 	int		i;
// 	t_token	*last_token;

// 	len = 0;
// 	i = 0;
// 	flag = 0;
// 	last_token = NULL;
// 	tmp = NULL;
// 	tmp_i = NULL;
// 	value = NULL;
// 	quotes = CLOSED;
// 	joker = token->str;
// 	new = ft_strdup("");
// 	while (joker[i])
// 	{
// 		quote_check(joker[i], &quotes);
// 		if (joker[i] == S_QUOTE)
// 		{
// 			new = process_single_quotes(new, joker, &i);
// 			quotes = CLOSED;
// 		}
// 		else if (quotes == D_QUOTE)
// 		{
// 			new = process_double_quotes(new, joker, &i, envp);
// 			quotes = CLOSED;
// 		}
// 		else if (quotes == CLOSED)
// 		{
// 			while (joker[i] && joker[i] != '\"' && joker[i] != '\'')
// 			{
// 				while (joker[i] && joker[i] != '$' && joker[i] != '\"'
// 					&& joker[i] != '\'')
// 					new = add_char(new, joker[i++]);
// 				if (ft_is_dollar(joker[i]) && (joker[i + 1] && joker[i
// 						+ 1] != '$'))
// 				{
// 					i++;
// 					len = check_name_and_return_len(&joker[i]);
// 					tmp = ft_substr(joker, i, len);
// 					if (!tmp)
// 						return (NULL);
// 					i += len;
// 					if ((value = get_env_value(tmp, envp)) != NULL)
// 					{
// 						if (value[0] == '\0')
// 							token->ambiguous = true;
// 						if (value[0] == ' ')
// 						{
// 							flag = 1; // space at start
// 							if (value[ft_strlen(value) - 1] == ' ')
// 								flag = 3; // space at start and end
// 						}
// 						else if (value[ft_strlen(value) - 1] == ' ')
// 							flag = 2;                      // space at end
// 						if (ft_strchr(value, ' ') == NULL) // single word value
// 						{
// 							new = ft_strjoin(new, value);
// 							continue ;
// 						}
// 						else
// 						{
// 							if (token->type != HEREDOC && token->type != RANDOM)
// 							{
// 								token->ambiguous = true;
// 							}
// 							tmp_i = &joker[i];
// 							last_token = split_value(new, value, token, flag);
// 							if (flag == 2 || flag == 3)
// 							{
// 								printf("last_token->str: %s\n",
// 									last_token->str);
// 								// there is a space at end, need new token
// 								// insert_token("", last_token,
// 									last_token->next);
// 									insert_token(&tmp_i, last_token,
// 										last_token->next);
// 									// while (*tmp_i && *tmp_i != '$'
// 									&& *tmp_i != '\"' && *tmp_i != '\'')
// 								// {
// 								// 	last_token->next->str = add_char(last_token->str,
// 											*tmp_i);
// 									// 	i++;
// 									// 	tmp_i++;
// 									// }
// 							}
// 							printf("token str: %s\n", token->str);
// 							if (*tmp_i)
// 							{
// 								if (*tmp_i && flag != 2 && flag != 3)
// 								// if has NO space at end
// 								{
// 									while (*tmp_i && *tmp_i != '$'
// 										&& *tmp_i != '\"' && *tmp_i != '\'')
// 									{
// 										last_token->str = add_char(last_token->str,
// 												*tmp_i);
// 										i++;
// 										tmp_i++;
// 									}
// 									new = ft_strdup(last_token->str);
// 									if (ft_is_dollar(*tmp_i) || *tmp_i == '\"'
// 										|| *tmp_i == '\'')
// 									{
// 										token = last_token;
// 										continue ;
// 									}
// 									else
// 									{
// 										printf("else str: %s\n", token->str);
// 										return (last_token);
// 									}
// 								}
// 								if (ft_is_dollar(*tmp_i) || *tmp_i == '\"'
// 									|| *tmp_i == '\'')
// 								{
// 									token = last_token;
// 									continue ;
// 								}
// 							}
// 							token = last_token;
// 							return (token);
// 						}
// 					}
// 				}
// 				else if (ft_is_dollar(joker[i]))
// 				{
// 					new = add_char(new, joker[i]);
// 					i++;
// 				}
// 			}
// 		}
// 	}
// 	token->str = new;
// 	return (token);
// }
