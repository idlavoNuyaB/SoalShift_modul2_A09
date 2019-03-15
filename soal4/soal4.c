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

int main() {
  pid_t pid, sid;
  int flag=1;
  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
     exit(EXIT_SUCCESS);
  }
  else{
      umask(0);
      sid=setsid();
      if(sid<0)exit(EXIT_FAILURE);
      if((chdir("/"))<0)exit(EXIT_FAILURE);
      close(STDIN_FILENO);
      close(STDOUT_FILENO);
      close(STDERR_FILENO);
      while(1){
        char temp[1000],nama[]={"/home/arvanna/Documents/makanan/makan_enak.txt"};
        struct stat info;
        FILE *fil;
        stat(nama,&info);//ngambil informasi dari nama
        time_t akhir=info.st_mtime;//ngecek jika terakhir kali dibuka
        double different=difftime(time(NULL),akhir);//selisih waktu terakhir dibuka dengan waktu sekarang 
        if(different<=30.0){
            char newName[]={"/home/arvanna/Documents/makanan/makanan_sehat"};
            sprintf(temp,"%d",flag);//mengubah flag menjadi temp dalam bentuk string
            strcat(newName,temp);//menggabungkan newname dengan temp
            strcat(newName,".txt");//menggabungkan newname dengan txt
            //printf("%s",newName);
            fil=fopen(newName,"w+");//buat file baru
            fclose(fil);
            flag++;//flag +1
        }
        sleep(5);
      }
      exit(EXIT_SUCCESS);
  }
}
