#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;

void *thread_fun(void*)
{
	int count = 0;
	while(true)
	{
		//pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
		cout<<"count:"<<count<<endl;
		count++;
		//pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
		//pthread_testcancel();
		//pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
		cout<<"-------------------------"<<endl;

		cout<<"+++++++++++++++++++++++++"<<endl;
		
	}

}
int main(void)
{
	pthread_t tid;
	pthread_create(&tid,NULL,thread_fun,NULL);
	sleep(2);
	pthread_cancel(tid);
	pthread_join(tid,NULL);
	return 0;
}


