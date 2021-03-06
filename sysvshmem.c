/*
  Demonstration of System V shared memory system calls

  Jim Teresco, The College of Saint Rose, Spring 2016

  $Id$
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

typedef struct {
  char message[80];
  int number;
} shared_data;

int main(int argc, char *argv[]) {
  
  pid_t pid;
  int status;
  int segment_id;
  shared_data *data;

  // allocate shared memory
  segment_id = shmget(IPC_PRIVATE, sizeof(shared_data), SHM_R|SHM_W);

  // attach to shared memory
  data = (shared_data *)shmat(segment_id, NULL, 0);
  strcpy(data->message, "Before fork");
  data->number = 0;

  // fork the child
  pid = fork();
  if (pid) {
    // child will print the old values, modify them
    printf("Original message: <%s>, number: %d\n", data->message,
	   data->number);
    strcpy(data->message, "The kid was here!");
    data->number = 17;

    exit(0);
  }
  else {
    // parent
    wait(&status);

    printf("After child message: <%s>, number: %d\n", data->message,
	   data->number);

    /* detach from shared memory segment */
    shmdt(data);
    
    /* free shared memory segment */
    shmctl(segment_id, IPC_RMID, NULL);
  }
  return 0;
}
