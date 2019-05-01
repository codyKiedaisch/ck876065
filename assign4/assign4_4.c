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
int arg3;
};

void *pzip(void *arguments)
{
struct arg_struct *args = arguments;
printf("Start- %d\n", args->arg1);
printf("End- %d\n", args->arg2);
printf("File Size- %d\n", args->arg3);

/*
while((something) !=0)
{
	int count=0;
	for(file_memory[start];file_memory[start]<file_memory[end];start++)
	{
		count=1;
		while(file_memory[start] == file_memory[start+1]
		{
		count++;
		}

		if(file_memory[start] == '\n')
		{
		printf("|");
		}
		if(file_memory[start] != '|')
		{
		int counts = sprintf(numline, "%d", count);
		fwrite(&file_memory[start], sizeof(char),1, mmap);
		fwritee(&numline,sizeof(char)*counts,1,mmap);
		}
	}
}
close(fd);
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

char *file_memory= mmap(NULL,sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd,0);
		//reads the file so that it can be written over

threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t));
struct arg_struct *args = malloc(sizeof(struct arg_struct));

printf("Test.txt: %s\n", file_memory);
printf("File size: %ld\n", sb.st_size);
int len =(sb.st_size)/num_threads;
printf("Segment size: %d\n", len);

for(int i=0;i<num_threads;i++)
{
	args->arg1 =(i*sb.st_size)/num_threads;
	args->arg2 =((i+1)*sb.st_size)/num_threads;
	args->arg3 = sb.st_size;

	pthread_create(&threads[i], NULL, pzip, (void *)&args);
}

for(int j=0;j<num_threads;j++) //threads that join it all together
{
	pthread_join(threads[j], NULL);
}

printf("Main Program\n");
close(fd);

}
