#include "minishell.h"

void	check_open_close(char *line)
{
    int i;
    int quote;

    i = 0;
    while (line && line[i])
	{
        if (line[i] == '\'' || line[i] == '\"')
        {
            quote = line[i];
            (i)++;
            while (line[i] && line[i] != quote)
            {
                (i)++;
                if (line[i] == '\0')
                {
                    printf("unclosed quote\n");
                    exit(-1);//unclosed quoteによるエラー

                }
            }
        }
        else
        {
            i++;
        }
	}
}