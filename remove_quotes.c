/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:23:48 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/23 13:58:53 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// void	remove_quotes(t_token *token)
// {
// 	int		i;
// 	char	*str;
// 	char		quote;

// 	i = 0;
// 	quote = CLOSED;
// 	str = token->str;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\'' || str[i] == '\"')
// 		{
// 			quote_check(str[i], &quote);
// 			//remove quote and skip to next char
// 			while (quote_check(str[i], &quote) != 0)
// 			{
// 				// skip while quote is open
// 			}
// 			// remove quote and check if word continues
// 		}
// 		i++;
// 	}
// 	token = token->next;
// }
