## MPI

Aquí se encuentra el desarrollo de la segunda evaluación de Introducción a la Computación Paralela.

#### Contenido

Se pueden observar 5 archivos los cuales son:
- **addition-and-subtraction-of-matrices.c** Archivo con el código asignado por el docente y se encuentra en [https://www.studytonight.com/c/programs/array/addition-and-subtraction-of-matrices](https://www.studytonight.com/c/programs/array/addition-and-subtraction-of-matrices). Consiste en un código en C que permite sumar dos matrices *(arreglo de 2 dimensiones)* de igual cantidad de filas y columnas.
- **mpi_addition-and-subtraction-of-matrices.sbach** Archivo para correr automaticamente el código tanto en serial como paralelizado en **Guane** *(supercomputadora de la Universidad Industrial de Santander)*. En este mismo documento, más abajo se explica cómo realizarlo.
- **mpi_addition-and-subtraction-of-matrices.c** Archivo modificado a partir de 'addition-and-subtraction-of-matrices.c'. Se usa MPI *(Message Passing Interface)* para paralelizar, mediante la instrucción 'pragma'
- **outputMPI_addition-and-subtraction-of-matrices.txt** Archivo de texto en donde se encuentran las salidas que tiene el código tanto en serial como en paralelo. Estas salidas serían las que normalmente se verían en la pantalla o consola al interactuar con el usuario más los adicionales que se coloquen en el archivo '.sbatch'
- **errorMPI_addition-and-subtraction-of-matrices.err** Archivo que permite visualizar los errores que se llegarían a generar al ejecutar el archivo '.sbatch' y que no permiten que llegue a buen término *(se genere la salida anteriormente detallada)*
- **serial_addition-and-subtraction-of-matrices.c** Es el archivo *addition-and-subtraction-of-matrices.c* modificado, que se ejecuta en serial *(sin paralelizar)*.
- **omp_addition-and-subtraction-of-matrices.c** Archivo con paralelización en OpenMP de la suma y resta de matrices. 
- **tiempos.txt** Archivo de texto que contiene la duración de tiempo de ejecución de cada uno de las formas del código *(Serial, OpenMP y MPI)* en milisegundos. Este sería el resultado final de ejecutar el archivo *sbatch* en el servidor o computadora para comparar la eficiencia de las formas de ejecutar el mismo código.

#### Implementación en *GUANE*

Una idea adicional a la paralelización es poderla implementar en la supercomputadora *GUANE*. Para esto es necesario subir cuatro archivos *('mpi__addition-and-subtraction-of-matrices.c' y 'omp_addition-and-subtraction-of-matrices.sbach' que corresponden a esta evaluación y 'omp_addition-and-subtraction-of-matrices.c', 'serial_addition-and-subtraction-of-matrices.c' para realizar la comparación de tiempo respectiva)* en nuestra sesión de usuarios, ya sea utilizando JupyterHub o SSH.

Nos ubicamos en la carpeta donde se encuentran estos archivos *(MPI)*, para posteriormente ejecutar la instrucción 'sbatch mpi_addition-and-subtraction-of-matrices.sbach' y esperamos a que haya los recursos disponibles, se desarrolla las instrucciones respectivas y se generan los archivos de salida.

Dentro del archivo '.sbatch' lo que se realiza es solicitar los recursos de la supercomputadora: partición, nombre del trabajo, número de nodos, archivos de salida, entre otros. Aquí se genera el archivo de salida/ejecución del código realizado '.c', que será el que la máquina correrá y dará los resultados en 'outputMPI_addition-and-subtraction-of-matrices.txt'.

Un archivo resultado importante es 'tiempos.txt' que contiene la demora de ejecución, en milisegundos, de cada implementación del mismo código *(Serial, OpenMP, MPI)*.
