#include "../include/minishell.h"
//start making it possible to renter command
//means making ft_exit 
//freeing 
//add history probably easy with redline function
#define clearwindow() printf("\033[H\033[J")

void print_tokens(t_tokens *tokens)
{
	int i = 0;
	while(tokens[i].token != NULL)
	{
		printf("token %d: %s\n",tokens[i].id, tokens[i].token);
		i++;
	}
}

void ft_free(t_tokens *tokens)
{
	free(tokens);
}

void	minishell_loop()
{
	char *prompt;
	t_tokens *tokens;
	int i = -1;
	while(1)
	{
	prompt = ft_strdup("minishell$ ");
	char *input = readline(prompt);
	
	tokens = tokenization(input);
	free(input);
	print_tokens(tokens);
	}
}


int main(int argc, char **argv)
{
	clearwindow();
	minishell_loop();
	
	
}