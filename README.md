# Proyecto Práctico - Programación Avanzada: Sistemas de Monitoreo Biomédico

En este proyecto desarrollará componentes esenciales para un sistema de procesamiento de datos de sensores biomédicos. El proyecto simula un escenario real donde un ingeniero debe procesar lecturas de múltiples sensores para evaluar los signos vitales de pacientes en una unidad de cuidados intensivos.

## Enunciado del Problema

El Hospital Universitario requiere un sistema para procesar datos recopilados de sensores biomédicos. Estos sensores monitorean constantemente a pacientes en la UCI y generan archivos de datos que deben ser analizados para detectar anomalías en los signos vitales.

Los datos de los sensores se almacenan en archivos `.bsf` (Biomedical Sensor Format), que contienen las lecturas en el siguiente formato binario:

### Estructura Sala de UCI

- **ID de la sala** (1 byte): Identifica la sala de UCI donde se encuentran los pacientes.
- **Número de máquinas** (1 byte): Cantidad de máquinas que están monitoreando a los pacientes en la sala.
- **Máquinas** (variable): Un arreglo dinámico de máquinas. Cada máquina tiene un número único y puede monitorear múltiples pacientes.

### Estructura Máquina de UCI

- **Id** (1 byte): Identifica la máquina que está monitoreando al paciente. Cada máquina tiene un número único.
- **Número de mediciones** (4 bytes): Cantidad de mediciones que se están realizando. Cada máquina puede tener múltiples mediciones.
- **Mediciones** (variable): Un arreglo dinámico de mediciones. Cada medición contiene información sobre el paciente y las lecturas de los sensores.

### Estructura de medición

- **ID del Paciente** (11 bytes): Código único que identifica al paciente monitoreado. Este código será de 10 caracteres y corresponde al documento de identidad del paciente.
- **Fecha y Hora** (24 bytes): Momento exacto de la lectura en formato "DD/MM/AAAA HH:MM:ss.sss".
- **Número de Lecturas** (4 bytes): Cantidad de lecturas almacenadas a continuación. El período de lectura varía dependiendo del tipo de sensor, por lo que a una misma hora puede tener distintas lecturas de varios tipos.
- **Lecturas** (variable): Un arreglo dinámico de lecturas.

### Estructura de Lectura

- **Tipo de Sensor** (1 byte): Identifica el tipo de sensor: 'T' (temperatura), 'P' (presión arterial), 'E' (ECG), 'O' (oxímetro).
- **Valor de medida** (4bytes / 8 bytes): Cada lectura consta de un valor double (8 bytes) que representa la medición del sensor. La interpretación depende del tipo de sensor:
  - Temperatura (°C) - Se almacena un solo valor de 8 bytes.
  - Presión arterial (mmHg) - Se almacenan dos valores consecutivos: sistólica y diastólica (4 bytes cada uno).
  - ECG (mV) - Se almacena un solo valor de 8 bytes.
  - Oximetría (% de saturación de oxígeno) - Se almacena un solo valor de 8 bytes.

Su tarea es desarrollar un programa en C++ que pueda procesar estos archivos y generar reportes útiles para el personal médico.

Este sistema se va a ejecutar en una pequeña computadora con linux, por lo que el manejo de la memoria debe ser muy eficiente. Siendo de esta manera, solamente se permitirá el uso del tipo string para separar en tokens los archivos de texto. En el sistema no se podrá usar el tipo string para almacenar los datos, ya que se utilizarán arreglos dinámicos para almacenar las lecturas de los sensores.

En la computadora, existirá un archivo de configuración llamado `configuracion.txt` que contiene los umbrales de alarma para cada tipo de sensor. El formato del archivo es el siguiente (Los comentarios comienzan con `#` y no estarán en el archivo real):

```csv
# Configuración de umbrales para sensores biomédicos
# Formato: TIPO_SENSOR,MIN,MAX
T,36.0,38.0
P_SIS,90,140
P_DIA,60,90
E,-3.858747,1.228621
O,95,100
```

Este archivo contiene los límites inferior y superior para cada tipo de sensor. El sistema debe cargar estos umbrales al inicio y utilizarlos para detectar anomalías en las lecturas de los pacientes.

Adicionalmente, existirá un archivo de texto con los datos de los pacientes de la clínica, que no necesariamente pertenecen a la UCI. Este archivo se llamará `pacientes.csv` y tendrá el siguiente formato:

