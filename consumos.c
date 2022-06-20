#include "header_tpfinal.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define clientes "clientes.dat"
#include <conio.h>
#define ESC 27
#include "gotoxy.h"
#include <windows.h>

/** \brief busca un id y devuelve flag 1 = id por parametro e id archivo iguales, flag 3 = cliente eliminado == 1
 *
 * \param entero id
 * \param archivo clientes
 * \return flag
 *
 */
int buscarId(int id,char archivo[])
{
    stCliente cliente;
    int flag=0;

    FILE * archi = fopen(archivo, "rb");
    if(archi)
    {
        while(flag==0 && fread(&cliente,sizeof(stCliente),1,archi)>0)
        {
            if(id==cliente.id)
            {
                flag=1;
                if(cliente.eliminado==1)
                {
                    flag=3;
                }
            }
        }
    }
    fclose(archi);
    return flag;
}

/** \brief pide numero de cliente por parametro y lo compara con el del puntero al archivo , devuelve la estructura de consumo con los id enlazados
 *
 * \param entero numero de cliente
 * \param puntero al archivo
 * \param estructura de consumos
 * \return consumos
 *
 */
stConsumos valiNroCli(int nroc,FILE*archi,stConsumos consumo)
{
    int flag = 0;
    stCliente cliente;
    if(archi)
    {
        rewind(archi);

        while(flag==0 && fread(&cliente,sizeof(stCliente),1,archi)>0)
        {
            if(nroc==cliente.nroCliente)
            {
                consumo.idCliente=cliente.id;
                flag=1;
            }
        }
        if(flag==0){

            consumo.id=0;
        }
    }
    return consumo;
}

/** \brief carga un consumo a la estructura
 *
 * \param entero nro de id
 * \param puntero al archivo de consumo
 * \param puntero al archivo de cliente
 * \return estructura de consumo
 *
 */
stConsumos altaConsumos(int id,FILE *archi,FILE *archcli)
{
    int nroc=0;
    stConsumos consumo;
   /// stCliente cliente;
    int flag=0;
    int flag2=0;

    if(archi && archcli)
    {
        consumo.id=id;

        system("cls");
        printf("\nIngrese el nro de cliente: ");
        scanf("%d",&nroc);
        consumo.idCliente=0;
        consumo=valiNroCli(nroc,archcli,consumo);
        ///valida el numero de cliente y devuelve flag
        if(consumo.idCliente>0)
        {
            flag=1;
        }
        ///si flag == 1 entonces permite cargar el consumo por año , mes y dia
        if (flag==1)
        {

            fflush(stdin);
            printf("\nIngrese a%co: ",164);
            scanf("%d", &consumo.anio);

            fflush(stdin);
            printf("\nIngrese mes: ");
            scanf("%d", &consumo.mes);

            fflush(stdin);
            printf("\nIngrese dia: ");
            scanf("%d", &consumo.dia);

            flag2 = validacionDiaMesAnio(consumo.anio,consumo.mes,consumo.dia);
            /// cuando valida la fecha devuelve un flag , si flag2 == 2 entonces permite ingresar los datos consumidos

            if (flag2 == 1 )
            {
                fflush(stdin);
                printf("\nIngrese los datos consumidos: ");
                scanf("%d", &consumo.datosConsumidos);
                flag2 = validacionConsumo(archi, consumo);
                /// cambia el valor del flag por la validacion de Consumo
            }
            else
            {
                printf("\nFecha incorrecta");
            }

            /// si el flag es igual a 2 o igual a 0, vuelve a dejar el id en 0
            if (flag2==2 || flag2==0)
            {
                consumo.id=0;
            }
            /*  if (cliente.eliminado == 1)
              {
                  printf("\nEl cliente se encuentra dado de baja");
              }*/
            consumo.baja=0;
        }
        else
        {
            printf("el nro de cliente es invalido");
            consumo.id=0;
        }
    }
    return consumo;
}

/** \brief carga los datos de consumo a un archivo
 *
 * \param archivo consumo
 * \param archivo cliente
 * \return void (no retorna)
 *
 */
