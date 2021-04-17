// [belum berjalan di latar belakang]
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

//[ untuk download foto ]
void func_donwload_foto() {    
    
    //download foto 
    char *argv[]={"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "foto.zip",  NULL};
    execv("/usr/bin/wget", argv);   
}

// [ untuk download musik ]
void func_download_musik() {

    //download musik
    char *args[]={"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "musik.zip",  NULL};
    execv("/usr/bin/wget", args);

}

// [ untuk downlaod film ]
void func_download_film() {
    
    //download film
    char *argc[]={"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "film.zip",  NULL};
    execv("/usr/bin/wget", argc);
}

void unzip_foto() {
    //unzip foto 
    char *argv[]={"unzip", "foto.zip", NULL};
    execv("/usr/bin/unzip", argv);
}

void unzip_musik() {

    //unzip musik 
    char *argv[]={"unzip", "musik.zip", NULL};
    execv("/usr/bin/unzip", argv);   

}

void unzip_film() {

    //unzip film 
    char *argv[]={"unzip", "film.zip", NULL};
    execv("/usr/bin/unzip", argv);

}

void rename_to_pyoto(){

    //rename FOTO -> Pyoto
    char *argv[]={"mv", "FOTO", "Pyoto", NULL};
    execv("/bin/mv", argv);
}

void rename_to_Musyik(){

    //rename MUSIK -> Myusik
    char *argv[]={"mv", "MUSIK", "Musyik", NULL};
    execv("/bin/mv", argv); 
}

void rename_to_Fylm(){

    //rename FILM -> Fylm
    char *argv[]={"mv", "FILM", "Fylm", NULL};
    execv("/bin/mv", argv);
    
}

void zipto_one() {
    //ZIP Pyoto,Fylm, Musyik ke satu zip
    char *argv[]={"zip", "-r" ,"Lopyu_Stevany.zip" , "Pyoto", "Musyik", "Fylm", NULL};
    execv("/usr/bin/zip", argv);
}

void delete_Musyik() {
    char *argv[]={"rm", "-r", "Musyik", NULL};
    execv("/bin/rm", argv);
}

void delete_Fylm() {
    char *argv[]={"rm", "-r", "Fylm", NULL};
    execv("/bin/rm", argv);
    
}

void delete_Pyoto() {
    char *argv[]={"rm", "-r", "Pyoto", NULL};
    execv("/bin/rm", argv);
}


void func2() {
  int i;
  for (i = 51; i < 101; i++) {
    printf("%d\n", i);
  }
}

int main() {
  pid_t child_id;
  int status;

  child_id = fork();
  if (child_id < 0) {
    exit(EXIT_FAILURE);
  }

  if (child_id == 0) {
    //func_donwload_foto();
    
    //**dieksekusi jam 16:22 [belum mengetahui cara untuk melakukan hal tersebut]
    pid_t child_download_1;
    int stat_1;

    child_download_1 = fork();
    if(child_download_1<0) {
        exit(EXIT_FAILURE);
    }

    if(child_download_1 == 0) {
        //func_download_musik();

        pid_t child_download_2;
        int stat_2;

        child_download_2 = fork();
        if (child_download_2==0) {

            pid_t child_download_3;
            int stat_3;

            child_download_3=fork();
            if(child_download_3==0) {

                pid_t child_4;
                int stat_4;

                child_4 = fork();
                if(child_4==0) {
                    
                    pid_t child_5;
                    int stat_5;

                    child_5 = fork();
                    if (child_5 == 0) {

                        pid_t child_6;
                        int stat_6;

                        child_6 = fork();
                        if(child_6==0) {

                            pid_t child_7;
                            int stat_7;

                            child_7=fork();
                            if (child_7==0) {


                                pid_t child_8;
                                int stat_8;

                                child_8=fork();
                                if (child_8==0) {
                                    
                                    pid_t child_9;
                                    int stat_9;

                                    child_9=fork();
                                    if(child_9==0) {
                                        func_donwload_foto();
                                    } else {
                                        while( wait(&stat_9)> 0 );
                                        func_download_film();
                                    }


                                } else {
                                    while( wait(&stat_8)> 0 );
                                    func_download_musik();
                                }
                                

                                
                            } else {
                                while( wait(&stat_7)> 0 );
                                unzip_foto();
                            }
                            


                        } else {
                            while( wait(&stat_6)> 0 );
                            unzip_film();
                        }


                    } else {
                        while( wait(&stat_5)> 0 );    
                        unzip_musik();
                    }


                }else {
                    while( wait(&stat_4)> 0 );
                    rename_to_pyoto();
                }
 

            } else {
                while( wait(&stat_3)> 0 );
                rename_to_Musyik();
            }


            
        } else {
            while( wait(&stat_2)> 0 );
            rename_to_Fylm();
        }
        


    } else {
        while( wait(&stat_1)> 0 );
        //func_download_film();
    }

  } else {
    while((wait(&status))> 0);
    //func2();
    //zipto_one();
    // dikesekusi jam 22.22 [belum mengetahui cara untuk melakukan hal tersebut]
    pid_t anak_1;
    int statAnak_1;

    anak_1=fork();
    if(anak_1==0) {

        pid_t anak_2;
        int statAnak_2;

        anak_2=fork();
        if(anak_2==0) {

            pid_t anak_3;
            int statAnak_3;

            anak_3 = fork();
            if(anak_3==0) {
                zipto_one();
            } else {
                while(wait(&statAnak_3)>0);
                delete_Fylm();
            }

        } else {
            while(wait(&statAnak_2)>0);
            delete_Musyik();
        }

    } else {
        while(wait(&statAnak_1)>0);
        delete_Pyoto();
    }

    
  }
}
