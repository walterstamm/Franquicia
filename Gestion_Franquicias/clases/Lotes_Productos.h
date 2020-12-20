#ifndef LOTES_PRODUCTOS_H_INCLUDED
#define LOTES_PRODUCTOS_H_INCLUDED
#include "Fecha.h"

class Lotes_Prod{
    private:
        int LId;
        int LCodProd;
        int LCantidad;
        Fecha LFe_Vto;
        bool LEstado;
    ///HAY QUE TENER EN CUENTA SI EL PEDIDO INGRESO
    ///SI INGRESO SE TOMA EN CUENTA PARA SUMAR LA CNATIDAD DE PRODUCTO
    ///SI NO INGRESO EL PEDIDO Y SE ELIMINO POR MOTIVOS RXTAORDINARIOS EL ESTADO 0 Y TAMPOCO SE CARGA
    ///DESCONTAR AL EFECTUAR UNA VENTA
    public:
        Lotes_Prod(){   ///     CONSTRUCTOR
                    LId=0;
                    LCodProd=0;
                    LCantidad=0;
                    LEstado=false;}
        ~Lotes_Prod(){};  ///     DESTRUCTOR
        ///     SET
        void setLid(int Id){ LId= Id;}
        void setLCodProd(int CodProd){ LCodProd = CodProd;}
        void setLCantidad(int Cant){ LCantidad = Cant;}
        void setFe_Vto(Fecha fe){LFe_Vto = fe;}
        void setLEstado_true(){ LEstado = true;}
        void setLEstado_false(){ LEstado = false;}
        ///     GET
        int getLId(){ return LId;}
        int getLCodProd(){ return LCodProd;}
        int getLCantidad(){ return LCantidad;}
        Fecha getLFe_Vto(){return LFe_Vto;}
        bool getLEstado(){ return LEstado;}

        void Cargar_Lotes_Prod();
        void MuestroLote();
        bool Grabar_Lotes_Prod(int);
        bool Leer_Lotes_Prod(int);
        ///bool Leer_Lotes_Prod();
        int NuevoID();///TRAE EL NUEVO LID PARA CARGAR UN NUEVO LOTE.
        void ModificarLote(int);
};

void MenuLotes();




#endif // LOTES_PRODUCTOS_H_INCLUDED
