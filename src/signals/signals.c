#include "../../include/minishell.h"

/* ctrl-C displays a new prompt on a new line. ◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing./*/
void p_signal_handler(int sig)
{
	if(sig == SIGINT)
	{
		write(1,"\n",2);
		signal(SIGINT, p_signal_handler);
	}
}

void signal_handler(int sig)
{
	if(sig == SIGINT)
	{
		write(1,"\n", 2);
		write(1,"msh$ ", 5);
		// signal(SIGINT, signal_handler);
	}
}
