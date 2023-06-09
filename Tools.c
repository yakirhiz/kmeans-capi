#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sc_header.h"


/*This module holds functions used as tools for the main Spec Clustering Algorithm*/

//for debugging
void printHello(void){
    puts("hello");
};

// reads observations from a file (same format as previous hw)
// used for debugging
double *readFile(int d, int N, char *path) {
    double *N_observations;
    int i, j;

/*  N_observations = matrix of size N*d*/
    N_observations = (double*) malloc((d*N) * sizeof(double));
    MALLOC_CHECK(N_observations)

    if (N_observations  == NULL){
        puts("\nProblem in reading Observations file\n");
    }

    FILE *f = fopen(path, "r");

    /* Fill N_observations according to the input file */
    for (i = 0; i < N; i++) {
        for (j = 0; j < d; j++) {
            fscanf(f ,"%lf,", &N_observations[i*d + j]);
        }
    }
    fclose(f);
    return N_observations;
}

/* Prints a Matrix of dimentions nxd*/
void printMat(const double *mat, int n, int d){
    int i;
    int j;

    for (i=0; i<n; i++){
        for (j=0; j<d; j++){
            /* we reached a new row*/
            if (j == d-1){
                printf("%lf\n", mat[i*d + j]);
            } else {
                printf("%lf,", mat[i*d + j]);
            }
        }
    }
}

/* input: 2 vectors of the same size
 * returns: the euclidean distance between vec1 and vec2, i.e. |vec1-vec2|^2 */
double euclidDist(const double vec1[], const double vec2[], int size){
    int i;
    double sum = 0;

    for (i = 0; i < size; i++){
        sum += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
    }
	
    return sum;
}

// input: row - vector, d - dimension
// ouput: sum of elements
double sumRow(double *row, int d){
    int i;
    double sum = 0;

    for (i = 0; i < d; i++){
        sum += row[i];
    }

    return sum;
}


double normColumn(const double *mat, int rows, int col){
    int i;
    double sum = 0;

    for (i=0; i<rows; i++){
        sum += mat[i*rows + col]*mat[i*rows + col];
    }

    return sqrt(sum);
}

// input:   matrices A,B nxn and columns colA & colB
// output:   dot product of column "colA" of A  and column "colB" of B
double dotCols(const double *A, int colA, const double *B, int colB, int n){
    int i;
    double dot_product = 0;

    for (i=0; i<n; i++){
        dot_product += A[i*n + colA] * B[i*n + colB];
    }

    return dot_product;
}

// input:   mats as 1D array - mat1 -> n1xd1, mat2 -> n2xd2 where d1==n2
// output:  mat -> n1xd2
double *multMat(double *mat1,int n1, int d1, double *mat2, int n2, int d2){
    int i, j, k;
    double val_ij;

    if(d1 != n2){
        puts("\n invalid matrix multiplication\n");
        return NULL;
    }

    double *res = (double *) calloc(n1*d2, sizeof(double));
    MALLOC_CHECK(res)

    for (i=0; i<n1; i++){
        for (j=0; j<d2; j++){
            val_ij = 0;
            for (k=0; k<d1; k++){
                val_ij += mat1[i*n1 + k]*mat2[k*n2 + j];
            }
            res[i*n1 + j] = val_ij;
        }
    }

    return res;

}

// Comparison function with regards to EPSILON difference. used for qsort()
// input:  a, b
// output: int > 0 iff a > b
//         int < 0 iff a < b
//         0 else
int comparefunc (const void * a, const void * b){
    double A = *((double *) a);
    double B = *((double *) b);

    double res = A-B;
    if (fabs(res) < EPSILON){
        return 0;
    } else if (res<0){
        return -1;
    } else {
        return 1;
    }

}
