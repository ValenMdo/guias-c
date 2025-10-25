#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDAD 7

typedef struct
{
    int idViaje;
    char origen[50];
    char destino[50];
    int cantidadPasajeros;
} Viaje;


typedef struct
{
    int idPasajero;
    int idViaje;
    char nombre[50];
    char dni[10];
    int despacheEquipaje;
} Pasajero;


/// ---------------------- prototipos ----------------------
int contarRegistrosArchivo(const char nombreArchivo[], size_t tamRegistro);
int cargarArregloPasajeros(const char nombreArchivo[], Pasajero arregloPasajeros[], int capacidad);
void mostrarUnPasajero(Pasajero p);
int contarPasajerosPorViaje(int idViajeBuscado, Pasajero arregloPasajeros[], int validosPasajeros);
int cargarArregloViajes(const char nombreArchivo[], Viaje arregloViajes[], int capacidad, Pasajero arregloPasajeros[], int validosPasajeros);
void mostrarUnViaje(Viaje v);
void listarViajesDisponibles(Viaje arregloViajes[], int validosViajes);
void escribirArchivoViajes(const char nombreArchivo[], Viaje arregloViajes[], int validosViajes);
void cargarArchivosPorOrigen(Viaje arregloViajes[], int validosViajes);
void cargarViajeEnArchivo(char nombreArchivoDestino[], Viaje unViaje);






int main()
{
    char archivoPasajeros[] = "pasajeros.bin";
    char archivoViajes[] = "viajes.bin";

    Pasajero arregloPasajeros[CAPACIDAD];
    Viaje arregloViajes[CAPACIDAD];

    int opcion, cantPasajeros = 0, cantViajes = 0;
    int idViajeBuscado;

    do
    {
        printf("\n------- MENU -------\n");
        printf("1. Contar registros de pasajeros\n");
        printf("2. Cargar arreglo de pasajeros\n");
        printf("3. Contar pasajeros por ID de viaje\n");
        printf("4. Cargar y actualizar arreglo de viajes\n");
        printf("5. Listar viajes disponibles\n");
        printf("6. Guardar viajes actualizados al archivo\n");
        printf("7. Crear archivos por origen\n");
        printf("0. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Cantidad de registros de pasajeros: %d\n", contarRegistrosArchivo(archivoPasajeros, sizeof(Pasajero)));
            break;

        case 2:
            cantPasajeros = cargarArregloPasajeros(archivoPasajeros, arregloPasajeros, CAPACIDAD);
            printf("Pasajeros cargados: %d\n", cantPasajeros);
            for (int i = 0; i < cantPasajeros; i++)
                mostrarUnPasajero(arregloPasajeros[i]);
            break;

        case 3:
            printf("Ingrese ID del viaje a buscar: ");
            scanf("%d", &idViajeBuscado);
            printf("Pasajeros en el viaje %d: %d\n", idViajeBuscado, contarPasajerosPorViaje(idViajeBuscado, arregloPasajeros, cantPasajeros));
            break;

        case 4:
            cantViajes = cargarArregloViajes(archivoViajes, arregloViajes,CAPACIDAD , arregloPasajeros, cantPasajeros);
            printf("Viajes cargados: %d\n", cantViajes);
            break;

        case 5:
            listarViajesDisponibles(arregloViajes, cantViajes);
            break;

        case 6:
            escribirArchivoViajes(archivoViajes, arregloViajes, cantViajes);
            break;

        case 7:
            cargarArchivosPorOrigen(arregloViajes, cantViajes);
            break;

        case 0:
            printf("Saliendo...\n");
            break;

        default:
            printf("Opcion invalida.\n");
        }

        printf("\n\n");

    }
    while (opcion != 0);

    return 0;
}



/*
1. Contar Registros en Archivo: Implementar una función que reciba el nombre del archivo
binario y el tamaño del registro, y retorne la cantidad total de registros en ese archivo. No se
debe recorrer el archivo registro por registro.
 */

int contarRegistrosArchivo(const char nombreArchivo[], size_t tamRegistro)
{

    int cant;
    FILE *arch = fopen(nombreArchivo, "rb");

    if( arch != NULL)
    {
        fseek(arch,0,SEEK_END); // posicion al final del archivo

        cant = ftell(arch) / tamRegistro;

        fclose(arch);
    }
    return cant;
}





