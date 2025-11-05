#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

static int nflag, eflag;

int main (int argc, char* argv[]) {

    char* filePath = NULL;
    char* fileContent;
    int line = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            nflag = 1;
        } else if (strcmp(argv[i], "-e") == 0) {
            eflag = 1;
        } else {
            filePath = argv[i];
        }
    }

    if (!filePath) {
        printf("Usage: %s [-n] <file>\n", argv[0]);
        return 1;
    }

    FILE *fptr = fopen(filePath, "r"); // read-only
    if (fptr == NULL) {
        printf("Error: No such file or directory");
        return 1;
    }

    // == Go to the end of the file for know the file size ==
    fseek(fptr, 0, SEEK_END);
    long fileSize = ftell(fptr);
    rewind(fptr);

    fileContent = malloc(fileSize + 1); // alloc mem
    if (!fileContent) {
        perror("malloc failed");
        fclose(fptr);
        return 1;
    }
    
    fread(fileContent, 1, fileSize, fptr);
    fileContent[fileSize] = '\0';

    // == Printing ==

    char* pointer = fileContent;
    int atLineStart = 1;
    while (*pointer) {
        if (atLineStart && nflag) { // if nflag
            printf("%6d  ", line++);
            atLineStart = 0;
        }
        
        if (*pointer == '\n') {
            if (eflag) { // if eflag
                putchar('$');
            }
            putchar('\n');
            atLineStart = 1;
        } else {
            putchar(*pointer); // Print other char
        }
        
        pointer++;
    }
    printf("\n");
    
    fclose(fptr);
    free(fileContent);
}