```csv
# id; tipoDeDocumento; documento; nombres; apellidos; fechaNacimiento; telefono; email; tipoDeSangre; entidadSalud; medicinaPrepagada

1; CC; 123456789; Juan; Pérez; 01/01/1980; 3001234567; juan.perez@example.com; A+; Medimas; Sura
2; TI; 987654321; María; Gómez; 15/05/1990; 3109876543; maría.gómez@example.com; O+; Coomeva;
3; CE; 456789123; Carlos; López; 20/10/1975; 3204567890; carlos.lopez@example.com; B+; Sanitas; Colsanitas
```

## Tareas a Implementar

El proyecto se ha dividido en entregas semanales (cada semana será un sprint). A continuación, se indica las tareas que debe implementar en cada entrega.

>[!WARNING]
> Si no se se entrega una tarea en la semana correspondiente, se debe entregar en la semana siguiente, pero se perderán puntos por retraso. En concreto, se perderán 30 puntos (1.5 en la nota final) por cada semana de retraso.
>
>Por ejemplo, si la tarea de la semana 1 no se entrega en la semana 1, se puede entregar en la semana 2, pero se perderán 30 puntos. Si se entrega en la semana 3, se perderán 60 puntos, y así sucesivamente. Lo mismo aplica para las tareas que se vayan acumulando en las siguientes semanas.
>
> **Esto no aplica para el primer sprint**, que se entregará en la semana 4.

>[!CAUTION]
> Si bien no están prohibidas las herramientas de IA, en caso de generar código con estas herramientas, los integrantes del equipo deben ser capaces de explicar el código generado y demostrar que lo entienden. Si no pueden hacerlo, esa porción de código no será aceptada.
>
> Si se utiliza IA para generar código, se debe indicar en el informe de entrega final, deben incluir el prompt e indicar claramente qué parte del código fue generado por IA y cuál fue escrito por los integrantes del equipo.
>
> Cualquier código que contenga referencias a la clase Vector o similares no será aceptado, ya que se debe utilizar arreglos dinámicos.

### Entrega semana 3 (sprint 1) [Taller de cadenas de caracteres y estructuras]

- **(15 puntos) Definición de Estructuras:**
   Defina las estructuras necesarias para representar:

  - Una lectura de sensor individual
  - Una medición de un paciente
  - Una máquina de UCI
  - Una sala de UCI
  - La información del archivo de configuración
  - La información de un paciente
  - La información de un archivo de pacientes
   
>[!NOTE]
> Cada estructura debe estar dentro de la carpeta libs y debe tener su propio archivo de cabecera.

- **(5 puntos) Menú Principal:**
   Implemente un menú principal que permita al usuario seleccionar entre las siguientes opciones:
  - Cargar archivo de configuración y datos de pacientes
  - Leer archivo `.bsf`
  - Generar reporte de anomalías
  - Calcular estadísticas
  - Exportar datos procesados
  - Salir
   
>[!NOTE]
> El menú debe ser interactivo y permitir al usuario seleccionar opciones mediante un número. No es necesario que, en este sprint, se implemente la funcionalidad de cada opción, solo el menú y la estructura básica del programa.

- **(20 puntos) Separar el archivo de configuración:**
   Desarrolle una función que reciba como parámetro una línea de texto del archivo de configuración, separe los valores y se guarden en un arreglo de caracteres. La función debe retornar un arreglo con los valores de configuración.

- **(20 puntos) Separar el archivo de pacientes:**
   Implemente una función que reciba una línea de texto del archivo de pacientes, separe los valores y los guarde en un arreglo de caracteres. La función debe retornar un arreglo con los datos del paciente.

- **(25 puntos) De cadenas a estructuras:**
   Desarrolle una función que reciba un arreglo de cadenas de caracteres (estas serán las líneas del archivo de configuración o de pacientes, según como corresponda) y cargue los datos en las estructuras definidas anteriormente.

- **(15 puntos) Comparar dos fechas:**
   Implemente una función que compare dos fechas en formato "DD/MM/AAAA HH:MM:ss.sss" y retorne verdadero si la primera fecha es mayor que la segunda, o falso en caso contrario. Esta función será útil para ordenar las lecturas de los pacientes.

>[!NOTE]
> Para todos los casos genere código de prueba que permita verificar el correcto funcionamiento de las funciones implementadas.

### Entrega semana 4 (sprint 2) [Taller de archivos de texto]

- **(40 puntos) Lectura de Archivos de configuración y de pacientes:**
   Desarrolle una función que lea un archivo de configuración y de pacientes; y cargue los datos en las estructuras definidas anteriormente.

- **(25 puntos) Detección de Anomalía en un paciente a partir de una lectura:**
   Implemente una función que analice una lectura de un paciente, distinta a ECG, y detecte si hay anomalías en los datos. La función debe utilizar los límites definidos en el archivo de configuración para determinar si una lectura es anormal.

