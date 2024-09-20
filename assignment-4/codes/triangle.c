#include <stdio.h>
#include <math.h>

int main() {
    double BC = 6.0; 
    double angle_B = 45.0; 

    // Open the file for writing
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
        fprintf(file, "While using cosine formula for finding side AC we will find that k must be less than %.1lf cm", BC);
    

    // Close the file
    fclose(file);
    printf("Output written to output.txt\n");

    return 0;
}

