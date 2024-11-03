#include <stdio.h>
#include <math.h>

int main() {
    double c_values[] = {0.48, 0.6, 1.21};
    double B_x = 0; // B as origin (0,0)
    double B_y = 0; // B as origin (0,0)
    double C_x = 6; // C as (6,0)
    double C_y = 0; // C as (6,0)

    FILE *file = fopen("results.txt", "w");
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        double c = c_values[i];
        double A_x = c * cos(M_PI / 4); // 45 degrees in radians
        double A_y = c * sin(M_PI / 4); // 45 degrees in radians
        fprintf(file, "%f, %f, %f, %f\n", c, A_x, A_y, C_x);
    }

    fclose(file);
    return 0;
}

