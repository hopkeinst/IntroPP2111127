/******************************************************************************
* FILE: mpi_mm.c
* DESCRIPTION:  
*   MPI Matrix Multiply - C Version
*   In this code, the master task distributes a matrix multiply
*   operation to numtasks-1 worker tasks.
*   NOTE:  C and Fortran versions of this code differ because of the way
*   arrays are stored/passed.  C arrays are row-major order but Fortran
*   arrays are column-major order.
* AUTHOR: Blaise Barney. Adapted from Ros Leibensperger, Cornell Theory
*   Center. Converted to MPI: George L. Gusciora, MHPCC (1/95)
* LAST REVISED: 04/13/05
******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define NRA 8                /* number of rows in matrix A */
#define NCA 5                 /* number of columns in matrix A */
#define NCB 5                  /* number of columns in matrix B */
#define MASTER 0               /* taskid of first task */
#define FROM_MASTER 1          /* setting a message type */
#define FROM_WORKER 2          /* setting a message type */

int main (int argc, char *argv[])
{
int	numtasks,              /* number of tasks in partition */
	taskid,                /* a task identifier */
	numworkers,            /* number of worker tasks */
	source,                /* task id of message source */
	dest;                  /* task id of message destination */
char	mtype;                 /* message type */
int rows,                  /* rows of matrix A sent to each worker */
	averow, extra, offset, /* used to determine rows sent to each worker */
	i, j, k, rc;           /* misc */
int	matA[NRA][NCA],           /* matrix A to be multiplied */
	matB[NRA][NCA],           /* matrix B to be multiplied */
	matC[NRA][NCA],           /* result matrix C */
    tMatC[NRA][NCA];
MPI_Status status;

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
if (numtasks < 2 ) {
  printf("Need at least two MPI tasks. Quitting...\n");
  MPI_Abort(MPI_COMM_WORLD, rc);
  exit(1);
  }
numworkers = numtasks-1;
    int totalE = NRA*NCA;


/**************************** master task ************************************/
   if (taskid == MASTER)
   {
      printf("mpi_mm has started with %d tasks.\n",numtasks);
      printf("Initializing arrays...\n");
      for (i=0; i<NRA; i++){
         for (j=0; j<NCA; j++){
            matA[i][j] = (i+j);
            printf("i=%d j=%d %d\n", i, j, matA[i][j]);
         }
      }
      for (i=0; i<NRA; i++){
         for (j=0; j<NCA; j++){
            matB[i][j]= i*j;
            printf("i=%d j=%d %d\n", i, j, matB[i][j]);
         }
      }
       printf("%d %d %d \n", matA[0][0], matA[1][1], matA[2][2]);
       
       printf("print matrix\n################\n\n");
       printf("first matrix\n");
       for(i=0;i<NRA;i++){
           for(j=0;j<NCA;j++){
               printf(" %d ", matA[i][j]);
           }
           printf("\n");
       }
       printf("second matrix\n");
       for(i=0;i<NRA;i++){
           for(j=0;j<NCA;j++){
               printf(" %d ", matB[i][j]);
           }
           printf("\n");
       }

      /* Send matrix data to the worker tasks */
      averow = NRA/numworkers;
      extra = NRA%numworkers;
      offset = 0;
      mtype = 'm';
      for (dest=1; dest<=numworkers; dest++)
      {  	
         //printf("Sending %d rows to task %d offset=%d\n",rows,dest,offset);
         MPI_Send(&matA[0][0], totalE, MPI_INT, dest, mtype,
                   MPI_COMM_WORLD);
         MPI_Send(&matB[0][0], totalE, MPI_INT, dest, mtype, MPI_COMM_WORLD);
      }

      /* Receive results from worker tasks */
      mtype = 'w';
      for (i=1; i<=numworkers; i++)
      {
         source = i;
          printf("Source %d\n", source);
          printf("%d\n", matC[7][5]);
          printf("%d\n", tMatC[7][5]);
          
         MPI_Recv(&matC, totalE, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
       printf("Source=%d | Tag=%d | Error=%d\n", status.MPI_SOURCE, status.MPI_TAG, status.MPI_ERROR);
          printf("%d\n", matC[7][5]);
          printf("%d\n", tMatC[7][5]);
         printf("Received results from task %d\n",source);
      }

      /* Print results */
      printf("******************************************************\n");
      printf("Result Matrix:\n");
      for (i=0; i<NRA; i++)
      {
         printf("\n"); 
         for (j=0; j<NCA; j++) 
            printf(" %d ", matC[i][j]);
      }
      printf("\n******************************************************\n");
      printf ("Done.\n");
   }


/**************************** worker task ************************************/
   if (taskid > MASTER)
   {
      mtype = 'm';
      MPI_Recv(&matA, totalE, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
       printf("Source=%d | Tag=%d | Error=%d\n", status.MPI_SOURCE, status.MPI_TAG, status.MPI_ERROR);
      MPI_Recv(&matB, totalE, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
        printf("In slave\n");
       printf("Source=%d | Tag=%d | Error=%d\n", status.MPI_SOURCE, status.MPI_TAG, status.MPI_ERROR);
      for (k=0; k<NCA; k++){ // rows
         for (i=0; i<NRA; i++) // columns
         {
             tMatC[i][k] = matA[i][k] + matB[i][k];
             printf("k=%d | i=%d | matA=%d | matB=%d | matC=%d\n",k,i,matA[i][k],matB[i][k],tMatC[i][k]);
         }
      }
       printf("tMatC %d \n",tMatC[7][4]);
       printf("Rows x Columns = %d\n", (NRA*NCA));
       
      mtype = 'w';
       int test[8][5] = {{1,2,3,4,5}, {6,7,8,9,0}, {0,1,2,3,4}, {5,6,7,8,9}, {9,0,1,2,3}, {4,5,6,7,8}, {8,9,0,1,2}, {3,4,5,6,7}};
       printf("test %d \n",test[7][4]);
       MPI_Send(&tMatC[0][0], totalE, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
       printf("tMatC %d \n",tMatC[7][4]);
       printf("test %d \n",test[7][4]);
       printf("End worker\n\n");
   }
   MPI_Finalize();
}
