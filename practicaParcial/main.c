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
    int anio;//año que cursa, recordar que no podemos utilizar la ñ para definir variables
} stAlumno;


int main()
{
    printf("Hello world!\n");
    return 0;
}


///------punto 1----------
void agregarAlFinal(char nombre[DIM], stAlumno alu)
{
    FILE *arch = fopen(nombre, "ab");

    if( arch != NULL)
    {
        fwrite(&alu,sizeof(stAlumno),1,arch);
        fclose(arch);
    }
    printf("\n alumno cargado correctamente.");
}

///------punto 2---------
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

///-----punto 3----------
int contarRegistros(char nombre[DIM])
{
    FILE *arch = fopen(nombre, "rb");
    stAlumno aux;
    int count = 0;

    if(arch != NULL)
    {
        while(fread(&aux,sizeof(stAlumno),1,arch) > 0)
        {
            count++;
        }
        fclose(arch);
    }
    return count;
}


///----- punto 4 --------
void cargaCincoMax(char nombre[DIM])
{
    stAlumno aux;
    FILE *arch = fopen(nombre,"ab");

    if(arch = NULL)
    {
        FILE *arch = fopen(nombre,"wb");
    }
    if(arch != NULL)
    {
        for(int i = 0; i < 5; i++)
        {
            aux = cargarUnAlumno();
            fwrite(&aux,sizeof(stAlumno),1,arch);
        }
        fclose(arch);
    }
    printf("\n se han cargado correctamente los 5 alumnos");
}


///------punto 5 ------------ (hecho en el 2)

/// ------- punto 6 ---------
stAlumno cargarUnAlumno()
{
    stAlumno aux;

    printf("\n Ingrese el legajo del alumno: ");
    scanf("%d",&aux.legajo);
    fflush(stdin);

    printf("\nIngrese nombre y apellido del alumno: ");
    gets(aux.nombreYapellido);
    fflush(stdin);

    printf("\n Ingrese edad del alumno: ");
    scanf("%d",&aux.edad);
    fflush(stdin);

    printf("\n Ingrese ciclo lectivo: ");
    scanf("%d",&aux.anio);

    return aux;
}

void cargarAlumnos(char nombre[DIM])
{
    char ver = 's';
    stAlumno aux;

    do
    {
        aux = cargarUnAlumno();
        agregarAlFinal(nombre,aux);

        printf("\ndeseas seguir cargando?(s/n): ");
        scanf("%c",&ver);
    }
    while(ver != 'n');
}

///---------- punto 7 --------
void arreglosMayores(char nombre[DIM], int arreglo[DIM])
{
    stAlumno aux;
    int i = 0;
    FILE *arch = fopen(nombre,"rb");

    if(arch != NULL)
    {
        while(fread(&aux,sizeof(stAlumno),1,arch) > 0)
        {
            if(aux.edad >= 18)
            {
                arreglo[i] = aux.legajo;
                i++;
            }
        }
        fclose(arch);
    }
    printf("\n Arreglo cargado correctamente");
}

/// --------- punto 8 --------
int mayoresA(char nombre[DIM], int edad)
{
    stAlumno aux;
    int cant = 0;
    FILE *arch = fopen(nombre,"rb");

    if(arch)
    {
        while(fread(&aux,sizeof(stAlumno),1,arch) > 0)
        {
            if(aux.edad > edad)
            {
                cant++;
            }
        }
        fclose(arch);
    }
    return cant;
}

/// ------------- punto 9 ----------
void mostrarCampo(stAlumno alu, char campo[15])
{
    if (strcmp(tolower(campo), "nombre") == 0)
    {
        printf("\nNombre: %s", alu.nombreYapellido);
    }
    else if (strcmp(tolower(campo), "edad") == 0)
    {
        printf("\nEdad: %d", alu.edad);
    }
    else if (strcmp(tolower(campo), "legajo") == 0)
    {
        printf("\nLegajo: %d", alu.legajo);
    }
    else if (strcmp(tolower(campo), "anio") == 0)
    {
        printf("\nAño: %d", alu.anio);
    }
    else
    {
        printf("\nCampo no válido.");
    }
}

