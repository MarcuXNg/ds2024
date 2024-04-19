// longest_path_reducer.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 1000

void reducer(FILE *input) {
    int max_length = 0;
    char longest_path[MAX_PATH_LENGTH];

    char line[MAX_PATH_LENGTH];
    while (fgets(line, sizeof(line), input) != NULL) {
        int length;
        char path[MAX_PATH_LENGTH];
        sscanf(line, "%d\t%s", &length, path);

        // Update max length and longest path if a longer path is found
        if (length > max_length) {
            max_length = length;
            strcpy(longest_path, path);
        }
    }

    // Output the longest path
    printf("%s\n", longest_path);
}

int main() {
    reducer(stdin);
    return 0;
}
