#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int factorial(int num);
int potencia(int base, int expo);
bool capicua(int arreglo[], int inicio, int fin);
int sumaRecursiva(int arr[], int dim);
int menorRecursivo(int arr[], int dim);

void main()
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

    sumaRecursiva(arr,n);
    menorRecursivo(arr,n;)
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

    if(arr[dim-1]< menor]){
        return arr[dim];
    }else{
        return menor;
    }
}
