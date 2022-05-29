#include "header-tpfinal.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

stCliente altaCliente(int *id)
{
    stCliente cliente;

    printf("Numero de cliente");
    scanf("%d",&cliente.nroCliente);

    fflush(stdin);
    printf("Nombre: ");
    gets(cliente.nombre);

    fflush(stdin);
    printf("Apellido: ");
    gets(cliente.apellido);

    fflush(stdin);
    printf("DNI: ");
    gets(cliente.dni);

    fflush(stdin);
    printf("Email: ");
    gets(cliente.email);

    fflush(stdin);
    printf("Domicilio: ");
    gets(cliente.domicilio);

    fflush(stdin);
    printf("Movil: ");
    gets(cliente.movil);

    cliente.eliminado = 0;
    id++;

    return cliente;
}

void muestraCliente(stCliente cliente)
{
    printf("Numero de cliente: %d",cliente.nroCliente);
    printf("\nNombre: %s",cliente.nombre);
    printf("\nApellido: %s",cliente.apellido);
    printf("\nDNI: %s",cliente.dni);
    printf("\nEmail: %s",cliente.email);
    printf("\nDomicilio: %s",cliente.domicilio);
    printf("\nMovil: %s",cliente.movil);

    if(cliente.eliminado == 0)
        printf("\n El usuario se encuentra activo");
    else
        printf("\n El usuario se encuentra dado de baja");
}

