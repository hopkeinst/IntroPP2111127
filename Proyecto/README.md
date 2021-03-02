# Pico y cedula
Las medidas de aislamiento y restricción de movilidad se han debido endurecer en los siguientes seis meses, debido a los problemas asociados con la deficiente atención médica, la vulnerabilidad de la población en términos sanitarios y aspectos culturales. Teniendo en cuenta que se tomó la decision de implementar un pico y cédula estricto observando el último dígito de la cédula (dia par = cédula que termina en cero y par, dia impar = cédula que termina en número impar), y utilizando un archivo que contiene los números de cédula para una población especifica obtenido del último censo electoral de 2019, responda las siguientes preguntas:

-¿Cuántas personas con cédula par e impar saldrían en cada dia correspondiente para su pico y cédula de los meses de febrero, marzo y abril? (Tenga en cuenta que cada mes tiene dias diferentes y asignaciones de fecha por dia diferentes).

-¿Cuántas veces las personas con pico y cédula par, pueden salir sin restricción los dias sábado?.

-¿Cuántas personas con pico y cédula impar pueden salir sin restricción los dias domingo?.

-Las personas con cédula de identificación de 10 dígitos son personas de 18 a 20 años. ¿Cuántas son y cómo es la distribución de salida por mes los fines de semana?

-Proporcione datos para dar información de análisis a los tomadores de decisiones políticos y ver si es proporcional y justa la medida del pico y cédula para esa población, observando números pares e impares, tomando, la población en general (cantidad total de habitantes), personas de menos de 20 años (cédulas con diez cifras), personas de mayores de 60 años (Entre 6 y 7 cifras) y extranjeros (cédulas con menos de 7 cifras).

## Solucion propuesta
Para la realizacion del diseño en paralelo se definieron primero 5 tareas: contar dias pares e impares mes 1, contar dias pares e impares mes 2, contar dias pares e impares mes 3, contar cedulas pares e impares y los numeros de digitos en estas y la impresion de las cuentas. Una vez definidas estas tareas se procedio a distribuirla sobre 4 procesos usando MPI:

- proceso master:este proceso realiza lo siguiente:
   - le asigna a los otros tres procesos las tareas de contar dias pares e impares mes 1, contar dias pares e impares mes 2 y contar dias pares e impares mes 3.
   - cuenta cedulas pares e impares y los numeros de digitos en estas.
   - recibe el resultado devuelto por los otros 3 procesos.
   - imprime los resultados de todos los procesos incluyendose.
   
- proceso worker 1:  cuenta los dias pares e impares mes 1, y luego le envia los resultados al proceso master.
- proceso worker 2:  cuenta los dias pares e impares mes 2, y luego le envia los resultados al proceso master.
- proceso worker 3:  cuenta los dias pares e impares mes 3, y luego le envia los resultados al proceso master.

## Observaciones sobre la solucion propuesta
- Esta solucion no es escalable ya que requiere estrictamente de 4 procesos, ni mas ni menos.
- Esta solucion con respecto a una secuencial se acelera de la siguiente manera: sea x1 el tiempo para ejecutar proceso  worker 1, x2 el tiempo para ejecutar  proceso worker 2, x3 el tiempo para ejecutar proceso worker 3, z el tiempo gastado en el mensajeo entre procesos, m el tiempo gastado en contar cedulas pares e impares y los numeros de digitos en estas y r el tiempo para imprimir. Dado lo anterior se tiene que:
  - El tiempo de ejecucion de la solucion secuencial seria x1 + x2 + x3 + m + r 
  - El tiempo de ejecucion de la solucion paralela seria el mayor tiempo gastado entre x1,x2 y x3 + m + r + z; sabiendo que para esta solucion z es pequeño ya que no se requiere mucho mensajeo entre procesos.


## Compilacion y ejecucion
Para compilar se uso el compilador mpicc para generar el ejecutable a partir del codigo fuente. La solucion se lanzo con 4 procesos(master, worker 1, worker 2, worker 3) unicamente en guane. 
