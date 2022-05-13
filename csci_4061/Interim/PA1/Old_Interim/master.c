#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

  //degree = 3
  pid_t pid_child;
  for (int i = 0; i < 3; ++i){
    pid_child = fork();
    if (pid_child == 0){
      execl("childprogram.exe", "childprogram.exe", NULL);
      printf("Error executing execl()\n");
      exit(0);
    }
  }

  pid_t terminated_pid;;
  while((terminated_pid = wait(NULL)) > 0) {
    continue;
  }

  printf("[Master] Merge Sort\n");
  
  return(0);
}