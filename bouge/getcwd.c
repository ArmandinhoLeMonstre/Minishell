#include <unistd.h>
#include <stdio.h> // for printf

int main(void)
{
    char *pwd;
    
    pwd = getcwd(NULL, 0);
    printf("pwd: %s\n", pwd);
    return (0);
}