#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

/*
//[step] 
1. download zip file
2. extract zip file
3. rename foldernya
4. zip folders to one
5. delete folder
*/

// [proses execv]
void execvProc(char commandPath[], char *argv[]) {
    pid_t childId;
    int status;

    childId = fork();

    if (childId < 0) {
        while(childId < 0) {
            childId = fork();
        }
            
        exit(EXIT_FAILURE);
    }
    
    if (childId == 0) {
        // child
        
        execv(commandPath, argv);
        exit(0);

    } else {
        //parent
        
        while ((wait(&status)) > 0);
    }
}

//[donwload]
void downloadFileLink(char downloadLink[], char nameExt[]) {
    char *argv[] = {"wget", "--no-check-certificate", downloadLink, "-O", nameExt, NULL};
    execvProc("/usr/bin/wget", argv);
}

//[extract]
void extractZip(char filename[]) {
    char *argv[] = {"unzip", filename, NULL};
    execvProc("/usr/bin/unzip", argv);
}

//[rename]
void renameFolder(char current[], char result[]) {
    char *argv[] = {"mv", current, result, NULL};
    execvProc("/bin/mv", argv);
}

//[zip to one]
void zipToOne() {
    char *argv[] = {"zip", "-r", "Lopyu_Stevany.zip", "Fylm", "Pyoto", "Myusik", NULL};
    execvProc("/usr/bin/zip", argv);
}

//[delete folder]
void deleteFolder(char folderName[]) {
    char *argv[] = {"rm", "-r", folderName, NULL};
    execvProc("/bin/rm", argv);
}

void processingFilm() {
    downloadFileLink("https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "film.zip");
    extractZip("film.zip");
    renameFolder("FILM", "Fylm");
}  

void processingMusik() {
    downloadFileLink("https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "musik.zip");   
    extractZip("musik.zip");
    renameFolder("MUSIK", "Myusik");
}

void processingFoto() {
    downloadFileLink("https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "foto.zip");
    extractZip("foto.zip");
    renameFolder("FOTO", "Pyoto");
}

void processTask(int i) {
    
    if(i == 0) {
        processingFoto();
    } 
    
    if(i == 1) {
        processingMusik();
    } 
    
    if(i == 2) {
        processingFilm();
    }

}




int main() {
    pid_t pid, sid;        // Variabel untuk menyimpan PID

    pid = fork();     // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
    * (nilai variabel pid < 0) */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
    * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    ///         /home/catycahyul/Documents/seslab/seslab2/1_ini_revisi_fix/soal1_revisi.c
    //          /home/catycahyul/Documents/seslab/seslab2/revisi/ver/try/soal1_revisi.c
    if ((chdir("/home/catycahyul/Documents/seslab/seslab2/revisi/vers/try")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) {
        time_t t = time(NULL);
        struct tm timeInfo = *localtime(&t);
        int i;
        
        if(timeInfo.tm_mday == 9 && timeInfo.tm_mon + 1 == 4 && timeInfo.tm_hour == 16 && timeInfo.tm_min == 22 && timeInfo.tm_sec == 00) {
            
            for(i=0; i<3; i++) {

                if(fork() == 0) {
                    processTask(i);
                    exit(0);
                }
            }
                  
            
        } else if(timeInfo.tm_mday == 9 && timeInfo.tm_mon + 1 == 4 && timeInfo.tm_hour == 22 && timeInfo.tm_min == 22 && timeInfo.tm_sec == 00) {
            zipToOne();
            deleteFolder("Fylm");
            deleteFolder("Myusik");
            deleteFolder("Pyoto");
        }

        sleep(1);
    }
    
    exit(0);
}
