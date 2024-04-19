// longest_path_mapper.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 1000

void mapper(FILE *input) {
    char line[MAX_PATH_LENGTH];
    while (fgets(line, sizeof(line), input) != NULL) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';

        // Split the path by '/'
        char *token = strtok(line, "/");
        int max_length = 0;
        char longest_path[MAX_PATH_LENGTH];

        // Find the longest path
        while (token != NULL) {
            int length = strlen(token);
            if (length > max_length) {
                max_length = length;
                strcpy(longest_path, token);
            }
            token = strtok(NULL, "/");
        }

        // Emit the length of the longest path and the path itself
        printf("%d\t%s\n", max_length, longest_path);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    mapper(input);

    fclose(input);
    return 0;
}
