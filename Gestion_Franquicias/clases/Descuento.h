#ifndef DESCUENTO_H_INCLUDED
#define DESCUENTO_H_INCLUDED
#include "Fecha.h"

class Descuento{
    private:
        bool Estado;
        float Monto, Porcentaje;///porcentaje es de descuento
        int ID;
        Fecha Actual;
    public:
        Descuento();
        bool Cargar_Descuento();
        void ListarDescuento();
        bool Guardar_Descuento();
        int Buscar_Descuento_ID(int =0);///busca el descuento por ID devuelve la posicion del descuento
        bool ModificarDescuento(int);///recibe la posicion en memoria del descuento y guarda la modificacion realizada
        int getID(){return ID;}
        float getMonto(){return Monto;}
        float getPorcentaje(){return Porcentaje;}
        bool getEstado(){return Estado;}
        void setMonto(float _Monto){Monto=_Monto;}
        void setPorcentaje(float _Porcentaje){Porcentaje=_Porcentaje;}
        void setEstado(bool _Estado){Estado=_Estado;}
        float GenerarDescuento(float); ///genera descuento
};

bool Validar_ID_Descuento(int); ///valida el ID
float GenerarDescuento(float); /// pide datos para generar el descuento y el metodo "GenerarDescuento(float)" lo genera y lo valida

#endif // DESCUENTO_H_INCLUDED
