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
#define Size 50 

int main(int argc, char* argv[])
{
    pid_t pid = 0;
    pid_t sid = 0;
    char al[50]; //inisialisasi variable temporal
    char ax[50]; //inisialiasasi variable temporal
    int i=0;    //inisialisasi variable buat loop

    int k; //inisialisasi variable peubah log#.log
    time_t t ; //inisialisasi time struct
    struct tm *tmp ; //inisialisasi time struct
    char MY_TIME[Size]; // inisialisasi string hasil output struct yang diinginkan untuk folder
    char c;//inisialisasi char c
    char loca[100]="log/"; //inisialisasi string untuk lokasi
    char filename[100]="/var/log/syslog"; //inisialisasi tempat syslog yang akan diambil
    FILE *fptr1, *fptr2, *fptr3;  //inisialisasi file yang akan dibuka
    time( &t );  //pengambilan waktu menggunakan fungsi time()
   
    mkdir("log", 0700); //pembuatan directory log
    //localtime() uses the time pointed by t , 
    // to fill a tm structure with the  
    // values that represent the  
    // corresponding local time. 
      
    tmp = localtime( &t ); //hasil waktu disimpan pada struct
      
    // using strftime to display time 
    
      
    pid = fork();// fork a new child process


    if (pid < 0)
    {
        printf("fork failed!\n");
        exit(1);
    }

    if (pid > 0)// its the parent process
    {
       printf("pid of child process %d \n", pid);
       fptr3 = fopen("nomerpid.txt", "w");
       fprintf(fptr3, "%d", pid);
       fclose(fptr3); 
        exit(0); //terminate the parent process succesfully
    }

    umask(0);//unmasking the file mode

    sid = setsid();//set new session
    if(sid < 0)
    {
        exit(1);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);


    //looping program utama
    while(1){
    strcpy(loca, "log/"); //untuk mengembalikan string loca menjadi "log/"
    time( &t ); //pengambilan waktu baru untuk proses yang berjalan
    tmp = localtime( &t ); 
    strftime(MY_TIME, sizeof(MY_TIME), "%d:%m:%Y:%H:%M", tmp); //pengambilan output dari struct 
    strcat(loca,MY_TIME); //menggabung loca dengan hasil struct (untuk lokasi penempatan)
    mkdir(loca, 0700); // pembuatan folder dalam log
    while(i<30){     // loop untuk file log#.log
    strcpy(ax,loca); //membuat variable ax menjadi sama dengan loca
    k=i+1;           //untuk penomoran log#
    sprintf(al, "/log%d", k); // penggabungan string dengan nomor k
    strcat(al,".log");   // penggabungan string dengan .log
// Open one file for reading 
    fptr1 = fopen(filename, "r");  //membuka file syslog
    strcat(ax,al);                 // penggabungan string untuk penentuan lokasi file log ditaruh

    // Open another file for writing 
    fptr2 = fopen(ax, "w");        //membua file log yang akan diisi
  
    // Read contents from file 
    c = fgetc(fptr1);             // menentukan panjangnya isi file syslog
    while (c != EOF)    //loop mengcopy isi syslog ke log#.log
    { 
        fputc(c, fptr2); 
        c = fgetc(fptr1); 
    } 
        fclose(fptr1); 
        fclose(fptr2);

         sleep(60);   // sleep waktu 60 detik
        
	i++;
}
  i=0;

      }
      return 0;
}