- **(35 puntos) Reporte de Mediciones de un Paciente:**
   Implemente una función que genere un archivo de texto (`mediciones_paciente_<idDePaciente>.txt`) que contenga todas las lecturas de un paciente específico, ordenadas cronológicamente y agrupadas por tipo de sensor, debe indicar si una lectura es anómala o normal. El formato debe ser claro y legible para el personal médico y debe incluir las mediciones de todos los sensores. Para ECG no es necesario incluir la detección de anomalía, solo se debe incluir el valor de la medición.
   Al final de las lecturas de cada tipo de sensor, debe incluir las estadísticas básicas (mínimo, máximo, promedio) de las lecturas.

>[!NOTE]
> Para el caso del reporte de mediciones, cree mediciones de prueba dentro de su código para verificar el correcto funcionamiento de la función. No es necesario que se lean de un archivo, pero sí que se simule el formato correcto de las lecturas.

### Entrega semana 5 (sprint 3) [Taller de archivos binarios]

- **(30 puntos) Lectura de Archivos BSF:**
   Desarrolle una función que lea un archivo binario `.bsf` y cargue los datos en las estructuras definidas anteriormente. La función debe manejar correctamente los diferentes tipos de sensores y las mediciones asociadas a cada paciente.

- **(30 puntos) Reporte de Anomalías para todos los pacientes:**
   Implemente una función que genere un archivo de texto (`anomalias.txt`) que liste todas las lecturas anómalas (excepto ECG), agrupadas por paciente y ordenados cronológicamente. El formato debe ser claro y legible para el personal médico.

- **(20 puntos) Detección de Anomalía en ECG:**
   Implemente una función que analice las lecturas de ECG de un paciente y detecte si hay anomalías en los datos. Un ECG tiene anomalías si la suma de los valores absolutos de la mínima y la máxima medición es mayor que la suma de los valores absolutos de los límites inferior y superior del ECG definidos en el archivo de configuración.

- **(20 puntos) Exportación de Pacientes con ECG Anómalo:**
   Desarrolle una función que genere un archivo binario con los pacientes que tienen un ECG anómalo. El archivo debe llamarse `pacientes_ecg_anomalos.dat` y tener el siguiente formato:

   - **ID del Paciente** (11 bytes): Código único que identifica al paciente.
   - **ID de la Máquina** (1 byte): Identifica la máquina que está monitoreando al paciente.
   - **Número de Mediciones ECG** (4 bytes): Cantidad de mediciones de ECG que tiene el paciente.
   - **Mediciones ECG** (variable): Un arreglo dinámico de mediciones de ECG, donde cada medición contiene:
   - **Fecha y Hora** (24 bytes): Momento exacto de la lectura en formato "DD/MM/AAAA HH:MM:ss.sss".
   - **Valor de Medida** (8 bytes): Valor de la medición de ECG.

> [!NOTE]
> En este caso, tendrá un archivo pequeño de lecturas y de pacientes con los que podrá probar el funcionamiento de la lectura de archivos binarios y de texto. Para la entrega final, el archivo será bastante más grande.
> 
> En el caso de las lecturas de ECG, tendrá las mediciones de un paciente con un ECG anómalo y otro con un ECG normal. De esta manera, podrá probar el correcto funcionamiento de la detección de anomalías en ECG y la exportación de pacientes con ECG anómalo.

### Entrega semana 6 (sprint 4) [Taller de arreglos dinámicos]

- **(100 puntos) Implementación de Arreglos Dinámicos:**
   En su proyecto, todos los arreglos deben ser dinámicos. Haga los cambios necesarios en las estructuras y funciones para que utilicen arreglos dinámicos en lugar de arreglos estáticos. No se permite el uso de la clase `std::vector` ni ninguna otra clase de la STL que maneje arreglos dinámicos. Tampoco podrá poner un tamaño fijo a los arreglos, ya que el tamaño de los datos puede variar dependiendo del archivo que se esté procesando, su código debe funcionar para cualquier tamaño de archivo.

### Entrega semana 7 (sprint 5) [Pruebas en Orange Pi/ Raspberry Pi / Compuatdor con Linux / Máquina Virtual]

Durante esta semana, se comprobará que el código funciona correctamente en una Raspberry Pi o en una máquina virtual con Linux. Se espera que el código se compile y ejecute sin errores, y que todas las funcionalidades implementadas funcionen correctamente. Se revisarán las siguientes funcionalidades:

- Lectura de archivos de configuración y de pacientes. (20 puntos)
- Lectura de archivos `.bsf`. (20 puntos)
- Generación de reportes de anomalías. (20 puntos)
- Cálculo de estadísticas. (20 puntos)
- Exportación de datos procesados. (20 puntos)

