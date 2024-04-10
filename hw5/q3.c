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

int main()
{

    switch (fork())
    {
    case -1:
        perror("fork");
        return 1;
    case 0:
    {
        pthread_t t1, t2;
        pthread_create(&t1, NULL, thread_proc, "First thread from parent process");
        pthread_create(&t2, NULL, thread_proc, "Second thread from parent process");
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        break;
    }
    default:
    {
        pthread_t t1, t2;
        pthread_create(&t1, NULL, thread_proc, "First thread from child process");
        pthread_create(&t2, NULL, thread_proc, "Second thread from child process");
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
    }
    }
}