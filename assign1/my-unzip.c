/*
* my-unzip.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define EOL 999999

void printOutput(int num, char character)
{
int count =0;
while(count < num)
{
printf("%c", character);
count++;
}
}

char writeOut(int x, int y)
{
unsigned pow =10;
while(y>= pow)
pow*= 10;
return x * pow +y;
}

int main(int argc, char *argv[])
{
for(int i =1; i<argc; i++)
{
FILE *fp = fopen(argv[i], "r");
if(fp == NULL)
{
exit(1);
}

char c, num, num2;
int sum;
bool numberTF = false;
while((c =fgetc(fp)))
{
if(c==EOF)
{
break;
}

if(isdigit(c))
{
if(numberTF)
{
numberTF = false;
num2 = c;
sum = writeOut(num - '0', num2 - '0');
}
else
{
num = c;
numberTF = true;
}
}

else if(isalpha(c))
{
if(!numberTF)
{
printOutput(sum,c);
}
numberTF = false;
printOutput(num - '0', c);
}
else if(c == '|')
{
printf("\n");
}
else if(c == ' ')
{
printf(" ");
}
}
fclose(fp);
}
return 0;
}

//Cody Kiedaisch
