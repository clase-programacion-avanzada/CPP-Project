# Proyecto programación avanzada C++ - Hellbank

## Enunciado

Hellbank es un banco que se dedica a la administración de cuentas bancarias. El banco tiene una serie de clientes que pueden tener una o más cuentas bancarias. Estas cuentas, a su vez, pueden tener una o más transacciones. Las transacciones pueden ser de dos tipos: crédito o débito.

Este banco usa un formato especial de archivos para guardar la información de los clientes, la extensión de estos archivos es `.hbt` y es de tipo binario. Dentro de este archivo se organiza la información de la siguiente manera:

```
Número de clientes (1 byte)
Clientes (variable) // Depende del número de clientes

    # Por cada cliente
    ID del cliente (10 bytes) // Arreglo de caracteres
    Nombre del cliente (20 bytes)
    Número de cuentas (1 byte)

    Cuentas (variable) // Depende del número de cuentas

        # Por cada cuenta
        Número de cuenta (10 bytes) // Arreglo de caracteres
        Tipo de cuenta (1 byte) // Puede ser 'A' para ahorros o 'C' para corriente
        Número de transacciones(1 byte)

        Transacciones(variable) // Depende del número de transacciones

            # Por cada transacción
            Tipo de transacción (1 byte) // Puede ser 'C' para crédito o 'D' para débito
            Monto en centavos(8 bytes)
```

Parte del trabajo ya fue realizado por uno de sus compañeros, pero desafortunadamente no pudo terminarlo (y tampoco usó las mejores prácticas de programación, pero está lo suficientemente bien para lo que se necesita). En el proyecto, se va a encontrar con un programa que lee un archivo de texto llamado [`entry_point.txt`](entry_point.txt) que contiene la información inicial de los clientes y sus cuentas. El programa lee este archivo y sobrescribe la información de los clientes si no existe el archivo `customers.hbt`.

Se le ha pedido que desarrolle las siguientes funcionalidades:

1. Se debe definir una estructura que represente una transacción según la especificación del archivo `.hbt`. (0.25)</br></br>
2. Se debe definir una estructura que represente una cuenta bancaria según la especificación del archivo `.hbt`. (0.25)</br></br>
3. Se debe definir una estructura que represente un cliente según la especificación del archivo `.hbt`. (0.25)</br></br>
4. Desarrolle una función que escriba un archivo `.hbt` con la información de los clientes y sus cuentas. (1.0) </br></br>
5. Desarrolle una función que permita ver la suma de los montos de las transacciones de un tipo particular para una cuenta de un cliente (debe permitir al usuario seleccionar el cliente, la cuenta y el tipo de transacción que desea ver).</br></br>
6. Desarrolle una función que permita ver la el saldo de una cuenta de un cliente (debe permitir al usuario seleccionar el cliente y la cuenta que desea ver), el saldo es la suma de los montos de las transacciones de tipo débito menos la suma de los montos de las transacciones de tipo crédito. Asuma un saldo inicial de 0.</br></br>
7. Desarrolle una función que permita generar un reporte de clientes como el mostrado en el archivo [example_report.txt](example_report.txt).</br></br>
8. Permita al usuario leer el archivo `customers.hbt` y realizar las operaciones anteriores. (Tenga en cuenta que en este problema, no le va a ser útil la librería BinaryFileHandler.h que se le ha proporcionado, ya que el tamaño de los datos es variable).</br></br>

## Recursos en línea

- [Binary Files](https://www.eecs.umich.edu/courses/eecs380/HANDOUTS/cppBinaryFileIO-2.html) [Artículo].
- [Difference between cpp text files and binary files](https://www.geeksforgeeks.org/difference-between-cpp-text-file-and-binary-file/) [Artículo].