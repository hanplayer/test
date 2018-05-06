#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
pthread_t tid1,tid2;

void *thread1(void*),*thread2(void*);

int main(int argc,char* argv[])
{
	void *status;
	pthread_create(&tid1,NULL,thread1,NULL);
	sleep(1);
	pthread_create(&tid2,NULL,thread2,NULL);
	
	pthread_join(tid2,&status);
	if(status!=PTHREAD_CANCELED)
	{
		printf("thread2 status = %p\n",status);
	}
	pthread_join(tid1,&status);
	if(status != NULL)
	{
		printf("thread1 status = %p\n",status);
	}
	
	printf("rw_refcount = %d,rw_nwaitreaders = %d,rw_nwaitwriters = %d\n",rwlock.__data.__lock,rwlock.__data.__nr_readers_queued,rwlock.__data.__nr_writers_queued);
	pthread_rwlock_destroy(&rwlock);

	return 0;
}


void *thread1(void *arg)
{
	pthread_rwlock_rdlock(&rwlock);
	printf("thread1() got a read lock\n");
	printf("++rw_refcount = %d,rw_nwaitreaders = %d,rw_nwaitwriters = %d shared = %d\n",rwlock.__data.__lock,rwlock.__data.__nr_readers_queued,rwlock.__data.__nr_writers_queued,rwlock.__data.__shared);
	sleep(3);
	//pthread_cancel(tid2);
	sleep(3);
	pthread_rwlock_unlock(&rwlock);
	printf("----rw_refcount = %d,rw_nwaitreaders = %d,rw_nwaitwriters = %d\n",rwlock.__data.__lock,rwlock.__data.__nr_readers_queued,rwlock.__data.__nr_writers_queued);
	return NULL;
}



void *thread2(void *arg)
{
	printf("thread2() trying to obtain a write lock\n");
	pthread_rwlock_wrlock(&rwlock);
	printf("thread2() got a write lock\n");
	printf("rw_refcount = %d,rw_nwaitreaders = %d,rw_nwaitwriters = %d\n",rwlock.__data.__lock,rwlock.__data.__nr_readers_queued,rwlock.__data.__nr_writers_queued);
	sleep(1);
	pthread_rwlock_unlock(&rwlock);
	printf("rw_refcount = %d,rw_nwaitreaders = %d,rw_nwaitwriters = %d\n",rwlock.__data.__lock,rwlock.__data.__nr_readers_queued,rwlock.__data.__nr_writers_queued);
	return NULL;
}





#if 0
#if defined __USE_UNIX98 || defined __USE_XOPEN2K
/* Data structure for read-write lock variable handling.  The
   structure of the attribute type is not exposed on purpose.  */
typedef union
{
# ifdef __x86_64__
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    unsigned long int __pad1;
    unsigned long int __pad2;
    /* FLAGS must stay at this position in the structure to maintain
       binary compatibility.  */
    unsigned int __flags;
# define __PTHREAD_RWLOCK_INT_FLAGS_SHARED	1
  } __data;
# else
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    /* FLAGS must stay at this position in the structure to maintain
       binary compatibility.  */
    unsigned char __flags;
    unsigned char __shared;
    unsigned char __pad1;
    unsigned char __pad2;
    int __writer;
  } __data;
# endif
  char __size[__SIZEOF_PTHREAD_RWLOCK_T];
  long int __align;
} pthread_rwlock_t;



gdb调试过程中理解到
由上面可知
__writer记录当前写者pthread_id
__nr_readers记录当前读者数量
_nr_writers_queued 写者等待的数量
__nr_readers_queued读者等待的数量
#endif

