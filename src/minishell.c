#include "../include/minishell.h"

int main(int argc, char **argv)
{
	char *prompt;
	t_tokens *tokens;
	int i = -1;

	prompt = ft_strdup("minishell$ ");
	char *input = readline(prompt);
	free(prompt);
	if(input == NULL)
	{
		usleep(100);
	}
	else{
		tokens = tokenization(input);
		while(tokens[++i].token)
			printf("token %d: %s\n",tokens[i].id, tokens[i].token);
	}
}