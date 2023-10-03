#include "../../include/minishell.h"

int tokenization(char *input)
{
	char **split_input;
	split_input = ft_split(input, ' ');
	if(split_input)
	{
		for (int i = 0; split_input[i]; i++)
        {
            printf("Split %d: %s\n", i, split_input[i]);
        }

	}
}