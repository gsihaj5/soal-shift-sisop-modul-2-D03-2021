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
    char *argv[] = {"zip", "-r", target_zip, destination_dir, NULL};
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
        sleep(1);
    }
    create_success_status(destination_dir);

    pid_t zip_child_id;
    zip_child_id = fork();
    exit_on_failed_fork(zip_child_id);
    if (zip_child_id == 0) {
        zip_folder(destination_dir);
    }
    while ((wait(&zip_child_id)) > 0) {
    } /*wait until mkdir done*/

    char *argv[] = {"rm", "-r", destination_dir, NULL};
    execv("/bin/rm", argv);
}

int main() {
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
        sleep(5);
    }
}
