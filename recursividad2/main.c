#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


int factorial(int num);
int potencia(int base, int expo);
bool capicua(int arreglo[], int inicio, int fin);
int sumaRecursiva(int arr[], int dim);
int menorRecursivo(int arr[], int dim);
int menorArch(FILE *arch);
void inverArch(FILE *arch, int inicio, int ultimo);
void mostrarArch(FILE *arch, int fin);
void mostrarIN();
void encontrar(int arr[], int a, int inicio, int dim);
int sumarDigitos(int in);
int contarDigitos(int in);
int mayores(int arr[], int num, int inicio, int dim);
int invertirDigitos(int num);
int buscarArr(int arr[], int dim, int inicio, int num);

int main()
{
   // int a = potencia(3,2);
   // printf("%d", a);


    int arr[] = {1,2,3,2,1};
    int n = sizeof(arr) / sizeof(arr[0]);

    /*if(capicua(arr,arr[0],arr[4])){
        printf("\n es capicua");
    }else{
        printf("\n no es capicua");
    }*/

    int i = sumaRecursiva(arr,n);
    //printf("%d", i);

    //int menor = menorRecursivo(arr,n;)
    //printf("\n %d",menor);


// ----------------------------------------------------------------------- ej 8
/*
int nums[] = {1, 2, 3, 4, 5};
FILE *g = fopen("numeros.dat", "wb");
fwrite(nums, sizeof(int), 5, g);
fclose(g);

FILE *f = fopen("numeros.dat", "rb");

    //FILE *arch = fopen("archivito.bin","rb");
    int prueba = menorArch(f);

    if(f == NULL){
        printf("\n error de arch");
    }

    if(prueba == INT_MAX){
        printf("\n error en la lectura");
    }else{
        printf("\n el menor del arch es: %d", prueba);
    }
    fclose(f);
*/

// ------------------------------------------------------------------- ej 9
/*
    FILE *arch = fopen("numeros.dat", "rb");
    fseek(arch,0,SEEK_END);
    int cant = ftell(arch)/sizeof(int);
    rewind(arch);

    inverArch(arch, 0, cant - 1);
    fclose(arch);

    */

// ------------------------------------------------------- ej 10
/*
    FILE *arch = fopen("numeros.dat", "rb");
    fseek(arch,0,SEEK_END);
    int cant = ftell(arch)/sizeof(int);

    mostrarArch(arch, cant - 1);
    fclose(arch);
    */
//--------------------------------------------------------------- ej 11

   // mostrarIN();
// --------------------------------------------------------- ej 12
    //encontrar(arr,3,0,4);

// ----------------------------------------------------- ej 13
/*
    int r = sumarDigitos(1235);
    printf("\n suma: %d", r);

    */
// ------------------------------------------- ej 14
/*
    int o = contarDigitos(1234);
    printf("\n cant de digitos: %d", o);
    */
// ------------------------------------------ ej 16
/*
    int num = 1;
    int may = mayores(arr,num,0,4);
    printf("\n cantidad de numeros mayores a %d: %d",num,may);
    */
// ----------------------------------------------- ej 17
    int dig;
    printf("\ningrese el numero a invertir: ");
    scanf(" %d",&dig);

    invertirDigitos(dig);

// ------------------------------------------------ ej 18

    buscarArr(arr,4,0,3);




    return 0;
}

int factorial(int num){
    int r;

    if(num == 0){
        r = 1;
    }else{
        r = num * factorial(num-1);
    }
    return r;
}

int potencia(int base, int expo){
    if(expo == 0){
        return 1;
    }else{
        return base * potencia(base, expo -1);
    }
}

bool capicua(int arreglo[], int inicio, int fin){

    if(inicio >= fin){
        return true;
    }

    if(arreglo[inicio] != arreglo[fin]){ // si los extremos son distintos
        return false;
    }

    return capicua(arreglo,inicio + 1, fin -1); //compara el siguiente par, mientras se va achicando hacia el medio
}

int sumaRecursiva(int arr[], int dim){

    if(dim==0){
        return 0;
    }else{
        return arr[dim-1] + sumaRecursiva(arr,dim-1);
    }
}


