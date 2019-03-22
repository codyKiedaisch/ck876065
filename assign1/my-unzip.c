/*
* my-unzip.c
*/



//change method names
//put my name on it so it looks normal
//turn in at end of semester


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char cat1(int x, int y)
{
unsigned pow = 10;
while(y>= pow)
pow *= 10;
return x * pow +y;
}


void printOutput(int num, char character)
{
int count =0;
while(count < num)
{
printf("%c", character);
count++;
}
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
sum = cat1(num - '0', num2 - '0');
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
