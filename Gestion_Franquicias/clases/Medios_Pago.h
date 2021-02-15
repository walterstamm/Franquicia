#ifndef MEDIOS_PAGO_H_INCLUDED
#define MEDIOS_PAGO_H_INCLUDED

class Medio_Pago{
    private:
        int ID;
        char Medio [30];
        float Monto, Descuento; ///habria que ingresar la fecha del dia que quiere realizar el descuento?
        bool Estado;
    public:
        Medio_Pago();
        bool Cargar_Mpago();///Mpago= medio de pago
        void Listar_Mpago();
        bool Guardar_Mpago();
        bool Modificar_Mpago(int );///estado en false
        int Buscar_ID_Mpago(int =0);///busca si existe el id del medio de pago
        ///gets
        int getID(){return ID;}
        char *getMedio(){return Medio;}
        float getMonto(){return Monto;}
        float getDescuento(){return Descuento;}
        bool getEstado(){return Estado;}
        ///sets
        void setMonto(float _monto){Monto=_monto;}
        void setDescuento(float _descuento){Descuento=_descuento;}
        void setEstado(bool _Estado){Estado=_Estado;}
        float Generar_MPago(float); ///genera descuento del medio pago
};

bool ValidarID_Mpago(int);///recive el ID
float Generar_MPago(float);/// pide datos para generar el descuento de medio pago y el metodo "Generar_MPago(float)" lo genera y lo valida

#endif // MEDIOS_PAGO_H_INCLUDED
