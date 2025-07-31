//process.c

#include "process.h"

void process_string(char *str){
  char* data = str;
  char command[10];
  char args[10];
  strcpy(command,strtok(data," "));
  strcpy(args,strtok(NULL," "));
  printf("command: %s\r\n",command);
  printf("args: %s\r\n\n",args);
  sleep_ms(1500);
}
