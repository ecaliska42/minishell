#include "libraries/minishell.h"

void	free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens != NULL)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		if (tmp->str != NULL)
			free(tmp->str);
			// free_and_null((void **)&tmp->str);
		free(tmp);
	}
}

// void one_function_to_free_them_all(t_mini *mini)
// {
//     if (mini->tokens)
//         free_tokens(&mini->tokens);
//     // if (mini->parse)
//     //     free_parsing_node(&mini->parse);
//     // if (mini->env)
//     //     free_environment(&mini->env);
//     free(mini);

// }
