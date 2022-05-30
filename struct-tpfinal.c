#include "header-tpfinal.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define clientes "clientes.dat"

stCliente altaUnCliente()
{
    stCliente cliente;

    fflush(stdin);
    printf("id: ");
    scanf("%d",&cliente.id);

    printf("numero de cliente: ");
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


    return cliente;
}
void cargaClienteArchivo(char nombreArchivo[])
{   stCliente cliente;

        FILE* archi=fopen(nombreArchivo,"ab");

        if(archi){
                        for (int i=0;i<55;i++)
        {
            cliente=altaUnCliente();
            fwrite(&cliente,sizeof(stCliente),1,archi);
        }
        }
        else
        printf("el archivo no pudo abrirse,");

        fclose(archi);

}
int contarRegistros(char archivo[])
{
    FILE *archi=fopen(archivo,"r");
    int registros=0;
    if (archi)
    {
        fseek(archi,0,SEEK_END);
        registros=ftell(archi)/sizeof(stCliente);
    }
    else
        printf("el archivo no pudo abrirse,");
    return registros;
}
void consultaCliente(stCliente cliente)
{
    printf("\nNumero de id........: %d",cliente.id);
    printf("\nNumero de cliente...: %d",cliente.nroCliente);
    printf("\nNombre............: %s",cliente.nombre);
    printf("\nApellido..........: %s",cliente.apellido);
    printf("\nDNI...............: %s",cliente.dni);
    printf("\nEmail.............: %s",cliente.email);
    printf("\nDomicilio.........: %s",cliente.domicilio);
    printf("\nMovil.............: %s",cliente.movil);

    if(cliente.eliminado == 0)
        printf("\nEl usuario se encuentra activo");
    else
        printf("\nEl usuario se encuentra dado de baja");
}
void muestraArchivoClientes(char nombreArchivo[]){
    FILE *archi = fopen(nombreArchivo, "rb");
    stCliente a;

    if(archi){
        while(fread(&a, sizeof(stCliente), 1, archi)>0){
            consultaCliente(a);
        }
    }
    fclose(archi);
}

    void mostrarMenu ()
    {
        printf("1)opcion 1\n");
        printf("2)opcion 2\n");
        printf("3)opcion 3\n");
        printf("4)opcion 4\n");
        printf("5)opcion 5\n");
        printf("6)opcion 6\n");
        printf("7)opcion 7\n");
        printf("8)opcion 8\n");
        printf("9)opcion 9\n");
        printf("10)opcion 10\n");
        printf("Para salir precione ESC caso contrario cualquier tecla \n");
    }
    void seleccion()
{   int registros=0;


    char opcion;
    char temp[10];
    do
    {
        fgets(temp,10,stdin);
        opcion = atoi(temp);
        switch(opcion)
        {
        case 0:
            break;
        case 1:{
                cargaClienteArchivo(clientes);
            }
            break;
        case 2:
            muestraArchivoClientes(clientes);
            break;
        case 3:
            {
                registros=contarRegistros(clientes);
                printf("\n%d\n",registros);
                system("pause");
            }
            break;
        case 4:
            printf("Usted selecciono %i \n",opcion);
            break;
        case 5:
            printf("Usted selecciono %i \n",opcion);
            break;
        case 6:
            printf("Usted selecciono %i \n",opcion);
            break;
        case 7:
            printf("Usted selecciono %i \n",opcion);
            break;
        case 8:
            printf("Usted selecciono %i \n",opcion);
            break;
        case 9:
            printf("Usted selecciono %i \n",opcion);
            break;
        case 10:
            printf("Usted selecciono %i \n",opcion);
            break;
        default:
            printf("Opcion incorrecta \n");
            break;
        }
    }
    while(opcion != 0);
}
