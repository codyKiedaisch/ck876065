#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

void *read_file(void *arg)//have another arg in here for the file so i can use sb
{

/*
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

*/

	printf("New Thread\n");
	return NULL;

}

/*
void *pzip(void *arg)
{
	//zips line segments made in the first thread
	return NULL;
}

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
int st_size=0;
char *file_memory = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		//reads the file so that it can be written over


threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t));//makes equal sized threads?
if(atoi(argv[1])>=2)
{
printf("File size: %ld\n", sb.st_size);
pthread_create(&threads[0], NULL, read_file, NULL);//creates first thread- for reading
}
else
{
//pthread_create(&threads[0], NULL, pzip, NULL);
printf("File size: %ld\n", sb.st_size);
exit(0);
}

//either have pzip threads made in read thread or here, idk yet
//but if its made outside of read it would be here
/*
int i=1;
for(i;i<num_threads-1;i++)
{
pthread_create(&threads[i], NULL, pzip, NULL);
}
*/

int j =0;//might have to change to either 0 or 1 depending on how program goes
for(j;j<num_threads;j++)
{
	pthread_join(threads[j],NULL);//joins threads together
}

printf("Main Thread\n");
close(fd);//closes the file



}
