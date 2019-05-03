
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
char *file = args->arg3;

//printf("Start- %d\n", start);
//printf("End- %d\n", end);
//printf("File- %d\n", *file);

/*
while(*file[start] != *file[start++])
{
	char *numline[100];
	int count=0;
	for(start;start<end;start++)
	{
		count=1;
		while(file[start] == file[start++])
		{
		numline += file[start];
		count++;
		}

		if(file[start] == '\n')
		{
		printf("|");
		}
		if(file[start] != '|')
		{
		int counts = sprintf(*numline, "%d", count);
		fwrite(&file[start], sizeof(char),1, mmap);
		fwrite(&numline,sizeof(char)*counts,1,mmap);
		}
	}
}
*/
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

//printf("Test.txt: %s\n", file_memory);
//printf("File size: %ld\n", sb.st_size);
int len =(sb.st_size)/num_threads;
//printf("Segment size: %d\n", len);



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
