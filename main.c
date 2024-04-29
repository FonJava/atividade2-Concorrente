#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PESSOAS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t pessoas_aguardando_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t caixa_liberado_cond = PTHREAD_COND_INITIALIZER;

int queue[NUM_PESSOAS];
int queue_count = 0;
int usando_caixa = 0;
int pessoa_na_fila = 0;

void *espera_na_fila(void *arg) {
  int id = *(int *)arg;
  pthread_mutex_lock(&mutex);
  printf("Pessoa %d: Aguardando na fila.\n", id + 1);
  queue[queue_count++] = id;
  pessoa_na_fila = 1;
  pthread_cond_signal(&pessoas_aguardando_cond);
  sleep(rand() % 3);
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

void *uso_caixa(void *thread_id) {
  int tid = *(int *)thread_id;

  pthread_mutex_lock(&mutex);

  while (pessoa_na_fila == 0) {
    printf("Ninguem na fila, aguardando...\n");
    pthread_cond_wait(&pessoas_aguardando_cond, &mutex);
  }

  while (usando_caixa == 1) {
    printf("Pessoa %d: caixa ocupado\n", tid + 1);
    pthread_cond_wait(&caixa_liberado_cond, &mutex);
  }

  usando_caixa = 1;
  printf("Pessoa %d: Usando o caixa\n", tid + 1);
  sleep(rand() % 5); // Espera simulando o uso do caixa
  queue[queue_count--] = tid;
  printf("Pessoa %d: Liberando o caixa\n", tid + 1);
  usando_caixa = 0;

  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&caixa_liberado_cond);

  pthread_exit(NULL);
}

int main(void) {
  pthread_t pessoas[NUM_PESSOAS];
  pthread_t caixa[NUM_PESSOAS];

  srand(time(NULL));

  for (int i = 0; i < NUM_PESSOAS; i++) {
    int *tid = malloc(sizeof(int));
    *tid = i;
    pthread_create(&caixa[i], NULL, uso_caixa, (void *)tid);
  }

  for (int i = 0; i < NUM_PESSOAS; i++) {
    int *id = malloc(sizeof(int));
    *id = i;
    pthread_create(&pessoas[i], NULL, espera_na_fila, (void *)id);
  }

  for (int i = 0; i < NUM_PESSOAS; i++) {
    pthread_join(pessoas[i], NULL);
  }

  for (int i = 0; i < NUM_PESSOAS; i++) {
    pthread_join(caixa[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&pessoas_aguardando_cond);
  pthread_cond_destroy(&caixa_liberado_cond);
  return 0;
}