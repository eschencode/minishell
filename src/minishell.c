#include "../include/minishell.h"

#define clearwindow() printf("\033[H\033[J")

void print_tokens(t_tokens *tokens)
{
	int i = 0;
	while(tokens[i].token != NULL)
	{
		printf("token %d: :%s: :%d:\n",tokens[i].id, tokens[i].token, tokens[i].type);
		i++;
	}
}

void ft_free(t_tokens *tokens, char *input, t_shell *shell)
{
	int i = 0;
	if (shell->tokens_flag)
	{
		while(tokens[i].token != NULL)
		{
			free(tokens[i].token);
			i++;
		}
		free(tokens);
	}
	free(input);
}

void	minishell_loop()
{
	char prompt[12] = "minishell$ ";
	t_tokens *tokens;
	t_shell shell;
	char *input;
	int i = -1;
	shell.tokens_flag = 0;
	rl_initialize();
	using_history();
	while(1)
	{
		input = readline(prompt);
		//check for cd command
		if(input[0] == 'c' && input[1] == 'd' && input[2] == ' ')
		{
			input[ft_strlen(input)] = '\0';
			if(chdir(input + 3) < 0)
				printf("cant cd %s\n",input +3);
		}
		//check empty input
		if(input == NULL || input[0] == '\0')
		{
			printf("empty input\n");
			free(input);
		}
		//exit
		if(strcmp(input, "exit") == 0)
		{
			ft_free(tokens, input, &shell);
			return ;
		}
		else
		{
			add_history(input); //adds history of commands
			tokens = tokenization(input);
			shell.tokens_flag = 1;
			free(input);
			print_tokens(tokens);
			//pwd command
			if(strcmp(&tokens->token[0], "pwd") == 0)
			{
				char cwd[1024];
				if (getcwd(cwd, sizeof(cwd)) != NULL)
				{
					printf("%s\n", cwd);
				}
			}
			// parser(tokens);
		}
	}
}


int main(int argc, char **argv)
{
	//clearwindow();
	minishell_loop();
}
