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