## Entrega

Debe entregar durante la semana 8, en un repositorio de Github o Gitlab, la siguiente documentación:

1. El código fuente.
2. Un README que explique cómo compilar y ejecutar el programa, así como una descripción de las funcionalidades implementadas.
3. Otro archivo markdown que contenga un informe final del proyecto. Este informe debe incluir:
   - Explicación de las estructuras utilizadas.
   - Descripción de las funciones implementadas.
   - Link a las conversaciones de IA utilizadas (si aplica) o prompts utilizados para generar código con IA.

La entrega se realiza en el salón de clases. El profesor va a seguir las indicaciones del repositorio para verificar que el código se compila y ejecuta correctamente. Si el código no compila o no se ejecuta, se considerará una entrega incompleta.

El profesor hará una serie de preguntas sobre el código para verificar que los integrantes del equipo entienden lo que han implementado. Si no pueden responder a las preguntas, se considerará que la entrega no es válida y restará puntos de la nota final.

La nota final del proyecto se calculará con base en las entregas semanales. Es decir, cada entrega semanal tendrá una puntuación específica y la nota final será el promedio de las puntuaciones obtenidas en cada entrega menos las penalizaciones que reciba en la entrega final si no se cumplen las condiciones de entrega.

### Restricciones

- No se permite el uso de librerías externas más allá de las estándar de C++ o creadas por usted.
- Debe utilizar arreglos dinámicos para almacenar las lecturas.
- El código debe estar bien documentado y seguir buenas prácticas de programación.

¡Buena suerte! Este proyecto simula una situación real que podría enfrentar como ingeniero.

---

## Cómo generar el archivo binario `.bsf`

Para generar el archivo binario `.bsf`, compile y ejecute cualquiera de los programas `generate_binary_files.cpp` o `generate_binary_files_using_strings.cpp`. Estos programas generan tres archivos binarios:

- **`patient_readings_simulation_tiny.bsf`**: Este archivo contiene simulaciones de lecturas para dos pacientes, con tres mediciones en total (dos de un paciente y una de otro). Este archivo es muy pequeño y se puede utilizar para pruebas iniciales. Este archivo solo contiene una lectura ECG para verificar que se está cargando correctamente el archivo binario y que se puede leer correctamente, no le servirá para probar la generación del archivo binario de anomalías ECG.

- **`patient_readings_simulation_small.bsf`**: Este archivo contiene simulaciones de lecturas para dos pacientes, uno con un ECG anómalo y otro con un ECG normal. Este archivo es más pequeño y se puede utilizar para pruebas iniciales.
- **`patient_readings_simulation.bsf`**: Este archivo contiene simulaciones de las lecturas de 1 día para cuatro pacientes. Este archivo es más grande y es el que se utilizará para la entrega final del proyecto.
  
Para ejecutar el programa, asegúrese de tener un compilador de C++ instalado, como `g++` o `clang++`. Luego, compile y ejecute el programa de la siguiente manera:

1. Abra una terminal y navegue hasta el directorio donde se encuentra el archivo `generate_binary_files.cpp` o `generate_binary_files_using_strings.cpp`. (Visual Studio Code lo hace automáticamente al abrir el proyecto y abrir el terminal integrado).

2. Compile el programa utilizando el compilador de C++ que prefiera:
   En caso de usar g++:

   ```bash
   g++ generate_binary_files.cpp -o generate_binary_files
   ./generate_binary_files
   ```

   En caso de usar clang++:

   ```bash
   clang++ generate_binary_files.cpp -o generate_binary_files
   ./generate_binary_files
   ```

3. Después de ejecutar el programa, se generarán los archivos binarios `patient_readings_simulation_small.bsf` y `patient_readings_simulation.bsf` en el directorio actual.

## Dónde está el archivo de configuración y de pacientes

Los archivos de [configuración](/data/configuracion.txt) y de pacientes se encuentran en la carpeta [data](/data/). Ahí, encontrará un archivo llamado [pacientes_small.csv](/data/pacientes_small.csv) que contiene los datos de dos pacientes, ambos corresponderan con los pacientes del archivo generado `patient_readings_simulation_small.bsf`.

Para la entrega final, se utilizará el archivo [pacientes.csv](/data/pacientes.csv) que contiene los datos de cuatro pacientes, dos con un ECG anómalo y dos con un ECG normal. Este archivo es más grande y es el que se utilizará para la entrega final del proyecto. De este archivo, aleatoriamente, se tomaron cuatro pacientes para generar el archivo `patient_readings_simulation.bsf`.