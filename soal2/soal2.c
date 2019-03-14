#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main()
{
    pid_t pid, sid;

    pid = fork();

    if (pid < 0) {
      exit(EXIT_FAILURE);
    }

    if (pid > 0) {
      exit(EXIT_SUCCESS);
    }
    else{
      umask(0);
      sid = setsid();
      if (sid < 0) {
        exit(EXIT_FAILURE);
      }
      if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
      }
      close(STDIN_FILENO);
      close(STDOUT_FILENO);
      close(STDERR_FILENO);

      while(1) {
        struct dirent *de;
        DIR *dr=opendir("/home/arvanna/modul2/hatiku");
        char nama[10],dir[100]="/home/arvanna/modul2/hatiku/";
        if(dr==NULL)exit(EXIT_FAILURE);
        while((de=readdir(dr))!=NULL){
          strcpy(nama,de->d_name);
          if(strcmp(nama,"elen.ku")==0){
              struct stat info;
	            strcat(dir,nama);
              if(stat(dir,&info)==0){
                  //printf("%d %d %d",info.st_uid,info.st_gid,info.st_mode);
                  //printf("%s",nama);
                  char perm[]="0777";
                  int i=strtol(perm,0,8);
                  chmod(dir,i);
                  struct passwd *owner=getpwuid(info.st_uid);
                  struct group *grup=getgrgid(info.st_gid);
                  //printf("%s %s",owner->pw_name,grup->gr_name);
                  if(strcmp(owner->pw_name,"www-data")==0 && strcmp(grup->gr_name,"www-data")==0){
                        remove(dir);
                      //printf("%s",nama);
                  }
                }
              //printf("%s",nama);
          }
        }
        closedir(dr);
        sleep(3);  
      } 
    }
}      