int menorRecursivo(int arr[], int dim){
    if(dim == 1){
        return arr[0];
    }

    int menor = menorRecursivo(arr,dim-1);

    if(arr[dim-1]< menor){
        return arr[dim];
    }else{
        return menor;
    }
}

//ej 8
int menorArch(FILE *arch){

    int aux;

    if(fread(&aux,sizeof(int), 1, arch) != 1){
        return INT_MAX;
    }

    int menor = menorArch(arch);

    return (aux < menor) ? aux : menor;
}

//ej 9
void inverArch(FILE *arch, int inicio, int ultimo){
    if(inicio >= ultimo){
        printf("\n Archivo invertido correctamente");
        return;
    }

    int a,b;

    // posicionarse en el primer registro y leer
    fseek(arch,inicio * sizeof(int),SEEK_SET);
    fread(&a,sizeof(int),1,arch);

    // posicionarse en el ultimo registro y leer
    fseek(arch,ultimo * sizeof(int),SEEK_SET);
    fread(&b,sizeof(int),1,arch);

    // moverse e intercambiar
    fseek(arch,inicio * sizeof(int),SEEK_SET);
    fwrite(&b, sizeof(int),1,arch);

    fseek(arch,ultimo * sizeof(int),SEEK_SET);
    fwrite(&a, sizeof(int),1,arch);

    inverArch(arch, inicio + 1, ultimo - 1);

}

// ej 10
void mostrarArch(FILE *arch, int fin){
    int b;

    // posicionarse en el ultimo registro y leer
    fseek(arch,fin * sizeof(int),SEEK_SET);
    fread(&b,sizeof(int),1,arch);

    printf("\n leido: %d", b);

    if(fin >= 0){
        mostrarArch(arch, fin - 1);
    }else{
        printf("\n archivo terminado");
    }
}


// ej 11
void mostrarIN(){
    char c;
    printf("\n ingrese una letra( ingrese * para finalizar): ");
    scanf(" %c",&c);

    if(c == '*'){
        return;
    }

    mostrarIN();
    printf(" %c", c);
}

// ej 12
void encontrar(int arr[], int a, int inicio, int dim){

    if(inicio == dim){
        return;
    }


    if(a == arr[inicio]){
        printf("\n encontrado, en la posicion %d", inicio);
        return;
    }

    encontrar(arr,a,inicio + 1, dim);

}

// ej 13
int sumarDigitos(int in){

    if(in == 0){
        return 0;
    }

    return (in % 10) + sumarDigitos(in / 10);
// toma el ultimo numero y lo suma al siguiente numero, pasando por parametro el numero menos el ultimo
// 1234 -> 4 + sumarDigitos(123)
// 123 -> 2 + sumarDigitos(12)
}

// ej 14
int contarDigitos(int in){
    if(in == 0) return 0;

    return 1 + contarDigitos(in/10);

}

// ej 15
bool esPrimo(int in, int div){
    if(in <= 1) return false;

    if(in == div) return true; //se llega al final sin divisores

    if(in % div == 0) return false; // hay algun divisor

    return esPrimo(in, div + 1);

}

bool primoAux(int num){
    return esPrimo(num, 2); //empieza a comprobar desde el divisor 2
}

// ej 16
int mayores(int arr[], int num, int inicio, int dim){

    if(inicio == dim) return 0;


    if(arr[inicio] > num){
        return 1 + mayores(arr, num, inicio + 1, dim);
    }else{
        return mayores(arr,num,inicio + 1, dim);
    }
}

// ej 17
int invertirDigitos(int num){

    if(num == 0){
        return 0;
    }

    int dig = num % 10;
    printf(" %d", dig);

    return invertirDigitos(num / 10);
}

// ej 18
int buscarArr(int arr[], int dim, int inicio, int num){
    if(dim == 0) return;

    if(arr[inicio] == num){
        printf("\n encontrado en la posicion: %d",inicio);
        return;
    }

    return buscarArr(arr,dim,inicio + 1, num);
}



