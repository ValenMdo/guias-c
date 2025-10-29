#include <stdio.h>
#include <stdlib.h>

#define DIM 30

void leerYcargar(char nombre[20],stAlumno *arr, int *cant);
void filtrarYcargar(stAlumno *arr,stAlumno *filtrados, int *cant, int condicion, int *countF);
void agregar(stAlumno **filtrados, int *countF, stAlumno nuevo);
stAlumno *redimensionar(stAlumno *arr, int tam);
void guardarEnArch(char nombre[20], stAlumno *arr, int *cant);
void mostrarAlumno(stAlumno alumno);
void mostrarArch(char nombre[20]);
int contar(stAlumno *arr, int cant, int anio);
void copiar(stAlumno *arr, stAlumno *arrNuevo, int cant,int anio, int contados);
void crearArch(stAlumno *arr, int *cant);
void recuArr(stAlumno *arr, int n);
void recuArch(FILE *arch);
void mostrarArch(char nombre[20]);




typedef struct
{
    int legajo;
    char nombreYapellido [30];
    int edad;
    int anio;//año que cursa
} stAlumno;

void main()
{
    char archivo[20] = "alumnos.dat";
    stAlumno * arreglo = NULL;
    int cant = 0;

    // Llamar al menú
    menu(archivo, &arreglo, &cant);
}



// --- IMPLEMENTACIÓN DEL MENÚ --- corregir
void menu(char archivo[20], stAlumno **arreglo, int *cant) {
    int opcion;
    int cant_filtrados = 0;
    stAlumno * arreglo_filtrado = NULL;
    int anio_condicion;
    stAlumno nuevo_alumno = {12345, "Nuevo Alumno Test", 20, 3}; // Alumno de prueba
    char archivo_destino[20] = "filtrados.dat";

    do {
        printf("\n\n--- MENU DE PRUEBA ---");
        printf("\n1. Leer archivo y cargar a arreglo dinamico (leerYcargar)");
        printf("\n2. Filtrar por anio (filtrarYcargar)");
        printf("\n3. Agregar alumno al arreglo filtrado (agregar)");
        printf("\n4. Redimensionar arreglo filtrado a tam 5 (redimensionar)");
        printf("\n5. Guardar arreglo filtrado en archivo (guardarEnArch)");
        printf("\n6. Contar y Copiar alumnos de un anio (contar/copiar)");
        printf("\n7. Crear archivos por anio (crearArch)");
        printf("\n8. Mostrar arreglo principal de atras para adelante (recuArr)");
        printf("\n9. Mostrar archivo principal recursivamente (recuArch)");
        printf("\n10. Salir");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                leerYcargar(archivo, arreglo, cant);
                break;
            case 2:
                if (*arreglo == NULL || *cant == 0) {
                    printf("\nPrimero debe cargar el arreglo con la opcion 1.");
                    break;
                }
                printf("\nIngrese anio a filtrar: ");
                scanf("%d", &anio_condicion);
                // Liberar arreglo filtrado anterior si existe
                if (arreglo_filtrado != NULL) free(arreglo_filtrado);
                arreglo_filtrado = NULL;
                cant_filtrados = 0;

                filtrarYcargar(*arreglo, &arreglo_filtrado, *cant, anio_condicion, &cant_filtrados);
                break;
            case 3:
                if (arreglo_filtrado == NULL) {
                    printf("\nPrimero debe filtrar alumnos con la opcion 2.");
                    break;
                }
                agregar(&arreglo_filtrado, &cant_filtrados, nuevo_alumno);
                break;
            case 4:
                if (arreglo_filtrado == NULL) {
                    printf("\nPrimero debe filtrar alumnos con la opcion 2.");
                    break;
                }
                printf("\nRedimensionando arreglo filtrado a tamano 5...");
                arreglo_filtrado = redimensionar(&arreglo_filtrado, 5);
                if (arreglo_filtrado != NULL) {
                    cant_filtrados = 5; // Asumimos éxito, el array ahora tiene 5 elementos
                    printf("\nArreglo filtrado redimensionado a 5 elementos.");
                }
                break;
            case 5:
                if (arreglo_filtrado == NULL) {
                    printf("\nPrimero debe filtrar alumnos con la opcion 2.");
                    break;
                }
                guardarEnArch(archivo_destino, arreglo_filtrado, cant_filtrados);
                break;
            case 6:
                if (*arreglo == NULL || *cant == 0) {
                    printf("\nPrimero debe cargar el arreglo con la opcion 1.");
                    break;
                }
                printf("\nIngrese anio a contar y copiar: ");
                scanf("%d", &anio_condicion);
                int contados = contar(*arreglo, *cant, anio_condicion);
                stAlumno *arr_copia = NULL;
                copiar(*arreglo, &arr_copia, *cant, anio_condicion, contados);
                if (arr_copia != NULL) {
                    printf("\nCopia de %d alumnos del anio %d realizada correctamente.", contados, anio_condicion);
                    free(arr_copia);
                }
                break;
            case 7:
                 if (*arreglo == NULL || *cant == 0) {
                    printf("\nPrimero debe cargar el arreglo con la opcion 1.");
                    break;
                }
                crearArch(*arreglo, *cant);
                printf("\nArchivos 'primero.dat', 'segundo.dat' y 'tercero.dat' creados/actualizados.");
                break;
            case 8:
                if (*arreglo == NULL || *cant == 0) {
                    printf("\nPrimero debe cargar el arreglo con la opcion 1.");
                    break;
                }
                printf("\n--- Mostrando Arreglo Principal en Orden Inverso ---");
                recuArr(*arreglo, *cant - 1);
                printf("\n--- Fin de Muestra Inversa ---");
                break;
            case 9:
                printf("\n--- Mostrando Archivo Principal Recursivamente (Inverso) ---");
                mostrarArch(archivo);
                printf("\n--- Fin de Muestra Recursiva ---");
                break;
            case 10:
                printf("\nSaliendo del programa. Memoria liberada.");
                if (arreglo_filtrado != NULL) free(arreglo_filtrado);
                break;
            default:
                printf("\nOpcion invalida. Intente de nuevo.");
        }
    } while(opcion != 10);
}



