#include <stdio.h>
#include <math.h>

int main() {
    FILE *file;
    file = fopen("parabola_points.txt", "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Generate points for the parabola x^2 = 4y
    float x, y;
    float step = 0.1;  // Step size for x
    float x_max = 10;  // Maximum value of x (you can adjust as needed)

    for (x = -x_max; x <= x_max; x += step) {
        y = (x * x) / 4.0;
        fprintf(file, "%f %f\n", x, y);
    }

    fclose(file);
    printf("Points have been written to parabola_points.txt\n");
    return 0;
}

