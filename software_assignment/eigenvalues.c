#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>

#define MAX_ITER 1000  // Increased maximum iterations
#define EPSILON 1e-14  // Increased precision

// Structure to store complex numbers
typedef struct {
    double real;
    double imag;
} ComplexNum;

// Function to print matrix
void printMatrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to create a matrix
double** createMatrix(int n) {
    double **matrix = (double**)malloc(n * sizeof(double*));
    if (matrix == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)calloc(n, sizeof(double));  // Using calloc for zero initialization
        if (matrix[i] == NULL) {
            printf("Memory allocation failed!\n");
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            exit(1);
        }
    }
    return matrix;
}

// Function to free matrix memory
void freeMatrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to copy matrix
void copyMatrix(double **src, double **dst, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

// Function to balance matrix for better numerical stability
void balanceMatrix(double **matrix, int n) {
    const double RADIX = 2.0;
    const double SQRDX = RADIX * RADIX;
    int done = 0;
    
    while (!done) {
        done = 1;
        for (int i = 0; i < n; i++) {
            double r = 0.0, c = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    c += fabs(matrix[j][i]);
                    r += fabs(matrix[i][j]);
                }
            }
            
            if (c != 0.0 && r != 0.0) {
                double g = r / RADIX;
                double f = 1.0;
                double s = c + r;
                
                while (c < g) {
                    f *= RADIX;
                    c *= SQRDX;
                }
                
                g = r * RADIX;
                while (c > g) {
                    f /= RADIX;
                    c /= SQRDX;
                }
                
                if ((c + r) / f < 0.95 * s) {
                    done = 0;
                    g = 1.0 / f;
                    for (int j = 0; j < n; j++) {
                        matrix[i][j] *= g;
                    }
                    for (int j = 0; j < n; j++) {
                        matrix[j][i] *= f;
                    }
                }
            }
        }
    }
}

// Improved Hessenberg transformation
void hessenbergForm(double **matrix, int n) {
    for (int k = 1; k < n - 1; k++) {
        // Find the largest element below diagonal in k-th column
        double max_val = 0.0;
        int max_row = k;
        for (int i = k + 1; i < n; i++) {
            if (fabs(matrix[i][k-1]) > fabs(max_val)) {
                max_val = matrix[i][k-1];
                max_row = i;
            }
        }
        
        if (fabs(max_val) < EPSILON) continue;
        
        // Swap rows and columns if necessary
        if (max_row != k) {
            for (int j = k-1; j < n; j++) {
                double temp = matrix[k][j];
                matrix[k][j] = matrix[max_row][j];
                matrix[max_row][j] = temp;
            }
            for (int j = 0; j < n; j++) {
                double temp = matrix[j][k];
                matrix[j][k] = matrix[j][max_row];
                matrix[j][max_row] = temp;
            }
        }
        
        // Perform elimination
        for (int i = k + 1; i < n; i++) {
            double factor = matrix[i][k-1] / matrix[k][k-1];
            if (fabs(factor) > EPSILON) {
                matrix[i][k-1] = 0.0;
                
                for (int j = k; j < n; j++) {
                    matrix[i][j] -= factor * matrix[k][j];
                }
                
                for (int j = 0; j < n; j++) {
                    matrix[j][k] += factor * matrix[j][i];
                }
            }
        }
    }
}

// Improved Wilkinson shift calculation
double calculateWilkinsonShift(double **matrix, int n) {
    if (n < 2) return 0.0;
    
    double a = matrix[n-2][n-2];
    double b = matrix[n-2][n-1];
    double c = matrix[n-1][n-2];
    double d = matrix[n-1][n-1];
    
    double tr = a + d;
    double det = a * d - b * c;
    double sqrtTerm = sqrt((tr * tr / 4.0) - det);
    double lambda1 = tr / 2.0 + sqrtTerm;
    double lambda2 = tr / 2.0 - sqrtTerm;
    
    return fabs(lambda1 - d) < fabs(lambda2 - d) ? lambda1 : lambda2;
}

// Improved QR decomposition with Wilkinson shift
void qrDecomposition(double **matrix, int n) {
    double shift = calculateWilkinsonShift(matrix, n);
    
    // Apply shift
    for (int i = 0; i < n; i++) {
        matrix[i][i] -= shift;
    }
    
    // Perform QR decomposition using Givens rotations
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (fabs(matrix[j][i]) > EPSILON) {
                double r = hypot(matrix[i][i], matrix[j][i]);
                double c = matrix[i][i] / r;
                double s = -matrix[j][i] / r;
                
                // Apply Givens rotation
                for (int k = i; k < n; k++) {
                    double temp = matrix[i][k];
                    matrix[i][k] = c * temp - s * matrix[j][k];
                    matrix[j][k] = s * temp + c * matrix[j][k];
                }
                
                for (int k = 0; k < n; k++) {
                    double temp = matrix[k][i];
                    matrix[k][i] = c * temp - s * matrix[k][j];
                    matrix[k][j] = s * temp + c * matrix[k][j];
                }
            }
        }
    }
    
    // Remove shift
    for (int i = 0; i < n; i++) {
        matrix[i][i] += shift;
    }
}

// Improved convergence check
int hasConverged(double **matrix, int n) {
    for (int i = 1; i < n; i++) {
        double threshold = EPSILON * (fabs(matrix[i-1][i-1]) + fabs(matrix[i][i]));
        if (fabs(matrix[i][i-1]) > threshold) {
            return 0;
        }
    }
    return 1;
}

// Function to find eigenvalues
void findEigenvalues(double **matrix, int n, ComplexNum *eigenvalues) {
    double **work_matrix = createMatrix(n);
    copyMatrix(matrix, work_matrix, n);
    
    // Apply initial transformations
    balanceMatrix(work_matrix, n);
    hessenbergForm(work_matrix, n);
    
    // Main iteration loop
    int iter = 0;
    int size = n;
    while (size > 1 && iter < MAX_ITER) {
        if (hasConverged(work_matrix, size)) {
            // Extract eigenvalue
            eigenvalues[size-1].real = work_matrix[size-1][size-1];
            eigenvalues[size-1].imag = 0.0;
            size--;
        } else {
            qrDecomposition(work_matrix, size);
            iter++;
        }
    }
    
    if (size == 1) {
        eigenvalues[0].real = work_matrix[0][0];
        eigenvalues[0].imag = 0.0;
    }
    
    freeMatrix(work_matrix, n);
}

int main() {
    int n;
    printf("Enter the order of the matrix: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Invalid matrix size!\n");
        return 1;
    }
    
    // Create and input matrix
    double **matrix = createMatrix(n);
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
    
    // Array to store eigenvalues
    ComplexNum *eigenvalues = (ComplexNum*)calloc(n, sizeof(ComplexNum));
    if (eigenvalues == NULL) {
        printf("Memory allocation failed!\n");
        freeMatrix(matrix, n);
        return 1;
    }
    
    // Find eigenvalues
    findEigenvalues(matrix, n, eigenvalues);
    
    // Print eigenvalues
    printf("\nEigenvalues are:\n");
    for (int i = 0; i < n; i++) {
        if (fabs(eigenvalues[i].imag) < EPSILON) {
            printf("%lf\n", eigenvalues[i].real);
        } else {
            printf("%lf + %lfi\n", eigenvalues[i].real, eigenvalues[i].imag);
        }
    }
    
    // Free memory
    freeMatrix(matrix, n);
    free(eigenvalues);
    
    return 0;
}
