# -soal-shift-sisop-modul-2-D08-2021

## **Soal 1**

Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar, namun sudah putus sebelum pacaran. Ketika dia galau memikirkan mantan, ia selalu menonton https://www.youtube.com/watch?v=568DH_9CMKI untuk menghilangkan kesedihannya. Di lain hal Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop demi menarik perhatian Stevany. Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi.

A. Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg

B. untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :).

C. Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload serta

D. memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan).

E. Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany).

F. Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip). Kemudian Steven meminta bantuanmu yang memang sudah jago sisop untuk membantunya mendapatkan hati Stevany. Bantu Woy!!

**Penyelesaian**

```
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
```
Pertama-tama dilakukan iclude header files yang dibutuhkan.

```
int main()
{
    pid_t pid, sid;

    pid = fork();

    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/tmp")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    	...
    	
   }
 
```
 
Pada fungsi main, terdapat _daemon function procces_ yang bertujuan agar program dapat berjalan pada background.

```
    char *FILM_ZIP = "film.zip";
    char *PHOTO_ZIP = "photo.zip";
    char *MUSIC_ZIP = "music.zip";
```

Variabel diatas digunakan untuk menyimpin folder zip dari file yang akan didownload.

```
while (1)
    {
        time_t t = time(NULL);
        struct tm now = *localtime(&t);

        if (now.tm_mday == 9 && now.tm_mon == 3 && now.tm_hour == 22 - 6 &&
            now.tm_min == 22 && now.tm_sec == 0)
        {
        	...
        }
        
        if (now.tm_mday == 9 && now.tm_mon == 3 && now.tm_hour == 22 &&
        now.tm_min == 22 && now.tm_sec == 0)
        {
        	...
        }
        
```

Awalnya waktu saat ini diambil kemudian disimpan ke variable __now__. kemudian program akan mengeck apakah waktu saat ini 6 jam sebelum ulang tahun atau sama dengan ulang tahun. Loop ini akan berjalan pada setiap detik.

```
            pid_t pid1, pid2;

            pid1 = fork();
            if (pid1 < 0)
            {
                exit(EXIT_FAILURE);
            }

            pid2 = fork();
            if (pid2 < 0)
            {
                exit(EXIT_FAILURE);
            }

            if (pid1 == 0 && pid2 > 0)
            {
                while (wait(NULL) > 0);
                
                char *argv[] = {"wget", "--no-check-certificate", "-o", "/dev/null",
                                "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", MUSIC_ZIP, NULL};
                execv("/bin/wget", argv);
            }
            else if (pid1 > 0 && pid2 == 0)
            {
                char *argv[] = {"wget", "--no-check-certificate", "-o", "/dev/null",
                                "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
                                "-O", PHOTO_ZIP, NULL};
                execv("/bin/wget", argv);
            }
            else if (pid1 == 0 && pid2 == 0)
            {
                char *argv[] = {"wget", "--no-check-certificate", "-o", "/dev/null",
                                "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download",
                                "-O", FILM_ZIP, NULL};
                execv("/bin/wget", argv);
            }
            
            while (wait(NULL) > 0);

```

Kemudian jika waktu saat ini 6 jam kurang dari waktu ulang tahun stephany, maka program akan di-fork sebanyak 2 kali sehingga program akan memiliki 2 child dan 1 grandchild. Akan dilakukan download file zip film, foto, musik yang kemudian disimpan sesuai dengan nama variable masing-masing yaitu __FILM_ZIP__, __PHOTO_ZIP__, dan __MUSIC_ZIP__ pada masing-masing proses. Namun procces pada child pertama akan menunggu hingga proses pada grandchild selesai sebelum melakukan download file.

```
            pid1 = fork();
            if (pid1 < 0)
            {
                exit(EXIT_FAILURE);
            }

            pid2 = fork();
            if (pid2 < 0)
            {
                exit(EXIT_FAILURE);
            }

            if (pid1 == 0 && pid2 > 0)
            {
                while (wait(NULL) > 0);

                char *argv[] = {"unzip", "-j", MUSIC_ZIP, "*.mp3", "-d", "./Musyik", NULL};
                execv("/bin/unzip", argv);
            }
            else if (pid1 > 0 && pid2 == 0)
            {
                char *argv[] = {"unzip", "-j", PHOTO_ZIP, "*.jpg", "-d", "./Pyoto", NULL};
                execv("/bin/unzip", argv);
            }
            else if (pid1 == 0 && pid2 == 0)
            {
                char *argv[] = {"unzip", "-j", FILM_ZIP, "*.mp4", "-d", "./Fylm", NULL};
                execv("/bin/unzip", argv);
            }

```
Setelah file selesai didownload, maka parent akan di-fork sebanyak dua kali. Pada masing-masing childnya, program akan melakukan unzip file-file ke dalam folder yang disimpan pada __./Fylm__, __./Pyoto__, dan __./Musyik__.


