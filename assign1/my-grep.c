/*
* my-grep.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main (int argc, char *argv[])
{
char *term = NULL;


for(int i=1; i<argc; i++)
{
//if there is no searchterm
if(i ==1)
{
FILE *fp = fopen(argv[1], "r");
if(fp != NULL)
{
printf("my-grep: empty term\n");
break;
}
term = argv[i];
i++;
}


//if file doesnt exist
FILE *fp2 = fopen(argv[i], "r");
if(fp2 ==NULL)
{
printf("my-grep: cannot open file\n");
exit(1);
}


//what prints out the terms found
char line[500];
int matches =0;

while(fgets(line, 500, fp2) !=NULL)
{
if(strstr(line, term) !=NULL)
{
printf("%s", line);
matches++;
}
}
}
exit(0);
}

//Cody Kiedaisch
