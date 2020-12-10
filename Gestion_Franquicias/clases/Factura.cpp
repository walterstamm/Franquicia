#include <vector>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include <stdio.h>
#include<cstring>
#include <iomanip> ///PARA TRABAJAR CON SETW
using namespace std;
#include "Factura.h"
#include "Fecha.h"
#include "Ventas.h"
#include "Producto.h"
#include "Comprobantes.h"

int Factura::BuscarPosicionFactura(int Nro){
    int pos=0;
    FILE *p = fopen("archivos/Facturas.dat" , "rb");
        if(p == NULL){
            cout<<"No se pudo abrir Facturas.dat.....\n";
            return -1;
        }
    while(fread(this, sizeof(Factura),1,p)){
        if(Nro == Nro_Fact){
            fclose(p);
            return pos; ///retorna la posicion del archivo
        }
        pos++;
    }
    fclose(p);
    return pos = -1; ///retorna -1 si no encontro.
}

void Factura::setFactura(int Cliente){
    Nro_Fact = Leo_Ultima_Factura()+1;
    Nro_Cliente = Cliente;
    Total_Pagar=0;///FUNCION PARA SUMAR LA VENTA FALTA
    Fecha_Factura.setFechaHoy();
}

int Factura::Leo_Ultima_Factura(){
    FILE *Fact=fopen("archivos/Facturas.dat", "rb");
    if(Fact == NULL){cout<<"No se abrio el Archivo Facturas.dat";
    return 0;}
    ///Vuelve 1 posición para leer el registro grabado
    fseek(Fact,-1*sizeof(Factura), SEEK_END); ///tiene un warning osea futuro error
    fread(this, sizeof(Factura), 1, Fact);///Muestro lo grabado recien
    fclose(Fact);
    return Nro_Fact;
}

void SumarVentas(int NroFat){ ///9-12-2020
    Ventas  V_Pago;
    Factura F_Pago;
    float Suma = 0;
    FILE *F = fopen("archivos/Facturas.dat", "rb+");///     ABRO ARCHIVO FACTURAS
    if(F == NULL){
        cout << "No se pudo abrir Facturas.dat ";
        return;
    }
    FILE *V = fopen("archivos/Ventas.dat", "rb");///     ABRO ARCHIVO VENTAS
    if ( V == NULL) {
        cout<< "No se pudo abrir Ventas.dat";
        fclose(F);
        return ;
    }

    while( fread( &V_Pago, sizeof(Ventas), 1 , V)){ ///     LEO VENTAS Y SI ES IGUAL QUE NROFAT LO SUMA A LA VARIABLE SUMA
        if( NroFat == V_Pago.getNro_Fact() ){
            Suma += V_Pago.getImporte();
            cout<<"SUMA: "<<Suma<<endl;
            system("pause");
        }
    }
    ///     LE ENVIO A SETTOTAL_PAGAR LA SUMA Y LO GUARDA EN LA EL ATRIBUTO TOTAL_PAGAR
    F_Pago.setTotal_Pagar(Suma);
    ///     LO UBICA EN EL ULTIMO REGISTRO
    fseek(F, -1 * sizeof(Factura), SEEK_END);
    ///     LO REESCRIBE CON LA SUMA TOTAL DEL PAGO
    if(fwrite(&F_Pago, sizeof(Factura), 1, F) == 1 ){
        cout<<"Se Grabo Correctamente";
    }
    fclose(V);
    fclose(F);
}

