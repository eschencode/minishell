#include "../../include/minishell.h"

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