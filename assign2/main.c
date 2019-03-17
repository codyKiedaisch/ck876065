/*
* main.c
* (Shell grsh)
* Cody Kiedaisch
*/

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int grsh_cd(char **args);
int grsh_exit(char **args);
int grsh_path(char **args);

//Common error message
char error_message[30] = "An error has occurred\n";

char *builtin_str[] = { "cd", "exit", "path" };
int (*builtin_func[]) (char **) = { &grsh_cd, &grsh_exit, &grsh_path };

int grsh_num_builtins()
{
return sizeof(builtin_str) / sizeof(char *);
}

//Builtin(1)
int grsh_cd(char **args)
{
if (args[1] == NULL)
{
write(STDERR_FILENO, error_message, strlen(error_message));
}
else {
if (chdir(args[1]) != 0)
{
write(STDERR_FILENO, error_message, strlen(error_message));
}
}
return 1;
}

//Builtin(2)
int grsh_exit(char **args)
{
return 0;
}

//Builtin(3)
int grsh_path(char **args)
{
if (args[1] == NULL)
{
write(STDERR_FILENO, error_message, strlen(error_message));
}
else {
if (access("/bin/ls", X_OK) != 0)
{
if (access("/usr/bin/ls", X_OK) !=0)
{
write(STDERR_FILENO, error_message, strlen(error_message));
}
}
}
}


//Runs the process, uses fork(), exec(), and wait()
int grsh_launch(char **args)
{
pid_t pid;
int status;

pid = fork();
if (pid ==0) //Child process
{
if (execvp(args[0], args) == -1)
{
write(STDERR_FILENO, error_message, strlen(error_message));
}
exit(EXIT_FAILURE);
}
else
if (pid < 0) //This shoudnt't happen
{
write(STDERR_FILENO, error_message, strlen(error_message));
}
else {
//Parent process
do {
waitpid(pid, &status, WUNTRACED);
}
while(!WIFEXITED(status) && !WIFSIGNALED(status));
}
return 1;
}


int grsh_file(char *args)
{
int status = 0;
while (status = 0);
{
char *line = NULL;
size_t bufsize = 0;
getline(&line, &bufsize, stdin);
if(STDIN_FILENO == STDERR_FILENO)
{
status = 1;
}
}
exit(0);
}


int grsh_execute(char **args)
{
int i;

//If cmd was empty
if (args[0] == NULL)
{
return 1;
}

//If cmd was a file
if(strstr(args[0], ".") != NULL)
{
if(args[1] != NULL)
{
write(STDERR_FILENO, error_message, strlen(error_message));
}
return grsh_file(args[0]);
}

//If cmd is in builtins
for (i=0; i < grsh_num_builtins(); i++)
{
if (strcmp(args[0], builtin_str[i]) == 0)
{
return (*builtin_func[i])(args);
}
}
//If cmd is not builtin or a file
return grsh_launch(args);
}


//Reads the input
char *grsh_read_line(void)
{
char *line = NULL;
size_t bufsize = 0;
getline(&line, &bufsize, stdin);
return line;
}


#define grsh_tok_BUFSIZE 64
#define grsh_tok_DELIM " \t\n"

//Splits the input into pieces (args)
char **grsh_split_line(char *line)
{
int bufsize = grsh_tok_BUFSIZE, position = 0;
char **tokens = malloc(bufsize * sizeof(char*));
char *token, **tokens_backup;

if(!tokens)
{
write(STDERR_FILENO, error_message, strlen(error_message));
exit(EXIT_FAILURE);
}

token = strtok(line, grsh_tok_DELIM);
while (token != NULL)
{
tokens[position] = token;
position++;

if (position >= bufsize)
{
bufsize += grsh_tok_BUFSIZE;
tokens_backup = tokens;
tokens = realloc(tokens, bufsize * sizeof(char*));

if(!tokens)
{
free(tokens_backup);
write(STDERR_FILENO, error_message, strlen(error_message));
exit(EXIT_FAILURE);
}
}
token = strtok(NULL, grsh_tok_DELIM);
}
tokens[position] = NULL;
return tokens;
}


/*
* Loop for the whole shell and main program
*/

//Loop for everything
void grsh_loop(void)
{
char *line;
char **args;
int status;

do {
printf("grsh> ");
line = grsh_read_line();
args = grsh_split_line(line);
status = grsh_execute(args);

free(line);
free(args);
}
while(status);
}


//Main for the shell
int main(int argc, char **argv)
{
//Run command loop
grsh_loop();
return EXIT_SUCCESS;
}
