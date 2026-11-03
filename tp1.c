#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define N 2    // nombre de clients
#define M 1000 // nombres de places
volatile int NombrePlaces = M;
bool flag[N];
int turn = 0;
void ES(int id) {
  flag[id] = true;
  turn = 1 - id;
  while (flag[1 - id] && turn == 1 - id) {
  };
}
void RS(int id) { flag[id] = false; }
void *worker(void *arg) {
  int id = *(int *)arg; // cast  to integer
  int NombreTickets = 0;
  int delai_ms = rand() % 1000;
  ES(id);
  while (NombrePlaces > 0) {
    NombrePlaces--;
    usleep(delai_ms);
    NombreTickets++;
    ES(id);
  }
  RS(id);
  printf("Client %d a acquis %d tickets.\n", id, NombreTickets);
  return NULL;
}
int main() {
  srand(time(NULL));
  pthread_t threads[N]; // 2 threads
  int ids[N];           // as  number of process 2
  for (int i = 0; i < N; i++) {
    ids[i] = i;
    pthread_create(&threads[i], NULL, worker, &ids[i]);
    // for thread creation
  }
  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL); // yasana bach ykhals
  }
  // program will be stoped after all threads end , not before
  return 0;
}
