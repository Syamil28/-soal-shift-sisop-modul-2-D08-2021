#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>


void folder(char *foldername){
  if(fork()==0){  
    char *makedir[] = {"mkdir", "-p",foldername, NULL};
    execv("/bin/mkdir", makedir);
  }   
}

void downloader(char *foldername){
  time_t rawtime;
  int i,size;
  char pic_name[204],buffer[100],url[100];

  for(i=0;i<10;i++){
      time(&rawtime);
      strftime(buffer, 100, "%Y-%m-%d_%X", localtime(&rawtime));
        
      sprintf(pic_name,"%s/%s.jpg",foldername,buffer);
      size = (int)time(NULL);
      size = (size%1000)+50;
      sprintf(url,"https://picsum.photos/%d",size);

      if(fork()==0){
          char *getpic[] = {"wget", "-qO", pic_name, url, NULL};
          execv("/usr/bin/wget", getpic);
      }
        sleep(5);
    }
}

void message(char *foldername){
  char dir[100];
  char message[25] = {"Download Success"};
  char temp;
  int i;
  int shift;

  strcpy(dir, foldername);
  strcat(dir, "/");
  strcat(dir, "status.txt");
  FILE *status = fopen(dir, "w");

  for(i = 0; i<strlen(message);i++){
    temp = message[i];
    if(temp>='a'&&temp<='z'){
      temp += shift;

      if(temp > 'z'){
        temp+=('a'-'z');
      }else if(temp<'a'){
        temp+=('z'-'a');
      }

    }

    if(temp>='A'&&temp<='Z'){
      temp += shift;

      if(temp > 'Z'){
        temp+=('A'-'Z');
      }else if(temp<'A'){
        temp+=('Z'-'A');
      }

    }
    fputc(temp, status);
  }
  fclose(status);
  
}

void archive(char *foldername){
  char temp[100];
  if(fork()==0){
    strcpy(temp, foldername);
    strcat(temp, ".zip");
    char *argv[] = {"zip", temp, "-rm", foldername, NULL};
    execv("/bin/zip", argv);
  }  
}



void killer(char const *argv[], int pid){
  FILE *killer = fopen("killer.sh", "w");
  fprintf(killer,"#!/bin/bash\n");
  if(strcmp(argv[1],"-z") == 0){
      fprintf(killer,"killall -9 %s\n",argv[0]);
  }
  else if(strcmp(argv[1],"-x") == 0){
      fprintf(killer,"kill -15 %d\n",pid);
  }
    
  fprintf(killer,"rm killer.sh\n");
  fclose(killer);
  // if(fork()==0){
  //   char *exc[] = {"chmod", "+x", "killer.sh", NULL};
  //   execv("/bin/chmod", exc);
  // }
}

int main(int argc, char const *argv[]) {
  pid_t pid, sid;        // Variabel untuk menyimpan PID
  char foldername[100];
  time_t rawtime;

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  // if ((chdir("/")) < 0) {
  //   exit(EXIT_FAILURE);
  // }

  killer(argv,(int)getpid());

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    // Tulis program kalian di sini
    time(&rawtime);
    strftime(foldername, 100, "%Y-%m-%d_%X", localtime(&rawtime));
    folder(foldername);   
    downloader(foldername);
    message(foldername);
    archive(foldername);     
    sleep(40);    
  }
}

