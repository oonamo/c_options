#include "options.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *matrix;
    int rows;
    int cols;
} Matrix;

Option_t new_matrix(int rows, int cols)
{
    Matrix *matrix = malloc(sizeof(Matrix));
    if (matrix == NULL)
    {
        return None;
    }

    matrix->matrix = malloc(sizeof(int) * rows * cols);
    if (matrix->matrix == NULL)
    {
        return None;
    }

    matrix->rows = rows;
    matrix->cols = cols;

    return Some(matrix);
}

void set_matrix(Matrix *matrix, int *intMatrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            matrix->matrix[i * matrix->cols + j] =
                intMatrix[i * matrix->cols + j];
        }
    }
}

Option_t add_matrices(Matrix *lhs, Matrix *rhs)
{
    if (lhs->rows != rhs->rows || lhs->cols != rhs->cols)
    {
        return None;
    }
    Option_t matrixOpt = new_matrix(lhs->rows, lhs->cols);
    if (!Option_OK(matrixOpt))
    {
        return None;
    }
    Matrix *matrix = unwrap(matrixOpt);
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            int index = i * matrix->cols + j;
            matrix->matrix[index] = lhs->matrix[index] + rhs->matrix[index];
        }
    }
    return Some(matrix);
}

void print_matrix(Matrix* matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            printf("%d ", matrix->matrix[i * matrix->cols + j]);
        }
        printf("\n");
    }
}

void free_matrix(Matrix **matrix)
{
    free((*matrix)->matrix);
    free(*matrix);
    matrix = NULL;
}

int main()
{
    Matrix *identity = unwrap(new_matrix(3, 3));
    Matrix *rref = unwrap(new_matrix(3, 4));

    int identityMatrix[3 * 3] = {
        1, 0, 0, 
        0, 1, 0, 
        0, 0, 1,
    };

    int reducedEchelonForm[] = {
        1, 0, 0, 5, 
        0, 1, 0, 4, 
        0, 1, 0, 8,
    };

    set_matrix(identity, (int *)identityMatrix);
    set_matrix(rref, (int *)reducedEchelonForm);

    printf("Attempting to add this matrix:\n");
    print_matrix(identity);
    printf("With:\n");
    print_matrix(rref);


    Option_t addedMatrix = add_matrices(identity, rref);

    if (!Option_OK(addedMatrix))
    {
      printf("Could not add the two matrices :( \n");
    }

    free_matrix(&identity);
    free_matrix(&rref);
    printf("Done!\n");
}
