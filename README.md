# SoalShift_modul2_A09

1. Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.

    Catatan : Tidak boleh menggunakan crontab.

    **Jawab:**
    
    * Buat folder modul2 dulu dan buat modul2/gambar
    
    * Lalu dengan asumsi berkas gambarnya di /home/[user]/Pictures ke /home/[user]/modul2/gambar, kita memindahkannya dengan merename   berkas gambarnya dari asal gambar ke tujuan.
    
    **Penjelasan :**
    
        DIR *dr = opendir("/home/arvanna/Pictures");
        if(dr==NULL)return 0;//jika tidak ada directorynya
     
     * Pertama, kita buka asal directory foldernya. Jika tidak ada return 0
     
            while((de=readdir(dr))!=NULL){//selama dibaca ada
           		strcpy(direct,"/home/arvanna/Pictures/");
           		strcpy(direct2,"/home/arvanna/modul2/gambar/");
           		temp=strstr(de->d_name,".png");//ngecek jika sama dengan png
           		strcpy(png,".png");
           		strcpy(grey,"_grey.png");
           		if(temp){
                		temp2=strtok(de->d_name,".");//ngesplit nama dengan png
                		strcpy(oldname,temp2);//mengduplicate nama lama dengan nama baru 
				        strcat(oldname,png);//nama lama +.png
                		strcat(temp2,grey);//nama baru +-grey.png
                		strcat(direct,oldname);//gabung directory baru + nama baru
                		strcat(direct2,temp2);//gabung directory lama + nama lama
                		rename(direct,direct2);//memindahkan
           		}
       		}
    
    * Kedua, ketika saat dibaca filenya ada, maka kita buat ngecek menggunakan strstr jika sama dengan .png
    
    * Jika iya, maka kita memisahkan nama file dengan png. Lalu kita menduplicate nama baru dengan nama lama. Nama lama ditambahin .png, sedangkan nama baru ditambahkan _grey.png. Lalu digabungkan directory lama dengan nama lama dan directory baru dengan nama baru.
    
    * Jika sudah, gunakan fungsi rename untuk mengganti nama sekaligus memindahkan file
    
    [**Source Code**](https://github.com/idlavoNuyaB/SoalShift_modul2_A09/blob/master/soal1/soal1.c)
    
2. Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.

    Catatan: Tidak boleh menggunakan crontab
    
    **Jawab :**
    
    * Mengecheck jika berkas pada directory home/{user}/modul2/hatiku/elen.ku itu ada, lalu mengubah permission menjadi 777 jika owner dan groupnya adalah www-data lalu dihapus setiap 3 detik
    
    **Penjelasan :**
    
        struct dirent *de;
        DIR *dr=opendir("/home/arvanna/modul2/hatiku");
        char nama[10],dir[100]="/home/arvanna/modul2/hatiku/";
        if(dr==NULL)exit(EXIT_FAILURE);
        
     * Pertama, di declare semua variabel yang dibutuhkan, lalu membuka directory yang dibutuhkan serta menyimpan directory tersebut ke dir. Jika directory itu tidak ada, maka exit.
     
           while((de=readdir(dr))!=NULL){
            strcpy(nama,de->d_name);//mengcopy list file ke nama
            if(strcmp(nama,"elen.ku")==0){//jika ada file yg namanya elen.ku
                struct stat info;
	            strcat(dir,nama);//menggabungkan directorynya dan elen.ku
                if(stat(dir,&info)==0){//memasukkan informasi dari dir ke info
                  char perm[]="0777";//masih basis 10
                  int i=strtol(perm,0,8);//diubah ke basis 8
                  chmod(dir,i);//mengubah permission ke 0777
                  struct passwd *owner=getpwuid(info.st_uid);//memasukkan user id info ke struct owner
                  struct group *grup=getgrgid(info.st_gid);//memasukkan group id info ke struct group
                  if(strcmp(owner->pw_name,"www-data")==0 && strcmp(grup->gr_name,"www-data")==0){
                        remove(dir);
                  }
                }
            }
            
      * Lalu mengecek jika directory itu ada filenya, maka kita mengcopy nama file tersebut ke variabel nama.
      
      * Membandingkannya jika sama dengan elen.ku
      
      * Menggabungkan variabel dir dengan nama
      
      * Jika sudah dimasukkan informasinya maka diubah permissionnya
      
      * Mendapatkan user_id owner dan group_id group
      
      * Membandingkan jika nama owner dan group adalah www-data, maka dihapus filenya
      
      [**Source Code**](https://github.com/idlavoNuyaB/SoalShift_modul2_A09/blob/master/soal2/soal2.c)

3. Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 

    Buatlah program C yang dapat :

    i)  mengekstrak file zip tersebut.

    ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 

    Catatan:  

    * Gunakan fork dan exec.

    * Gunakan minimal 3 proses yang diakhiri dengan exec.

    * Gunakan pipe

    * Pastikan file daftar.txt dapat diakses dari text editor
    
    **Jawab :**
    
    * Mengekstrak file campur2.zip lalu menyimpan file yang berekstensi .txt ke daftar.txt
    
    **Penjelasan :**
    
    	 pid_t child_id,child_id2,child_id3;
  	 int pip[2],stats;
  	 child_id = fork();
  	 pipe(pip);//pip pertama
  	 pipe(pip+2);//pip kedua

    * Ngedeklarasikan variabel yang dibutuhkan dan membuat dua pipe dengan satu variabel saja.
    
    	   if (child_id == 0) {
    		char *zip[3] = {"unzip", "campur2.zip", NULL};
    		execvp(zip[0], zip);//buat nge unzip
  	    }
	   
    * Mengunzip file campur2.zip
    
    	  while(wait(&stats)>0);//menunggu child hingga selesai
    	  child_id2=fork();
    	  if(child_id2==0){
            dup2(pip[1],1);//buat menyimpan hasil ls nanti. Intinya buat write
            close(pip[1]);
            close(pip[0]);
            close(pip[3]);
            close(pip[2]);
            char *see[]={"ls","/home/arvanna/campur2/",NULL};
            execvp(see[0],see);//melihat semua data di directory itu
    	  }
    	  else{
            child_id3=fork();
            if(child_id3>0){
                    dup2(pip[0],0);//ngebaca yang dari ls tadi
                    dup2(pip[3],1);//nyimpan hasil dari greb nanti
                    close(pip[3]);
                    close(pip[1]);
                    close(pip[2]);
                    close(pip[0]);
                    char *grab[]={"grep",".txt$",NULL};
                    execvp(grab[0],grab);//ketika ada file yang paling belakang isinya.txt diambil     
            }
            else{
                    char hasil[1000];
                    close(pip[1]);
                    close(pip[0]);
                    close(pip[3]);
                    read(pip[2],hasil,sizeof(hasil));//ngebaca dari greb tadi
                    close(pip[2]);
                    FILE *file=fopen("/home/arvanna/modul2/daftar.txt","w+");//buat file
                    fputs(hasil,file);//memasukkan hasil ke file
                    fclose(file);          
            }
          }
     
     * Menunggu status child_id hingga selesai
     
     * Melihat directory campur2 dengan ls
     
     * Mengambil yang paling belankang .txt dengan grep .txt$
     
     * Memasukkan hasil ke daftar.txt
     
     [**Source Code**](https://github.com/idlavoNuyaB/SoalShift_modul2_A09/blob/master/soal3/soal3.c)
     
4. Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik). Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

    Contoh:

    * File makan_enak.txt terakhir dibuka pada detik ke-1

    * Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

    Catatan: 

    * dilarang menggunakan crontab

    * Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst
    
    **Jawab :**
    
    * Berkas makan_enak.txt tiap dibuka akan memunculkan makan_sehat1.txt,dst tiap 5 detik selama selang waktu 30 detik.
    
    **Penjelasan :**
    
    	char temp[1000],nama[]={"/home/arvanna/Documents/makanan/makan_enak.txt"};
        struct stat info;
        FILE *fil;

    * Mendeklarasikkan variabel yang dibutuhkan
    
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
    
    * Mengambil informasi dari variabel nama
    
    * Mengecek terakhir kali dibuka
    
    * Menghitung perbedaan waktu sekarang dengan terakhir kali dibuka
    
    * Jika perbedaanya kurang dari sama dengan 30, maka deklarasikan nama baru
    
    * Mengubah flag yang berupa int ke string lalu disimpan ke temp
    
    * Menggabungkan nama baru dengan temp, lalu dengan txt
    
    * Lalu membuat file baru dengan namanya nama baru
    
    * Kemudian di close lalu flag ditambah satu
    
    [**Source Code**](https://github.com/idlavoNuyaB/SoalShift_modul2_A09/blob/master/soal4/soal4.c)

    
5. Kerjakan poin a dan b di bawah:

    a. Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log

      Ket:

      * Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]

      * Per menit memasukkan log#.log ke dalam folder tersebut

      * ‘#’ : increment per menit. Mulai dari 1

    b. Buatlah program c untuk menghentikan program di atas.

      NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.


