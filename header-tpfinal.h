//#ifndef HEADER-TPFINAL_H_INCLUDED
#define HEADER-TPFINAL_H_INCLUDED


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
}stCliente;

typedef struct
{
    int id; /// campo único y autoincremental int idCliente
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a … dependiendo del mes
    int datosConsumidos; /// expresados en mb. int baja; /// 0 si está activo - 1 si está eliminado
}stConsumos;

stCliente altaCliente(int *id);
//#endif // HEADER-TPFINAL_H_INCLUDED
