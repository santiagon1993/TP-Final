#include "header_tpfinal.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define clientes "clientes.dat"
#include <conio.h>
#define ESC 27


stCliente altaUnCliente(int id)
{
    int flag=0;
    stCliente cliente;

    cliente.id = id;

    system("cls");
    printf("numero de cliente: ");
    scanf("%d",&cliente.nroCliente);
    flag=validacionNroCliente(cliente,clientes);

    fflush(stdin);
    printf("Nombre: ");
    gets(cliente.nombre);

    fflush(stdin);
    printf("Apellido: ");
    gets(cliente.apellido);

    fflush(stdin);
    printf("DNI: ");
    gets(cliente.dni);
    if(flag==0)
        flag=validacionDni(cliente.dni,clientes);


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

    if (flag ==1)
    {
        printf("el cliente ya se encuentra en los registros.");
       // system("pause");
        cliente.nroCliente=0;
    }

    return cliente;
}



void borclien()
{
    FILE *arch =fopen("clientes.dat","rb");
    if (arch==NULL)
        exit(1);
    printf("\ningrese el id a eliminar: ");
    int cod;
    fflush(stdin);
    scanf("%d",&cod);

    stCliente cliente;

    FILE *nuevo = fopen("cliente.tmp","ab");
    if (arch==NULL)
        exit(1);

    int existe=0;
    fread(&cliente, sizeof(stCliente), 1, arch);
    while(!feof(arch))
    {
        if (cod==cliente.id)
        {
            printf("Eliminado %i %s %s\n", cliente.id, cliente.nombre, cliente.dni);
            system("pause");
            existe=1;
        }
        else
        {
            fwrite(&cliente, sizeof(stCliente), 1, nuevo);
        }
        fread(&cliente, sizeof(stCliente), 1, arch);
    }
    if (existe==0)
    {
        printf("\nNo existe un cliente con ese id\n");
        system("pause");
    }
    fclose(arch);
    fclose(nuevo);

    remove("clientes.dat");
    rename("cliente.tmp", "clientes.dat");
}

void cargaClienteArchivo(char nombreArchivo[])
{   int static valido=0;
    char salida='s';
    valido = contarRegistros(clientes);
    stCliente cliente;

    FILE* archi=fopen(nombreArchivo,"ab");

    if(archi)
    {

        do
        {valido++;
        cliente=altaUnCliente(valido);

        if(cliente.nroCliente!=0)
           {
               fwrite(&cliente,sizeof(stCliente),1,archi);
               printf("\nEl alta ha sido exitosa.");
           }
           printf("\npresione una tecla para cargar un nuevo cliente, ESC para volver al menu\n");
           fflush(stdin);
           salida=getch();

        } while(salida!=ESC);
    }

    else
        printf("el archivo no pudo abrirse,");

    fclose(archi);

}

int validacionNroCliente(stCliente b, char archivo[])
{
    int flag=0;
    stCliente a;
    FILE* archi = fopen(archivo,"rb");


    if(archi)
    {
        while(fread(&a,sizeof(stCliente),1,archi) && flag==0)
        {

            if(b.nroCliente==a.nroCliente)
            {
                flag = 1;
            }

        }
    }
    else
        printf("el archivo no pudo ser abierto");
    return flag;

}

int validacionDni(char dni[], char archivo[])
{
    int flag=0;
    stCliente a;
    FILE* archi = fopen(archivo,"rb");


    if(archi)
    {
        while(fread(&a,sizeof(stCliente),1,archi) && flag==0)
        {

            if(strcmpi(dni,a.dni)==0)
            {
                flag = 1;
            }

        }
    }
    else
        printf("el archivo no pudo ser abierto");
    return flag;

}
/**void cargaClienteArchivo(char nombreArchivo[])
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

}*/
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
    printf("\n\n========================================================================================\n");

}
void muestraArchivoClientes(char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    stCliente a;
    if(archi)
    {
        while(fread(&a, sizeof(stCliente), 1, archi)>0)
        {
            consultaCliente(a);
        }
        system("pause");
        fclose(archi);
    }

}

stCliente buscarPorDni(char dni[],char archivo){
    FILE* archi = fopen(archivo , "rb");
    stCliente a;
    stCliente b;
    int flag=0;
    if(archi)
    {
        while(fread(&a,sizeof(stCliente),1,archi)>0 && flag==0)
        {
            if(strcmpi(dni,a.dni)==0)
            {
                b=a;
                flag=1;
            }
        }
        if (flag==1)
        {

        }

    }

 return b;
}

void mostrarMenu()
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
    printf("\n");
}
void seleccion()
{
    int registros=0;

    int opcion;
    do
    {
        system("cls");
        mostrarMenu();
        scanf("%d",&opcion);
        switch(opcion)
        {
        case 0:
            break;
        case 1:
        {
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
            break;
        case 5: borclien();
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
