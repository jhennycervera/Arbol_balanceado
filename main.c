/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: jhenn
 *
 * Created on 22 de noviembre de 2020, 10:13 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
/*
 * 
 */

//guarda en el arreglo los elementos del arbol
void en_orden2(TArbol ptrArbol, int * arr, int * ind){
    
    if (ptrArbol) {
        en_orden2(ptrArbol->izq, arr, ind);
        arr[*ind]= ptrArbol->elem;              //cambiar para trabajar con arreglos de punteros y otra para lista
        (*ind)++;
        en_orden2(ptrArbol->der,arr, ind);
    }
    
}
int niveles(TArbol ptr_arbol){
    int izq=0,der=0;
    if(ptr_arbol==NULL)
        return 0;
    if(ptr_arbol->der!=NULL)
        der = niveles(ptr_arbol->der);
    if(ptr_arbol->izq!=NULL)
        izq = niveles(ptr_arbol->izq);

    if(izq>der)
        return(izq+1);
    else    
        return(der+1);
}

int esta_balanceado(TArbol ptrArbol){
    
    if(ptrArbol==NULL){
        return 1;
    }
    int nivel_izq= niveles(ptrArbol->izq);
    int nivel_der= niveles(ptrArbol->der);
    
    
    if( abs(nivel_izq - nivel_der) <=1 && esta_balanceado(ptrArbol->der) && esta_balanceado(ptrArbol->izq))
        return 1;
    return 0;
    
}


TArbol balancear_Arbol( int *arr, int ini, int fin){
    if(ini>fin){
        return NULL;
    }
    
    int medio= (ini +fin)/2;
    
    TNodo * nodo_raiz= (TNodo*)malloc(sizeof(TNodo));
    nodo_raiz->elem=arr[medio];
    nodo_raiz->der= nodo_raiz->izq=NULL;
    
    nodo_raiz->izq=balancear_Arbol(arr, ini, medio-1);
    nodo_raiz->der=balancear_Arbol(arr, medio+1, fin);
    
    return nodo_raiz;
}

int main(int argc, char** argv) {

    TArbol ptArbol,ptArbol2 ;
    int tam=5;
    int arr[5], ind=0;
    
    crea_arbol(&ptArbol);
    inserta_nodo(&ptArbol, 5);
    inserta_nodo(&ptArbol, 4);
    inserta_nodo(&ptArbol, 3);
    inserta_nodo(&ptArbol, 2);
    inserta_nodo(&ptArbol, 1);
    
    en_orden2(ptArbol, arr, &ind);
    
    for(int i=0; i<tam; i++){
        printf("%d ", arr[i]);
    }
    
    if(esta_balanceado(ptArbol)){
        printf("\nEsta balanceado\n");
    }
    else{
        printf("\nNo esta balanceado\n");
    }
    
/*
    crea_arbol(&ptArbol2);
    inserta_nodo(&ptArbol2, 5);
    inserta_nodo(&ptArbol2, 4);
    inserta_nodo(&ptArbol2, 6);
    
    if(esta_balanceado(ptArbol2)){
        printf("\nEsta balanceado arbol 2\n");
    }
    else{
        printf("\nNo esta balanceado arbol 2\n");
    }
*/
    printf("Nivel de arbol sin balancear: %d\n",niveles(ptArbol));
    
    ptArbol2= balancear_Arbol(arr, 0, tam-1);
    
    en_orden(ptArbol2);
    
    if(esta_balanceado(ptArbol2)){
        printf("\nEsta balanceado arbol 2\n");
    }
    else{
        printf("\nNo esta balanceado arbol 2\n");
    }
    
    printf("Nivel de arbol balanceado: %d\n",niveles(ptArbol2));
    return (EXIT_SUCCESS);
}

