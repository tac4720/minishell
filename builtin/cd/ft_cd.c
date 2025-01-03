#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//TODO: エラーハンドリングの追加
//TODO: 環境変数の操作 OLDPWD, PWDの更新
//TODO: 相対パスを渡された場合,環境変数を更新するために絶対パスへの変換が必要

int ft_cd(char **args)
{
	if (args[1] == NULL)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	chdir(args[1]);
	return (0);
}

// int main(int argc, char **argv)
// {
// 	ft_cd(argv);
// 	return (0);
// }
