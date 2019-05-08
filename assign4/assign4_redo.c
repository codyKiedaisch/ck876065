
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct arg_struct
{
int arg1;
int arg2;
char *arg3;
}args;

void *pzip(void *arguments)
{
struct arg_struct *args = arguments; //all the numbers keep changing

int start = args->arg1;
int end = args->arg2;

//printf("Start- %d\n", start); //check if start is working
//printf("End- %d\n", end); //check if end is working
//printf("File- %s\n", args->arg3); //check if file came thru


int count =0;
int first =0;
char *numline[500];

while(start!=end)
{
	//printf("Got here");
	if(args->arg3[start] == args->arg3[start+1])
	{
	count++;
		if(first ==0)
		{
		*numline =args->arg3[start];
		first++;
		}
	start++;
	}

	if(args->arg3[start] != args->arg3[start+1])
	{
	start++;
	first=0;
	}

	if(args->arg3[start] == '\n')
	{
	start++;
	}
}
int counts =sprintf(*numline, "%d", count);
fwrite(&args->arg3[start], sizeof(char), 1, stdout);
fwrite(&numline, sizeof(char)*counts, 1, stdout);
return NULL;
}


int main(int argc, char*argv[])
{
pthread_t *threads; //thread descriptor

int num_threads = atoi(argv[1]); //number of threads

int fd;
fd = open(argv[2], O_RDWR, S_IRUSR | S_IWUSR); //start of mmap()
struct stat sb;

if(fstat(fd,&sb) == -1)
{
	perror("couldn't get file size\n"); //file couldnt be opened
}

char *file_memory= mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd,0);
		//reads the file so that it can be written over

threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t));

//printf("Test.txt: %s\n", file_memory); //checks file was opened
//printf("File size: %ld\n", sb.st_size); //checks file size
int len =(sb.st_size)/num_threads;
//printf("Segment size: %d\n", len); //checks math for len



for(int i=0;i<num_threads;i++)
{
struct arg_struct *args = malloc(sizeof(struct arg_struct));
	args->arg1 =i*len;
	args->arg2 =((i+1)*len);
	args->arg3 =file_memory;

	pthread_create(&threads[i], NULL, pzip, (void*)args);
}

for(int j=0;j<num_threads;j++) //joins all threads together
{
	pthread_join(threads[j], NULL);
}

//printf("Main Program\n");
close(fd);

}
