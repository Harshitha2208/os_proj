#include <stdio.h>
#include <string.h>

int createfile(){

    char name[100];
    printf("enter filename : \n");
    scanf("%s",name);
    char filename[50]; // Assuming a maximum length for the filename

    // Concatenate ".txt" to the name
    strcpy(filename, name);
    strcat(filename, ".txt");

    // File pointer
    FILE *file;

    // Open file in write mode, if it doesn't exist, create it
    file = fopen(filename, "w");

    // Check if file is successfully opened
    if (file == NULL) {
        printf("Unable to create file.\n");
        return 1; // Return an error code
    }



    // Close the file
    fclose(file);

    printf("File created and written successfully.\n");

    return 0; // Return success

}
int readfile(){
     char name[100];
    printf("enter filename : \n");
    scanf("%s",name);
    char filename[50]; // Assuming a maximum length for the filename

    // Concatenate ".txt" to the name
    strcpy(filename, name);
    strcat(filename, ".txt");

    FILE *file;
    char character;

    // Open the file in read mode
    file = fopen(filename, "r");

    // Check if the file is successfully opened
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1; // Return an error code
    }

    // Read and print the contents of the file character by character
    while ((character = fgetc(file)) != EOF) {
        printf("%c", character);
    }

    // Close the file
    fclose(file);

    return 0; // Return success
}

int updatefile(){
     char name[100];
    printf("enter filename : \n");
    scanf("%s",name);
    char filename[50]; // Assuming a maximum length for the filename

    // Concatenate ".txt" to the name
    strcpy(filename, name);
    strcat(filename, ".txt");
    FILE *file;

    // Open the file in append mode
    file = fopen(filename, "a");

    // Check if the file is successfully opened
    if (file == NULL) {
        printf("Unable to open the file for appending.\n");
        return 1; // Return an error code
    }

    char content[200];
    scanf("%s",content);
    fprintf(file,content);

    // Close the file
    fclose(file);

    printf("Content appended successfully.\n");

    return 0; // Return success
}

int deletefile(){
     char name[100];
    printf("enter filename : \n");
    scanf("%s",name);
    char filename[50]; // Assuming a maximum length for the filename

    // Concatenate ".txt" to the name
    strcpy(filename, name);
    strcat(filename, ".txt");
     if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        printf("Unable to delete the file '%s'.\n", filename);
        perror("Error"); // Print the system error message
        return 1; // Return an error code
    }

    return 0;
}

void filecrud(){
    int choice2;
    printf("enter file crud choice : \n");
    scanf("%d",&choice2);
    switch(choice2){
        case 1: createfile();break;
        case 2: readfile();break;
        case 3: updatefile();break;
        case 4:deletefile();break;
        default:printf("option out of scope\n");
    }
}