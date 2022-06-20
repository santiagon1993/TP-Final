#ifndef HEADER_TPFINAL_H_INCLUDED
#define  HEADER_TPFINAL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "header_tpfinal.h"
#define DIM 1000
#define clientes "clientes.dat"
#define consumos "consumos.dat"
#include "gotoxy.h"
#include <time.h>

typedef struct
{
    int id; /// campo único y autoincremental
    int nroCliente;
    char nombre[30];
    char apellido[30];
    char dni[10];
    char email[30];
    char domicilio[45];
    char movil[12];
    int eliminado; /// 0 si está activo - 1 si está eliminado
} stCliente;

typedef struct
{
    int id; /// campo único y autoincremental
    int idCliente;
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a … dependiendo del mes
    int datosConsumidos; /// expresados en mb.
    int baja; /// 0 si está activo - 1 si está eliminado
}stConsumos;

///---------- Clientes -------------

stCliente altaUnCliente(int id,FILE * archi);
void cargaClienteArchivo(char nombreArchivo[]);
int contarRegistros(char archivo[],int tipoDato);
int validacionNroCliente(stCliente b, FILE* archi);
int validacionDni(char dni[], FILE* archi);
void muestraArchivoClientes(char nombreArchivo[]);
void consultaCliente(stCliente cliente);
stCliente buscarporID(char archivo[],int id);
int buscarPorDni(char dni[],FILE* archi,int param);
stCliente buscarPorNroCliente(int nrocliente,FILE * archi);
///funcion borrar cliente para uso del programador
void borclien();

void menuModificar();
void seleccionModificar(int id);
stCliente modificardomicilio(stCliente cliente);
stCliente modificarNombre(stCliente cliente);
stCliente modificarApellido(stCliente cliente);
stCliente modificarDNI(stCliente cliente,FILE* archi);
stCliente modificarMovil(stCliente cliente);
stCliente modificarEmail(stCliente cliente);
stCliente modificarAltaBaja(stCliente cliente);
void modificarCliente(char archivo[],int id,int flag);

///---------- Menu -------------

void mostrarMenu();
void seleccion();

///---------- Consumos -------------

stConsumos altaConsumos(int id,FILE *archi,FILE *archcli);
void cargaRandCons(char arcon[],char arcli[]);
int validacionConsumo (FILE * archi, stConsumos a);
int validacionDiaMesAnio (int anio,int mes,int dia);
int validardia31(int dia);
int validardia30(int dia);
stConsumos valiNroCli(int nrocliente,FILE*archi,stConsumos consumo);
void mostrarConsumos(stCliente cliente, char archivo[],char archicli[]);
void muestraUnConsumo(stConsumos cons,FILE*archi);
void listadoConsumos(char archivo[],char archicli[]);
void muestraConsFecha(char archivo[],char archicli[],int dia,int anio,int mes,int flag);
void modificarAltaBajaCons(char archivo[],char archivocli[],int id);

#endif // HEADER-TPFINAL_H_INCLUDED
