#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main() {
  pid_t child_id,child_id2,child_id3;
  int pip[2],stats;
  child_id = fork();
  pipe(pip);
  pipe(pip+2);
  if (child_id < 0) {
    exit(EXIT_FAILURE);
  }

  if (child_id == 0) {
    char *zip[3] = {"unzip", "campur2.zip", NULL};
    execvp(zip[0], zip);
  } 
  else {
    while(wait(&stats)>0);
    child_id2=fork();
    if(child_id2==0){
            dup2(pip[1],1);//write
            close(pip[1]);
            close(pip[0]);
            close(pip[3]);
            close(pip[2]);
            char *see[]={"ls","/home/arvanna/campur2/",NULL};
            execvp(see[0],see);
            
            //printf("t");
    }
    else{
            //wait(NULL);
            child_id3=fork();
            if(child_id3>0){
                    dup2(pip[0],0);
                    dup2(pip[3],1);//write
                    close(pip[3]);
                    close(pip[1]);
                    close(pip[2]);
                    close(pip[0]);
                    char *grab[]={"grep",".txt$",NULL};
                    execvp(grab[0],grab);
                    //printf("hell");       
            }
            else{
                    //wait(NULL);
                    char hasil[1000];
                    close(pip[1]);
                    close(pip[0]);
                    close(pip[3]);
                    read(pip[2],hasil,sizeof(hasil));
                    close(pip[2]);
                    //printf("%s",hasil);
                    FILE *file=fopen("/home/arvanna/modul2/daftar.txt","w+");
                    fputs(hasil,file);
                    fclose(file);          
                    //printf("%d",check);
            }
    }
  }
}