// 1) leer el archivo "alumnos.dat" y cargarlo en un arreglo dinamico
void leerYcargar(char nombre[20],stAlumno *arr, int *cant)
{

    FILE *arch = fopen(nombre,"rb");

    if(arch == NULL)
    {
        printf("\n error al abrir el archivo");
    }

    //calculo tamaño
    fseek(arch,0,SEEK_END);
    int tam = ftell(arch);
    cant = tam/sizeof(stAlumno);


    arr = (stAlumno*)malloc(cant*sizeof(stAlumno)); //asigno memoria
    if(!arr)
    {
        printf("\n error al asignar memoria");
    }

    fread(arr,sizeof(stAlumno),cant,arch);
    fclose(arch);
    printf("\n el arreglo se cargo correctamente");

}

// 2) filtrar alumnos mayores y cargarlos a un nuevo arreglo dinamico
void filtrarYcargar(stAlumno *arr,stAlumno *filtrados, int *cant, int condicion, int *countF)
{

    countF = 0;
    int k = 0;

    for(int i = 0; i < cant; i++ )
    {
        if(arr[i].anio == condicion)
        {
            countF++;
        }
    }

    if(count > 0)
    {
        filtrados = (stAlumno*)malloc(countF*sizeof(stAlumno));
        for(int j = 0; j < cant; j++)
        {
            if(arr[j].anio == condicion && k =< countF)
            {
                filtrados[k] = arr[j];
                k++;
            }
        }
        printf("\n arreglo cargado correctamente con %d alumnos filtrados", countf);

    }
    else
    {
        printf("\n no hay alumnos de esa edad");
    }
}

