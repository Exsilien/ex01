#include <stdio.h>
#include <stdlib.h>

typedef enum err {ok, bad} error;

unsigned int n = 0;


error CreateMatrix(int*** matrix) {
  error res = ok;
  *matrix = (int**)calloc(n, sizeof(int*));
  if(!*matrix) {
    res = bad;
  } else {
    for (int i=0;i < n;++i) {
      (*matrix)[i] = (int*)calloc(n, sizeof(int));
      if(!(*matrix)[i]) {
        for(int j=0;j < i;++j) {
          free(*(matrix)[j]);
        }
        free(*matrix);
        res = bad;
        break;
      }
    } 
  }
  return res;
}

error FillMatrix(int** matrix) {
  error res = ok;
  for(int i=0;i < n;++i) {
    for(int j=0;j < n;++j) {
      int num = 0;
      if (scanf("%d", &num)) matrix[i][j] = num;
      else {
        res = bad;
        break;
      }
    }
  }
  return res;
}

void MultMatrix(int **mat1, int** mat2, int** res) {
  for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = 0;
            for (int k = 0; k < n; k++) {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    } 
}

void displayMatrix(int **matrix) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
          if (j == 0) printf("%d", matrix[i][j]);
          else printf(" %d", matrix[i][j]);
            
        }
        if (i + 1 != n) printf("\n");
    }
}

void FreeMatrix(int **matrix) {
  for(int i=0;i < n;++i) free(matrix[i]);
  free(matrix);
}

int main() {
  int **matrix_a, **matrix_b, **res;
  if (scanf("%u", &n) != 1 || CreateMatrix(&matrix_a) || CreateMatrix(&matrix_b) || CreateMatrix(&res) || FillMatrix(matrix_a) || FillMatrix(matrix_b)) {
    printf("n/a");
  } else {
    MultMatrix(matrix_a, matrix_b, res);
    displayMatrix(res);
    FreeMatrix(matrix_a);
    FreeMatrix(matrix_b);
    FreeMatrix(res);
  }
  return 0;
} 