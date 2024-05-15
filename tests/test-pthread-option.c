#include <pthread.h> // for pthread_create, pthread_join, pthread_exit
#include <stdio.h>   // for printf
#include <stdlib.h>  // for exit

#define NITER 100000

void *Count(void *a);

int cnt = 0;

void *Count(void *a)
{
    int i, tmp;
    for (i = 0; i < NITER; i++)
    {
        tmp = cnt;     /* copy the global cnt locally */
        tmp = tmp + 1; /* increment the local copy */
        cnt = tmp;     /* store the local value into the global cnt */
    }
}

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;

    if (pthread_create(&tid1, NULL, Count, NULL))
    {
        printf("\n ERROR creating thread 1");
        exit(1);
    }

    if (pthread_create(&tid2, NULL, Count, NULL))
    {
        printf("\n ERROR creating thread 2");
        exit(1);
    }

    if (pthread_join(tid1, NULL)) /* wait for the thread 1 to finish */
    {
        printf("\n ERROR joining thread");
        exit(1);
    }

    if (pthread_join(tid2, NULL)) /* wait for the thread 2 to finish */
    {
        printf("\n ERROR joining thread");
        exit(1);
    }

    if (cnt < 2 * NITER)
        printf("\n BOOM! cnt is [%d], should be %d\n", cnt, 2 * NITER);
    else
        printf("\n OK! cnt is [%d]\n", cnt);

    pthread_exit(NULL);
    return 0;
}
