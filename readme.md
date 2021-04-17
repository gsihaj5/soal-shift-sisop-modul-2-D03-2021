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
## Cara Pengerjaan 📝
Pada soal ini, soal belum bisa diselesaikan dengan baik, proses pengerjaan belum berjalan pada latar belakang dan belum berjalan pada waktu yang ditentukan.
Soal ini dikerjakan dengan cara :
1. mendownload file-file yang diminta dengan cara seperti berikut
```c
void func_donwload_foto() {    
    
    //download foto 
    char *argv[]={"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "foto.zip",  NULL};
    execv("/usr/bin/wget", argv);   
}
```
cara diatas kemudian diaplikasikan pada file lainnya dengan perubahan link dan argumennya
2.  unzip hasil download dengan cara seperti berikut
```c
void unzip_foto() {
    //unzip foto 
    char *argv[]={"unzip", "foto.zip", NULL};
    execv("/usr/bin/unzip", argv);
}
```
3.  mengubah hasil unzip ke nama folder yang serupa dengan keterangan soal
```c
void rename_to_pyoto(){

    //rename FOTO -> Pyoto
    char *argv[]={"mv", "FOTO", "Pyoto", NULL};
    execv("/bin/mv", argv);
}
```
4.  zip folder ke dalam suatu zip dengan nama Lopyu_Stevany.zip
```c
void zipto_one() {
    //ZIP Pyoto,Fylm, Musyik ke satu zip
    char *argv[]={"zip", "-r" ,"Lopyu_Stevany.zip" , "Pyoto", "Musyik", "Fylm", NULL};
    execv("/usr/bin/zip", argv);
}
```
5. Menghapus folder
```c
void delete_Pyoto() {
    char *argv[]={"rm", "-r", "Pyoto", NULL};
    execv("/bin/rm", argv);
}
```

## Kendala 🕳
1. Belum bisa mengimplementasikan pada daemon agar berjalan di latar belakang
2. Belum bisa mengatur program agar berjalan pada waktu yang diminta pada deskripsi soal

