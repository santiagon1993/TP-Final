#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header-tpfinal.h"
#define DIM 1000
#define clientes "clientes.dat"

int main()
{   char archivoClientes[DIM];
    stCliente stClientes[DIM];
    int x=0;
  //  int ID=0;
   // char n[20],a[20];


    mostrarMenu();
    seleccion();
    /*stClientes[ID]=altaUnCliente(ID);
    consultaCliente(stClientes[0]);
    printf("\n\n%d",ID);*/


    return 0;
}
