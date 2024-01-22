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
	int i = -1;
	if (shell->tokens != NULL)
	{
		while(tokens[++i].token != NULL)
			free(tokens[i].token);
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
	if (shell->input_str == NULL || \
	ft_strncmp(shell->input_str, "exit", ft_strlen("exit")) == 0 || \
	ft_strncmp(shell->input_str, "q", ft_strlen("q")) == 0)
	{
		ft_free_all(tokens, shell);
		shell->loop_exit = 1;
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
	if (shell->input_str[0] == '\0' \
	|| count_quotes(shell->input_str) % 2 != 0 \
	|| validate_input_str(shell) == 1)
	{
		free(shell->input_str);
		return (1);
	}
	return (0);
}

void minishell_init(t_shell *shell)
{
	shell->tokens = NULL;
	rl_initialize();
	using_history();
	env_init(shell);
	shell->cd_last_path = NULL;
	shell->path = NULL;
	shell->exe_path = NULL;
	shell->exit_code = 0;
	add_path_to_hist(shell);
}

int syntaxchecker_onlyretoken(t_shell *shell)
{
	if(shell->num_tokens == 1 && (shell->tokens[0].type == RIGHT || shell->tokens[0].type == RIGHT_RIGHT ||shell->tokens[0].type == LEFT || shell->tokens[0].type == LEFT_LEFT))
	{
		printf("syntax error\n");
		return(1);
	}
	else 
		return(0);
}

int exit_check(t_shell *shell)
{
	int i =0;
	if(!(ft_strncmp(shell->input_str, "exit", ft_strlen("exit")) == 0))
		return(0);
	if(shell->num_tokens > 2)
	{
		printf("to mamy arguments for exit\n");
		return(1);
	}	
	if(shell->num_tokens == 2)
	{
		while(shell->tokens[1].token[i] != '\0')
		{
			if(!ft_isdigit(shell->tokens[1].token[i]))
			{
				printf("exit only takes numeric arguments\n");
				return(1);
			}
			i++;
		}
		exit(ft_atoi(shell->tokens[1].token));
	}
	else
	{
		
		exit(0);
	}
	return(1);
}

void	minishell_loop(t_shell *shell)
{
	char prompt[6] = "msh$ ";
	shell->input_str = readline(prompt);
	if (eval_input_error(shell) == 0)
	{
		if (shell->tokens != NULL)
			ft_free_tokens(shell->tokens);
		add_history(shell->input_str);
		run_expanders(shell);
		tokenization(shell, shell->input_str);
		if (exit_check(shell) == 1)
			return;
		if (syntaxchecker_onlyretoken(shell) == 1)
			return;
		// print_tokens(shell->tokens);
		parser(shell);
		// print_clist(shell);
		executor(shell);
		ft_free_clist(shell);
		free(shell->input_str);
	}
}

void sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void sigquit_handler(int sig)
{

	if (sig == SIGQUIT)
	{
		 // Move the cursor to the beginning of the line
        write(1, "\r", 1);
        // Clear the line
        write(1, "\033[K", 3);
        // Reprint the line
        printf("msh$ %s", rl_line_buffer);
        // Move readline's cursor to the end of the line
        rl_point = rl_end;
	}
}

void sigs_init(struct sigaction *sa_int, struct sigaction *sa_quit)
{
	sa_int->sa_handler = sigint_handler;
	sigemptyset(&sa_int->sa_mask);
	sa_int->sa_flags = 0;
	sigaction(SIGINT, sa_int, NULL);

	sa_quit->sa_handler = sigquit_handler;
	sigemptyset(&sa_quit->sa_mask);
	sa_quit->sa_flags = 0;
	sigaction(SIGQUIT, sa_quit, NULL);
}

int main()
{
	t_shell shell;
	struct sigaction sa_int;
	struct sigaction sa_quit;
	shell.loop_exit = 0;

	sigs_init(&sa_int, &sa_quit);
	minishell_init(&shell);

	while (shell.loop_exit == 0)
		minishell_loop(&shell);
}
