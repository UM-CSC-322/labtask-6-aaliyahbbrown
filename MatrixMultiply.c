#include <stdio.h>
#include <stdlib.h>

double *input_matrix(int *numRows, int *numColumns, char *name) {
  double *matrix;

  // get user input
  printf("Enter the number of rows and columns of %s: ", name);
  scanf("%d %d", numRows, numColumns);

  // create space for matrix using malloc. creates space based on user input
  matrix = (double *)malloc((*numRows)* (*numColumns) * sizeof(double));

  //enter the values for the matrix based on size input 
  printf("Enter the values of the matrix %s: ", name);
  for (int i = 0; i < (*numRows * *numColumns);i++) {
    scanf("%lf", &matrix[i]);
  }
  return matrix;
}

int matrix_multiply(double *matrix1, int matrixOneRows, int matrixOneCol, double *matrix2, int matrixTwoRows, int matrixTwoCol, double *result) {
//the column of 1 must equal the row of 2. (m * n)(n *p)
  if (matrixOneCol != matrixTwoRows) {
    printf("Invalid mulitplication");
    return 0;
  } else {
    // multiply the matrices
    for (int i = 0; i < matrixOneRows; i++) {
      for(int j =0; j < matrixTwoCol; j++){
        result[i * matrixTwoCol + j] = 0;
        for (int k = 0; k < matrixTwoRows; k++) {
          result[i * matrixTwoCol + j] += matrix1[i * matrixOneCol + k] * matrix2[k * matrixTwoCol + j];
        }
      } 
    }  
  return 1; //successful!
  }  
}

void output_matrix(double *matrix, int numRows, int numColumns ) {
  //output the input matrices. 
  for (int i = 0; i < numRows;i++) {
    for (int j =0; j < numColumns;j++) {
      printf("%.2lf ", matrix[i * numColumns + j]);
    }
    printf("\n");
  }
  //return matrix; 
}

int main(void) {

  double *m1, *m2, *m3;
  int m1_rows, m1_columns, m2_rows, m2_columns;

  // fill in by rows first not columns
  if (((m1 = input_matrix(&m1_rows, &m1_columns, "Matrix 1")) != NULL) &&
      ((m2 = input_matrix(&m2_rows, &m2_columns, "Matrix 2")) != NULL) &&
      ((m3 = malloc(m1_rows * m2_columns * sizeof(double))) != NULL)) {
    printf("Matrix 1\n");
    output_matrix(m1, m1_rows, m1_columns);
    printf("Matrix 2\n");
    output_matrix(m2, m2_rows, m2_columns);
    if (matrix_multiply(m1, m1_rows, m1_columns, m2, m2_rows, m2_columns, m3)) {
      printf("Product\n");
      output_matrix(m3, m1_rows, m2_columns);
      free(m1);
      free(m2);
      free(m3);
      return (0);
    } else {
      printf("Error in dimensions\n");
      free(m1);
      free(m2);
      free(m3);
      return (-1);
    }
  } else {
    free(m1);
    free(m2);
    free(m3);
    printf("Error allocating memory\n");
    return (-2);
  }
}

