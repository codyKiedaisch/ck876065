/*
* my-grep.c
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
char pat[10], temp[200]
FILE *fp = fopen("bar.txt", "r");
	if(fp == NULL)
	{
	printf("my-grep: cannot open file\n");
	exit(1);
	}
	pat = "foo";
	else
	{
	while(!feof(fp)
	{
	fgets(temp,1000,fp);
	if(strstr(temp,pat))
	   printf("%s",temp);
	}
	}
fclose(fp);
exit(0);
}
