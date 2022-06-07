#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Usuarios.h"
#define MAX 10

User *logarUser()
{
    User *infoUser;


    infoUser = (User*) calloc(MAX, sizeof(User));

    if (strcmp(infoUser[10].usuario, "\0") != 0)
    {
        printf("ola");
    }
    return infoUser;
}