## OpenMP

Aquí se encuentra el desarrollo de la primera evaluación de Introducción a la Computación Paralela.

#### Contenido

Se pueden observar 5 archivos los cuales son *(ordenados por orden de uso e importancia)*:
- **addition-and-subtraction-of-matrices.c** Archivo suministrado por el docente. Consiste en un código en C que permite sumar dos matrices *(arreglo de 2 dimensiones)* de igual tamaño.
- **omp_addition-and-subtraction-of-matrices.c** Archivo modificado a partir de 'addition-and-subtraction-of-matrices.c'. Se usa OpenMP para paralelizar, mediante la instrucción 'pragma'
- **omp_addition-and-subtraction-of-matrices.sbach** Archivo para correr automaticamente el código paralelizado en la supercomputadora de *Guane*. En este mismo dcoumento, más abajo se explica cómo realizarlo.
- **output_addition-and-subtraction-of-matrices.txt** Archivo de texto en donde se encuentran las salidas que tiene el código paralelizado. Estas salidas serían las que normalmente se verían en la pantalla o consola al interactuar con el usuario más los adicionales que se coloquen en el archivo '.sbatch'
- **error_addition-and-subtraction-of-matrices.err** Archivo que permite visualizar los errores que se llegarían a generar al ejecutar el archivo '.sbatch' y que no permiten que llegue a buen término *(se genere la salida anteriormente detallada)*

#### Implementación en *GUANE*

Una idea adicional a la paralelización es poderla implementar en la supercomputadora *GUANE*. Para esto es necesario subir dos archivos *('omp_addition-and-subtraction-of-matrices.c', 'omp_addition-and-subtraction-of-matrices.sbach')* en nuestra sesión de usuarios, ya sea utilizando JupyterHub o SSH.

Nos ubicamos en la carpeta donde se encuentran estos archivos, para posteriormente ejecutar la instrucción 'sbatch omp_addition-and-subtraction-of-matrices.sbach' y esperamos a que haya los recursos disponibles, se desarrolla las instrucciones respectivas y se generan los archivos de salida.

Dentro del archivo '.sbatch' lo que se realiza es solicitar los recursos de la supercomputadora: partición, nombre del trabajo, número de nodos, archivos de salida, entre otros. Aquí se genera el archivo de salida/ejecución del código realizado '.c', que será el que la máquina correrá y dará los resultados en 'output_addition-and-subtraction-of-matrices.txt'