// 3) agregar un nuevo alumno usando realloc
void agregar(stAlumno **filtrados, int *countF, stAlumno nuevo)
{

    int nuevoTam = *countF + 1;

    stAlumno *nuevoArr = realloc(*filtrados, nuevoTam * sizeof(stAlumno));

    if(nuevoArr != NULL)
    {
        *filtrados = nuevoArr;
        (*filtrados)[nuevoTam - 1] = nuevo;
        (*countF)++;
        printf("\n nuevo alumno cargado correctamente");
    }
    else
    {
        printf("\n error al asignar memoria");
    }

}

// 4) redimensionar arreglo a tamaño especificado
stAlumno *redimensionar(stAlumno *arr, int tam)
{

    stAlumno *arrNuevo = realloc(*arr,tam*sizeof(stAlumno));

    if(arrNuevo != NULL)
    {
        *arr = arrNuevo;
        return arr;
    }
    else
    {
        printf("\n no se pudo redimensionar");
        return arr;
    }
}

// 5) guardar el contenido del arreglo en un archivo
void guardarEnArch(char nombre[20], stAlumno *arr, int *cant)
{

    FILE *arch = fopen(nombre,"wb");

    if(arch)
    {
        fwrite(arr,sizeof(stAlumno),cant,arch);

        fclose(arch);
    }

    printf("\n arreglo copiado correctamente con %d registros",cant);

}

void mostrarAlumno(stAlumno alumno)
{

    printf("\n nombre: %s", alumno.nombreYapellido);
    printf("\n edad: %d", alumno.edad);
    printf("\n año que cursa: %d", alumno.anio);
    printf("\n legajo: %d", alumno.legajo);
}

void mostrarArch(char nombre[20])
{
    FILE *arch = fopen(nombre,"rb");
    stAlumno aux;

    if(arch)
    {
        while(fread(aux,sizeof(stAlumno),1,arch)>0)
        {
            mostrarAlumno(aux);
        }
        fclose(arch);
    }
}


// 6)
int contar(stAlumno *arr, int cant, int anio)
{
    int count = 0;

    for(int i = 0; i < cant ; i++)
    {
        if(arr[i].anio == anio)
        {
            count++;
        }
    }

    return count;
}

void copiar(stAlumno *arr, stAlumno *arrNuevo, int cant,int anio, int contados)
{
    int z = 0;
    arrNuevo = (stAlumno *)malloc(contados *sizeof(stAlumno));

    for(int j = 0; j < cant ; j++)
    {
        if(arr[j].anio == anio  && z =< contados)
        {
            arrNuevo[z] = alumnos[j];
            z++;
        }
    }
}

// 7)
void crearArch(stAlumno *arr, int *cant)
{

    FILE *arch;

    for(int i = 0; i < cant, i++)
    {
        if(arr[i].anio == 1)
        {
            arch = fopen("primero.dat", "ab");
        }
        else if(arr[i].anio == 2)
        {
            arch = fopen("segundo.dat", "ab");
        }
        else
        {
            arch = fopen("tercero.dat", "ab");
        }

        if(arch)
        {
            fwrite(&arr,sizeof(stAlumno),1,arch);
            fclose(arch);
        }
    }
}


// 8) funcion recursiva que muestre los registros del arreglo de atras para adelante
// main: recu(&arr, cant -1)
void recuArr(stAlumno *arr, int n){
    if(n >= 0){
        mostrarAlumno(arr[i]);
        recu(arr,n-1);
    }
}

// 9) leer un archivo de manera recursiva
void recuArch(FILE *arch){

    stAlumno aux;

    if(fread(aux,sizeof(stAlumno),1,arch) != 1){
        return;
    }

    recuArch(arch);

    mostrarAlumno(aux);
}

void mostrarArch(char nombre[20]){

    FILE *arch = fopen(nombre, "rb");

    if(!arch){
        printf("\n error al abrir el archivo");
    }

    printf("\n comenzando lectura recursiva");


    recuArch(arch);

    fclose(arch);

    printf("\n lectura terminada");

}



