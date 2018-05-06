#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void my_lock(int fd)
{
#if 1
	struct flock lock;
	
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	

	fcntl(fd,F_SETLKW,&lock);
#endif
}



void my_unlock(int fd)
{
#if 1
	struct flock lock;
	
	lock.l_type = F_UNLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;

	fcntl(fd,F_SETLK,&lock);	
#endif
}


int main(int argc ,char * argv[])
{
	int fd;
	long i,seqno;
	pid_t pid;
	ssize_t n;
	char line[10];
	pid = getpid();
	
	fd = open("tmp.txt",O_RDWR|O_CREAT);
	
	for(int i = 0;i < 20;i++)
	{
		my_lock(fd);
		
		lseek(fd,0L,SEEK_SET);
		n = read(fd,line,10);
		line[n] = '\0';
		n = sscanf(line,"%ld\n",&seqno);
		printf("%s:pid = %ld,#seq = %ld\n",argv[0],(long)pid,seqno);
		seqno++;
		snprintf(line,sizeof(line),"%ld\n",seqno);
		lseek(fd,0L,SEEK_SET);
		write(fd,line,strlen(line));
		
		my_unlock(fd);
	}

	
	return 0;
}












