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

int main()
{
    //mengkill program yang berjalan
    int x; //insialisasi variable x
    char b[50]; //inisualisasi char 
 	FILE *fptr3; //inisialisasi file 
    fptr3 = fopen("nomerpid.txt", "r"); // membuka file dengan nama nomerpid.txt
    fscanf(fptr3, "%d", &x); //menscan isi file 
    fclose(fptr3); // menutup file
    sprintf(b, "%d", x); // merubah inputan dari integer menjadi string
    char *argv[4] = {"kill", b, NULL}; // mengkill program dengan nomer pid yang telah didapatkan
    execv("/bin/kill", argv); // directory kill

      return 0;
}
