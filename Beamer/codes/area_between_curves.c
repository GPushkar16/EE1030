#include <stdio.h>
#include <math.h>

// Define the functions for the curve and the line
double curve(double x) {
    return x * x / 4.0;  // y = x^2 / 4
}

double line(double x) {
    return (x + 2) / 4.0;  // y = (x + 2) / 4
}

// Numerical integration using the trapezoidal rule
double integrate(double (*f1)(double), double (*f2)(double), double a, double b, int n) {
    double h = (b - a) / n;  // Step size
    double area = 0.0;

    for (int i = 0; i < n; i++) {
        double x1 = a + i * h;
        double x2 = a + (i + 1) * h;

        // Area of trapezoid between the functions
        double y1 = f2(x1) - f1(x1);
        double y2 = f2(x2) - f1(x2);

        area += 0.5 * (y1 + y2) * h;
    }

    return area;
}

int main() {
    // Define integration bounds
    double a = -1.0;
    double b = 2.0;
    int n = 10000;  // Number of intervals for better accuracy

    // Calculate area
    double area = integrate(curve, line, a, b, n);

    // Write result to area.txt
    FILE *file = fopen("area.txt", "w");
    if (file != NULL) {
        fprintf(file, "Area between the curve and the line: %f\n", area);
        fclose(file);
        printf("Area has been written to area.txt\n");
    } else {
        printf("Error opening file!\n");
    }

    return 0;
}

