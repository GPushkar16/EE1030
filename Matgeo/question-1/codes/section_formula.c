#include <stdio.h>

void section_formula(double x1, double y1, double x2, double y2, double m, double n, double* px, double* py) {
    *px = (m * x2 + n * x1) / (m + n);
    *py = (m * y2 + n * y1) / (m + n);
}

