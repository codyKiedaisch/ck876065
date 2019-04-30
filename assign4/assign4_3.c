#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

/*
void *read_file(void *arg)//have another arg in here for the file so i can use sb
{

	//gotta get this into a loop that makes seperate line segments from the file for pzip
	//correctly divides file into line segments based on the size of the file/num_threads
	int s= *((int *)arg);
	int start= (s*st_size)/num_threads;//start of line
	int end= ((s+1)*st_size)/num_threads;//end of line
	//somehow ive gotta get each thread to zip different line segments from file

	int i=1;
	for(i;i<num_threads-1;i++)
	{
	pthread_create(&threads[i], NULL, pzip, NULL);
	}
	printf("Thread %d start zipping from %d and ending at %d\n", s, start, end);



	printf("New Thread\n");
	return NULL;

}
*/


void *pzip(void *arguments)
{
	//struct arg_struct *args= arguments;
	//printf("Starting value: %d\n", args.arg1);
	//printf("End value: %d\n", args.arg2);
	//zips line segments made in the first thread
	printf("New Thread\n");
	return NULL;
}

/*
void *write(void *arg)
{
	//writes zipped stuff back to file
	//have pzip send zipped segments to the thread using write
	//use file_memory to save back into file
	return NULL;
}
*/


int main(int argc, char *argv[])
{
pthread_t *threads;//thread descriptor

int num_threads = atoi(argv[1]);//might want to add 1or2 if i make a read/write thread

int fd;
fd = open(argv[2], O_RDWR, S_IRUSR | S_IWUSR); //start of mmap()
struct stat sb;

if(fstat(fd,&sb) == -1)
{
	perror("couldn't get file size\n"); //file couldnt be opened
}
char *file_in_memory = mmap(NULL,sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		//reads the file so that it can be written over

printf("Test.txt: %s\n", file_in_memory);
threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t));//makes equal sized threads?

printf("File size: %ld\n", sb.st_size);
int len =(sb.st_size)/num_threads;
printf("Length of segments: %d \n", len);

/*
int a=0;
struct arg_struct *args = malloc(sizeof(struct arg_struct));
for(a;a<sb.st_size;a+len)
{
args->arg1=a;
args->arg2=a+len;
*/
for(int i=0;i<num_threads;i++)
{
	pthread_create(&threads[i], NULL, pzip, NULL);
}
//}


for(int j=0;j<num_threads;j++)
{
	pthread_join(threads[j],NULL);//joins threads together
}


printf("Main Thread\n");
close(fd);//closes the file



}
