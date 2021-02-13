#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <clocale>
#include <iostream>
using namespace std;
#include "InterfazGrafica/ui.h"
#include "Menu_Principal.h"
#include "Menu_Pedidos.h"

int main(){
    setlocale(LC_ALL, "spanish");

    Inicio_Ver_Vto();

    short opcion;
    do{
        title("MENÚ PRINCIPAL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        system ("cls");
        title("MENÚ PRINCIPAL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        cout<<endl<<"---------------------------";
        cout<<endl<<"1) MENÚ PRODUCTO...........";
        cout<<endl<<"2) MENÚ PROVEDORES.........";
        cout<<endl<<"3) MENÚ FACTURACION........";
        cout<<endl<<"4) MENÚ LOTES..............";
        ///cout<<endl<<"5) MENÚ MEDIOS PAGO........";
        cout<<endl<<"5) MENÚ ENCABEZADO.........";
        ///cout<<endl<<"6) MENÚ DESCUENTO..........";
        cout<<endl<<"0) SALIR DEL PROGRAMA......";
        cout<<endl<<"---------------------------";
        cout<<endl<<"\t OPCIÓN: ";
        cin>>opcion;
        system ("cls");
        switch(opcion){
        case 1:
            MENU_PRODUCTO();
        break;
        case 2:
            Menu_Pedidos();
            break;
        case 3:
            MENU_FACTURACION();
        break;
        case 4:
            ///Lotes();
            MenuLotes();
        break;
        case 10:
            Menu_Medio_Pago();
        break;
        case 9:
            Menu_Descuento();
        break;
        case 0:
        break;
        case 5:
            Menu_Encabezado();
        break;
        default:
            msj("                     OPCIÓN INCORRECTA", 15, 4, 15, 1);
        break;
        }
    }while (opcion!=0);
return 0;
}