/*
2. Cargar Arreglo de Pasajeros: Implementar una función que reciba el nombre del archivo
"pasajeros.bin", un arreglo de Pasajero previamente declarado en main con un tamaño igual a la
cantidad total de registros del archivo, y la capacidad máxima de ese arreglo. La función debe
cargar todos los registros del archivo en el arreglo y retornar la cantidad de pasajeros
válidamente cargados. Opcional: Implementar y usar una función auxiliar void
mostrarUnPasajero(Pasajero p) para verificar la carga.
.*/

int cargarArregloPasajeros(const char nombreArchivo[], Pasajero arregloPasajeros[], int capacidad)
{
    Pasajero aux;
    int i = 0;
    FILE *arch = fopen(nombreArchivo, "rb");

    if(arch != NULL)
    {
        while(fread(&aux,sizeof(Pasajero),1,arch) > 0)
        {
            arregloPasajeros[i] = aux;
            i++;
        }
        fclose(arch);
    }
    return i;
}

void mostrarUnPasajero(Pasajero p)
{

    printf("\n ID del pasajero: %d ", p.idPasajero);
    printf("\n ID del viaje: %d",p.idViaje);
    printf("\n Nombre: %s",p.nombre);
    printf("\n DNI: %s", p.dni);
    printf("\n Despache equipaje: %d",p.despacheEquipaje);
}




/*
3. Contar Pasajeros por Viaje: Implementar una función que reciba un idViajeBuscado, el arreglo
de Pasajeros cargado en el ejercicio anterior, y la cantidad de pasajeros válidos en él. La
función debe recorrer el arreglo y retornar la cantidad de pasajeros asignados a ese
idViajeBuscado.
int contarPasajerosPorViaje(int idViajeBuscado, Pasajero arregloPasajeros[], int validosPasajeros).*/

int contarPasajerosPorViaje(int idViajeBuscado, Pasajero arregloPasajeros[], int validosPasajeros)
{
    int cantidad = 0;

    for(int i = 0; i < validosPasajeros; i++)
    {
        if(arregloPasajeros[i].idViaje == idViajeBuscado)
        {
            cantidad++;
        }
    }
    return cantidad;
}



/*
4. Cargar y Actualizar Arreglo de Viajes: Implementar una función que reciba el nombre del
archivo "viajes.bin", un arreglo de Viaje previamente declarado en main con un tamaño igual a la
cantidad total de registros del archivo, y la capacidad máxima de ese arreglo. La función debe
cargar todos los registros del archivo en el arreglo. Luego de cargar, debe recorrer el arreglo de
Viajes y para cada viaje, actualizar su campo cantidadPasajeros usando la función
contarPasajerosPorViaje del ejercicio 3. Retornar la cantidad de viajes válidamente cargados.
int cargarArregloViajes(const char nombreArchivo[], Viaje arregloViajes[], int capacidad, Pasajero
arregloPasajeros[], int validosPasajeros)*/

int cargarArregloViajes(const char nombreArchivo[], Viaje arregloViajes[], int capacidad, Pasajero arregloPasajeros[], int validosPasajeros)
{

    Viaje aux;
    int i=0;
    FILE *arch = fopen(nombreArchivo, "rb");

    if(arch != NULL)
    {
        while(fread(&aux,sizeof(Viaje),1,arch) > 0 && i < capacidad)
        {
            arregloViajes[i] = aux;
            i++;
        }

        for(int j = 0; j<i; j++)
        {
            arregloViajes[j].cantidadPasajeros = contarPasajerosPorViaje(arregloViajes[j].idViaje, arregloPasajeros, validosPasajeros);
        }

        fclose(arch);
    }

    return i-1;
}





/*
5. Listar Viajes Disponibles (Iterativo): Implementar una función iterativa (usando bucles, sin
recursividad) que reciba el arreglo de Viajes cargado y la cantidad de viajes válidos. La función
debe mostrar por pantalla todos los viajes que tienen lugar disponible. Un viaje tiene lugar
disponible si su cantidadPasajeros es menor a la constante CAPACIDAD. Opcional: Implementar
y usar una función auxiliar void mostrarUnViaje(Viaje v).
void listarViajesDisponibles(Viaje arregloViajes[], int validosViajes)escribirArchivoViajes()*/