void Descuento_Stock(int NroFactura){

    Producto P_Stock;
    Ventas   V_Stock;

    ///     ABRO LOS ARCHIVOS PRODUCTO Y VENTAS
    FILE *P = fopen("archivos/producto.dat", "rb+");
    FILE *V = fopen("archivos/Ventas.dat", "rb");
    if(P == NULL || V == NULL){
        cout << "No se pudo abrir algun archivo producto.dat o Ventas.dat";
        fclose(P);
        fclose(V);
        return;
    }
    ///     LEO VENTAS Y SI ES IGUAL QUE NROFAT LO SUMA A LA VARIABLE SUMA
    while( fread( &P_Stock, sizeof(Producto), 1 , P)){


        fseek(V, sizeof(Ventas), SEEK_SET);
        while( fread( &V_Stock, sizeof(Ventas), 1, V)){

            if( NroFactura == V_Stock.getNro_Fact()
               && P_Stock.getID() == V_Stock.getCod_Producto()){
                int pos = P_Stock.Buscar_Producto_ID(P_Stock.getID());
                int cant = -(V_Stock.getCant_Producto());
                bool grabo=false;
                P_Stock.setMod_Cantidad(cant);
                grabo=P_Stock.ModificarProducto(pos);
                if(grabo == true){
                    cout<<"Grabo bien";
                    system("pause");
                }else{ cout<<"No grabo";}
                system("pause");
            }
        }
    }
    fclose(V);
    fclose(P);
}

bool Factura::Guardo(){
    FILE *Fact=fopen("archivos/Facturas.dat", "ab");
    if(Fact == NULL){cout<<"No se abrió el Archivo Facturas.dat"; return false;}
    fwrite(this, sizeof(Factura),1,Fact);///Despues de guardar esta en la ultima posición
    fclose(Fact);
    return true;
}

void Factura::Muestro_Guardado(){///PARA VERIFICAR SI REALMENTE GRABÓ
    FILE *Fact=fopen("archivos/Facturas.dat", "rb");
    if(Fact == NULL){cout<<"No se abrio el Archivo Facturas.dat";}
    ///Vuelve 1 posición para leer el registro grabado
    fseek(Fact,-1*sizeof(Factura), SEEK_END);
    fread(this, sizeof(Factura), 1, Fact);///Muestro lo grabado recien
    fclose(Fact);
}

