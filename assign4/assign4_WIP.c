#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int main(int argc, char *argv[])
{
pthread_t *threads;//thread descriptor

int num_threads = atoi(argv[1]);


int fd = open(argv[2], O_RDWR, S_IRUSR | S_IWUSR); //start of mmap()
struct stat sb;

if(fstat(fd,&sb == -1)
{
	perror("couldn't get file size\n"); //file couldnt be opened
}
char *file_memory = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		//reads the file so that it can be written over


threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t));//makes equal sized threads?

int i =0;
for(i=0;i<num_threads;i++)
{
pthread_create(&threads[i], NULL, pzip, NULL);//creates threads
//one of the NULLs might have to be replaced with the open file
}

int j =1;//might have to change back to 0 if i run into a problem with the reading
for(j;j<num_threads;j++)
{
pthread_join(threads[j],NULL);//joins threads together
//NULL might have to be replaced with end file
}
printf("Main Thread");
close(fd);//closes the file

void *read(void *arg)
{
int i=1;
for(i;i<num_threads-1;i++)
{
pthread_create(&threads[i], NULL, pzip, NULL);
}
int s= *((int *)arg);
int start(s*st_size)/num_threads;
int end = ((s+1)*st_size)/num_threads;

printf("Thread %d start zipping from %d and ending at %d\n", s, start, end);
return NULL;
}

void *pzip(void *arg)
{
//zips line segments made in the first thread
}

void *write(void *arg)
{
//writes zipped stuff back into file
}
}
