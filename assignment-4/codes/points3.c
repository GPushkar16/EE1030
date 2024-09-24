#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

int main() {
    // Define the angle B in degrees
    double B_degrees = 45.0;
    // Convert B to radians
    double B_radians = B_degrees * (PI / 180.0);
    
    // Scaling factor for point A
    double scaling_factor = 1.21;

    // Calculate points A, B, and C
    double A[2];
    double B[2] = {0, 0};  // Point B is at (0, 0)
    double C[2] = {6, 0};  // Point C is at (6, 0)

    // Calculate A using the formulas A = (0.48 * cos(B), 0.48 * sin(B))
    A[0] = scaling_factor * cos(B_radians);
    A[1] = scaling_factor * sin(B_radians);

    // Open a file for output
    FILE *file = fopen("output3.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Output points in a simple format
    fprintf(file, "A %.4f %.4f\n", A[0], A[1]);
    fprintf(file, "B %.4f %.4f\n", B[0], B[1]);
    fprintf(file, "C %.4f %.4f\n", C[0], C[1]);

    // Close the file
    fclose(file);

    return 0;
}

