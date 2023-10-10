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
		printf("token %d: :%s:\n",tokens[i].id, tokens[i].token);
		i++;
	}
}

void ft_free(t_tokens *tokens, char *input)
{
	int i = 0;
	while(tokens[i].token != NULL)
	{
		free(tokens[i].token);
		i++;
	}
	free(tokens);
	free(input);
}

void	minishell_loop()
{
	char prompt[12] = "minishell$ ";
	t_tokens *tokens;
	char *input;
	int i = -1;
	rl_initialize();
	
	while(1)
	{
	input = readline(prompt);
	if(input == NULL || input[0] == '\0')
	{
		printf("empty input\n");
		free(input);
	}
	else
	{
		tokens = tokenization(input);
		print_tokens(tokens);
		ft_free(tokens, input);
	}
	
	}
}


int main(int argc, char **argv)
{
	clearwindow();
	minishell_loop();
	
	
}