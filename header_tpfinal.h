#ifndef HEADER_TPFINAL_H_INCLUDED
#define  HEADER_TPFINAL_H_INCLUDED

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
    int id; /// campo único y autoincremental int idCliente
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a … dependiendo del mes
    int datosConsumidos; /// expresados en mb. int baja; /// 0 si está activo - 1 si está eliminado
} stConsumos;

stCliente altaUnCliente();
//void consultaCliente(stCliente cliente);
stCliente altaUnCliente(int id);
int validacionNroCliente(stCliente b, char archivo[]);
int validacionDni(char dni[], char archivo[]);
char nomRand (char n[]);
char apellRand(char a[]);
void mostrarMenu();
void seleccion();
void muestraArchivoClientes(char nombreArchivo[]);
void cargaClienteArchivo(char nombreArchivo[]);
int contarRegistros(char archivo[]);
void borclien();
stCliente buscarPorDni(char dni[],char archivo);

#endif // HEADER-TPFINAL_H_INCLUDED
