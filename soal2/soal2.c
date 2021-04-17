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
