#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(void)
{

    DIR *dir;
    struct dirent *ls_dir;
    char nome_pasta[100];
    printf("Digite qual a pasta deseja abrir\n");
    scanf("%s", nome_pasta);

    dir = opendir(nome_pasta);

    //dir é o ponteiro para a pasta, q mostra tudo o que tem dentro
    while ( ( ls_dir = readdir(dir) ) != NULL )
    {
        //isso faz imprmir os arquivos que estão dentro da pasta
        printf ("%s\n", ls_dir->d_name);
    }


    closedir(dir);

    return 0;

}