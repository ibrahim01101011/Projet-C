#include "auth.h"
#include <string.h>
#include<stdio.h>
int ajouterAuth(char * filename, auth a )
{

a.espAdmin=1;
    FILE * f=fopen(filename, "a");
    if(f!=NULL)
    {
        fprintf(f,"%d\n",a.espAdmin);
        fclose(f);
        return 1;
    }
    else return 0;
}

int verifyAuth(char username[],char password[]){
int access=0;
auth a;
if ((strcmp(username,"admin")==0)&&(strcmp(password,"0000")==0))
{
int x= ajouterAuth("auth.txt", a );
access=1;

}
if ((strcmp(username,"donneur")==0)&&(strcmp(password,"0000")==0))
{
int x= ajouterAuth("auth.txt", a );
access=2;

}
if ((strcmp(username,"user")==0)&&(strcmp(password,"0000")==0))
{
int x= ajouterAuth("auth.txt", a );
access=3;

}
return access;
}

int verifyAdmin(char filename[]){

int result=0;
    auth a;
a.espAdmin=0;
    FILE * f=fopen(filename, "r");
    if(f!=NULL)
    {
while (fscanf(f,"%d\n",&a.espAdmin)!=EOF){
     
if (a.espAdmin==1){
result=1;
}
    }

}
//remove(filename);
fclose(f);
return result;

}




