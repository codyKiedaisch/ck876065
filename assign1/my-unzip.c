/*
* my-zip.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t size = 32;
int x =0;

int main (int argc, char *argv[])
{
FILE *fp = fopen("file.txt", "r");
	if(fp == NULL)
	{
	printf("my-unzip: cannot open file\n");
	exit(1);
	}
	else
	{
		while(getline(&buffer, &size, stdin))
		{
		for(i=1;argv[i]<size;i++)
		{
		i++;
		for(j=0;j<=i;j++)
		{
		j++;
		printf(argv[x], stdout);
		}
		x+2;
		}
		}
	}
fclose(fp);
exit(0);
}
