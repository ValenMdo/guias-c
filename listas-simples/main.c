#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    persona dato;
    struct nodo * siguiente;
} nodo;


typedef struct
{
    char nombre[20];
    int edad;
} persona;




void main()
{
    nodo * lista = iniNull();

    persona p1 = leerArch("personas.dat");
    nodo * n1 = crearNodo(p1);

}


//crear una lista vacia
nodo *iniNull()
{
    return NULL;
}

//crear nodo
nodo *crearNodo(persona p)
{
    nodo * n1 = (nodo*)malloc(sizeof(nodo));
    n1->dato = p; //usar flecha
    n1->siguiente = NULL;
    return n1;
}


//1) leer de un archivo y subirlo a una lista al principio
nodo * archLista(char nombreArch[20], nodo * lista)
{

    FILE *arch = fopen(nombreArch, "rb");
    persona aux;

    if(arch != NULL)
    {
        while(fread(&aux,sizeof(persona),1,arch))
        {
            nodo * nodoNuevo = crearNodo(aux);
            agregarP(nodoNuevo, lista);
        }
        fclose(arch);
    }
    else
    {
        printf("\n error al abrir el archivo");
    }
    return lista;
}

//agregar nodo al principio de la lista
nodo * agregarP(nodo * nuevo, nodo * lista)
{
    if(lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        nuevo->siguiente = lista;
        lista = nuevo;
    }
    return lista;
}


//agregar en orden
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
            nodo * ante = lista; //se agarra un nodo anterior y uno posterior, para comparar y saber lsi va entre medio de los dos
            nodo * seg = lista->siguiente;// siguiente nodo
            while((seg != NULL)&&
                    (strcmp(nuevoNodo->dato.nombre,seg->dato.nombre)>0))
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

// 2) cargar cada nodo en orden a la lista
nodo * archListaOr(char nombreArch[20], nodo * lista)
{

    FILE *arch = fopen(nombreArch, "rb");
    persona aux;

    if(arch != NULL)
    {
        while(fread(&aux,sizeof(persona),1,arch))
        {
            nodo * nodoNuevo = crearNodo(aux);
            agregarEnOrden(lista, nodoNuevo);
        }
        fclose(arch);
    }
    else
    {
        printf("\n error al abrir el archivo");
    }
    return lista;
}


// 3)buscar en lista
nodo * buscarNodo(nodo * lista, char nombre[20])
{
    nodo * seg; //apunta al nodo de la lista que está siendo procesado
    seg = lista; //con esto evito cambiar el valor de la variable

    while ((seg != NULL) && (strcmp(nombre, seg->dato.nombre)!=0))
    {
//busco mientras me quede lista por recorrer y no haya encontrado el nombre
        seg=seg->siguiente; //avanzo hacia el siguiente nodo.
    }

    return seg;
}


// 4) borra el primer nodo
nodo * borarNodo(nodo * lista)
{
    if(lista != NULL)
    {
        nodo * aux = lista;
        lista = lista -> siguiente;

        free(aux);
    }
    return lista;
}


// 5) eliminar el ultimo nodo
nodo * borrarUlt(nodo * lista)
{
    nodo * ante = lista;
    nodo * sig = lista->siguiente;



    while(sig->siguiente != NULL)
    {
        ante = sig;
        sig = sig->siguiente;
    }

    free(sig);
    ante->siguiente = NULL;

    return ante;
}

// 6) contar nodos que cumplen la condicion
void contar(nodo * lista, int condicion)
{

    int count = 0;

    if(lista == NULL)
    {
        printf("\nLa lista está vacía.");
        return;
    }

    nodo * aux = lista;


    while(aux->siguiente != NULL)
    {
        if(aux->dato.edad == condicion)
        {
            count++;
        }
        aux = aux->siguiente;
    }

    printf("\n nodos que cumplen la condicion: %d",count);

}

//mostrar
void mostrarNodo(nodo * ver)
{
    if(ver != NULL)
    {
        printf("\n nombre: %s",ver->dato.nombre);
        printf("\n edad: %d",ver->dato.edad);
    }
}

// 7) mostrar toda la lista atras para adelante
void mostrarInverso(nodo * lista)
{

    if(lista == NULL)
    {
        return;
    }

    mostrarInverso(lista->siguiente); //recorre hasta el final

    mostrarNodo(lista); //cuando vuelve en la recursion imprime cada nodo
}

// 8) eliminar nodos con condicion RECURSIVA
nodo * eliminarCon(nodo * lista, int condicion)
{

    if(lista == NULL)
    {
        return;
    }

    lista->siguiente = eliminarCon(lista->siguiente, condicion);

    if(lista->dato.edad == condicion)
    {
        nodo * aux = lista->siguiente;
        free(lista);
        return aux;
    }

    return lista;

}

// 8) eliminar nodos con condicion SIN RECURSION
void eliminarSR(nodo * lista, int condicion)
{

    nodo * primero = lista;
    nodo * sig;

    if(lista == NULL)
    {
        printf("\n lista vacia");
    }

    while(primero->siguiente != NULL)
    {
        if(primero->dato.edad == condicion)
        {
            nodo * aux = primero;
            primero = primero->siguiente;
            free(lista);
        }
    }
}
