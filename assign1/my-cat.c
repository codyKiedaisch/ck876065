/*
* my-cat.c
*/
#include <stdio.h>
#include <stdlib.h>

#define EOL 999999

int main (int argc, char *argv[])
{
for(int i; i<argc; i++)
{
FILE *fp = fopen(argv[i], "r");

	if(fp == NULL)
	{
	printf("my-cat: cannot open file\n");
	exit(1);
	}
	else
	{
	char buffer[EOL];
	while(fgets(buffer,EOL,fp))
	printf("%s",buffer);
	}
}
exit(0);
}

//Cody Kiedaisch
