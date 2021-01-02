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
        void setNroFact(int Nueva_Fact){Nro_Fact = Nueva_Fact;} ///Le asigna el nuevo numero de factura = la ultima del archivo +1
        void setEstado(bool Est){Estado = Est; }
        void setTotal_Pagar(float Suma){Total_Pagar = Suma;}
        float setImporte(float);
        void setNro_Cliente(int clien){ Nro_Cliente = clien;}
        void setFecha_Factura(Fecha dia){ Fecha_Factura = dia;}

        void getFactura(Factura){
                cout<<"Nro_Fact:    "<<Nro_Fact<<endl;
                cout<<"Fecha: "<<getFecha().getDia()<<"/"<<getFecha().getMes()<<"/"<<getFecha().getAnio()<<endl;
                cout<<"Nro_Cliente: "<<Nro_Cliente<<endl;
                cout<<"Total_Pagar: "<<Total_Pagar<<endl;
                cout<<"Estado:      "<<Estado<<endl;}

        int getNros_Factura(){return Nro_Fact;} ///Devuelve el nro de factura que tiene el objeto
        Fecha getFecha(){ return Fecha_Factura;}
        int getNroCliente(){return Nro_Cliente;}
        float getTotal_Pagar(){return Total_Pagar;}
        bool getEstado(){return Estado;}
        bool GuardoFactura();
        void Muestro_Guardado();
        int BuscarPosicionFactura(int);
        void MostrarFactura();
};

int Leo_Ultima_Factura();
Factura GeneroNuevaFactura();
void Mostrar_ResumenVenta();
int  Mostrar_ResumenVenta(int);
void Mostrar_TodaVenta();
void Mostrar_Facturas_Eliminadas();
float SumarVentas(int);
void Menu_Reportes();
void Mostrar_Rotulo_Factura();
void Mostrar_Comprobante();
void Facturas_Fecha();
void Ventas_Fecha();
void Ventas_Mes();
void Descuento_Stock(int);
void Detalle_Ventas();
void Encab_Fac(int);


#endif // FACTURA_H_INCLUDED
