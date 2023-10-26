#include "../../include/minishell.h"

void print_tokens(t_tokens *tokens)
{
	int i = 0;
	while(tokens[i].token != NULL)
	{
		printf("token %d: :%s: :%d:\n",tokens[i].id, tokens[i].token, tokens[i].type);
		i++;
	}
}

TokenType is_type(const char *token)
{
	int i = 0;
	while(token[i])
	{
		if(token[i] == '|')
			return(PIPE);
		if(token[i] == '<' && token[i +1] == '<')
			return(LEFT_LEFT);
		else if(token[i] == '<')
			return(LEFT);
		if(token[i] == '>' && token[i+1] == '>')
			return(RIGHT_RIGHT);
		else if(token[i] == '>')
			return(RIGHT);
		if(token[i] == '\'')
			return(SINGLE_QUOTE);
		if(token[i] == '"')
			return(DOUBLE_QUOTE);
		i++;
	}
	return(WORD);
}

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
	while(i < num_tokens)
	{
		tokens[i].type = is_type(split_input[i]);
		tokens[i].token = malloc(ft_strlen(split_input[i]) * sizeof(char));
		ft_memcpy(tokens[i].token, split_input[i],ft_strlen(split_input[i]));
		tokens[i].id = i;
		i++;
	}
	tokens[i].token = NULL;
	tokens[i].id = -1;
	i = 0;
	while(split_input[i])
	{
		free(split_input[i]);
		i++;
	}

	return(tokens);
}
