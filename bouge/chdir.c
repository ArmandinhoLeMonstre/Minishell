#include <unistd.h>
#include <stdio.h> // for printf

int main(void)
{
    char *pwd;
    
    pwd = getcwd(NULL, 0);
    printf("pwd before chdir: %s\n", pwd);
    chdir("/Users/armitite/Cursus/Minishell/bouge");
    pwd = getcwd(NULL, 0);
    printf("pwd after chdir: %s\n", pwd);
    return (0);
}