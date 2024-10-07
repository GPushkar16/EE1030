#include <stdio.h>
#include <math.h>

// Function for the first curve y = (x + 2) / 4
double func1(double x) {
    return (x + 2) / 4;
}

// Function for the second curve y = x^2 / 4
double func2(double x) {
    return x * x / 4;
}

// Function to compute the area between the curves using numerical integration
double computeArea(double a, double b, int n) {
    double delta_x = (b - a) / n; // Step size
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        double x = a + i * delta_x;
        double y1 = func1(x); // First curve
        double y2 = func2(x); // Second curve
        area += (y1 - y2) * delta_x; // Add the area of each slice
    }
    return area;
}

int main() {
    double a = -1.0; // Lower limit of integration
    double b = 2.0;  // Upper limit of integration
    int n = 1000;    // Number of slices (higher value for better accuracy)

    double area = computeArea(a, b, n);

    // Open a file to write the output
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write the result to the file
    fprintf(file, "The area between the curves is: %lf\n", area);

    // Close the file
    fclose(file);

    // Print message indicating success
    printf("Output has been written to output.txt\n");

    return 0;
}

