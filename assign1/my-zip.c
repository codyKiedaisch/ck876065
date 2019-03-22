/*
* my-zip.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EOL 999999;

int main (int argc, char *argv[])
{

char *line =NULL;
char numline[500];
int read;
size_t len =0;

for(int i =1; i<argc; i++)
{
FILE *fp = fopen(argv[i], "r");

if(fp ==NULL)
{
exit(1);
}

while((read =getline(&line, &len, fp)) != -1)
{
int count;
for(int a =0; a< read; a++)
{
count =1;
while(line[a] == line[a+1])
{
count++;
a++;
}

if(line[a] == '\n')
{
printf("|");
}
if(line[a] != '|')
{
int counts = sprintf(numline, "%d", count);
fwrite(&numline, sizeof(char)*counts,1, stdout);
fwrite(&line[a], sizeof(char), 1, stdout);
}
}
}
fclose(fp);
}
exit(0);
}

//Cody Kiedaisch