void enRango(char nombre[DIM],int in, int fin)
{
    stAlumno aux;
    FILE *arch = fopen(nombre,"rb";

                       if(arch != NULL)
{
    while(fread(&aux,sizeof(stAlumno),1,arch) > 0)
        {
            if(aux.edad >= in && aux.edad =< fin)
            {
                mostrarCampo(aux, 'nombre');
            }
        }
        fclose(arch);
    }
}

/// -------------- punto 10 -------------
stAlumno alumnoMayor(char nombre[DIM])
{
    stAlumno aux, mayor;
    int actual = 0;
    FILE *arch = fopen(nombre, "rb");

    if(arch != NULL)
    {
        fread(&mayor,sizeof(stAlumno),1,arch);
        while(fread(&aux,sizeof(stAlumno),1,arch) > 0)
        {
            if(mayor.edad < aux.edad)
            {
                mayor = aux;
            }
        }
        fclose(arch);
    }
    return mayor;
}

/// ----------- punto 11 ----------
int alumnosXcursada(char nombre[DIM], int aniocursada)
{
    stAlumno aux;
    int count = 0;
    FILE *arch = fopen(nombre,"rb");

    if(arch != NULL)
    {
        while(fread(&ux,sizeof(stAlumno),1,arch) > 0)
        {
            if(aux.anio == aniocursada)
            {
                count++;
            }
        }
        fclose(arch);
    }
    return count;
}

/// ------- punto 12 -----------
void copiarArreglo(char nombre[DIM],stAlumno arreglo[DIM],int validos)
{
    FILE *arch = fopen(nombre,"ab");

    if(arch != NULL)
    {
        fwrite(arreglo,sizeof(stAlumno),validos,arch);

        fclose(arch);
    }
    printf("\n arreglo copiado correctamente con %d registros",validos);
}

void archToArray(char nombre[DIM],stAlumno arreglo[DIM], int cursada)
{
    stAlumno aux;
    int i = 0;
    FILE *arch = fopen(nombre,"rb");

    if(arch != NULL)
    {
        while(fread(&aux,sizeof(stAlumno),1,arch) > 0)
        {
            if(aux.anio == cursada && i < DIM)
            {
                arreglo[i] = aux;
                i++;
            }
        }
        fclose(arch);
    }
}

/// --------- punto 13 ---------
int cuentaRegistrosArchivoFtell(char nombre[DIM])
{
    int cantidad =0;
    FILE* arch= fopen(nombreArchivo,"rb"); // no funciona si abro con ab o a+b

    if(arch != NULL)
    {
        fseek(arch,0, SEEK_END); // me posiciono al final del archivo

        cantidad = ftell(arch)/ sizeof(alumno);

        fclose(arch);
    }
    return cantidad;
}

/// ----------- punto 14 ----------
void mostrarTalRegistro(char nombre[DIM], int registro){
    int cant = cuentaRegistrosArchivoFtell(nombre);

    if(pos =< cant){

        FILE *arch = fopen(nombre,"rb");

        if(arch != NULL){

            stAlumno aux;

            fseek(arch, sizeof(stAlumno) * (registro - 1),SEEK_SET);

            fread(&aux,sizeof(stAlumno),1,arch);

            mostrarUnAlumno(aux);

            fclose(arch);
        }
    }
}
 /// --------- punto 15 -----------
 void modificarAlumnoAeleccion(char archivo[], int pos)
{
    FILE* archi = fopen(archivo, "r+b"); // abrir en modo lectura/escritura binaria

    if (archi != NULL)
    {
        alumno a;

        fseek(archi, sizeof(alumno) * (pos - 1), SEEK_SET);
        fread(&a, sizeof(alumno), 1, archi);

        a = modificarDatosAlumno(a);

        fseek(archi, -sizeof(alumno), SEEK_CUR); // volver atrás para sobrescribir
        fwrite(&a, sizeof(alumno), 1, archi);

        fclose(archi);
    }
}

alumno modificarDatosAlumno(alumno a)
{
    printf("\n--- Datos actuales del alumno ---\n");
    mostrarAlumno(a);

    char control;

    printf("\nModificar nombre y apellido (s/n)? ");
    getchar(); // limpiar buffer
    control = getchar();
    if (control == 's' || control == 'S') {
        printf("Nuevo nombre y apellido: ");
        getchar(); // limpiar \n pendiente
        fgets(a.nya, sizeof(a.nya), stdin);
        a.nya[strcspn(a.nya, "\n")] = '\0'; // eliminar salto de línea
    }

    printf("\nModificar edad (%d) (s/n)? ", a.edad);
    getchar();
    control = getchar();
    if (control == 's' || control == 'S') {
        printf("Nueva edad: ");
        scanf("%d", &a.edad);
    }

    printf("\nModificar año que cursa (%d) (s/n)? ", a.anio);
    getchar();
    control = getchar();
    if (control == 's' || control == 'S') {
        printf("Nuevo año: ");
        scanf("%d", &a.anio);
    }

    printf("\n--- Datos modificados ---\n");
    mostrarAlumno(a);

    return a;
}
