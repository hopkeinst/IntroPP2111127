#!/bin/bash

#SBATCH --partition=normal
#SBATCH --ntasks=4
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=2

#SBATCH --job-name=pyc
#SBATCH --output=mpi_resultados.txt
#SBATCH --error=mpi_tiempo.txt

#SBATCH --mail-type=ALL
#SBATCH --mail-user=bassbeat120@hotmail.com

python convert.py 
module load devtools/mpi/openmpi/3.1.4
time mpirun -np 4 mpi_pico_cedula Cedulas.txt

