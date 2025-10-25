#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#define DIM 30



typedef struct
{
    int legajo;
    char nombreYapellido [30];
    int edad;
    int anio;//a�o que cursa, recordar que no podemos utilizar la � para definir variables
} stAlumno;

int main()
{
    printf("Hello world!\n");
    return 0;
}



void leerArch_y_pasar(char archivo[20], stAlumno *alumnos, int *cant){
    FILE *arch;
    arch = fopen(archivo, "rb");

    if(!arch){
        printf("\n error al abrir el archivo");
    }

    fseek(arch,0,SEEK_END);
    int tam = ftell(arch);
    cant = tam/sizeof(stAlumno);

    alumnos = (stAlumno *)malloc(cant*sizeof(stAlumno));
    if(!alumnos){
        printf("\nerror al reservar memoria");
    }

    fread(alumnos,sizeof(stAlumno),cant,arch);
    fclose(arch);
    printf("\n el arreglo se lleno correctamente con %d alumnos", cant);
}



// ejercicio 2
void filtrar(stAlumno *alumnos, int cant, stAlumno *filtrados, int *cantFiltrados){
    int fil = 0;
    int z = 0;

    for(int i = 0; i < cant ; i++){
        if(alumnos[i].edad > 21){
            fil++;
        }
    }

    cantFiltrados = fil;
    filtrados = (stAlumno *)malloc(fil *sizeof(stAlumno));

    for(int j = 0; j < cant ; j++){
        if(alumnos[j].edad > 21 && z =< cantFiltrados){
            filtrados[z] = alumnos[j];
            z++;
        }
    }
}

// ejercicio 3
stAlumno* agregarAlumno(stAlumno *arr, int *cantidad, stAlumno nuevo){

    stAlumno *nuevoArr = (stAlumno*) realloc(arr, (*cantidad + 1) * sizeof(stAlumno));

    if (nuevoArr != NULL) {
        nuevoArr[*cantidad] = nuevo;
        (*cantidad)++;
    }

    return nuevoArr;
}

//ejercicio 4
stAlumno* redimensionarArreglo(stAlumno *arr, int nuevoTam) {
    return (stAlumno *) realloc(arr, nuevoTam * sizeof(stAlumno));
}

//ejercicio 5
void arrToArch(stAlumno *arr, int *cant, char nombreArch[DIM]){
    FILE *arch = fopen(nombre,"ab");

    if(arch != NULL)
    {
        fwrite(arr,sizeof(stAlumno),cant,arch);

        fclose(arch);
    }
    printf("\n arreglo copiado correctamente con %d registros",cant);
}


void mostrarUnAlumno(stAlumno aux)
{
    printf("\n Legajo: %d\n nombre y apellido: %s \nedad: %d\nanio de cursada:%d",aux.legajo,aux.nombreYapellido,aux.edad,aux.anio);
}

void mostrarContenido(char nombre[DIM])
{
    FILE *arch = fopen(nombre, "rb");
    stAlumno aux;

    if(arch != null)
    {
        while(fread(&aux,sizeof(stAlumno),1,arch) > 0)
        {
            mostrarUnAlumno(aux);
        }
        fclose(arch);
    }
}

// ejercicio 6
int contar(stAlumno *arr, int cant, int anio){
    int count = 0;

    for(int i = 0; i < cant ; i++){
        if(arr[i].anio == anio){
            count++;
        }
    }

    return count;
}

void copiar(stAlumno *arr, stAlumno *arrNuevo, int cant,int anio , int contados){
    int z = 0;
    arrNuevo = (stAlumno *)malloc(contados *sizeof(stAlumno));

    for(int j = 0; j < cant ; j++){
        if(arr[j].anio == anio  && z =< contados){
            arrNuevo[z] = alumnos[j];
            z++;
        }
    }
}

// ejercicio 7


