void MENU_FACTURACION(){

    int Opcion=200;
    while(Opcion){
        system("cls");
        title("MENU FACTURACION", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);

        cout<<"\n============================================  |";
        cout<<"\n01-Generar Factura..........................  |";
        cout<<"\n02-Muestro Factura..........................  |";
        cout<<"\n03-Eliminar Factura.........................  |";
        cout<<"\n04-Listar Facturas Eliminadas...............  |";
        cout<<"\n05-Listar Facturas por Nro y Prod (todas)...  |";
        cout<<"\n06-Reportes a eleccion por el usuario.......  |";
        cout<<"\n============================================  |";
        cout<<"\n00- Volver al MENU PRINCIPAL................  |";
        cout<<"\n============================================  |";
        cout<<"\nOpcion: "; cin>>Opcion;
        cout<<"============================================\n";


       switch(Opcion){
            case 1:
            {
                int CodProducto, CantProducto, Registros=0;
                char Mas_Producto = 's';
                Factura Nueva;
                Nueva = GeneroNuevaFactura();  ///  DEVUELVO EL REGISTRO FACURA
                {   ///     CREO OBJETOS PRODUCTO Y VENTAS
                    Producto Prod;
                    Ventas Vent;
                    vector<Ventas> V_venta;
                    while(Mas_Producto == 's' || Mas_Producto == 'S'){
                        cout<<"\n 0 = Muestra listado productos";
                        do{     ///     SI INGRESA 0 MUESTRA EL LISTADO O ERRONEO VUELVE A PEDIR INGRESO
                            cout<<"\n  CodProducto: "; cin>>CodProducto;
                            while(CodProducto == 0){
                                Prod.Mostrar();
                                cout<<"\n>>>CodProducto: ";          cin>>CodProducto;
                            }
                            ///     CARGO CANTIDAD DEL PRODUCTO
                            cout<<"Ingrese Cantidad de Producto: ";  cin>>CantProducto;

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
                            }else{CodProducto =0;}
                        }while(CodProducto ==0);

                            for(unsigned  int i=0; i<V_venta.size(); i++){
                                V_venta.at(i).MostrarVenta();
                            }
                            cout<<"*Continua ingresando Productos? S=SI; N=NO: ";
                            cin>>Mas_Producto;
                        while(!(Mas_Producto=='S'||Mas_Producto=='N'||Mas_Producto=='s'||Mas_Producto=='n')){
                            cout<<">>> Debe Ingresar un valor correcto"; cin>>Mas_Producto;
                        }
                    }   /// Cierro el while de Ventas

                    char confirmar;
                    cout<<"Confirmar Factura: SI=S, NO=N  "; cin>>confirmar;
                        while(!(confirmar == 's' || confirmar == 'S' || confirmar == 'n' || confirmar == 'N')){
                            cout<<">>>>>Confirmar Factura: SI=S, NO=N  "; cin>>confirmar;
                        }
                        if(confirmar == 's' || confirmar== 'S'){
                            for(unsigned int i=0; i<V_venta.size(); i++){
                                V_venta.at(i).GuardaVentas(Vent);   ///     GUARDO EN EL ARCHIVO VENTAS OJO ANTES DE GUARDAR
                            }
                            SumarVentas(Vent.getNro_Fact()); ///TENGO QUE VER QUE PASA QUE NO SUMA Y AGREGA A FACTURA
                            Nueva.Guardo();
                            Descuento_Stock(Nueva.getNros_Factura());

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

Factura GeneroNuevaFactura(){
    {
    ///     CREO OBJETO FACTURA
    Factura Nueva;
    int Cliente=-1;
    cout<<"\nINGRESE CLIENTE: "; cin>>Cliente;
    cout<<"Fecha: "<<Nueva.getFecha().getDia()<<"/"<<Nueva.getFecha().getMes()<<"/"<<Nueva.getFecha().getAnio()<<endl;
    ///GENERO NRO FACTURA CON NRO CLIENTE EN LA MEMORIA.
    ///Nueva.setFactura(Cliente);
    int fact = Nueva.Leo_Ultima_Factura()+1;
    Nueva.setNroFact(fact);
    ///Nueva.setFecha_Factura(Fecha().setFechaHoy()); ///Fecha_Factura.setFechaHoy();
    Nueva.setNro_Cliente(Cliente);
    Nueva.setTotal_Pagar( 0);///FUNCION PARA SUMAR LA VENTA FALTA
    Nueva.setEstado(true);
    ///         ======ACA PUEDO LLAMAR A LA FUNCION QUE MUESTRA LOS DATOS DE LA FACTURA  =====
    return Nueva;
    }
}

void Mostrar_ResumenVenta(){ ///de la Factura Actual
    cout<<"ENTRE EN MOSTRAR RESUMEN VENTA"<<endl;
    system("pause");

    Factura fac;
    Ventas ven;

    int NroF = fac.Leo_Ultima_Factura()+1; ///Traigo el ultimo numero

        ///     Muestro las ventas de la facturael resumen de ventas
        cout<<"==============================================================================="<<endl;
        cout << left;
        cout << setw(6) << "NROF";
        cout << setw(7) << "Codigo " << setw(18) << "Descripcion" << setw(6) << "Cant" << setw(15) << "P. Unidad" << setw(10) << "Importe" << endl;
        cout<<"==============================================================================="<<endl;
        FILE *V = fopen("archivos/Ventas.dat", "rb");
        if(V == NULL) {
            cout<<"No se pudo abrir Ventas.dat";
            return;
        }
        while(fread(&ven, sizeof(Ventas), 1, V) ){
            cout<<"ENTRO EN EL WHILE"<<endl;
            system("pause");

            int veo = ven.getNro_Fact();
            cout<<"Nro_F: "<<NroF<<"  veo: "<<veo<<endl;
            system("pause");

            if(NroF == veo){
                cout<<"ENTRO EN EL IF ES DECIR NROF == VEO"<<endl;
                system("pause");

                cout << left;
                cout << setw(6);
                cout << ven.getNro_Fact();
                cout << setw(7);
                cout << ven.getCod_Producto();
                cout << setw(18);
                cout << ven.getDescripcion();
                cout << setw(6);
                cout << ven.getCant_Producto();
                cout << setw(15);
                cout << ven.getPrecio();
                cout << setw(10);
                cout << ven.getImporte()<<endl;
            }
        }
        cout<<"==============================================================================="<<endl;
        cout<<"MOSTRO HASTA LA ULTIMA FILA"<<endl;
        fclose(V);
        system("pause");
        system("cls");
}

void Mostrar_TodaVenta(){ ///de la Factura Actual
        Ventas Aux;
        system("cls");
        FILE *Veo=fopen("archivos/Ventas.dat", "rb");
        if(Veo == NULL){
            cout<<"No se pudo abrir Ventas.dat ";
            return;
        }
        cout<<"==============================================================================="<<endl;
        cout<<"\nRESUMEN DE NROS FACTURAS EMITIDAS CON SUS VENTAS: "<<endl;
        cout<<"==============================================================================="<<endl;
        cout << left;
        cout << setw(6) << "NROF";
        cout << setw(7) << "Codigo " << setw(18) << "Descripcion" << setw(11) << " Cantidad" << setw(15) << "P. Unidad" << setw(10) << "Importe" << endl;
        cout<<"==============================================================================="<<endl;

        while (fread(&Aux, sizeof(Ventas), 1, Veo)){
                cout << right;
                cout << setw(3);
                cout << Aux.getNro_Fact()<<" ";
                cout << setw(6);
                cout << Aux.getCod_Producto()<<"   ";
                cout << left<< setw(20);
                cout << Aux.getDescripcion();
                cout << right << setw(6);
                cout << Aux.getCant_Producto();
                cout << setw(11);
                cout << Aux.getPrecio();
                cout << setw(12);
                cout << Aux.getImporte()<<endl;
        }

        cout<<"==============================================================================="<<endl;
        cout<<"MOSTRO HASTA LA ULTIMA FILA"<<endl;
        system("pause");
        fclose(Veo);
        system("cls");
}

void Mostrar_Comprobante(){
    Encabezado Rot;
    system("cls");
    FILE *Enc = fopen("archivos/Encabezado.dat", "rb");
    if( Enc == NULL){
        cout<<"No se pudo abrir el archivo ";
        return; }
    fseek(Enc, 0 * sizeof(Encabezado), SEEK_SET);
    fread(&Rot, sizeof(Encabezado), 1, Enc);
    cout<<"==============================================================================="<<endl;
    cout<<"         DATOS DE LA EMPRESA DE LA FRANQUICIA: "<<endl;
    cout<<"==============================================================================="<<endl;
    cout << "RAZON SOCIAL: " <<Rot.getRazon_Social()<<"    CUIT: " << Rot.getCuit()<<endl;
    cout << "DIRECCION:    " <<Rot.getDireccion()<< "     LOCALIDAD Y PROVICIA: " << Rot.getLocalidad_Provincia()<<endl;
    cout << "FECHA INICIO ACTIVIDAD:  "<<Rot.getFecha_inic().getDia()<<"/"<<Rot.getFecha_inic().getMes()<<"/"<<Rot.getFecha_inic().getAnio()<<" TELEFONO: "<<Rot.getTelefono()<<endl;
    ///cout <<"==============================================================================="<<endl;
}

void Mostrar_Rotulo_Factura(){
    Factura Rotulo;
    FILE *Fa= fopen("archivos/Facturas.dat", "rb");
    if(Fa == NULL){
        cout<<"No se pudo abrir Facturas.dat"<<endl;
        return;
    }

    cout<<"==============================================================================="<<endl;
    cout<<"         DETALLE DE LA FACTURA NRO: "<<Rotulo.Leo_Ultima_Factura()<<endl;
    cout<<"==============================================================================="<<endl;
    cout << right;
    cout << setw(4) << "NROF";
    cout << setw(12) << "DD/MM/AAAA " << setw(10) << "Cliente   " << setw(12) << "Imp/Pagar" << setw(8) << "Estado" <<  endl;
    cout<<"==============================================================================="<<endl;

    fseek(Fa, -1 * sizeof(Factura), SEEK_END);
    fread(&Rotulo, sizeof(Factura), 1 ,Fa );

        ///if(Rotulo.Leo_Ultima_Factura() == Rotulo.getNros_Factura()){
            cout << right;
            cout << setw(3);
            cout << Rotulo.getNros_Factura();
            ///int dia; if(Elim.getFecha().getDia()<10){ dia=1; }else{ dia = 2;}
            cout << setw(3);
            cout << Rotulo.getFecha().getDia();
            cout << "/";
            cout << setw(2);
            cout << Rotulo.getFecha().getMes();
            cout << "/";
            cout << setw(4);
            cout << Rotulo.getFecha().getAnio();
            cout << setw(9);
            cout << Rotulo.getNroCliente();
            cout << setw(12);
            cout << Rotulo.getTotal_Pagar();
            cout << setw(8);
            cout << Rotulo.getEstado();
            cout << endl;
        ///}

    ///cout<<"==============================================================================="<<endl;
    fclose(Fa);
}

void Mostrar_Facturas_Eliminadas(){
    Factura Elim;

    system("cls");
    FILE *Fa= fopen("archivos/Facturas.dat", "rb");
    if(Fa == NULL){
        cout<<"No se pudo abrir Facturas.dat"<<endl;
        return;
    }
    cout<<"==============================================================================="<<endl;
    cout<<"\n       RESUMEN DE NROS FACTURAS EMITIDAS Y ELIMINADAS: "<<endl;
    cout<<"==============================================================================="<<endl;
    cout << right;
    cout << setw(4) << "NROF";
    cout << setw(12) << "DD/MM/AAAA "<<left << setw(10) << " Cliente" << right << setw(12) << "Imp/Pagar" << setw(8) << "Estado" <<  endl;
    cout<<"==============================================================================="<<endl;

    while( fread(&Elim, sizeof(Factura), 1 ,Fa )  ){
        if(Elim.getEstado() == false){
            cout << right;
            cout << setw(3) << Elim.getNros_Factura()<<"";
            ///int dia; if(Elim.getFecha().getDia()<10){ dia=1; }else{ dia = 2;}
            cout << setw(4) << Elim.getFecha().getDia() << "/" << setw(2) << Elim.getFecha().getMes() << "/" << setw(4) << Elim.getFecha().getAnio();
            cout << setw(9);
            cout << Elim.getNroCliente();
            cout << setw(14);
            cout << Elim.getTotal_Pagar();
            cout << setw(8);
            cout << Elim.getEstado();
            cout << endl;
        }
    }
    cout<<"==============================================================================="<<endl;
    system("PAUSE");
    system("cls");
    fclose(Fa);
}

void Menu_Reportes(){
    int Opcion;
    while(Opcion){
        system("cls");
        title("                MENU REPORTES", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        cout<<"\n================================================";
        cout<<"\n01-Facturas emitidas por fecha..................";
        cout<<"\n02-Ventas realizadas por fecha..................";
        cout<<"\n03-Ventas realizadas en el mes..................";
        cout<<"\n04-Importes recaudado en el mes.................";
        cout<<"\n05-Importes recaudados en el dia................"; ///RESUMEN DE NROS FACTURAS EMITIDAS CON SUS VENTAS
        cout<<"\n06-Totales de cada Producto vencido.............";
        cout<<"\n07-informe Ventas: Cant Prod y Recaud ==Vector..";
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

            }
            break;

            case 5:
            {

            }
            break;

            case 6:
            {

            }
            break;

            case 7:
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

void Facturas_Fecha(){
    Factura Fecha;
    int Dia, Mes, Anio;
    system("cls");
    title("MENU REPORTES = 01-Facturas emitidas po fecha", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
    cout<<endl;
    cout<<"Ingrese la fecha DD:    ";   cin>>Dia;
    cout<<"Ingrese la fecha MM:    ";   cin>>Mes;
    cout<<"Ingrese la fecha AAAA:  ";   cin>>Anio;

    FILE *Fa= fopen("archivos/Facturas.dat", "rb");
    if(Fa == NULL){
        cout<<"No se pudo abrir Facturas.dat"<<endl;
        return;
    }
    cout<<"==============================================================================="<<endl;
    cout<<"\n         RESUMEN DE NROS FACTURAS EMITIDAS POR FECHA: "<<endl;
    cout<<"==============================================================================="<<endl;
    cout << right;
    cout << setw(4) << "NROF";
    cout << setw(12) << "DD/MM/AAAA " << setw(10) << "Cliente   " << setw(12) << "Imp/Pagar" << setw(8) << "Estado" <<  endl;
    cout<<"==============================================================================="<<endl;
    float Tot_Factura=0;
    while( fread(&Fecha, sizeof(Factura), 1 ,Fa )  ){
        ///if(Fecha.getFecha().getDia() == Dia && Fecha.getFecha().getMes() == Mes && Fecha.getFecha().getAnio() == Anio){
            cout << right;
            cout << setw(3);
            cout << Fecha.getNros_Factura();
            ///int dia; if(Elim.getFecha().getDia()<10){ dia=1; }else{ dia = 2;}
            cout << setw(3);
            cout << Fecha.getFecha().getDia();
            cout << "/";
            cout << setw(2);
            cout << Fecha.getFecha().getMes();
            cout << "/";
            cout << setw(4);
            cout << Fecha.getFecha().getAnio();
            cout << setw(9);
            cout << Fecha.getNroCliente();
            cout << setw(12);
            cout << Fecha.getTotal_Pagar();
            cout << setw(8);
            cout << Fecha.getEstado();
            cout << endl;
            Tot_Factura +=Fecha.getTotal_Pagar();
        ///}
    }
    cout<<"==============================================================================="<<endl;
    cout<<"                                           TOTAL RECAUDADO:  "<<Tot_Factura<<endl;
    cout<<"==============================================================================="<<endl;
    system("PAUSE");
    system("cls");
    fclose(Fa);
}

void Ventas_Fecha(){    ///     ACA TENGO QUE TRABAJAR CON LOS DOS ARCHIVOS FACTURAS Y VENTAS
        Factura F_Fecha;
        Ventas V_Fecha;

        int Dia, Mes, Anio;
        system("cls");
        title("MENU REPORTES = 02-Ventas realizadas por fecha", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        cout<<endl;
        cout<<"Ingrese la fecha DD:    ";   cin>>Dia;
        cout<<"Ingrese la fecha MM:    ";   cin>>Mes;
        cout<<"Ingrese la fecha AAAA:  ";   cin>>Anio;

        FILE *Fac = fopen("archivos/Facturas.dat", "rb");
        FILE *Ven=fopen("archivos/Ventas.dat", "rb");
        if(Fac == NULL && Ven == NULL){
            cout<<"No se pudo abrir Venas.dat ";
            fclose(Fac);
            fclose(Ven);
            return;
        }

        cout<<"==============================================================================="<<endl;
        cout<<"\n         RESUMEN DE VENTAS REALIZADAS POR FECHA: "<<endl;
        cout<<"==============================================================================="<<endl;
        cout << left;
        cout << setw(6) << "NROF";
        cout << setw(7) << "Codigo " << setw(18) << "Descripcion" << setw(6) << "Cant" << setw(15) << "P. Unidad" << setw(10) << "Importe" << endl;
        cout<<"==============================================================================="<<endl;
        while(fread(&F_Fecha, sizeof(Factura), 1, Fac)){
            if(F_Fecha.getFecha().getDia()== Dia && F_Fecha.getFecha().getMes()== Mes && F_Fecha.getFecha().getAnio()== Anio){
                fseek(Ven, sizeof(Ventas), SEEK_SET);
                while (fread(&V_Fecha, sizeof(Ventas), 1, Ven)){
                    if(F_Fecha.getNros_Factura() == V_Fecha.getNro_Fact()){
                        cout << left;
                        cout << setw(6);
                        cout << V_Fecha.getNro_Fact();
                        cout << setw(7);
                        cout << V_Fecha.getCod_Producto();
                        cout << setw(18);
                        cout << V_Fecha.getDescripcion();
                        cout << setw(6);
                        cout << V_Fecha.getCant_Producto();
                        cout << setw(15);
                        cout << V_Fecha.getPrecio();
                        cout << setw(10);
                        cout << V_Fecha.getImporte()<<endl;
                    }
                }
            }
        }
        cout<<"==============================================================================="<<endl;
        cout<<"MOSTRO HASTA LA ULTIMA FILA"<<endl;
        system("pause");
        fclose(Fac);
        fclose(Ven);
        system("cls");
}

void Ventas_Mes(){
        Factura F_Fecha;
        Ventas V_Fecha;

        int Mes, Anio;
        system("cls");
        title("MENU REPORTES = 03-Ventas realizadas por mes y año", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        cout<<endl;
        cout<<"Ingrese la fecha MM:    ";   cin>>Mes;
        cout<<"Ingrese la fecha AAAA:  ";   cin>>Anio;

        FILE *Fac = fopen("archivos/Facturas.dat", "rb");
        FILE *Ven=fopen("archivos/Ventas.dat", "rb");
        if(Fac == NULL && Ven == NULL){
            cout<<"No se pudo abrir Venas.dat ";
            fclose(Fac);
            fclose(Ven);
            return;
        }

        cout<<"==============================================================================="<<endl;
        cout<<"\n         RESUMEN DE VENTAS REALIZADAS POR MES Y AÑO: "<<endl;
        cout<<"==============================================================================="<<endl;
        cout << left;
        cout << setw(6) << "NROF";
        cout << setw(7) << "Codigo " << setw(18) << "Descripcion" << setw(6) << "Cant" << setw(15) << "P. Unidad" << setw(10) << "Importe" << endl;
        cout<<"==============================================================================="<<endl;

        while(fread(&F_Fecha, sizeof(Factura), 1, Fac)){
            if(F_Fecha.getFecha().getMes()== Mes && F_Fecha.getFecha().getAnio()== Anio){
                fseek(Ven, sizeof(Ventas), SEEK_SET);
                while (fread(&V_Fecha, sizeof(Ventas), 1, Ven)){
                    if(F_Fecha.getNros_Factura() == V_Fecha.getNro_Fact()){
                        cout << left;
                        cout << setw(6);
                        cout << V_Fecha.getNro_Fact();
                        cout << setw(7);
                        cout << V_Fecha.getCod_Producto();
                        cout << setw(18);
                        cout << V_Fecha.getDescripcion();
                        cout << setw(6);
                        cout << V_Fecha.getCant_Producto();
                        cout << setw(15);
                        cout << V_Fecha.getPrecio();
                        cout << setw(10);
                        cout << V_Fecha.getImporte()<<endl;
                    }
                }
            }
        }
        cout<<"==============================================================================="<<endl;
        cout<<"MOSTRO HASTA LA ULTIMA FILA"<<endl;
        system("pause");
        fclose(Fac);
        fclose(Ven);
        system("cls");
}

void Detalle_Ventas(){  ///     SE HIZO CON VECTORES
    cout<<" ==== INICIO VENTAS ========="<<endl;
    int Vuelta=0, Cant_Total=0, Pr01=0, Pr02=0, Pr03=0, Pr04=0, Pr05=0, Pr06=0, Pr07=0, Pr08=0, Pr09=0;
    int Imp01=0, Imp02=0, Imp03=0, Imp04=0, Imp05=0, Imp06=0, Imp07=0, Imp08=0, Imp09=0;
    cout << "CREO OBJETO VENTAS: " << endl;
    Ventas Leo;
    FILE *L = fopen("archivos/Ventas.dat", "rb");
    if(L == NULL){
        cout<<"NO FUNCIONO";  system("pause");
        return;
    }

    ///cout << "CARGO LA VENTA EN EL VECTOR: " << endl;
    vector <Ventas> Vec;

    ///cout << "LEO EL ARCHIVO VENTAS: " << endl;
    while(fread(&Leo, sizeof(Ventas), 1, L)){
        Cant_Total += Leo.getCant_Producto();

        switch(Leo.getCod_Producto()){
        case 1:
            Pr01 += Leo.getCant_Producto();
            Imp01 += Leo.getImporte();
        break;
        case 2:
            Pr02 += Leo.getCant_Producto();
            Imp02 += Leo.getImporte();
        break;
        case 3:
            Pr03 += Leo.getCant_Producto();
            Imp03 += Leo.getImporte();
        break;
        case 4:
            Pr04 += Leo.getCant_Producto();
            Imp04 += Leo.getImporte();
        break;
        case 5:
            Pr05 += Leo.getCant_Producto();
            Imp05 += Leo.getImporte();
        break;
        case 6:
            Pr06 += Leo.getCant_Producto();
            Imp06 += Leo.getImporte();
        break;
        case 7:
            Pr07 += Leo.getCant_Producto();
            Imp07 += Leo.getImporte();
        break;
        case 8:
            Pr08 += Leo.getCant_Producto();
            Imp08 += Leo.getImporte();
        break;
        case 9:
            Pr09 += Leo.getCant_Producto();
            Imp09 += Leo.getImporte();
        break;
        }
        Vuelta++;
        Ventas Cargo;
        Cargo.Cargar_Venta(Leo.getNro_Fact(), Leo.getCod_Producto(), Leo.getDescripcion(), Leo.getCant_Producto(), Leo.getPrecio(), Leo.getImporte());
        Vec.push_back(Cargo);
    }

    cout<<"======================================================================="<<endl;
    cout<<"DETALLE CONTABLE CANTIDAD VENDIDA TOTAL, POR PROD Y RECAUDACION TOTAL: "<<endl;
    cout<<"======================================================================="<<endl;
    cout<<"Cantidad Total de Productos Vendidos: "<< Cant_Total<<endl;
    cout<<"Detalle por Producto Vendido y Recaudado:  "<<endl;
    cout<<"Producto codigo 01:   "<<Pr01<<"  Recaudado:  "<< Imp01 << endl;
    cout<<"Producto codigo 02:   "<<Pr02<<"  Recaudado:  "<< Imp02 << endl;
    cout<<"Producto codigo 03:   "<<Pr03<<"  Recaudado:  "<< Imp03 << endl;
    cout<<"Producto codigo 04:   "<<Pr04<<"  Recaudado:  "<< Imp04 << endl;
    cout<<"Producto codigo 05:   "<<Pr05<<"  Recaudado:  "<< Imp05 << endl;
    cout<<"Producto codigo 06:   "<<Pr06<<"  Recaudado:  "<< Imp06 << endl;
    cout<<"Producto codigo 07:   "<<Pr07<<"  Recaudado:  "<< Imp07 << endl;
    cout<<"Producto codigo 08:   "<<Pr08<<"  Recaudado:  "<< Imp08 << endl;
    cout<<"Producto codigo 09:   "<<Pr09<<"  Recaudado:  "<< Imp09 << endl<<endl;

    cout << left;
    cout << setw(1);
    cout << "Pr01 + Pr02 + Pr03 + Pr04 + Pr05 + Pr06 + Pr07 + Pr08 + Pr09 =           ";
    ///cout << right;
    cout << setw(75);
    cout << Pr01 + Pr02 + Pr03 + Pr04 + Pr05 + Pr06 + Pr07 + Pr08 + Pr09<<endl;
    cout << left;
    cout << setw(1);
    cout<<"Imp01 + Imp02 + Imp03 + Imp04 + Imp05 + Imp06 + Imp07 + Imp08 + Imp09 =  ";
    ///cout << right;
    cout << setw(75);
    cout << Imp01 + Imp02 + Imp03 + Imp04 + Imp05 + Imp06 + Imp07 + Imp08 + Imp09<<endl;
    system("pause");

    cout << ">>>>>Venta #" << Vuelta << endl;
    ///     Muestro las ventas de la facturael resumen de ventas
    cout<<"==============================================================================="<<endl;
    cout << left;
    cout << setw(6) << "NROF";
    cout << setw(7) << "Codigo " << setw(18) << "Descripcion" << setw(6) << "Cant" << setw(15) << "P. Unidad" << setw(10) << "Importe" << endl;
    cout<<"==============================================================================="<<endl;

    for(unsigned int i=0; i<Vec.size(); i++){
        Vec.at(i).MostrarVenta();
    }
    system("pause");

}
