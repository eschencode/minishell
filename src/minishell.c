#include "../include/minishell.h"

int main(int argc, char **argv)
{
	char *prompt;

	prompt = ft_strdup("minishell$ ");
	char *input = readline(prompt);
	free(prompt);
	if(input == NULL)
	{
		usleep(100);
	}
	else{
		tokenization(input);
	}


	
}