## Hasil Pengerjaan 🖥
![nomer1 jam 14:00](https://github.com/widigdacahya/gif/blob/main/nomer1_.gif?raw=true)

# ============== NO 2 ===============

## PENYELESAIAN

```
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <dirent.h>

int main() {
	int status;
	pid_t child_id = fork();
	
	if(child_id==0) {
		char *argv[] = {"unzip", "/home/bagas/modul2/pets.zip", "-d", "/home/bagas/modul2/petshop", NULL};
		execv("/usr/bin/unzip", argv);
	}
	while((wait(&status))>0);
	
	DIR *dp;
	struct dirent *ep;
	dp = opendir("/home/bagas/modul2/petshop");
	int status2;
	if(dp!=NULL) {
		while((ep=readdir(dp))) {
			if((ep->d_type==DT_DIR)&&(strcmp(ep->d_name, ".")!=0)&&(strcmp(ep->d_name, "..")!=0)) {
				pid_t child_id2 = fork();
				if(child_id2==0) {
					char file_gaguna[] = "/home/bagas/modul2/petshop/";
					strcat(file_gaguna, ep->d_name);
					char *argv[] = {"rm", "-r", file_gaguna, NULL};
					execv("/bin/rm", argv);
				}
			}
		}
	}
	while(wait(&status2)>0);
	
	DIR *dp2;
	struct dirent *ep2;
	dp2 = opendir("/home/bagas/modul2/petshop");
	int flag=0;
	char folder[50][100];
	if(dp2!=NULL) {
		while((ep2=readdir(dp2))) {
			if(ep2->d_type==DT_REG) {
				char a[100], b[100];
				memset(folder[flag], '\0', sizeof(folder[flag]));
				memset(a, '\0', sizeof(a));
				strcpy(b, ep2->d_name);
				for(int i=0;i<strlen(b);i++) {
					if(b[i]==';')
						break;
					a[i]=b[i];
				}
				int ada=0;
				for(int i=0;i<flag;i++) {
					if(strcmp(folder[i], a)==0) {
						ada=1;
						break;
					}
				}
				if(ada==0) {
					strcpy(folder[flag], a);
					flag++;
				}
			}
		}
	}
	
	int status3;
	for(int i=0;i<flag;i++) {
		pid_t child_id3 = fork();
		if(child_id3==0) {
			char nm_folder[] = "/home/bagas/modul2/petshop/";
			strcat(nm_folder, folder[i]);
			char *argv[] = {"mkdir", nm_folder, NULL};
			execv("/bin/mkdir", argv);
		}
	}
	while(wait(&status3)>0);
	
	DIR *dp3;
	struct dirent *ep3;
	dp3 = opendir("/home/bagas/modul2/petshop");
	if(dp3!=NULL) {
		while(ep3=readdir(dp3)) {
			if(ep3->d_type==DT_REG) {
				char file[200], hewan[200], nama[200], umur[300];
				char hewan2[200], nama2[200], umur2[300];
				memset(hewan, '\0', sizeof(hewan));
				memset(nama, '\0', sizeof(nama));
				memset(umur, '\0', sizeof(umur));
				memset(hewan2, '\0', sizeof(hewan2));
				memset(nama2, '\0', sizeof(nama2));
				memset(umur2, '\0', sizeof(umur2));
				strcpy(file, ep3->d_name);

				int tanda=0, p_tanda=0, dua_hewan=0;
				for(int i=0;i<strlen(file);i++) {
					if(tanda==0) {
						if(file[i]==';') {
							tanda++;
							p_tanda=i+1;
							continue;
						}
						hewan[i]=file[i];
					}
					if(tanda==1) {
						if(file[i]==';') {
							tanda++;
							p_tanda=i+1;
							continue;
						}
						nama[i-p_tanda]=file[i];
					}
					if(tanda==2) {
						if((file[i]=='_')) {
							tanda++;
							p_tanda=i+1;
							continue;
						} else if(((file[i]=='.')&&(file[i+1]=='j')))
							break;
						umur[i-p_tanda]=file[i];
					}
					if(tanda==3) {
						if(file[i]==';') {
							tanda++;
							p_tanda=i+1;
							continue;
						}
						hewan2[i-p_tanda]=file[i];
					}
					if(tanda==4) {
						if(file[i]==';') {
							tanda++;
							p_tanda=i+1;
							continue;
						}
						nama2[i-p_tanda]=file[i];
					}
					if(tanda==5) {
						if((file[i]=='.')&&(file[i+1]=='j')) {
							dua_hewan=1;
							break;
						}
						umur2[i-p_tanda]=file[i];
					}
				}
				int status4;
				pid_t child_id4 = fork();
				if(child_id4==0) {
					char dari[] = "/home/bagas/modul2/petshop/"; 
					strcat(dari, ep3->d_name);
					char ke[200];
					sprintf(ke, "/home/bagas/modul2/petshop/%s/%s", hewan, nama);
					char *argv[] = {"cp", dari, ke, NULL};
					execv("/bin/cp", argv);
				}
				while(wait(&status4)>0);
				
				char keterangan[] = "/home/bagas/modul2/petshop/";
				strcat(keterangan, hewan);
				char txt[] = "/keterangan.txt";
				strcat(keterangan, txt);
				FILE *fp;
				fp = fopen(keterangan, "a+");
				fprintf(fp, "nama : %s\n", nama);
				fprintf(fp, "umur : %s tahun\n\n", umur);
				fclose(fp);
				
				if(dua_hewan==0) {
					int status6;
					pid_t child_id6 = fork();
					if(child_id6==0) {
						char hapus[] = "/home/bagas/modul2/petshop/";
						strcat(hapus, ep3->d_name);
						char *argv[] = {"rm", "-r", hapus, NULL};
						execv("/bin/rm", argv);
					}
					while(wait(&status6)>0);
				}
				
				if(dua_hewan==1) {
					int status5;
					pid_t child_id5 = fork();
					if(child_id5==0) {
						char dari[] = "/home/bagas/modul2/petshop/"; 
						strcat(dari, ep3->d_name);
						char ke[200];
						sprintf(ke, "/home/bagas/modul2/petshop/%s/%s", hewan2, nama2);
						char *argv[] = {"cp", dari, ke, NULL};
						execv("/bin/cp", argv);
					}
					while(wait(&status5)>0);					
					char keterangan[] = "/home/bagas/modul2/petshop/";
					strcat(keterangan, hewan2);
					char txt[] = "/keterangan.txt";
					strcat(keterangan, txt);
					FILE *fp;
					fp = fopen(keterangan, "a+");
					fprintf(fp, "nama : %s\n", nama2);
					fprintf(fp, "umur : %s tahun\n\n", umur2);
					fclose(fp);
					
					int status7;
					pid_t child_id7 = fork();
					if(child_id7==0) {
						char hapus[] = "/home/bagas/modul2/petshop/";
						strcat(hapus, ep3->d_name);
						char *argv[] = {"rm", "-r", hapus, NULL};
						execv("/bin/rm", argv);
					}
					while(wait(&status7)>0);
				}
			}
		}
	}
	return 0;
}
```

## DESKRIPSI

### Soal a
Soal a diselesaikan dengan menggunakan fork untuk mengextract zip ke folder yang diberi nama petshop. Kemudian untuk menghapus file-file yang tidak diperlukan, disini menggunakan Directory Listing. Kemudian diseleksi agar hanya jenis file 'folder' saja yang dicari. Lalu disini akan menggunakan fork lagi untuk menghapus file-file tersebut.

### Soal b
Soal b diselesaikan dengan menggunakan Directory Listing dan fork. Pertama directory listing, diseleksi agar hanya file-file biasa atau yang bukan folder yang dicari. Lalu akan dibuat folder sesuai dengan jenis hewan berdasarkan nama file. Jika folder dengan jenis hewan tersebut belum dibuat maka folder akan dibuat berdasarkan nama file gambar sampai dengan ';' yang menandakan jenis hewannya dengan menggunakan fork lagi.

### Soal c, d, dan e
Soal c dan d diselesaikan dengan menggunakan Directory Listing dan fork. Pertama directory listing, diseleksi agar hanya file-file biasa atau yang bukan folder yang dicari. Lalu masing-masing file akan dipindai namanya char per char untuk menyimpan jenis hewan, nama, dan umurnya yang masing-masing disimpan di sebuah string. Jika dalam satu gambar tersebut terdapat 2 hewan, maka akan diberi tanda dua_hewan=1 dan jenis hewan, nama dan umurnya akan disimpan di string yang berbeda dari hewan pertama. Kemudian dibuat fork untuk meng-copy gambar tersebut ke folder yang sesuai serta di-rename dengan nama dari hewan tersebut. Lalu nama dan umur hewan disimpan pada keterangan.txt dengan menggunakan fopen dengan a+ agar data yang diinput ditambahkan ke bagian akhir text. Jika pada gambar hanya terdapat satu hewan maka gambar akan langsung dihapus setelah nama dan umur disimpan pada text. Jika terdapat lebih dari satu hewan, maka akan dilakukan proses yang sama dengan menggunakan string-string yang satunya.

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


