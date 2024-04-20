// t_token	*split_value(char *str, char *value, t_token *token) // ORIGINAL
// {
// 	char	**words;
// 	t_token	*last;
// 	t_token	*new;
// 	int		i;

// 	i = 0;
// 	last = token;
// 	words = ft_split(value, ' ');
// 	if (words == NULL)
// 		return (NULL);
// 	if (i == 0) // no space at start	 
// 	{
// 		last->str = ft_strjoin(str, words[0]);
// 		if (last->str == NULL)
// 		{
// 			free(words);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	while (words[i] != NULL)
// 	{
// 		new = malloc(sizeof(t_token));
// 		if (new == NULL)
// 		{
// 			free(words);
// 			return (NULL);
// 		}
// 		new->str = ft_strdup(words[i]);
// 		if (new->str == NULL)
// 		{
// 			free(new);
// 			free(words);	
// 			return (NULL);
// 		}
// 		new->next = last->next;
// 		new->type = last->type;
// 		last->next = new;
// 		last = new;
// 		i++;
// 	}
// 	i = 0;
// 	while (words[i] != NULL)
// 	{
// 		free(words[i]);
// 		words[i] = NULL;
// 		i++;
// 	}
// 	free(words);
// 	words = NULL;
// 	return (last);
// }

// -----------------------------------------------------------------------

// char	*process_double_quotes(char *new, char *str, int *i, t_mini *ms) //ORIGINAL
// {
// 	int		len;
// 	char	*tmp;
// 	char	*value;

// 	(*i)++;
// 	while (str[*i] && str[*i] != '\"')
// 	{
// 		if ((ft_is_dollar(str[*i])) && (str[(*i) + 1] && (str[(*i) + 1] != '$'
// 					&& str[(*i) + 1] != '\"' && str[(*i) + 1] != '?' && ft_isalnum(str[(*i) + 1]))))
// 		{
// 			(*i)++;
// 			len = check_name_and_return_len(&str[*i]);
// 			tmp = ft_substr(str, *i, len);
// 			if (!tmp)
// 				return (NULL);
// 			(*i) += len;
// 			if ((value = get_env_value(tmp, ms->env)) != NULL)
// 			{
// 				new = ft_strjoin(new, value);
// 			}
// 		}
// 		if (replace_exit_code(str, &new, i, ms));
// 		else if (ft_is_dollar(str[*i]))
// 		{
// 			new = add_char(new, str[*i]);
// 			(*i)++;
// 		}
// 		while (str[*i] && str[*i] != '$' && str[*i] != '\"')
// 		{
// 			new = add_char(new, str[*i]);
// 			(*i)++;
// 		}
// 	}
// 	if (str[*i] == '\"')
// 		(*i)++;
// 	return (new);
// }

// -----------------------------------------------------------------------

// int	ft_strtok(t_shell *shell, int *i) // ORIGINALS
// {
// 	char	*line;
// 	t_token	*last_token;

// 	if (!shell)
// 		return (ERROR);
// 	line = shell->input;
// 	while (line[*i] != '\0')
// 	{
// 		if (ft_is_space(line[*i]) == true && line[*i] != '\0')
// 		{
// 			(*i)++;
// 			continue ;
// 		}
// 		last_token = add_new_empty_token(shell);
// 		if (!last_token)
// 		{
// 			printf("Error: Token add failed\n");
// 			return (ERROR);
// 		}
// 		ft_tokenizer(shell, last_token, *i);
// 		if (last_token->type != RANDOM)
// 			not_random(last_token, i);
// 		if (last_token->type == PIPE)
// 		{
// 			while (ft_is_space(line[*i]) == true && line[*i] != '\0')
// 				(*i)++;
// 			if (line[*i] != '\0')
// 			{
// 				last_token = add_new_empty_token(shell);
// 				ft_tokenizer(shell, last_token, *i);
// 				if (last_token->type != RANDOM)
// 					not_random(last_token, i);
// 			}
// 		}
// 		if (not_pipe(shell, last_token, i) == ERROR)
// 			return (ERROR);
// 	}
// 	return (SUCCESS);
// }
