#ifndef PEDIDO_H_INCLUDED
#define PEDIDO_H_INCLUDED
#include "Fecha.h"
class Pedido{

    private:
        int ID;
        int Codigo_Producto;
        int Cantidad;
        Fecha Fecha_Generado;
        Fecha Vencimiento;
        bool Estado;
    public:
        Pedido();///Constructor
        ~Pedido();///Destructor

        void setFecha();///establece la fecha

        bool Cargar_Pedido();///carga todos los valores del pedido
        void Mostrar_Pedido();///muestra el pedido
        void setCodigo_Producto(int);
        void setCantidad(int);
        void setEstado(bool);
        void setID(int);
        int getID();
        int getCodigo_Producto();
        int getCantidad();
        bool getEstado();
        int NumeroPedido();
        bool GuardaPedido();
};

#endif // PEDIDO_H_INCLUDED
