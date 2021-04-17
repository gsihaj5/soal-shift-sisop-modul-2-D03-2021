# soal-shift-sisop-modul-2-D03-2021

# LAPORAN PENGERJAAN SOAL SHIFT

# ============== NO 1 ===============
## Soal 📘
Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar, namun sudah putus sebelum pacaran. Ketika dia galau memikirkan mantan, ia selalu menonton https://www.youtube.com/watch?v=568DH_9CMKI untuk menghilangkan kesedihannya. Di lain hal Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop demi menarik perhatian Stevany. Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi. 
  * (a) Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg 
  * (b) untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :). 
  * (c) Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload serta 
  * (d) memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan).
  * (e) Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany). 
  * (f) Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip).
   - **Note:**
   - Ulang Tahun Stevany : 09 April Pukul 22.22 WIB
   - Semua poin dijalankan oleh 1 script di latar belakang, termasuk mendownload file zip-nya. Jadi cukup jalankan script 1x serta ubah time dan date untuk check hasilnya. Preview : https://drive.google.com/drive/folders/1NzRiPPoVlR_H8P51cxN4jaceeFQGk4un *tontonnya 720p biar jelas.. ಠ‿ಠ
   - Tidak boleh menggunakan fungsi system(), mkdir(), dan rename() (Yang di bahasa C) .... FORBIDDENNN!!
   - Tidak boleh pake cron !!!
   - Menggunakan fork dan exec.
   - link donwload file
   - > Foto :https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/view
   - > Film :https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view
   - > Musik :https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view
   - **Tips :**
   - Gunakan fungsi wait() dan sleep() untuk memperlancarrr..
   - untuk mendownload zip yang dibutuhkan bisa menggunakan command :
```
wget --no-check-certificate "https://drive.google.com/uc?id=ID-FILE&export=download" -O Nama_untuk_filenya.ext
```
   -contoh
```
Wget --no-check-certificate "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download" -O Musik_for_Stevany.zip
```
## Hasil Pengerjaan 🖥

## Cara Pengerjaan 📝
Pada soal ini, soal belum bisa diselesaikan dengan baik, proses pengerjaan belum berjalan pada latar belakang dan belum berjalan pada waktu yang ditentukan.
Soal ini dikerjakan dengan cara :
1. mendownload file-file yang diminta dengan cara seperti berikut
```
void func_donwload_foto() {    
    
    //download foto 
    char *argv[]={"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "foto.zip",  NULL};
    execv("/usr/bin/wget", argv);   
}
```
cara diatas kemudian diaplikasikan pada file lainnya dengan perubahan link dan argumennya
2.  unzip hasil download dengan cara seperti berikut
```
void unzip_foto() {
    //unzip foto 
    char *argv[]={"unzip", "foto.zip", NULL};
    execv("/usr/bin/unzip", argv);
}
```
3.  mengubah hasil unzip ke nama folder yang serupa dengan keterangan soal
```
void rename_to_pyoto(){

    //rename FOTO -> Pyoto
    char *argv[]={"mv", "FOTO", "Pyoto", NULL};
    execv("/bin/mv", argv);
}
```
4.  zip folder ke dalam suatu zip dengan nama Lopyu_Stevany.zip
```
void zipto_one() {
    //ZIP Pyoto,Fylm, Musyik ke satu zip
    char *argv[]={"zip", "-r" ,"Lopyu_Stevany.zip" , "Pyoto", "Musyik", "Fylm", NULL};
    execv("/usr/bin/zip", argv);
}
```
5. Menghapus folder
```
void delete_Pyoto() {
    char *argv[]={"rm", "-r", "Pyoto", NULL};
    execv("/bin/rm", argv);
}
```

## Kendala 🕳
1. Belum bisa mengimplementasikan pada daemon agar berjalan di latar belakang
2. Belum bisa mengatur program agar berjalan pada waktu yang diminta pada deskripsi soal


# ============== NO 3 ===============

## PENYELESAIAN

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

void exit_on_failed_fork(pid_t child_id) {
    if (child_id < 0)
        exit(EXIT_FAILURE);
}

void create_directory(char destination_dir[100]) {
    //create dir
    char *argv[] = {"mkdir", "-p", destination_dir, NULL};
    execv("/bin/mkdir", argv);
}

void write_success_message_to(FILE *file) {
    char success_message[] = "Download Success";
    int i = 0;
    int shift = 5;

    while (success_message[i] != '\0') {
        if (success_message[i] >= 'A' && success_message[i] <= 'Z') {
            char newletter = success_message[i] - 'A';
            newletter += shift;
            newletter = newletter % 26;
            success_message[i] = newletter + 'A';
        }
        if (success_message[i] >= 'a' && success_message[i] <= 'z') {
            char newletter = success_message[i] - 'a';
            newletter += shift;
            newletter = newletter % 26;
            success_message[i] = newletter + 'a';
        }
        i++;
    }

    fprintf(file, "%s", success_message);
}

