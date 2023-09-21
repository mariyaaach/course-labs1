//Один вектор:
//Ненулевому элементу соответствуют две ячейки: первая содержит номер столбца, вторая содержит значение элемента. Нуль
//в первой ячейке означает конец строки, а вторая ячейка содержит в этом случае номер следующей хранимой строки. Нули
//в обеих ячейках являются признаком конца перечня ненулевых элементов разреженной матрицы. 
//Найти элемент матрицы, ближайший к заданному значению. Разделить на него элементы строки и столбца, на
//пересечении которых он расположен. Если таких элементов несколько, обработать все.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100

typedef struct {
    int row;
    int col;
    double real;
    double imaginary;
} ComplexElement;

typedef struct {
    int rows;
    int cols;
    ComplexElement elements[MAX_SIZE];
} SparseMatrix;

void nul(SparseMatrix *matrix){
    ComplexElement el;
    el.col=0;
    el.row=0;
    el.real=0;
    el.imaginary=0;
    for(int i=0; i<(matrix->rows*matrix->cols); i++){
        matrix->elements[i] = el;
    }
}

void initializeMatrix(SparseMatrix *matrix) {
    printf("Enter number of rows: ");
    scanf("%d", &matrix->rows);

    printf("Enter number of columns: ");
    scanf("%d", &matrix->cols);

    nul(matrix);

    int i, j, count;
    printf("Enter number of non-zero elements: ");
    scanf("%d", &count);

    printf("Enter non-zero elements:\n");
    for (i = 0; i < count; i++) {
        ComplexElement element;
        printf("Row: ");
        scanf("%d", &element.row);

        printf("Column: ");
        scanf("%d", &element.col);

        printf("Real part: ");
        scanf("%lf", &element.real);

        printf("Imaginary part: ");
        scanf("%lf", &element.imaginary);

        matrix->elements[i] = element;
    }
}

void printSparseMatrix(SparseMatrix matrix) {
    printf("\nSparse Matrix Representation:\n");
    printf("-----------------------------\n");
    printf("Row\tColumn\tReal\tImaginary\n");
    printf("-----------------------------\n");

    int i;
    for (i = 0; i < MAX_SIZE; i++) {
        ComplexElement element = matrix.elements[i];
        if (element.row == 0 && element.col == 0) {
            break;
        }

        printf("%d\t%d\t%.2f\t%.2f\n", element.row, element.col, element.real, element.imaginary);
    }

    printf("-----------------------------\n");
}

void printMatrix(SparseMatrix matrix) {
    printf("\nMatrix Representation:\n");
    printf("-----------------------\n");

    int i, j;
    for (i = 1; i <= matrix.rows; i++) {
        for (j = 1; j <= matrix.cols; j++) {
            int k;
            for (k = 0; k < MAX_SIZE; k++) {
                ComplexElement element = matrix.elements[k];
                if (element.row == 0 && element.col == 0) {
                    break;
                }

                if (element.row == i && element.col == j) {
                    printf("%.2f+%.2fi\t", element.real, element.imaginary);
                    break;
                }
            }

            if (k == MAX_SIZE) {
                printf("0+0i\t");
            }
        }
        printf("\n");
    }

    printf("-----------------------\n");
}

int findNearestElement(SparseMatrix matrix, double targetReal, double targetImaginary, ComplexElement *nearestElement) {
    int i;
    int found = 0;
    double minDistance = INFINITY;

    for (i = 0; i < MAX_SIZE; i++) {
        ComplexElement element = matrix.elements[i];
        if (element.row == 0 && element.col == 0) {
            break;
        }

        double distance = sqrt(pow(element.real - targetReal, 2) + pow(element.imaginary - targetImaginary, 2));
        if (distance < minDistance) {
            *nearestElement = element;
            minDistance = distance;
            found = 1;
        }
    }

    return found;
}

void divideByNearestElement(SparseMatrix *matrix, ComplexElement nearestElement) {
    int i;
    for (i = 0; i < MAX_SIZE; i++) {
        ComplexElement element = matrix->elements[i];
        if (element.row == 0 && element.col == 0) {
            break;
        }

        if (element.row == nearestElement.row || element.col == nearestElement.col) {
            element.real /= nearestElement.real;
            element.imaginary /= nearestElement.imaginary;
            matrix->elements[i] = element;
        }
    }
}

int main() {
    SparseMatrix matrix;
    initializeMatrix(&matrix);

    printSparseMatrix(matrix);
    printMatrix(matrix);

    double targetReal, targetImaginary;
    printf("\nEnter target element (real part): ");
    scanf("%lf", &targetReal);
    printf("Enter target element (imaginary part): ");
    scanf("%lf", &targetImaginary);

    ComplexElement nearestElement;
    if (findNearestElement(matrix, targetReal, targetImaginary, &nearestElement)) {
        printf("\nNearest Element:\n");
        printf("Row: %d\n", nearestElement.row);
        printf("Column: %d\n", nearestElement.col);
        printf("Real part: %.2f\n", nearestElement.real);
        printf("Imaginary part: %.2f\n", nearestElement.imaginary);

        divideByNearestElement(&matrix, nearestElement);

        printf("\nMatrix after division:\n");
        printMatrix(matrix);
    } else {
        printf("\nNo non-zero elements found in the matrix.\n");
    }

    return 0;
}