void cargaConsumoArchivo(char archivo[],char arccli[])
{
    char opcion;
    static int id=0;
    id=contarRegistros(consumos,0);

    stConsumos consumo;

    FILE * archi = fopen (archivo, "r+b");
    FILE * archicli = fopen (arccli, "rb");
    if(archi && archicli)
    {
        do
        {
            id++;
            consumo = altaConsumos(id,archi,archicli);

            if(consumo.id!=0)
            {
                fwrite(&consumo,sizeof(stConsumos),1,archi);
                printf("\n se ha cargado el consumo con exito.");
            }
            else
            {
                id--;
            }

            printf("\nESC para salir, cualquier tecla para continuar. ");
            opcion=getch();
        }
        while (opcion!=ESC);

        fclose(archi);
    }
    else
    {
        printf("\nintente nuevamente.");
        FILE * archi = fopen (archivo, "ab");
        fclose(archi);
    }
}

/** \brief corrobora si la fecha ingresada es valida
 *
 * \param entero año
 * \param entero mes
 * \param entero dia
 * \return flag 1 si es verdadero
 *
 */
int validacionDiaMesAnio (int anio,int mes,int dia)
{
    ///meses 1 3 5 7 8 10 12 = 31 --- meses 4 6 9 11 = 30 ---- mes 2 = 28 / biciesto 29 .. devuelve un flag = 1 si la fecha es correcta
    int flag = 0;

    if(mes >=1 && mes <=12)
    {
        switch (mes)
        {
        case 1:                         ///ENERO
        {
            flag=validardia31(dia);

        }
        break;

        case 2:                         ///FEBRERO
        {
            if (anio % 4 == 0 && anio % 100 !=0)
            {
                if(dia >=1 && dia <=29 )
                {
                    flag = 1;
                }
                else
                {
                    flag = 0;
                }
            }
            else if (dia >= 1 && dia <=28)
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }

        }
        break;

        case 3:                                    ///MARZO
        {
            flag=validardia31(dia);
        }
        break;

        case 4:                                     ///ABRIL
        {
            flag=validardia30(dia);

        }
        break;

        case 5:                                    /// MAYO
        {
            flag=validardia31(dia);

        }
        break;

        case 6:                                  ///JUNIO
        {
            flag=validardia30(dia);

        }
        break;

        case 7:                                 ///JULIO
        {
            flag=validardia31(dia);

        }
        break;

        case 8:                                 ///AGOSTO
        {
            flag=validardia31(dia);

        }
        break;

        case 9:                                 ///SEPTIEMBRE
        {
            flag=validardia30(dia);

        }
        break;

        case 10:                                ///OCTUBRE
        {
            flag=validardia31(dia);

        }
        break;

        case 11:                                ///NOVIEMBRE
        {
            flag=validardia30(dia);

        }
        break;

        case 12:                                ///DICIEMBRE
        {
            flag=validardia31(dia);

        }

        break;

        }
    }

    return flag;
}

/** \brief valida si la cantidad de dias es correcta, modularizacion
 *
 * \param entero dia
 * \return flag 1 si es verdadero
 *
 */
int validardia31(int dia)
{
    int flag=0;
    if(dia >=1 && dia <=31 )
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    return flag;
}

/** \brief valida si la cantidad de dias es correcta, modularizacion
 *
 * \param entero dia
 * \return flag 1 si es verdadero
 *
 */
int validardia30(int dia)
{
    int flag=0;
    if(dia >=1 && dia <=30 )
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    return flag;
}

/** \brief muestra los consumos de un cliente, y busca si coincide el id entonces los acumula
 *
 * \param estructura de cliente
 * \param archivo consumo
 * \param archivo cliente
 * \return void (no retorna)
 *
 */
