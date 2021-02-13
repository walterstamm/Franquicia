#include <iostream>
using namespace std;
#include <cstdlib>
#include <clocale>
#include <cstdio>
#include <vector>
#include "Menu_Principal.h"
#include "InterfazGrafica/ui.h"
#include "Menu_Producto/Menu_Producto.h"
#include "Medio_Pago/Medio_Pago.h"
#include "menus/MenuDescuento.h"
#include "Clases/Comprobantes.h"
#include "clases/Lotes_Productos.h"
#include "clases/Factura.h"
#include "clases/Producto.h"
#include "clases/Ventas.h"

void MENU_PRODUCTO(){
    short opcion;
    do{
        title("MENÚ PRODUCTO", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        cout<<endl<<"--------------------------------------";
        cout<<endl<<"1) CARGAR PRODUCTO";
        cout<<endl<<"2) MODIFICAR CANTIDAD DEL PRODUCTOS";
        cout<<endl<<"3) MODIFICAR CANTIDAD MINIMA";
        cout<<endl<<"4) LISTAR TODOS LOS PRODUCTOS";
        cout<<endl<<"5) LISTAR PRODUCTO POR ID";
        cout<<endl<<"6) ELIMINAR PRODUCTO";
        cout<<endl<<"7) MODIFICAR PRECIO DEL PRODUCTO";
        cout<<endl<<"8) VOLVER AL MENÚ PRINCIPAL";
        cout<<endl<<"9) VENDER";
        cout<<endl<<"--------------------------------------";
        cout<<endl<<"\t OPCIÓN: ";
        cin>>opcion;
        system ("cls");
        switch(opcion){
        case 1:
            Cargar_Producto(); ///declaracion recibe un int
            system("pause");
            system("cls");
        break;
        case 2:
            Modificar_Cantidad();
            system("pause");
            system("cls");
        break;
        case 3:
            Modificar_La_Cantidad_minima();
            system("pause");
            system("cls");
        break;
        case 4:
            Mostrar_Todos_Producto();
            system("pause");
            system("cls");
        break;
        case 5:
            Mostrar_X_Producto();
            system("pause");
            system("cls");
        break;
        case 6:
            Eliminar_Producto();
            system("pause");
            system("cls");
        break;
        case 7:
            Modificar_Precio();
            system("pause");
            system("cls");
        break;
        case 8:
            return;
        break;
        case 9:
            ventas();
            system("pause");
            system("cls");
        break;
        default:
            msj("OPCIÓN INCORRECTA", 15, 3, 1, 1);
        break;
        }
    }while (opcion!=7);
}


void Menu_Medio_Pago(){
    short opcion;
    do{
        title("MENÚ MEDIO PAGO", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        cout<<endl<<"------------------------------------------";
        cout<<endl<<"1) CARGAR MEDIO PAGO";
        cout<<endl<<"2) ELIMINAR MEDIO DE PAGO";
        cout<<endl<<"3) LISTAR TODOS MEDIO DE PAGO";
        cout<<endl<<"5) LISTAR X MEDIO DE PAGO";
        cout<<endl<<"6) MODIFICAR MEDIO DE PAGO";
        cout<<endl<<"7) VOLVER AL MENÚ PRINCIPAL";
        cout<<endl<<"------------------------------------------";
        cout<<endl<<"\t OPCIÓN: ";
        cin>>opcion;
        system ("cls");
        switch(opcion){
        case 1:
            Cargar_Medio_pago();
            system ("pause");
            system ("cls");
        break;
        case 2:
            Eliminar_Mpago();
            system ("pause");
            system ("cls");
        break;
        case 3:
            Mostar_TodosMpago();
            system ("pause");
            system ("cls");
        break;
        case 4:
            Mostar_TodosMpago();
            system ("pause");
            system ("cls");
        break;
        case 5:
            Mostrar_X_Mpago();
            system ("pause");
            system ("cls");
        break;
        case 6:
            Modificar_Mpago();
            system ("pause");
            system ("cls");
        break;
        case 7:
        break;
        default:
            msj("OPCIÓN INCORRECTA", 15, 3, 1, 1);
        break;
        }
    }while (opcion!=7);
}

void Menu_Descuento(){
    short opcion;
    do{
        title("MENÚ DESCUENTO", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        cout<<endl<<"------------------------------------------";
        cout<<endl<<"1) CARGAR DESCUENTO";
        cout<<endl<<"2) ELIMINAR DESCUENTO";
        cout<<endl<<"3) LISTAR TODOS LOS DESCUENTOS";
        cout<<endl<<"4) LISTAR DESCUENTOS POR ID";
        cout<<endl<<"5) MODIFICAR DESCUENTO";
        cout<<endl<<"6) VOLVER AL MENÚ PRINCIPAL";
        cout<<endl<<"------------------------------------------";
        cout<<endl<<"\t OPCIÓN: ";
        cin>>opcion;
        system ("cls");
        switch(opcion){
        case 1:
            CargarDescuento();
            system ("pause");
            system ("cls");
        break;
        case 2:
            ModificarEstadoDescuento();
            system ("pause");
            system ("cls");
        break;
        case 3:
            ListarTodosDescuento();
            system ("pause");
            system ("cls");
        break;
        case 4:
            Mostrar_x_Descuento();
            system ("pause");
            system ("cls");
        break;
        case 5:
            ModificarDescuento();
            system ("pause");
            system ("cls");
        break;
        case 6:
        break;
        default:
            msj("OPCIÓN INCORRECTA", 15, 3, 1, 1);
        break;
        }
    }while (opcion!=6);
}

void Inicio_Ver_Vto(){
    Lotes_Prod Ven;
    Fecha hoy, lote;
    FILE *V = fopen("archivos/Lotes.dat", "rb");
    if(V == NULL){return;}

    Encab_Lote();
    while(fread(&Ven, sizeof(Lotes_Prod), 1, V)){
        if(Ven.getLEstado()== 1){
            lote.setAnio(Ven.getLFe_Vto().getAnio());
            lote.setMes(Ven.getLFe_Vto().getMes());
            lote.setDia(Ven.getLFe_Vto().getDia());
            if(lote < hoy){
                Ven.MuestroLote();
            }
        }
    }
    cout<<"==================================================="<<endl<<endl;
    system("pause");
    fclose(V);
}

void MENU_FACTURACION(){
    int Opcion=200;
    while(Opcion){
        system("cls");
        title("MENU FACTURACIÓN", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        cout<<"\n============================================  |";
        cout<<"\n01-Generar Factura..........................  |";
        cout<<"\n02-Muestro Factura..........................  |";
        cout<<"\n03-Eliminar Factura.........................  |";
        cout<<"\n04-Listar Facturas Eliminadas...............  |";
        cout<<"\n05-Listar Facturas por Nro y Prod (todas)...  |";
        cout<<"\n06-Reportes a eleccion por el usuario.......  |";
        cout<<"\n============================================  |";
        cout<<"\n00- Volver al MENÚ PRINCIPAL................  |";
        cout<<"\n============================================  |";
        cout<<"\nOpcion: "; cin>>Opcion;
        cout<<"============================================\n";
       switch(Opcion){
            case 1:
            {
                int CodProducto, CantProducto, Registros=0;
                char Mas_Producto = 's';
                Factura Nueva;
                Producto Pro;
                Nueva = GeneroNuevaFactura(); ///  DEVUELVO EL REGISTRO FACURA
                cout<<"FACTURA NURO: "<<Nueva.getNros_Factura()<<"=="<<endl;
                {   ///     CREO OBJETOS PRODUCTO Y VENTAS

                    Ventas Vent;
                    vector<Ventas> V_venta;
                    while(Mas_Producto == 's' || Mas_Producto == 'S'){
                            cout<<"\n 0 = Muestra listado productos";
                        do{     ///     SI INGRESA 0 MUESTRA EL LISTADO O ERRONEO VUELVE A PEDIR INGRESO
                            cout<<"\n  CodProducto: "; cin>>CodProducto;
                            while(CodProducto == 0){
                                Pro.Mostrar();
                                cout<<"\n>>>CodProducto: ";
                                cin>>CodProducto;
                            }
                            ///     CARGO CANTIDAD DEL PRODUCTO
                            cout<<"Ingrese Cantidad de Producto: ";
                            cin>>CantProducto;
                            Registros = V_venta.size();
                            if(Registros>0){
                                for(unsigned int i=0; i<V_venta.size(); i++){
                                    if(CodProducto == V_venta.at(i).getCod_Producto()){
                                        CantProducto += V_venta.at(i).getCant_Producto();
                                        V_venta.erase(V_venta.begin()+i);
                                    }
                                }
                            }
                            Vent = Preventa(CodProducto, Nueva.getNros_Factura(), CantProducto);
                            if(Vent.getImporte()> 0){
                                V_venta.push_back(Vent);
                            }else{CodProducto = 0;}
                        }while(CodProducto ==0);
                            system("cls");
                            cout<<endl<<endl;
                            Mostrar_Comprobante();
                            Encab_Fac(-1);
                            Factura().MostrarFactura();
                            Encab_Venta();
                            for(unsigned  int i=0; i<V_venta.size(); i++){
                                V_venta.at(i).MostrarVenta();
                            }
                            cout<<"==============================================================================="<<endl;
                            cout<<"\n*****Continua ingresando Productos?*****"<<endl;
                            cout<<" S = CONTINUA, N = NO CONTINUA: ";
                            cin>>Mas_Producto;
                        while(!(Mas_Producto=='S'||Mas_Producto=='N'||Mas_Producto=='s'||Mas_Producto=='n')){
                            cout<<">>>>> Debe Ingresar un valor correcto <<<<<<<"<<endl;
                            cout<<" S = CONTINUA, N = NO CONTINUA: ";
                            cin>>Mas_Producto;
                        }
                    }   /// Cierro el while de Ventas

                    char confirmar;
                    cout<<"    CONFIRMA FACTURA   "<<endl;
                    cout<<" S = CONFIRMA, N = NO CONFIRMA: ";
                     cin>>confirmar;
                        while(!(confirmar == 's' || confirmar == 'S' || confirmar == 'n' || confirmar == 'N')){
                            cout<<"\n>>>>> CONFIRMA FACTURA <<<<<<<  "<<endl;
                            cout<<" S = CONFIRMA, N = NO CONFIRMA: ";
                             cin>>confirmar;
                        }
                        if(confirmar == 's' || confirmar== 'S'){
                            int Regi=0;
                            float Suma = 0;
                            for(unsigned int i=0; i<V_venta.size(); i++){
                                if(V_venta.at(i).getImporte()!=0){
                                    V_venta.at(i).GuardaVentas();   ///     GUARDO EN EL ARCHIVO VENTAS OJO ANTES DE GUARDAR
                                    Regi++;
                                    Suma += V_venta.at(i).getImporte();
                                }
                            }
                            cout<<endl<<endl;
                            cout<<"PRODUCTOS DIFERENTES = "<<Regi<<endl;
                            cout<<"SUMA DE IMPORTES     = "<<Suma<<endl;
                            system("pause");
                            Nueva.setTotal_Pagar(Suma); ///TENGO QUE VER QUE PASA QUE NO SUMA Y AGREGA A FACTURA
                            Nueva.GuardoFactura();
                            ///PARA DESCONTAR DE LOTES
                            Descuento_Lote(Nueva.getNros_Factura());
                            system("cls");
                        }else{
                            cout<<"SE ELIMINO LOS REGISTROS DE VENTAS Y LA FACTURA"<<endl;
                            system("pause");}
                    system("cls");
                }///        HASTA ACA LA ULTIMA LINEA
            }
            break;
            case 2:///      02-Muestro Factura..........................";
            {
            Mostrar_Comprobante();
            Mostrar_Rotulo_Factura();
            Mostrar_ResumenVenta();
            }
            break;
            case 3:///      03-Eliminar Factura.........................";
            {   ///     CREO UN OBJETO CLASE FACTURA
                Factura Baj;
                int Nro;
                cout<<"Ingrese el Número de Factura a eliminar: ";
                cin>>Nro;
                cout<<endl;
                int pos = Baj.BuscarPosicionFactura(Nro); /// BUSCO LA POSICION QUE PIDO EN BUSCARPOSICION
                cout<<"pos:  "<<pos;
                system("pause");
                if( pos != -1 ){                     /// SI ESTA ME MUESTRA LA POSICION O -1 SI NO ESTA
                    FILE *B = fopen("archivos/Facturas.dat", "rb+");
                    if(B == NULL){
                        cout<<"No se pudo abrir Facturas.dat ";
                        return;
                    }

                    fseek(B, pos *sizeof(Factura), SEEK_SET);
                    ///fread(&Baj, sizeof(Factura), 1, B);

                    bool Est = false;
                    Baj.setEstado(Est);
                    cout<<"Baj.getEstado(): "<<Baj.getEstado();
                    system("pause");

                    int Grabo = fwrite(&Baj, sizeof(Factura), 1, B);
                    if(Grabo == 1){
                        cout<<"El Numero de Factura requerido se Eliminó correctamente"<<endl;
                    }else{
                        cout<<"Upps!! Hubo un error"<<endl;
                    }
                    fclose(B);
                }
            }
            break;
            case 4:///      04-Listar Facturas Eliminadas...............";
            {
            Mostrar_Facturas_Eliminadas();
            }
            break;
            case 5:///      n05-Listar Facturas por Nro y Prod (todas)...";
            {
            Mostrar_TodaVenta();
            }
            break;
            case 6:///      06-Reportes a eleccion por el usuario.......";
            {
            Menu_Reportes();
            }
            break;
            case 0:///      00- Volver al MENU PRINCIPAL................";
            {
            return;
            }
            break;
            default:///     mensaje de error con ui.cpp
            {
            msj("           DEBERA ELEGIR UNA OPCION CORRECTA", 15, 4, 15, 1);
            }
            break;
        }
    }
}

void Menu_Reportes(){
    setlocale(LC_ALL, "spanish");
    int Opcion;
    while(Opcion){
        system("cls");
        title("                MENU REPORTES", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        cout<<"\n================================================";
        cout<<"\n01-Facturas emitidas por fecha..................";
        cout<<"\n02-Ventas realizadas por fecha..................";
        cout<<"\n03-Ventas realizadas en el mes..................";
        cout<<"\n04-Importes recaudado en el mes/año.............";
        cout<<"\n05-Totales de cada Producto vencido.............";
        cout<<"\n06-informe Ventas: Cant Prod y Recaud ==Vector..";
        cout<<"\n================================================";
        cout<<"\n00- Volver al MENU FACTURACION..................";
        cout<<"\n================================================";
        cout<<"\nOpcion: "; cin>>Opcion;
        cout<<"================================================\n";

        switch(Opcion){
            case 1: ///     01-Facturas emitidas en mismo dia...........";
            {
                Facturas_Fecha();
            }
            break;

            case 2:///      02-Ventas realizadas por fecha..............";
            {
                Ventas_Fecha();
            }
            break;

            case 3:///      03-Ventas realizadas por mes y año..........";
            {
                Ventas_Mes();
            }
            break;

            case 4:
            {
                Facturas_Mes();

            }
            break;

            case 5:
            {
                Lotes_Prod_Vencido(); /// LOTES DE PRODUCTOS QUE TIENEN CANTIDAD > 0 Y ESTADO == 0
            }
            break;

            case 6:
                Detalle_Ventas();
            break;

            case 0:
            {
                return;
            }
            break;

            default:
            {
                msj("           DEBERÁ ELEGIR UNA OPCIÓN CORRECTA", 15, 4, 15, 1);
            }
            break;
        }
    }
}

