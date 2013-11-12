/* Used just for thread tests in laboratory classes */

#include <threads/thread.h>
#include <stddef.h>
#include <stdio.h>
#include "devices/timer.h"
#include "threads/interrupt.h"

static void thread_test (void *);

void
my_test_create_threads(void)
{
	int i;
	int thread_cnt = 5;

	msg ("Thread \"%s\" begins creating %d threads", thread_current()->name, thread_cnt);
	for (i=0; i<thread_cnt; i++){
		char name[16];
		snprintf (name, sizeof name, "my_thread %d", i);
		thread_create (name, PRI_DEFAULT, thread_test, NULL);
	}
	msg ("Thread \"%s\" finished creating %d threads", thread_current()->name, thread_cnt);

	/* Wait for the previously created threads to finish their execution */
	timer_sleep (1000 + 100);

	msg ("Thread \"%s\" exits its function", thread_current()->name);
}

static void print_thread_info(struct thread* t, void* aux)
{
	printf("Thread \"%s\" info: [name=%s, tid=%d, status=%s]\n", t->name, t->name, t->tid, thread_status(t->status));
}

static void thread_test (void *argv UNUSED){
	msg ("Thread \"%s\" is running.", thread_current()->name);
	print_thread_info(thread_current(), NULL);
}
