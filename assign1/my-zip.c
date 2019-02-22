/*
* my-zip.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EOL 999999

int main (int argc, char *argv[])
{
size_t size = 32
int count= 0;

FILE *fp = fopen("file.txt", "r");
	if(fp == NULL)
	{
	printf("my-zip: cannot open file\n");
	exit(1);
	}
	else
	{
		char buffer[EOL];
		while(getline(&buffer, &size, stdin))
		{
		for(i=0;argv[i]=argv[i+1];i++)
		{
		count++;
		}
		fwrite(const void, *argv[0]+count, size, stdout, FILE *file.txt)
		printf("%s",stdout);
		}
	}
fclose(fp);
exit(0);
}
