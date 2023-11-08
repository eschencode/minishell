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

void ft_free_tokens(t_tokens *tokens)
{
	int i = 0;
		while(tokens[i].token != NULL)
		{
			free(tokens[i].token);
			i++;
		}
	free(tokens);
}

void ft_free_all(t_tokens *tokens, t_shell *shell)
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
	free(shell->input_str);
}

void	minishell_loop()
{
	char prompt[12] = "minishell$ ";
	t_tokens *tokens;
	t_shell shell;
	//char *shell.input_str;
	int i = -1;
	shell.tokens_flag = 0;
	rl_initialize();
	using_history();
	while(1)
	{
		shell.input_str = readline(prompt);
		//check for cd command
		cd(shell);
		//check empty shell.input_str
		if (shell.input_str == NULL || shell.input_str[0] == '\0')
		{
			printf("empty input\n");
			free(shell.input_str);
		}
		//exit
		else if (strcmp(shell.input_str, "exit") == 0)
		{
			ft_free_all(tokens, &shell);
			return ;
		}
		else
		{
			if (shell.tokens_flag)
				ft_free_tokens(tokens);
			add_history(shell.input_str); //adds history of commands
			tokens = tokenization(shell.input_str);
			shell.tokens = tokens;
			shell.tokens_flag = 1;
			//pwd command
			if(strcmp(&tokens->token[0], "pwd") == 0)
			{
				char cwd[1024];
				if (getcwd(cwd, sizeof(cwd)) != NULL)
				{
					printf("%s\n", cwd);
				}
			}
			checker(&shell);
			// print_tokens(shell.tokens);
		}
	}
}


int main(int argc, char **argv)
{
	signal(SIGINT, signal_handler);
	//clearwindow();
	minishell_loop();
}
