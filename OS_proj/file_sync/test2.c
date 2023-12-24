#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "hashy.h"

pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

void copy_file(const char *source_path, const char *destination_path) {
    pthread_mutex_lock(&file_mutex);

    printf("Copying file from %s to %s\n", source_path, destination_path);

    // Perform the file copy operation (simplified for demonstration)
    FILE *source = fopen(source_path, "rb");
    FILE *destination = fopen(destination_path, "wb");

    if (source == NULL || destination == NULL) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    int ch;
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, destination);
    }

    fclose(source);
    fclose(destination);

    pthread_mutex_unlock(&file_mutex);
}

void move_file(const char *source_path, const char *destination_path) {
    pthread_mutex_lock(&file_mutex);

    printf("Moving file from %s to %s\n", source_path, destination_path);

    // Perform the file move operation (simplified for demonstration)
    if (rename(source_path, destination_path) != 0) {
        perror("Error moving file");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_unlock(&file_mutex);
}

void update_file(const char *file_path, const char *new_content) {
    pthread_mutex_lock(&file_mutex);

    printf("Updating file at %s\n", file_path);

    // Perform the file update operation (simplified for demonstration)
    FILE *file = fopen(file_path, "w");

    if (file == NULL) {
        perror("Error opening file for update");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", new_content);

    fclose(file);

    pthread_mutex_unlock(&file_mutex);
}

void *task1(void *arg) {
    copy_file("file1.txt", "backup/file1_backup.txt");
    return NULL;
}

void *task2(void *arg) {
    move_file("file2.txt", "archive/file2_archive.txt");
    return NULL;
}

void *task3(void *arg) {
    update_file("file3.txt", "New content for file3");
    return NULL;
}

void user_register(){
    char username[100];
    
}

int main() {
    bool sync = false;
    const char *filename = "user.txt";
    int new_user;

    FILE *file = fopen(filename, "r");
    int firstCharacter = fgetc(file);
    printf("%d\n\n",firstCharacter);

    if (file == NULL) {
        perror("Error opening file");
    }

    else if (firstCharacter == -1) {
        printf("The file is empty.\n");
        hash();
    } 
    else if(firstCharacter>=33){
        printf("\n\n1 - Register\n2 - Authenticate\n");
        scanf("%d",&new_user);
        switch(new_user){
            case 1 : hash();break;
            case 2 : authenticate_user(); sync=true;break;
            default:printf("choice out of scope\n");
        }
    }


    fclose(file);

    if(sync==true){
    pthread_t thread1, thread2, thread3;

    // Create threads for file synchronization tasks
    if (pthread_create(&thread1, NULL, task1, NULL) != 0 ||
        pthread_create(&thread2, NULL, task2, NULL) != 0 ||
        pthread_create(&thread3, NULL, task3, NULL) != 0) {
        perror("Error creating threads");
        exit(EXIT_FAILURE);
    }

    // Wait for all threads to finish
    if (pthread_join(thread1, NULL) != 0 ||
        pthread_join(thread2, NULL) != 0 ||
        pthread_join(thread3, NULL) != 0) {
        perror("Error joining threads");
        exit(EXIT_FAILURE);
    }

   }
}
