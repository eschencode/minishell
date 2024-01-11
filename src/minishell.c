#include "../include/minishell.h"

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

void free_double_str(char **str)
{
	int y;
	y = -1;
	while (str[++y])
		free(str[y]);
}

void ft_free_clist(t_shell *shell)
{
	t_clist **tracer;
	t_clist *old_node;

	tracer = &shell->clist;
	while (*tracer)
	{
		old_node = *tracer;
		*tracer = (*tracer)->next;
		free_double_str(old_node->cmd);
		free(old_node->cmd);
		free(old_node);
	}
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
	free_env(shell);
	if (shell->cd_last_path)
		free(shell->cd_last_path);
	if (shell->exe_path)
		free(shell->exe_path);
	if (shell->path)
		free(shell->path);
}

void env_init(t_shell *shell)
{
	int y;
	int len;
	extern char **environ;

	len = 0;
	while (environ[len])
		len++;
	shell->env = malloc(sizeof(char *) * (len + 1));
	y = -1;
	while (environ[++y])
		shell->env[y] = ft_strdup(environ[y]);
	shell->env[y] = NULL;
}

int eval_exit_loop(t_shell *shell, t_tokens *tokens)
{
	if (ft_strncmp(shell->input_str, "exit", ft_strlen("exit")) == 0 || \
	ft_strncmp(shell->input_str, "q", ft_strlen("q")) == 0)
	{
		ft_free_all(tokens, shell);
		return (1);
	}
	return (0);
}

int validate_input_str(t_shell *shell)
{
	int x;
	char *str;


	str = shell->input_str;
	x = -1;

	while(str[++x])
	{
		if (str[x] != ' ' && str[x] != '\t')
			return (0);
	}
	return (1);
}

int eval_input_error(t_shell *shell)
{
	if (shell->input_str == NULL || shell->input_str[0] == '\0' \
	|| count_quotes(shell->input_str) % 2 != 0 || validate_input_str(shell) == 1)
	{
		free(shell->input_str);
		return (1);
	}
	return (0);
}

void	minishell_loop()
{
	char prompt[12] = "msh$ ";
	t_tokens *tokens;
	t_shell shell;
	shell.tokens_flag = 0;
	rl_initialize();
	using_history();
	env_init(&shell);
	shell.cd_last_path = NULL;
	shell.path = NULL;
	shell.exe_path = NULL;
	shell.exit_code = 0;
	add_path_to_hist(&shell);
	while(1)
	{
		shell.input_str = readline(prompt);
		if (shell.input_str == NULL)
			return ;
		if (eval_exit_loop(&shell, tokens))
			return ;
		if (eval_input_error(&shell) == 0)
		{
			if (shell.tokens_flag)
				ft_free_tokens(tokens);
			add_history(shell.input_str); //adds history of commands
			tilde_expander(&shell);
			if (strstr(shell.input_str, "\"") != NULL || strstr(shell.input_str, "\'") != NULL)
				expander_quotes(&shell);
			tokens = tokenization(&shell, shell.input_str);
			shell.tokens = tokens;
			shell.tokens_flag = 1;
			checker(&shell);
			parser(&shell);
			ft_expander(&shell);
			executor(&shell);
			ft_free_clist(&shell);
			free(shell.input_str);
			// free(shell.path);
		}
	}
}

int main()
{
	signal(SIGINT, signal_handler);
	//clearwindow();
	minishell_loop();
}
