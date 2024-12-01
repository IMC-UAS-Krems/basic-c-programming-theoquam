#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int is_pos_int(const char *str) {
    while (*str) {
        if(!isdigit(*str)) {
            return 0;
            str++;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    // initialize random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;

    // WRITE YOUR CODE HERE
    
// When the program is called with a number of arguments different from 2, the code will output the following text to the standard output:
// Incorrect usage. You provided n arguments. The correct number of arguments is 2
// Instead of n, the program will output the actual number of arguments passed to the program.
    if (argc != 3) {
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc - 1);
        return 1;
    }
// The program will then check if all arguments passed are integers greater than 0. If this is not the case, the program will output the following text to the standard output:
// Incorrect usage. The parameters you provided are not positive integers
    if(!is_pos_int(argv[1]) || !is_pos_int(argv[2])) {
        printf("Incorrect usage. The parameters you provided are not positive integers\n");
        return 1;
    }
// The program will then create a dynamically allocated matrix of integers using the dimensions passed as parameters. For instance, if the program is called with assignment 5 10, a matrix of 5 rows and 10 columns will be created. Each entry of this matrix will be initialized to a random integer between 1 and 100.
    int nrows = atoi(argv[1]);
    int ncols = atoi(argv[2]);

    int **matrix = malloc(nrows * sizeof(int*));
    if (matrix == NULL) {
        printf("Memory allocation failed\n");
        return 1;   
    }

    for (int i = 0; i < nrows; i++) {
        matrix[i] = malloc(ncols * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
    }

    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            matrix[i][j] = rand() % maxrand + minrand;
        }
    }
// The program will create a file called matrix.txt that contains the previously generated matrix with one row on each line, and using a whitespace separator between each entry. No whitespace should be appended at the end of each line. The last row should end with a carriage return.
    FILE *f = fopen("matrix.txt", "w");
    if (f == NULL) {
        printf("Failed to open the file\n");
        return 1;
    }
    
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            fprintf(f, "%d ", matrix[i][j]);
        }
        fprintf(f, "\n");
    }
    
    fclose(f);
    
    for (int i = 0; i < nrows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
