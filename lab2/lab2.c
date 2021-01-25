#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

pthread_t providerThread, consumerThread;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


int thread_args[2];
int ready = 0; int rc;

void handle(int r)
{
  pthread_cancel(providerThread);
  pthread_cancel(consumerThread);
  rc = pthread_join(providerThread, NULL);
  rc = pthread_join(consumerThread, NULL);
  exit(0);
}

void* provider(void *args)
{
  while (true)
  {
    pthread_mutex_lock(&lock);
    if (ready)
    {
      pthread_mutex_unlock(&lock);
      continue;
    }
    ready = 1;
    printf("Message sended \n");
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    sleep(1);
  }
  return NULL;
}

void* consumer(void *args)
{
  while (true)
  {
    pthread_mutex_lock(&lock);
    while(!ready)
    {
      pthread_cond_wait(&cond, &lock);
    }
    ready = 0;
    printf("Message received\n");
    pthread_mutex_unlock(&lock);
  }

  return NULL;
}

int main()
{
  signal(SIGINT, handle);

  thread_args[0] = 0;
  thread_args[1] = 1;
  rc = pthread_create(&providerThread, NULL, &provider, &thread_args[0]);
  rc = pthread_create(&consumerThread, NULL, &consumer, &thread_args[1]);

  while(true){};
  return 0;
}


