#ifndef FACTURA_H_INCLUDED
#define FACTURA_H_INCLUDED
#include "Fecha.h"
#include "ui.h"


class Factura{
    private:
        int Nro_Fact;
        Fecha Fecha_Factura;
        int Nro_Cliente;
        float Total_Pagar;
        bool Estado;
    public:
        Factura(){
                Nro_Fact = 0;
                Nro_Cliente = 0;
                Total_Pagar=0;
                Estado = true;}
        ~Factura(){}
        void setFactura(int);
        void setNroFact(int Nro){Nro_Fact = Nro;}
        void setEstado(bool Est){Estado = Est; }
        void setTotal_Pagar(float Suma){Total_Pagar = Suma;}
        float setImporte();
        void setNro_Cliente(int clien){ Nro_Cliente = clien;}
        void setFecha_Factura(Fecha dia){ Fecha_Factura = dia;}

        void getFactura(){  cout<<"Nro_Fact:    "<<Nro_Fact<<endl;
                            cout<<"Nro_Cliente: "<<Nro_Cliente<<endl;
                            cout<<"Total_Pagar: "<<Total_Pagar<<endl;
                            cout<<"Estado:      "<<Estado<<endl;}

        int getNro_Factura(){return Nro_Fact;} ///trae la ultima y suma 1
        int getNros_Factura(){return Nro_Fact;}
        Fecha getFecha(){ return Fecha_Factura;}
        int getNroCliente(){return Nro_Cliente;}
        float getTotal_Pagar(){return Total_Pagar;}
        bool getEstado(){return Estado;}
        int Leo_Ultima_Factura();
        bool Guardo();
        void Muestro_Guardado();
        int BuscarPosicionFactura(int);
};

Factura GeneroNuevaFactura();
void Mostrar_ResumenVenta();
void Mostrar_TodaVenta();
void Mostrar_Facturas_Eliminadas();
void SumarVentas(int);
void Menu_Reportes();
void Mostrar_Rotulo_Factura();
void Mostrar_Comprobante();
void Facturas_Fecha();
void Ventas_Fecha();
void Ventas_Mes();
void Descuento_Stock(int);
void Detalle_Ventas();



#endif // FACTURA_H_INCLUDED
