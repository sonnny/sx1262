//process.c
//expects commands
// FW4, FW3, FW2, FW1, STOP, BACK, LEFT, RIGHT
#include "process.h"

#define MINIMUM_SPEED 1500

void process_string(char *str){
  char* data = str;
  char command[10];
  char args[10];
  strcpy(command,strtok(data," "));
  strcpy(args,strtok(NULL," "));
  if(strcmp(command,"FW1") == 0) forward(MINIMUM_SPEED);
  else if (strcmp(command,"FW2") == 0)    forward(MINIMUM_SPEED  + 750);
  else if (strcmp(command,"FW3") == 0)    forward(MINIMUM_SPEED + 1500);
  else if (strcmp(command,"FW4") == 0)    forward(MINIMUM_SPEED  + 2250);
  else if (strcmp(command,"STOP") == 0)   stop();
  else if (strcmp(command,"BACK") == 0)   reverse(MINIMUM_SPEED);
  else if (strcmp(command,"LEFT") == 0)   servo_left();
  else if (strcmp(command,"CENTER") == 0) servo_center();
  else if (strcmp(command,"RIGHT") == 0)  servo_right();  
  sleep_ms(10);
}
