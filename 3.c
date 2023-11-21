#include <stdio.h>

int main(int ac, char **argv)
{
	int i = 0;
	while(argv[1][i])
	{
		printf("%s,\n",argv[1][i]);
		i++;
	}
}