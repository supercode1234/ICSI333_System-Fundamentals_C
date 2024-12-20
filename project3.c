//
//  main.c
//  project3
//
//  Created by Haolin Wang on 4/16/23.

// CSI333, System Fundamentals
// project 3
// Spring 2023
// TA: Manasa Nanuru
// Me: Haolin Wnag
// NetID: HW479779


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>

// copying files
void copy (const char* source, const char* destination){
    // using BUFSIZ macro for the large array size
    char buffer[BUFSIZ];
    
    
    // copying to itself
    if (strcmp(source, destination) == 0){
        printf("Cannot copy file to itself.\n");
        return; // exits the function
    }
    
    // file already exists in the file
    if (access(destination, F_OK) == 0){
        char answer;
        printf("File %s exists. Overwrite? (y or n)", destination);
        scanf(" %c", &answer);
        if (answer == 'n')
            return; //exit the function
    }
    
    //create a file
    
    // opening source and destination folders
    int source_folder = open (source, O_RDONLY);
    int destination_folder = open(destination, O_WRONLY | O_CREAT| O_TRUNC, 0644);
    ssize_t bytes_read;
    
    while ((bytes_read = read(source_folder, buffer, sizeof(buffer)))>0){
        printf("bb: %s",buffer);
        write(destination_folder, buffer, bytes_read);
        // bug, should create a file instead of a folder, and write to it.
    }
    
    // close both of the folders
    close(source_folder);
    close(destination_folder);
    
    // output its action
    printf("File %s successfully copied to %s.\n", source, destination);
}


// method for moving files
void move1 (const char* source, const char* destination){
    if (strcmp(source, destination) == 0){
        printf("Cannot move file to itself.\n");
        return; // exits the function
    }
    
    int result = link (source, destination);
    
    // if link doesn't return 0, which means it failed to link the new file
    if (result < 0){
        // then it will call the copy() method to copy everything to the destination
        printf("Can't link to directory %s\n",destination);
        perror("link");
        copy(source, destination);
    }
    
    // deleting the source folder by unlinking it
    unlink(source);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");

    if (strcmp(argv[0], "./move") == 0)
        printf("This is the usage: move source1 [source2...] destination\n");
    else if (strcmp (argv[0], "./copy") == 0)
        printf("This is the usage: copy source1 [source2...] destination\n");
    
    if(argc<4) {
        printf("argc is less than 4, exiting. Proper usage is below: \n");
        printf("Proper usage:  {copy or move} source1 [source2...] destination\n", argv[0]);
        return 1;// error, exit the program
    }
    const char* action = argv[1];
    const char* source = argv[2];
    const char* destination = argv[argc-1];// the last argument
    
    struct stat sb_source, sb_destination;
    stat (source, &sb_source);
    stat (destination, &sb_destination);
    
//    // makes sure the source is a directory
//    if (!S_ISDIR(sb_source.st_mode)){
//        fprintf(stderr, "Source '%s' should be a direcotry", source);
//        exit(EXIT_FAILURE);
//    }
    
    // makes sure the destination is a directory
//    if (!S_ISDIR(sb_destination.st_mode)){
//        fprintf(stderr, "Destination '%s' should be a direcotry", destination);
//        exit(EXIT_FAILURE);
//    }
    
// if action is "copy"
    if(strcmp(action, "copy") == 0){
        // loop is for multiple source folders
        // starts to read from argv[2]
        for (int i = 2; i < argc - 1; i++){
            source = argv[i];
            copy(source, destination);
        }
    }

// else if action is "move"
    else if (strcmp(action, "move") == 0) {
        // loop is for multiple source folders
        // starts to read from argv[2]
        for (int i = 2; i < argc - 1; i++){
            source = argv[i];
            move1(source, destination);
        }
    }
    
// else if action is either "copy" or "move"
    else {
        printf("Unknown action: %s\n", action);
        return 1;
    }
    return 0;
}
