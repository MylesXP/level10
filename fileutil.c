#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// DIRECTIONS
// Choose whether you are doing the 2D array or
// the array of arrays.
// For the 2D array,
//    implement loadFile2D, substringSearch2D, and free2D.
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.

#define MAX_LINE_LENGTH 100  // Maximum length of each line in the file

// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char **loadFileAA(char *filename, int *size) {
    FILE *in = fopen(filename, "r");
    if (!in) {
        perror("Can't open file");
        exit(1);
    }

    // Allocate memory for an array of strings (arr).
    char **arr = NULL;
    char buffer[MAX_LINE_LENGTH];
    int capacity = 10;  // Initial capacity
    arr = malloc(capacity * sizeof(char *));
    if (!arr) {
        perror("Memory allocation failed");
        exit(1);
    }

    *size = 0; // Initialize size

    // Read the file line by line.
    while (fgets(buffer, sizeof(buffer), in)) {
        // Trim newline.
        buffer[strcspn(buffer, "\n")] = 0;

        // Expand array if necessary (realloc).
        if (*size >= capacity) {
            capacity *= 2;
            arr = realloc(arr, capacity * sizeof(char *));
            if (!arr) {
                perror("Memory reallocation failed");
                exit(1);
            }
        }

        // Allocate memory for the string (str).
        arr[*size] = malloc((strlen(buffer) + 1) * sizeof(char));
        if (!arr[*size]) {
            perror("Memory allocation for string failed");
            exit(1);
        }

        // Copy each line into the string (use strcpy).
        strcpy(arr[*size], buffer);

        // Attach the string to the large array (assignment =).
        (*size)++;
    }

    // Close the file.
    fclose(in);

    // Return pointer to the array of strings.
    return arr;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char *substringSearchAA(char *target, char **lines, int size) {
    for (int i = 0; i < size; i++) {
        if (strstr(lines[i], target)) {  // Check if target substring is in line
            return lines[i]; // Return the line if substring is found
        }
    }
    return NULL; // Return NULL if not found
}

// Free the memory used by the array
void freeAA(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]); // Free each string
    }
    free(arr); // Free the array of strings
}
