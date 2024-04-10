#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_proc(void *data)
{
    while (1)
    {
        printf("This is thread %d\n", (int)data);
        sleep(1);
    }
}

int num_threads = 10;

int main(int argc, char *argv[])
{
    pthread_t t[num_threads];
    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&t[i], NULL, thread_proc, (void *)i);
    }
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(t[i], NULL);
    }
}