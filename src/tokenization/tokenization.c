#include "../../include/minishell.h"

t_tokens *tokenization(char *input)
{
	int i;
	int num_tokens;
	char **split_input;
	t_tokens *tokens;
	
	num_tokens = 0;
	i = 0;

	split_input = ft_split(input, ' ');
	if(split_input)
	{
		while(split_input[num_tokens])
			num_tokens++;
	}
	tokens = malloc((num_tokens + 1) * sizeof(t_tokens));
	while(i <= num_tokens)
	{
		tokens[i].token = split_input[i];
		tokens[i].id = i;
		i++;
	}
	tokens[i].token = NULL;
	tokens[i].id = -1;
	i = 0;
	
	return(tokens);
}