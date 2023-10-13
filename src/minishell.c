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
	int c = 9;
	while(c > 5)
	{
		c--;
	input = readline(prompt);
	printf("%s\n",input);
	if(input[0] == 'c' && input[1] == 'd' && input[2] == ' ')
	{

		input[ft_strlen(input)] = '\0';
		if(chdir(input + 3) < 0)
			printf("cant cd %s\n",input +3);
	}
	else if (strcmp(input, "pwd") == 0) {
            // Implement the 'pwd' command
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                	printf("%s\n", cwd);
			}
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
