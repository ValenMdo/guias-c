#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nombre[20];
    int edad;
} persona;

typedef struct
{
    persona dato;
    struct nodo * siguiente;
} nodo;



int main()
{
    printf("Hello world!\n");
    return 0;
}

//crear una lista vacia
nodo *iniNull()
{
    return NULL;
}

//cargar un nodo con una persona
nodo * crearNodo(persona p)
{
    nodo * n1 = (nodo*)malloc(sizeof(nodo));
    n1->dato = p;
    ni->siguiente = NULL;
    return n1;
}

nodo * archToLista(char nombre[20], nodo * lista)
{

    FILE *arch = fopen(nombre,"rb");
    persona aux;

    if(arch)
    {
        while(fread(&aux,sizeof(persona),1,arch)>0)
        {
            nodo * nuevo = crearNodo(aux);
            alPrincipio(nuevo, lista);
        }
        fclose(arch);
        printf("\n archivo pasado a una lista");
    }
    else
    {
        printf("\n error al abrir el archivo");
    }
    return lista;
}

// cargar nodo al principiop de la lista
nodo * alPrincipio(nodo * nuevoNodo, nodo * lista)
{

    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->siguinte = lista; //pongo el nuevo nodo al principio
        lista = nuevoNodo; //el principio de la lista apunta al nuevo nodo
    }
    return lista;

}

// 2) cargar una lista desde un archivo en orden
nodo * agregarEnOrden(nodo * lista, nodo * nuevoNodo)
{

    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        if(strcmp(nuevoNodo->dato.nombre,lista->dato.nombre)<0)
        {
            lista = agregarPpio(lista, nuevoNodo);
        }
        else
        {
            nodo * ante = lista; //se agarra un nodo anterior y uno posterior, para comparar y saber si va entre medio de los dos
            nodo * seg = lista->siguiente;// siguiente nodo
            while((seg != NULL)&&(strcmp(nuevoNodo->dato.nombre,seg->dato.nombre) > 0))
            {
                //avanzan al siguiente
                ante = seg;
                seg = seg->siguiente;
            }
            // inserto el nuevo nodo en el lugar indicado.
            nuevoNodo->siguiente = seg;
            ante->siguiente = nuevoNodo;
        }
    }
    return lista;
}

nodo * pasajeOrd(char nombre[], nodo * lista)
{

    FILE *arch = fopen(nombre,"rb");
    persona aux;

    if(arch)
    {
        while(fread(&aux,sizeof(persona),1,arch)>0)
        {
            nodo * nuevo = cargarNodo(aux);
            agregarEnOrden(lista, nuevo);
        }
        fclose(arch);
    }
}

// 3) bsucar en una lista
int buscar(nodo * lista, int edad)
{

    nodo * aux;

    aux = lista;

    while(lista != NULL && aux->dato.edad != edad)
    {
        aux = aux->siguiente;
    }

    return 1;
}

// 4) rliminar el primer nodo de la lista
nodo * eliminarPrimero(nodo * lista)
{

    if(lista != NULL)
    {
        nodo * aux;
        aux = lista;

        lista = lista->siguiente;

        free(aux);
    }

    return lista;

}

// 5) eliminar el ultimo nodo de la lista
void eliminarUlt(nodo * lista){

    nodo * aux;
    aux = lista;

    nodo * sig;
    sig = lista->siguiente;

    while(sig->siguiente != NULL){
        aux = sig;
        sig = sig->siguiente;
    }

    free(sig);
    aux->siguiente = NULL;

    printf("\n ultimo nodo eliminado correctamente");

}