void mostrarConsumos(stCliente cliente, char archivo[],char archicli[])
{
    ///mostrar los datos del cliente y los datos consumidos hasta el momento
    stConsumos consumo;
    int acum=0;

    FILE *archicons = fopen(archivo, "rb");
    FILE *archicliente = fopen(archicli, "rb");

    if (archicons&&archicliente)
    {
        consultaCliente(cliente);

        while(fread(&consumo,sizeof(stConsumos),1,archicons)>0)
        {
            if(cliente.id==consumo.idCliente)
            {
                muestraUnConsumo(consumo,archicliente);
                acum=acum+consumo.datosConsumidos;
            }
        }
        printf("\nEl total de datos consumidos es de : %d MB\n",acum);
        system("pause");
    }

    fclose(archicons);
    fclose(archicliente);
}

/** \brief muestra un consumo de un cliente
 *
 * \param estructura de consumo
 * \param puntero al archivo
 * \return void (no retorna)
 *
 */
void muestraUnConsumo(stConsumos cons,FILE*archi)
{
    rewind(archi);
    stCliente cliente;
    if(archi)
    {
        fseek(archi,sizeof(stCliente)*(cons.idCliente-1),SEEK_CUR);
        fread(&cliente,sizeof(stCliente),1,archi);
        printf("\nID.....................: %d",cons.id);
        printf("\nNro Cliente............: %d",cliente.nroCliente);
        printf("\nfecha..................: %d/%d/%d",cons.dia,cons.mes,cons.anio);
        printf("\ndatos consumidos (MB)..: %d",cons.datosConsumidos);

        if (cons.baja==1)
        {
            printf("\nel consumo se encuentra dado de baja.");
        }
        else if(cons.baja==0)
        {
            printf("\nEl consumo se encuentra activo.");
        }
        printf("\n\n========================================================================================\n");
    }

}

/** \brief muestra consumo por fecha
 *
 * \param archivo consumo
 * \param archivo cliente
 * \param entero dia
 * \param entero año
 * \param entero mes
 * \param entero flag tomado de la funcion ...
 * \return void (no retorna)
 *
 */
void muestraConsFecha(char archivo[],char archicli[],int dia,int anio,int mes,int flag)
{
    stConsumos consumo;

    FILE* archi = fopen(archivo,"rb");
    FILE* archicliente = fopen(archicli, "rb");

    if (archi && archicliente)
    {
        while(fread(&consumo,sizeof(stConsumos),1,archi)>0)
        {

            if (flag==3 && consumo.anio == anio && consumo.dia == dia && consumo.mes == mes)
            {
                muestraUnConsumo(consumo,archicliente);
            }
            if (flag==2 && consumo.anio == anio && consumo.mes == mes)
            {
                muestraUnConsumo(consumo,archicliente);
            }
            if (flag==1 && consumo.anio == anio)
            {
                muestraUnConsumo(consumo,archicliente);
            }
        }
        fclose(archi);
        fclose(archicliente);
        system("pause");
    }
}

/** \brief valida que la fecha del consumo y el id sean correctos entonces se acumulan los datos y se cargan al archivo
 *
 * \param puntero al archivo
 * \param estructura de consumo
 * \return flag 2 si el id y la fecha son correctas
 *
 */
int validacionConsumo (FILE * archi, stConsumos a)
{
    int flag = 1;
    stConsumos b;

    if (archi)
    {
        rewind(archi);

        while(flag==1 && fread(&b,sizeof(stConsumos),1,archi)>0)
        {

            if(a.idCliente == b.idCliente && a.anio == b.anio && a.mes == b.mes && a.dia == b.dia)
            {
                flag = 2;

                b.datosConsumidos = a.datosConsumidos + b.datosConsumidos;
                fseek(archi,sizeof(stConsumos)*(-1),SEEK_CUR);
                fwrite(&b, sizeof(stConsumos),1,archi);
                printf("\nSe ha cargado el consumo con exito.");
            }
        }
    }


    else
    {

        printf("el archivo no se pudo abrir");
        system("pause");
    }
    return flag;
}

/** \brief muestra todos los consumos pertenecientes a cada cliente
 *
 * \param archivo consumo
 * \param archivo cliente
 * \return void (no retorna)
 *
 */
