#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void switchCases(char* message) {
  int i = 0;
  while(message[i] != '\0') {
    if(message[i] > 64 && message[i] < 91) {
      message[i]+=32;
    }
    else if(message[i] > 96 && message[i] < 123) {
      message[i]-=32;
    }
    i++;
  }
}

int main(int argc, char** argv){
  int i=0, fd[2];
  char message[10] = "Hi There";
  
  /*char message[10];
  while(i<10){
    scanf("%c",&message[i]);
    i++;
  }*/
  
    
  // Membuat pipe
    if (pipe(fd) == -1) {
      printf("There was an error in pipe creation. Program will now exit.\n");
      return -1;}
    //menduplikat proses, child
    pid_t child;
    child = fork();
    
    if(child < 0) {
      printf("Forking failed.");
      return -1;
    }
    
    if(child == 0) {
      close(fd[0]);
      switchCases(message);
      write(fd[1],message,10);
    }
    
    //Parent
    else if(child > 0) {
      close(fd[1]);
      char read_buffer[10];
      read(fd[0],read_buffer,10);
      printf("%s",read_buffer);
      
    }
    return 0;
  }
