#ifndef COMPROBANTES_H_INCLUDED
#define COMPROBANTES_H_INCLUDED
#include "Fecha.h"


class Encabezado{
    private:
        char Razon_Social[20];///Fisica o Jurídica dependiendo de
        char Cuit[15];
        char Direccion[40];///Calle Nro Localidad
        char Localidad_Provincia[30];
        char Telefono[14];
        Fecha Fecha_Inicio_Activ;
        char Otros[50];
    public:
        Encabezado();///CONSTRUCTOR
        ~Encabezado();///DESTRUCTOR
        void setFecha_ini(Fecha);

        void setRazon_Social(); ///Fisica o Jurídica dependiendo de
        void setCuit();
        void setDireccion();///Calle Nro
        void setLocalidad_Provincia();///LOCALIDAD - PROVINCIA
        void setTelefono();///011-2222-2222
        Fecha setFecha_inic();
        void setOtros();

        char *getRazon_Social();///Fisica o Jurídica dependiendo de
        char *getCuit();
        char *getDireccion();///Calle Nro
        char *getLocalidad_Provincia();///LOCALIDAD - PROVINCIA
        char *getTelefono();///011-2222-2222
        Fecha getFecha_inic();
        char *getOtros();

        void setCargar_Encabezado(char *, char *, char *, char *, char *);
        void getMostrar_Encabezado();

};



#endif // COMPROBANTES_H_INCLUDED
