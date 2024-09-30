#include <stdio.h>
#include <math.h>

// Function for the parabola y = x^2 / 4
double parabola(double x) {
    return (x * x) / 4.0;
}

// Function for the line y = (x + 2) / 4
double line(double x) {
    return (x + 2) / 4.0;
}

// Function to compute area using the trapezoidal rule
double integrate(double (*f1)(double), double (*f2)(double), double a, double b, int n) {
    double h = (b - a) / n;  // Width of each small rectangle
    double area = 0.0;
    
    for (int i = 0; i < n; i++) {
        double x1 = a + i * h;
        double x2 = a + (i + 1) * h;
        area += 0.5 * h * (f1(x1) - f2(x1) + f1(x2) - f2(x2));  // Area of trapezoid
    }
    
    return area;
}

int main() {
    // Define limits of integration (intersection points)
    double a = -1;  // Intersection point x = -1
    double b = 2;   // Intersection point x = 2

    // Number of intervals for integration
    int n = 1000;  // Higher value for better accuracy

    // Calculate area
    double area = integrate(parabola, line, a, b, n);
    
    // Print the result to a text file
    FILE *file = fopen("area_between_curves.txt", "w");
    if (file != NULL) {
        fprintf(file, "Area between the curves x^2 = 4y and x = 4y - 2: %.4f\n", area);
        fclose(file);
        printf("Area calculated and saved to area_between_curves.txt\n");
    } else {
        printf("Error opening file for writing.\n");
    }

    return 0;
}

