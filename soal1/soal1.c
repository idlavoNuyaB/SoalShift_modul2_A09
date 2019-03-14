#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <syslog.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int main() {
  pid_t pid,pid_1,sid;
  pid = fork();

  if (pid < 0){
  exit(EXIT_FAILURE);
  }
  if (pid > 0) {
    char *buat[4] = {"mkdir","-p","modul2",NULL};
    execv("/bin/mkdir",buat);
  }
  else {
    pid_1 =fork();
    if (pid_1 > 0){
       char *buatlagi[4] = {"mkdir","-p","modul2/gambar",NULL};
       execv("/bin/mkdir",buatlagi);
    }
    else {
       	umask(0);

  	sid = setsid();

  	if (sid < 0) {
    	exit(EXIT_FAILURE);
  	}

	close(STDIN_FILENO);
  	close(STDOUT_FILENO);
  	close(STDERR_FILENO);

  	while(1) {
    		struct dirent *de;
       		char *temp,*temp2,oldname[30],grey[10],png[10],direct[100],direct2[100];
       		DIR *dr = opendir("/home/arvanna/Pictures");
       		if(dr==NULL)return 0;
       		while((de=readdir(dr))!=NULL){
           		strcpy(direct,"/home/arvanna/Pictures/");
           		strcpy(direct2,"/home/arvanna/modul2/gambar/");
           		temp=strstr(de->d_name,".png");
           		strcpy(png,".png");
           		strcpy(grey,"_grey.png");
           		if(temp){
                		temp2=strtok(de->d_name,".");
                		strcpy(oldname,temp2);
						strcat(oldname,png);
                		strcat(temp2,grey);
                		strcat(direct,oldname);
                		strcat(direct2,temp2);
                		rename(direct,direct2);
                		//printf("%s\n",oldname);
                		//printf("%s\n",temp2);
                		//char *cp[]={"cp",temp2,"/home/arvanna/modul2/gambar",NULL};
                		//execv("/bin/cp",cp);
           		}
       		}
		closedir(dr);
    		sleep(30);
  	} 
  	exit(EXIT_SUCCESS);	
    }
  }
}
