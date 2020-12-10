#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED
#include "Factura.h"

class Ventas{
    private:
        int V_Nro_Fact;
        int Cod_Producto;
        char Descripcion[20];
        int Cant_Producto;
        float Precio;
        float Importe;
    public:
        Ventas();
        ~Ventas(){};
        void setNro_Factura(int);
        void setCod_Producto(int CodProducto){Cod_Producto = CodProducto;}
        void setDescripcion(char *Descrip){strcpy(Descripcion, Descrip);}
        void setCant_Producto(int CantProducto){Cant_Producto = CantProducto;}
        void setPrecio(float Precios){Precio = Precios;}
        void setImporte(float imp){ Importe = imp; }
        void Cargar_Venta(int , int , char *, int , float , float );
        void getVentas();
        int getCod_Producto(){return Cod_Producto;}
        char *getDescripcion(){return Descripcion;}
        int getCant_Producto(){ return Cant_Producto;}
        float getPrecio(){ return Precio;}
        float getImporte(){ return Importe;}
        void getVentas(int);
        int getNro_Fact(){return V_Nro_Fact;}
        int Leo_Ventas();
        int BuscarPosicion(int);
        void MostrarVenta();
        void GuardaVentas(Ventas);
};

Ventas Preventa(int, int, int);

    /**cout<<Nueva.getNro_Factura()<<endl;
    cout<<Nueva.getFecha().getDia()<<"/"<<Nueva.getFecha().getMes()<<"/"<<Nueva.getFecha().getAnio()<<endl;
    cout<<Nueva.getNroCliente()<<endl;
    cout<<Nueva.getNros_Factura()<<endl;
    cout<<Nueva.getTotal_Pagar()<<endl;*/



#endif // VENTAS_H_INCLUDED