```
            pid_t pid1;

            pid1 = fork();
            if (pid1 < 0)
            {
                exit(EXIT_FAILURE);
            }

            if (pid1 == 0)
            {
                char *username = malloc(33 * sizeof(char));
                cuserid(username);

                char *TARGET_PATH = malloc(50 * sizeof(char));
                sprintf(TARGET_PATH, "/home/%s/Lopyu_Stevany.zip", username);

                char *argv[] = {"zip", "-r", TARGET_PATH, "./Fylm", "./Pyoto", "./Musyik", 		NULL};
                execv("/bin/zip", argv);
            }

            while (wait(NULL) > 0);
```
Selanjutnya jika waktu saat ini sama dengan waktu ulang tahun stephany, maka program akan di-fork. Pada proses childnya, pertama username dari user yang menjalankan program diambil kemudian digabungkan dengan nama zip akhirnya dan disimpan ke __TARGET_PATH__. kemudian folder film, foto, dan musik di-zip dengan nama yang sesuai dengan __TARGET_PATH__. Parent proses akan menunggu hingga proses zip selesai.

```
            pid1 = fork();
            if (pid1 < 0)
            {
                exit(EXIT_FAILURE);
            }

            if (pid1 == 0)
            {
                char *argv[] = {"rm", "-r", "./Fylm", "./Pyoto", "./Musyik",
                                FILM_ZIP, PHOTO_ZIP, MUSIC_ZIP, NULL};
                execv("/bin/rm", argv);
            }
        }
```

Setelah selesai dizip, maka program akan kembali di-fork. folder dan file zip yang dihasilkan pada proses sebelumnya kecuali zip akhir akan dihapus pada proes anaknya.

###Dokumentasi###


### **Penyelesaian Soal 2**
- 2.a. Mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop” dan menghapus folder-folder yang tidak dibutuhkan
```c
    pid_t child_id;
    int status;
    char direct[]="/home/yudo/Documents/Modul2/petshop";
    char FileName[]="petshop";
  
    struct dirent *dp;
    DIR *dir = opendir(direct);

    child_id = fork();

    if (child_id < 0) {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }

    if (child_id == 0) {
        // this is child

        char *argv1[] = {"unzip", "pets.zip", "-d", direct, "*.jpg", NULL};
        execv("/bin/unzip", argv1);

    }
```
Pertama deklarasi char `direct` yang menyimpan alamat folder yang akan dibuat. Lalu program untuk mengextract zip dan menyimpannya dalam directory petshop ditaruh pada pointer `argv1[]` dengan nama program `unzip` dan dieksekusi dengan execv. . Digunakan `-d` untuk menunjukkan path yang akan dituju. Agar folder yang tidak dibutuhkan tidak ikut terextract maka ditambahkan `*.jpg`, hasilnya yang dieksekusi hanya file .jpg.


### **Penyelesaian Soal 3**
### **Soal 3a**
Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].

Berikut merupakan fungsi untuk membuat sebuah direktori
```
void folder(char *foldername){
  if(fork()==0){  
    char *makedir[] = {"mkdir", "-p",foldername, NULL};
    execv("/bin/mkdir", makedir);
  }   
}
```
### **Soal 3b**
Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar  ersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.

Berikut merupakan fungsi untuk mengunduh 10 gambar dengan jeda 5 detik dari https://picsum.photos/ dengan ketentuan ukuran `(n%1000) + 50 pixel` dimana `n` adalah detik Epoch Unix. Dengan menghitung nilai dari (n%1000) + 50 kemudian disimpan dalam variable dan nantinya akan dimasukkan ke dalam link https://picsum.photos/.

``` 
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
```

### **Soal 3c**
Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.

Berikut merupakan fungsi untuk membuat file status.txt yang didalamnya terdapat pesan Download Success yang nantinya akan dienkripsi menggunakan Caesar Cipher. Kemudian file tersebut akan disimpan kedalam direktori yang sudah dibuat sebelumnya.
```
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
```

Fungsi dibawah ini merupakan fungsi untuk membuat direktori yang berisikan 10 gambar dan status.txt menjadi .zip
```
void archive(char *foldername){
  char temp[100];
  if(fork()==0){
    strcpy(temp, foldername);
    strcat(temp, ".zip");
    char *argv[] = {"zip", temp, "-rm", foldername, NULL};
    execv("/bin/zip", argv);
  }  
}
```

### **Soal 3d**
Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin rogram tersebut akan men-generate sebuah program “Killer” yang executable, dimana rogram tersebut akan menterminasi semua proses program yang sedang berjalan dan kan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai esuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat antinya harus merupakan program bash.

Pembuatan program killer adalah dengan memanggil fungsi killer sebelum proses loop

```
....
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
....

```
Didalam fungsi killer terdapat syntax untuk membuat file killer.

```
FILE *killer = fopen("killer.sh", "w");
```

### **Soal 3e**
Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).

Berikut merupakan fungsi untuk membuat program killer yang merupakan program bash untuk menghentikan proses. Program yang dibuat sesuai dengan argumen yang diinput saat program dijalankan. Untuk argumen `-z` script akan berisi command yang akan menghentikan seluruh proses terjadi. Sedangkan argumen `-x` akan berisi command untuk menghentikan progrma utama namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori) dengan passing value `getpid()` saat memanggil fungsi.


```
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
     
}
```

Berikut merupakan fungsi `main()` untuk memanggil  fungsi diatas dengan dengan jeda setiap 40 detik dan passing value untuk nama folder sesuai dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].

```
int main(int argc, char const *argv[]) {
  char foldername[100];
  time_t rawtime;

....

  killer(argv,(int)getpid());
....

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
  
```

### **Kendala :**

•	Program daemon berhenti setelah menyelesaikan satu proses saja

•	Program berhenti setelah melakukan zip file

•	Tidak ada spasi pada hasil enkripsi `Download Success` 

