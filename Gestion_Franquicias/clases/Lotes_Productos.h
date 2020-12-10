#ifndef LOTES_PRODUCTOS_H_INCLUDED
#define LOTES_PRODUCTOS_H_INCLUDED
#include "Fecha.h"

class Lotes_Prod{
    private:
        int LId;
        int LCodProd;
        int Cantidad:
        Fecha Fe_Vto;
        bool Estado;
    ///HAY QUE TENER EN CUENTA SI EL PEDIDO INGRESO
    ///SI INGRESO SE TOMA EN CUENTA PARA SUMAR LA CNATIDAD DE PRODUCTO
    ///SI NO INGRESO EL PEDIDO Y SE ELIMINO POR MOTIVOS RXTAORDINARIOS EL ESTADO 0 Y TAMPOCO SE CARGA
    ///DESCONTAR AL EFECTUAR UNA VENTA
    public:
        Lotes_Prod(){   ///     CONSTRUCTOR
                    LId=0;
                    LCodPord=0;
                    Fecha().Cargar_Fecha_Vencimiento();
                    Estado=false;}
        ~Lotes_Prod();  ///     DESTRUCTOR
        ///     SET
        void setLid(int Id){ LId= Id;};
        void setLCodProd(int CodProd){ LCodProd = CodProd;};
        void setCantidad(int Cant){ Cantidad = Cant; };
        Fecha setFe_Vto(Fecha){Fecha().Cargar_Fecha(); };
        void setEstado_true(){ Estado = true;};
        void setEstado_false(){ Estado = false;};
        ///     GET
        int getLid(){ return LId;};
        int getLCodProd(){ return LCodProd;};
        int getCantidad(){ return Cantidad; };
        Fecha getFe_Vto(){};
        bool setEstado(){ return Estado;};
};















#endif // LOTES_PRODUCTOS_H_INCLUDED
