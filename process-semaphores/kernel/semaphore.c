#include "types.h"
#include "param.h"
#include "riscv.h"
#include "spinlock.h"
#include "defs.h"

typedef struct semaphore_struct {
  int value;
  struct spinlock lock;
}semaphore;

semaphore sems_array[MAXSEMS];

void 
init_semaphores(void)
{
  for(unsigned int i = 0; i < MAXSEMS; i++){;
    sems_array[i].value = DEFVALUE;
    initlock(&(sems_array[i].lock), "sem");
  }
}

int
sem_open(int sem, int value)
{
  if (sem >= MAXSEMS || sem < 0) {
    printf("Valor de semaforo unvalido\n");
    return 0;
  }

  char val = 0;

  acquire(&(sems_array[sem].lock));

  if (sems_array[sem].value == -1) {
    sems_array[sem].value = value;
    val = 1;
  }

  release(&(sems_array[sem].lock));

  return val;
}

int 
sem_down(int sem)
{
  if (sem < 0 || sem >= MAXSEMS){
    return 0;
  }
  acquire(&sems_array[sem].lock);
  while(sems_array[sem].value == 0){
    sleep(&sems_array[sem], &sems_array[sem].lock);
  }
  sems_array[sem].value--; 
  release(&sems_array[sem].lock);
  return 1;
}

int
sem_up(int sem)
{
  if (sem < 0 || sem >= MAXSEMS){
    return 0;
  }
  acquire(&sems_array[sem].lock);

  if(sems_array[sem].value == 0){
    wakeup(&sems_array[sem]);
  }
  sems_array[sem].value++; 
  release(&sems_array[sem].lock); 
  return 1;
}

int
sem_en(int value)
{
  int sem = 0;
  while (sem < MAXSEMS && !sem_open(sem, value)) {
    ++sem;
  }
  return (sem == MAXSEMS) ? -1 : sem;
}

int
sem_close(int sem)
{
  if (sem >= MAXSEMS || sem < 0) {
    printf("Valor de semaforo invalido\n");
    return 0;
  }
  semaphore *sem_ptr = &sems_array[sem];
  char val = 0;
  acquire(&(sems_array[sem].lock));
  if (sem_ptr -> value != -1) {
    sem_ptr -> value = -1;
    val = 1;
    wakeup(sem_ptr);
  }else {
    val = 0;
  }
  release(&(sems_array[sem].lock));
  return val;
}
