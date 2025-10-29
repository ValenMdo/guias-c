#include <stdio.h>
#include <stdlib.h>

void recorrerArr(int arr[], int i, int tam);
void arrInverso(int arr[], int tam);
int capicua(int arr[], int i, int j);
int sumarArr(int arr[], int i, int tam);
int buscarMenor(int arr[], int i, int tam);
void entradaInv();
void contiene(int arr[], int condicion, int tam, int i);
int sumarDigitos(int n);
int contarDigitos(int n);
void esPrimo(int n, int div);
void auxPrimo(int n);
int contarCond(int arr[] , int condicion, int tam, int inicio);
int invertirDigitos(int n);

int main()
{
    int arr[5] = {1,2,3,4,5};
    int arr2[5] = {1,2,3,2,1};
    int tam2 = 5;

    //recorrerArr(arr,0,5);

    //arrInverso(arr,5);

   // int r = capicua(arr2, 0, tam2 - 1);
    //printf("%d",r);

   // int r = sumarArr(arr,0,tam2);
    //printf("%d",r);

    //int r = buscarMenor(arr,0,tam2);
   // printf("%d",r);

   //entradaInv();

   //contiene(arr,5,5,0);

  // int r = sumarDigitos(123);
   //printf("%d",r);

   //int r = contarDigitos(1234);
   //printf(" %d", r);

   //auxPrimo(3);

   //int r = contarCond(arr,3,5,0);
   // printf(" %d", r);

    // invertirDigitos(123);

}

// 1)
int factorial(int n){
    int r;

    if(r == 0){
        r = 1;
        return r;
    }else{
        r = r * factorial(n-1);
        return r;
    }
}

// 2)
int potencia(int base, int expo){
    int r;

    if(expo == 0){
        r = 1;
        return r;
    }else{
        r = base * potencia(base, expo - 1);
        return r;
    }
}

// 3)
void recorrerArr(int arr[], int i, int tam){
    if(i == tam){
        return ;
    }else{
        printf("\n %d",arr[i]);
        recorrerArr(arr, i+1, tam);
    }

}

// 4)
void arrInverso(int arr[], int tam){
    if(tam == 0){
        return;
    }else{
        printf("\n %d",arr[tam-1]);
        arrInverso(arr, tam-1);
    }
}

// 5)
int capicua(int arr[], int i, int j){
    int r;

    if(i<j){
        if(arr[i] == arr[j]){
            r=capicua(arr,i+1,j-1);
        }else{
            r = 0;
        }
    }else{
        r=1;
    }

    return r;

}

// 6)
int sumarArr(int arr[], int i, int tam){


    if(i == tam){
        return 0;
    }else{
        return arr[i] + sumarArr(arr,i+1,tam);
    }
}


// 7)
int buscarMenor(int arr[], int i, int tam){

    int sig;

    if(i == tam ){
        return arr[i];
    }

    sig = buscarMenor(arr,i + 1, tam);
    if(arr[i] < sig){
        return arr[i];
    }else{
        return sig;
    }

}

// 8)
int buscarMenorArch(FILE *arch){
    int r;

    if( fread(&r,sizeof(int),1,arch) != 1){
        return 222;
    }

    int menor = buscarMenorArch(arch);

    return (r < menor) ? r : menor;
}

// 9)
// ultimo = tamArch()
void invertirArch(FILE *arch, int primero, int ultimo){

    if(primero >= ultimo){
        printf("\n archivo invertido");
        return;
    }


    int a,b;

    // leer y almacenar el primer registro
    fseek(arch,primero * sizeof(int),SEEK_CUR);
    fread(&a,sizeof(int),1,arch);


    //leer y almacenar el ultimo registro
    fseek(arch, ultimo * sizeof(int),SEEK_SET);
    fread(&b,sizeof(int),1,arch);

    fseek(arch,primero * sizeof(int),SEEK_CUR);//movemos y escribimos invertido
    fwrite(&b,sizeof(int),1,arch);

    fseek(arch, ultimo * sizeof(int),SEEK_SET);
    fwrite(&a,sizeof(int),1,arch);

    invertirArch(arch,primero + 1, ultimo - 1);

}

int tamArch(FILE *arch){
    fseek(arch,0,SEEK_END);

    int tam = ftell(arch) / sizeof(int);

    return tam;
}

// 10)
void mostrarInv(FILE *arch, int ultimo){
    int a;

    fseek(arch,ultimo * sizeof(int), SEEK_SET); //mover hasta el ultimo registro y leer
    fread(&a,sizeof(int),1,arch);

    printf("\n leido: %d", a);

    if(ultimo >= 0){
        mostrarInv(arch, ultimo + 1);
    }else{
        printf("\n archivo terminado");
    }
}

// 11)
void entradaInv(){
    char c;

    printf("\n ingresa una letra(com * salis): ");
    scanf(" %c", &c);

    if(c == '*'){
        return;
    }

    entradaInv();
    printf("\n %c", c);
}

// 12)
void contiene(int arr[], int condicion, int tam, int i){
    if(i == tam){
        return;
    }

    if(arr[i] == condicion){
        printf("\n contiene %d en la posicion: %d",condicion,i);
        return;
    }

    contiene(arr,condicion,tam,i + 1);
}

// 13)
int sumarDigitos(int n){

    if(n == 0){
        return 0;
    }

    return (n % 10) + sumarDigitos(n/10);

}

// 14)
int contarDigitos(int n){

    if(n == 0){
        return 0;
    }

    return 1 + contarDigitos(n/10);

}

// 15)
void esPrimo(int n, int div){
    if(n <= 1){
        printf("\n numero no valido");
        return;
    }

    if(n == div){
        printf("\n es primo");
        return;
    }

    if(n % div == 0){
        printf("\n no es primo");
        return;
    }

    esPrimo(n,div + 1);
}

void auxPrimo(int n){
    esPrimo(n,2); //compueba desde el divisor 2
}


// 16)
int contarCond(int arr[] , int condicion, int tam, int inicio){
    if(tam == 0 ){
        return 0;
    }

    if(inicio == tam){
        return 0;
    }

    if(arr[inicio] > condicion && inicio <= tam){
        return 1 + contarCond(arr,condicion, tam, inicio + 1);
    }else{
        contarCond(arr,condicion,tam,inicio + 1);
    }
}


// 17)
int invertirDigitos(int n){
    if(n == 0){
        return 0;
    }

    int dig = n%10;
    printf(" %d",dig);

    return invertirDigitos(n/10);
}
