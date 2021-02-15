#ifndef DETALLE_PEDIDOS_H_INCLUDED
#define DETALLE_PEDIDOS_H_INCLUDED

class Detalle_Pedido{
    private:
        int ID_Pedido;
        int ID_Producto;
        int cantidad;
        float precio;
    public:
        Detalle_Pedido();
        void setID_Pedido(int);
        void setID_Producto(int);
        void setCantidad(int);
        void setPrecio(float);

        int getID_Pedido();
        int getID_Producto();
        int getCantidad();
        float getPrecio();
};


#endif // DETALLE_PEDIDOS_H_INCLUDED
