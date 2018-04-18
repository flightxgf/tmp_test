#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#include <pthread.h>
#include <unistd.h>


static pthread_t tid1;


/* ��������ֵ��� */
static void check_result(char* str,int result)
{
    if (0 == result)
    {
	 rt_kprintf("%s successfully!\n",str);
    }
    else  {
	rt_kprintf("%s failed! error code is %d\n",str,result);
	}    
}

/* �߳���ں���*/
static void* thread_entry1(void* parameter)
{
    int count = 0;
    int no = (int) parameter; /* ����̵߳���ڲ��� */

	//rt_signal_unmask(2);
	rt_thread_kill(tid1, 2);
	//rt_signal_mask(2);
	while (1) {
    rt_kprintf("\n\n");
	rt_kprintf("thread%d count: %d-------------\n", no, count ++);
	rt_thread_delay(RT_TICK_PER_SECOND*10);
//	rt_signal_unmask(2);
	//rt_thread_kill(tid1, 2);
	}
    return NULL;
}

void handler(int sig)
{
	rt_kprintf("[sig] = %d\n",sig);
} 



int signal_sample_init(void)
{
	int result;
	rt_signal_install(2, handler);	

    /* �����߳�1, ����ΪĬ��ֵ����ں�����thread_entry����ں���������1 */
	result = pthread_create(&tid1,NULL,thread_entry1,(void*)1);
    check_result("thread1 created", result);
	//rt_thread_kill(tid1, 2);
	
	return 0;
}
INIT_APP_EXPORT(signal_sample_init);









