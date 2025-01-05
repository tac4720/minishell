#include <linux/limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ft_pwd(char **args)
{

	if (args[2] != NULL) 
  	{
		return (1);
  	}
  char *buff = malloc(PATH_MAX);
  char *path = getcwd(buff, PATH_MAX);
  printf("%s\n", path);
  free(path);
  return 0;
}

// int main(int argc, char **argv)
// {
//   ft_pwd(argv);
// }
