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
	if (ft_strncmp(shell->input_str, "exit", ft_strlen("exit")) == 0 || \
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
	if (shell->input_str == NULL || shell->input_str[0] == '\0' \
	|| count_quotes(shell->input_str) % 2 != 0 || validate_input_str(shell) == 1)
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
	add_path_to_hist(shell);
}

void	minishell_loop(t_shell *shell)
{
	char prompt[6] = "msh$ ";
	shell->input_str = readline(prompt);
	if (shell->input_str == NULL || eval_exit_loop(shell, shell->tokens))
		return ;
	if (eval_input_error(shell) == 0)
	{
		if (shell->tokens != NULL)
			ft_free_tokens(shell->tokens);
		add_history(shell->input_str);
		run_expanders(shell);
		shell->tokens = tokenization(shell, shell->input_str);
		parser(shell);
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
		rl_redisplay();
	}
}

void eof_handler(int sig)
{
	if (sig == SIGTERM)
		exit(0);
}

void sigs_init(struct sigaction *sa_int, struct sigaction *sa_eof)
{
	sa_int->sa_handler = sigint_handler;
    sigemptyset(&sa_int->sa_mask);
    sa_int->sa_flags = 0;

	sa_eof->sa_handler = eof_handler;
    sigemptyset(&sa_eof->sa_mask);
    sa_eof->sa_flags = 0;

	sigaction(SIGINT, sa_int, NULL);
	sigaction(SIGTERM, sa_eof, NULL);
}

// run on signal code 1, exit on signal code 0
int main()
{
	t_shell shell;
	struct sigaction sa_int;
	struct sigaction sa_eof;
	shell.loop_exit = 0;

	sigs_init(&sa_int, &sa_eof);
	minishell_init(&shell);

	while (shell.loop_exit == 0)
		minishell_loop(&shell);
}