void mostrarUnViaje(Viaje v)
{
    printf("\n ID: %d  ",v.idViaje);
    printf("\n Origen: %s",v.origen);
    printf("\n Destino: %s",v.destino);
    printf("\n cantidad de pasajeros: %d",v.cantidadPasajeros);
}

void listarViajesDisponibles(Viaje arregloViajes[], int validosViajes)
{
    for(int i=0; i < validosViajes; i++)
    {
        if(arregloViajes[i].cantidadPasajeros < CAPACIDAD)
        {
            mostrarUnViaje(arregloViajes[i]);
        }
    }
}



/*
6. Actualizar Archivo de Viajes: Implementar una función que reciba el nombre del archivo
"viajes.bin", el arreglo de Viajes actualizado en el ejercicio 4, y la cantidad de viajes válidos. La
función debe sobrescribir completamente el archivo "viajes.bin" con los datos del arreglo
actualizado, incluyendo los valores de cantidadPasajeros modificados.
void escribirArchivoViajes(const char nombreArchivo[], Viaje arregloViajes[], int validosViajes).*/

void escribirArchivoViajes(const char nombreArchivo[], Viaje arregloViajes[], int validosViajes)
{
    FILE *arch = fopen(nombreArchivo,"wb"); // "wb" ya que pide sobreescribir el archivo

    if(arch != NULL)
    {
        fwrite(arregloViajes,sizeof(Viaje),validosViajes,arch);

        fclose(arch);
    }
    printf("\n Archivo cargado con el arreglo correctamente");
}



/*7. Generar Archivos por Origen: Implementar una función que reciba el arreglo de Viajes
actualizado y la cantidad de viajes válidos. La función debe generar un archivo binario nuevo
por cada ciudad de origen distinta que exista en el arreglo de viajes. Cada uno de estos nuevos
archivos debe contener solo los viajes cuyo origen coincide con el nombre del archivo
(ejemplo: si hay viajes con origen "MarDelPlata", se creará "MarDelPlata.bin"). Opcional:
Implementar una función auxiliar void cargarViajeEnArchivo(const char
nombreArchivoDestino[], Viaje unViaje) que reciba un viaje y lo escriba al final del archivo
especificado.
void cargarArchivosPorOrigen(Viaje arregloViajes[], int validosViajes)*/

void cargarArchivosPorOrigen(Viaje arregloViajes[], int validosViajes)
{
    for (int i = 0; i < validosViajes; i++)
    {
        int yaProcesado = 0; // auxiliar que me ayuda a ver si el destino ya fue procesado
        for (int j = 0; j < i; j++)
        {
            if (strcmp(arregloViajes[i].origen, arregloViajes[j].origen) == 0)
            {
                yaProcesado = 1; // cambia valor si ya estaba procesado
                break;
            }
        }
        if (yaProcesado != 1)
        {
            char nombreArchivo[60];
            sprintf(nombreArchivo, "%s.bin", arregloViajes[i].origen); //concatenar para crear el nombre del archivo con la ciudad

            for (int k = 0; k < validosViajes; k++)
            {
                if (strcmp(arregloViajes[k].origen, arregloViajes[i].origen) == 0)
                {
                    cargarViajeEnArchivo(nombreArchivo, arregloViajes[k]);
                }
            }
        }
    }
}

void cargarViajeEnArchivo(char nombreArchivoDestino[], Viaje unViaje)
{
    FILE *arch = fopen(nombreArchivoDestino, "ab");

    if (arch == NULL)
    {
        arch = fopen(nombreArchivoDestino, "wb");
    }

    if (arch != NULL)
    {
        fwrite(&unViaje, sizeof(Viaje), 1, arch);
        fclose(arch);
    }

    printf("\n se cargo correctamente el viaje en el archivo %s",nombreArchivoDestino);
}





/*
8. Función main Principal: Dentro de la función main, invocar todas las funciones desarrolladas
en los ejercicios anteriores en el orden lógico de su ejecución. Asegúrese de mostrar los
resultados por pantalla cuando corresponda para verificar la correcta ejecución de cada paso.

*/
