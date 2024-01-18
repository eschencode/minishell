#include "../../include/minishell.h"

TokenType is_type(const char *token)
{
	int i = 0;
	while(token[i])
	{
		if(token[i] == '|')
			return(PIPE);
		if(token[i] == '<' && token[i + 1] == '<')
			return(LEFT_LEFT);
		else if(token[i] == '<')
			return(LEFT);
		if(token[i] == '>' && token[i + 1] == '>')
			return(RIGHT_RIGHT);
		else if(token[i] == '>')
			return(RIGHT);
		i++;
	}
	return(WORD);
}

int count_quotes(char *input)
{
	int i;
	int quotes;

	i = -1;
	quotes = 0;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
			quotes++;
	}
	return (quotes);
}

void	tokenization(t_shell *shell, char *input)
{
	int i;
	char **split_input;
	t_tokens *tokens;

	i = 0;
	shell->num_tokens = 0;
	custom_split(input);
	split_input = ft_split(input, ' ');
	while(split_input[shell->num_tokens])
		shell->num_tokens++;
	tokens = malloc((shell->num_tokens + 1) * sizeof(t_tokens));
	while(i < shell->num_tokens)
	{
		tokens[i].type = is_type(split_input[i]);
		tokens[i].token = malloc((ft_strlen(split_input[i]) + 1) * sizeof(char));
		strcpy(tokens[i].token, split_input[i]);
		tokens[i].id = i;
		i++;
	}
	tokens[i].token = NULL;
	tokens[i].id = -1;
	free_double_str(split_input);
	free(split_input);
	shell->tokens = tokens;
}