void listadoConsumos(char archivo[],char archicli[])
{
    system("cls");
    stConsumos consumo;

    FILE * archi =fopen(archivo,"rb");
    FILE * archicliente =fopen(archicli,"rb");

    if (archi && archicliente)
    {


        while(fread(&consumo,sizeof(stConsumos),1,archi)>0)
        {
            muestraUnConsumo(consumo,archicliente);
        }
    }

    system("pause");
    fclose(archi);
    fclose(archicliente);

}

/** \brief modifica si un consumo se encuentra dado de baja o de alta
 *
 * \param archivo consumo
 * \param archivo cliente
 * \param entero id
 * \return void (no retorna)
 *
 */
void modificarAltaBajaCons(char archivo[],char archivocli[],int id)
{
    int flag=0;
    stConsumos consumo;
   /// int opc=0;
    FILE* archi = fopen(archivo,"r+b");
    FILE* archicl = fopen(archivocli,"rb");

    if(archi&&archicl)
    {
        while(flag==0 && fread(&consumo,sizeof(stConsumos),1,archi)>0)
        {
            if (id==consumo.id)
            {
                flag=1;
                printf("\n");
                muestraUnConsumo(consumo,archicl);
                printf("\n");
                /// si el id cliente y el id consumo son iguales entonces muestra el consumo del cliente y cambia el flag a 1

                if (consumo.baja == 0 )
                {
                    consumo.baja=1;

                }
                else if(consumo.baja==1)
                {
                    consumo.baja=0;

                }

                fseek(archi,sizeof(stConsumos)*(-1),SEEK_CUR);
                fwrite(&consumo,sizeof(stConsumos),1,archi);
                printf("\nEl consumo fue modificado con exito.\n");

            }
        }
  system("pause");

        fclose(archicl);
        fclose(archi);
    }

}

/** \brief carga mil consumos aleatorios a los clientes que se encuentran en el archivo clientes
 *
 * \param archivo consumo
 * \param archivo cliente
 * \return void (no retorna)
 *
 */
void cargaRandCons(char arcon[],char arcli[]){
srand(time(NULL));
int nrocliente;
int nroc;
int opc=0;
int flag=0;
int total=0;
int flag2=0;
stConsumos consumo;
///stCliente cliente;
 static int id=0;
    id=contarRegistros(consumos,0);
    nrocliente=contarRegistros(clientes,1);
    nrocliente=nrocliente+134;

FILE*arcons=fopen(arcon,"r+b");
FILE*arclien=fopen(arcli,"r+b");

if(arcons && arclien){

      printf("\ningrese la cantidad de consumos random a cargar: \n");
      scanf("%d",&opc);

      do
        {
            id++;

            consumo.id=id;

        system("cls");
        nroc=rand()%100+135;
        consumo.idCliente=0;
        consumo=valiNroCli(nroc,arclien,consumo);
        if(consumo.idCliente>0)
        {
            flag=1;
        }
        if (flag==1)
        {

            consumo.anio=2022;

            consumo.mes= rand()%7;
            consumo.dia= rand()%31;

            flag2 = validacionDiaMesAnio(consumo.anio,consumo.mes,consumo.dia);

            if (flag2==1)
            {
                flag2=valFechaActual(consumo);
            }

            if (flag2 == 1 )
            {
                consumo.datosConsumidos=rand()%120;
                flag2 = validacionConsumo(arcons, consumo);
            }
            else
            {
                printf("\nFecha incorrecta");
            }
            if (flag2==2 || flag2==0)
            {
                consumo.id=0;
            }
            consumo.baja=0;
        }
        else
        {
            printf("\nel nro de cliente es invalido\n");
            consumo.id=0;
        }

            if(consumo.id!=0)
            {
                fwrite(&consumo,sizeof(stConsumos),1,arcons);
            }
            else
            {
                id--;
            }

        total++;

        }
        while (total<opc);

        fclose(arcons);

}

}

/** \brief valida la fecha del consumo que sea menor a la fecha vigente (21/06/2022)
 *
 * \param estructura de consumos
 * \return flag 1 si es verdadero
 *
 */
int valFechaActual(stConsumos consumo)
{int flag=0;

    if (consumo.mes<7)
    {
        if (consumo.dia<=21)
        {
            flag=1;
        }
    }

    return flag;
}



