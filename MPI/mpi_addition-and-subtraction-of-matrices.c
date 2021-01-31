/*
  Parallelization of the code 'addition-and-subtraction-of-matrices.c' that consists of the addition and subtraction of don square matrices of order n.

  For this task, the interaction with the user has been eliminated so that everything is done by the computer automatically, using the random library.

  In each session that changes are made, they will be commented respectively.

  Modified by: Jorge Saul Castillo Jaimes - 2111127 - hopkeinst@gmail.com - Student UIS

  OpenMP will be used to parallelize, taking into account the concepts seen in the course 'Introduction to Parallel Computing'

  File: mpi_addition-and-subtraction-of-matrices.c

  IMPORTANT !!! Comments in Spanish. It will soon be translated to English.
*/

#include<stdio.h>
#include<stdlib.h>

// Para tener en cuenta el tiempo
#include<time.h>
#include<sys/time.h>

// Para el uso de MPI
#include<mpi.h>

// Funcion para generar numeros aleatorios
int randBetween(int min, int max)
{
    return (int)(((double)rand()/RAND_MAX)*(max-min)+min);
}

double timevalDiff(struct timeval *a, struct timeval *b)
{
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) - (double)(b->tv_sec + (double)b->tv_usec/1000000);
}

int main(int argc, char* argv[])
{
    FILE* ft;
    struct timeval tIni, tFin;
    double segs;

    int taskid, numtasks, workers;
    int nRowsTask, extraRows, offset, dest, rows;
    int i, j, source;

    int n, m, c, d, first[10][10], second[10][10], sum[10][10], diff[10][10];
    int t1[10][10], t2[10][10], t3[10][10], t4[10][10];

    gettimeofday(&tIni, NULL);
    
    // El tamaño de las matrices, de manera aleatoria
    m = randBetween(2, 10); // filas
    n = randBetween(2, 10); // columnas
    m = 3;
    n = 4;
    MPI_Status status;
    MPI_Request request;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&taskid);

    if(taskid == 0){ // Master
        
        printf("###########################################");
        printf("\n\t--- CODE IN MPI ---\n");
        printf("###########################################\n");

        //Se llenan las matrices de manera aletoria
        for(c = 0; c < m; c++){   // to iterate the rows
            for(d = 0; d < n; d++){  // to iterate the columns
                first[c][d] = randBetween(-20, 20); // Se llena de manera aleatoria
            }
        }
        for(c = 0; c < m; c++){  // to iterate the rows
            for(d = 0; d < n; d++){   // to iterate the columns
                second[c][d] = randBetween(-20, 20); // Se llena de manera aleatoria
            }
        }
        
        // Mostrando las matrices
        printf("\nThe first matrix is: \n");
        for(c = 0; c < m; c++){   // to iterate the rows
            for(d = 0; d < n; d++){   // to iterate the columns
                printf("%d\t", first[c][d]);
            }
            printf("\n");
        }
        printf("\n\nThe second matrix is: \n");
        for(c = 0; c < m; c++){   // to iterate the row
            for(d = 0; d < n; d++){  // to iterate the column
                printf("%d\t", second[c][d]);
            }
            printf("\n");
        }

        // Se realiza calculo para ver cuantas filas de las matrices se pasa a cada 'trabajador'
        workers = numtasks-1; // numero de trabajadores, subprocesos
        nRowsTask = m/workers; // Cantidad de filas a ser tratadas por cada subproceso
        extraRows = m%workers; // El restante de filas, por si no es una division entera
        offset = 0; // Para tener en cuenta desde que fila se pasa a cada subproceso
        // Y ahora, teniendo la cantidad de subprocesos, se les envía para que los realicen
        for(dest = 1; dest <= workers; dest++){
            rows = (dest <= extraRows) ? nRowsTask+1 : nRowsTask;
            MPI_Send(&offset, 1, MPI_INT, dest, 'M', MPI_COMM_WORLD);
            MPI_Send(&rows, 1, MPI_INT, dest, 'M', MPI_COMM_WORLD);
            MPI_Send(&first[offset][0], rows*n*2, MPI_INT, dest, 'M', MPI_COMM_WORLD);
            MPI_Send(&second[offset][0], rows*n*2, MPI_INT, dest, 'M', MPI_COMM_WORLD);
            offset += rows;
        }

        for (i = 1; i <= workers; i++) { // Recibiendo los subprocesos
            source = i;
            MPI_Recv(&offset, 1, MPI_INT, source, 'W', MPI_COMM_WORLD, &status);
            MPI_Recv(&rows, 1, MPI_INT, source, 'W', MPI_COMM_WORLD, &status);
            MPI_Recv(&sum[offset][0], rows*n*2, MPI_INT, source, 'W', MPI_COMM_WORLD, &status);
            MPI_Recv(&diff[offset][0], rows*n*2, MPI_INT, source, 'W', MPI_COMM_WORLD, &status);
        }
        
        // Mostrando resultados
    printf("\n\nThe sum of the two entered matrices is: \n\n");
    for(c = 0; c < m; c++){
        for(d = 0; d < n; d++){
            printf("%d\t", sum[c][d]);
        }
        printf("\n");
    }
    // printing the elements of the diff matrix
    printf("\n\nThe difference(subtraction) of the two entered matrices is: \n\n");
    for(c = 0; c < m; c++){
        for(d = 0; d < n; d++){
            printf("%d\t", diff[c][d]);
        }
        printf("\n");
    }
    
    gettimeofday(&tFin, NULL);
    segs = timevalDiff(&tFin, &tIni);
    printf("\nTiempo de ejecucion en MPI (%d task): %.16g milisegundos\n", taskid, (segs*1000.0));
  
    ft = fopen("tiempos.txt", "a");
    fprintf(ft, "MPI (%d task): %.16g milisegundos\n", taskid, (segs*1000.0));
    fclose(ft);
        
    }

    if(taskid > 0){ // Trabajadores / Subprocesos
        MPI_Recv(&offset, 1, MPI_INT, 0, 'M', MPI_COMM_WORLD, &status);
        MPI_Recv(&rows, 1, MPI_INT, 0, 'M', MPI_COMM_WORLD, &status);
        MPI_Recv(&t1[offset][0], rows*n*2, MPI_INT, 0, 'M', MPI_COMM_WORLD, &status);
        MPI_Recv(&t2[offset][0], rows*n*2, MPI_INT, 0, 'M', MPI_COMM_WORLD, &status);
        
        for(i = 0; i < rows; i++){
            for(j = 0; j < n; j++){
                t3[i][j] = t1[i][j] + t2[i][j];
                t4[i][j] = t1[i][j] - t2[i][j];
                //printf("i=%d | j=%d | f=%d | s=%d | sum=%d | diff=%d \n", i, j, t1[i][j], t2[i][j], t3[i][j], t4[i][j]);
            }
        }
        MPI_Send(&offset, 1, MPI_INT, 0, 'W', MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, 0, 'W', MPI_COMM_WORLD);
        MPI_Send(&t3[offset][0], rows*n*2, MPI_INT, 0, 'W', MPI_COMM_WORLD);
        MPI_Send(&t4[offset][0], rows*n*2, MPI_INT, 0, 'W', MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}