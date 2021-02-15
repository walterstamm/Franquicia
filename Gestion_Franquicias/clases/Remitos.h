#ifndef REMITOS_H_INCLUDED
#define REMITOS_H_INCLUDED
#include "Fecha.h"
class Remito{

    private:
        int ID_Provedor;
        int Codigo_Producto;
        int Cantidad;
        float Precio;
        int Nro_Remito;
        Fecha Vto_Producto;
        Fecha Fecha_Remito;
        bool Estado;

    public:
        Remito();
        ~Remito();

        void setFecha_Remito();
        void setVto_Producto(Fecha);
        void Cargar_Remito();
        void Mostrar_Remito();

        void setID_Provedor(int);
        void setCodigo_Producto(int);
        void setCantidad(int);
        void setPrecio(float);
        void setNro_Remito(int);
        void setEstado(bool);

        int setID_Provedor();
        int setCodigo_Producto();
        int setCantidad();
        float setPrecio();
        int setNro_Remito();
        bool setEstado();
};



#endif // REMITOS_H_INCLUDED
