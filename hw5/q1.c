#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_proc(void *data)
{
    char *str;
    str = (char *)data;
    while (1)
    {
        printf("%s\n", str);
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("usage : labthread1 arg1 arg2", argv[0]);
        return 1;
    }
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_proc, argv[1]);
    pthread_create(&t2, NULL, thread_proc, argv[2]);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}