void zip_folder(char destination_dir[100]) {
    char target_zip[100];
    strcpy(target_zip, destination_dir);
    strcat(target_zip, ".zip");

    // zip -r my_arch.zip my_folder
    char *argv[] = {"zip", "-qr", target_zip, destination_dir, NULL};
    execv("/bin/zip", argv);
}

void create_success_status(char destination_dir[100]) {
    FILE *status_file;

    char full_path[100];
    sprintf(full_path, "%s/success.txt", destination_dir);
    status_file = fopen(full_path, "w");

    write_success_message_to(status_file);

    fclose(status_file);
}

void download_an_image(char destination_dir[100]) {
    time_t t = time(NULL);
    struct tm *time = localtime(&t);
    char download_path[100] = "https://picsum.photos/";
    char time_string[50];
    char file_name[100];

    //generate path arguments
    sprintf(time_string, "%ld", t % 1000 + 50);
    strcat(download_path, time_string);

    //generate file name with time
    strftime(file_name, sizeof(file_name), "%Y-%m-%d_%H:%M:%S", time);
    strcat(destination_dir, "/");
    strcat(destination_dir, file_name);

    //download image
    char *argv[] = {"wget", "-qO", destination_dir, download_path, NULL};
    execv("/bin/wget", argv);
}

void download_n_images_to(int number_of_image, char destination_dir[100]) {
    for (int i = 0; i < number_of_image; i++) {
        pid_t dl_child_id;
        dl_child_id = fork();
        exit_on_failed_fork(dl_child_id);

        if (dl_child_id == 0) {
            download_an_image(destination_dir);
        }
        sleep(5);
    }
    create_success_status(destination_dir);

    pid_t zip_child_id;
    zip_child_id = fork();
    exit_on_failed_fork(zip_child_id);
    if (zip_child_id == 0) {
        zip_folder(destination_dir);
    }

    while ((wait(&zip_child_id)) > 0) {
    } /*wait until zip done*/

    char *argv[] = {"rm", "-r", destination_dir, NULL};
    execv("/bin/rm", argv);
}

void write_killer_bash(FILE *file, char killer_arg) {
    fprintf(file, "#!/bin/bash\n");

    if (killer_arg == 'x') {
        pid_t process_id;
        process_id = getpid();
        fprintf(file, "kill -9 %d\n", process_id);
    } else if (killer_arg == 'z') {
        pid_t session_id;
        session_id = getsid(0);
        fprintf(file, "pkill -s %d\n", session_id);
    }
}

void create_killer_bash(char killer_arg) {
    FILE *killer_file;

    char path[100] = "soal3_kill.sh";
    killer_file = fopen(path, "w");

    write_killer_bash(killer_file, killer_arg);

    fclose(killer_file);
}

int main(int argc, char *argv[]) {
    create_killer_bash((argv[1])[1]);
    pid_t child_id;
    int child_stat;

    while (1) {
        child_id = fork();
        exit_on_failed_fork(child_id);

        if (child_id == 0) {
            pid_t mkdir_child_id;
            int mkdir_child_stat;

            //assign directory name by time
            time_t t = time(NULL);
            struct tm *time = localtime(&t);
            char destination_dir[100];
            strftime(destination_dir, sizeof(destination_dir), "%Y-%m-%d_%H:%M:%S", time);
            printf("%s\n", destination_dir);

            mkdir_child_id = fork();
            exit_on_failed_fork(mkdir_child_id);

            if (mkdir_child_id == 0)
                create_directory(destination_dir);

            while ((wait(&mkdir_child_stat)) > 0) {
            } /*wait until mkdir done*/

            download_n_images_to(10, destination_dir);
        }
        sleep(40);
    }
}
```

## DESKRIPSI

### soal a
soal pertama diselesaikan dengan membuat infinite loop yang didalamnya ada fork
child process yang dijalankan adalah fork lagi dan membuat direktory sebagai child process,
parent process nya mendownload 10 gambar.

### soal b
soal b dijalankan sebagai parent process dari soal a yang membuat directory.
soal b diselesaikan dengan membuat loop yang didalamnya ada fork untuk mendownload gambar setiap 5 detik.

### soal c
setelah loop dari 10 gambar selesai proses, yang dijalankan adalah proses pembuatan message success yang dienkripsi menggunakan
caesar cipher. setelah success maka melakukan fork kembali untuk menzip folder lalu menjalankan delete folder.

### soal d dan e 
killer program dibuat dengan mengambil argumen dari program (soal e) kemudian menulis killer file dengan format shell script
yang di tulis menggunakan fopen.
1. untuk flag z -> menggunakan perintah pkill -s dengan parameter session id untuk kill semua process nya
1. untuk flag x -> menggunakan perintah kill -9 untuk kill parent saja dan membiarkan child process berjalan hingga selesai


