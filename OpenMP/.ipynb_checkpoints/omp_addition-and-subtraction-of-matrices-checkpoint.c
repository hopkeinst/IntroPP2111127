/*
  Parallelization of the code 'addition-and-subtraction-of-matrices.c' that consists of the addition and subtraction of don square matrices of order n.

  For this task, the interaction with the user has been eliminated so that everything is done by the computer automatically, using the random library.

  In each session that changes are made, they will be commented respectively.

  Modified by: Jorge Saul Castillo Jaimes - 2111127 - hopkeinst@gmail.com - Student UIS

  OpenMP will be used to parallelize, taking into account the concepts seen in the course 'Introduction to Parallel Computing'

  File: omp_addition-and-subtraction-of-matrices.c

  IMPORTANT !!! Comments in Spanish. It will soon be translated to English.
*/

#include<stdio.h>
#include<stdlib.h>
// Importamos la librería de OpenMP
#include<omp.h>

// Funcion para generar numeros aleatorios
int randBetween(int min, int max)
{
    return (int)(((double)rand()/RAND_MAX)*(max-min)+min);
}

int main()
{
    printf("\n\n\t\tStudytonight - Best place to learn\n\n\n");

    int n, m, c, d, first[10][10], second[10][10], sum[10][10], diff[10][10];

    // El tamaño de las matrices, de manera aleatorio
    m = randBetween(2, 10);
    n = randBetween(2, 10);

    //Se llenan las matrices de manera aletoria
    // Paralelizamos el llenado
    // Se van a compartir los datos de las matrices y su tamaño, pero el indice si va a ser de cada paralelizacion
    #pragma omp parallel shared (first, second, m, n) private(c, d)
    {
    #pragma omp parallel for
    for(c = 0; c < m; c++)   // to iterate the rows
        for(d = 0; d < n; d++)   // to iterate the columns
            first[c][d] = randBetween(-20, 20); // Se llena de manera aleatoria

    #pragma omp parallel for
    for(c = 0; c < m; c++)   // to iterate the rows
        for(d = 0; d < n; d++)   // to iterate the columns
            second[c][d] = randBetween(-20, 20); // Se llena de manera aleatoria
    }
    /*
        printing the first matrix
    */
    printf("\n\nThe first matrix is: \n\n");
    for(c = 0; c < m; c++)   // to iterate the rows
    {
        for(d = 0; d < n; d++)   // to iterate the columns
        {
            printf("%d\t", first[c][d]);
        }
    printf("\n");
    }

    /* 
        printing the second matrix
    */
    printf("\n\nThe second matrix is: \n\n");
    for(c = 0; c < m; c++)   // to iterate the rows
    {
        for(d = 0; d < n; d++)   // to iterate the columns
        {
            printf("%d\t", second[c][d]);
        }
    printf("\n");
    }

    /* 
        finding the SUM of the two matrices 
        and storing in another matrix sum of the same size
    */
    // Se vuelve a paralelizar, cambiando lo compartido y privado segun el caso
    #pragma omp parallel shared (first, second, sum) private(c, d)
    {
    #pragma omp parallel for
    for(c = 0; c < m; c++)
        for(d = 0; d < n; d++)
            sum[c][d] = first[c][d] + second[c][d];
    }
    // printing the elements of the sum matrix
    printf("\n\nThe sum of the two entered matrices is: \n\n");
    for(c = 0; c < m; c++)
    {
        for(d = 0; d < n; d++)
        {
            printf("%d\t", sum[c][d]);
        }
        printf("\n");
    }

    /*
        finding the DIFFERENCE of the two matrices 
        and storing in another matrix difference of the same size
    */
    #pragma omp parallel shared (first, second, diff) private(c, d)
    {
    #pragma omp parallel for
    for(c = 0; c < m; c++)
        for(d = 0; d < n; d++)
            diff[c][d] = first[c][d] - second[c][d];
    }
    // printing the elements of the diff matrix
    printf("\n\nThe difference(subtraction) of the two entered matrices is: \n\n");
    for(c = 0; c < m; c++)
    {
        for(d = 0; d < n; d++)
        {
            printf("%d\t", diff[c][d]);
        }
        printf("\n");
    }

    printf("\n\n\t\t\tCoding is Fun !\n\n\n");
    return 0;
}