#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include <iomanip> ///PARA TRABAJAR CON SETW

using namespace std;
#include "Lotes_Productos.h"
#include "Producto.h"
#include "Ventas.h"
#include "Fecha.h"

void MenuLotes(){
    Lotes_Prod lot;
    int Opcion;
    while(true){
        system("cls");
        cout<<"====================================================== "<<endl;
        cout<<"              MENU LOTES                               "<<endl;
        cout<<"====================================================== "<<endl;
        cout<<"01 LISTAR LOTES ACTIVOS                                "<<endl;
        cout<<"02 LISTAR LOTES ACTIVOS POR PRODUCTO SELECCIONADO      "<<endl;
        cout<<"03 LISTAR LOTES POR COMPLETO                           "<<endl;
        cout<<"04 CARGAR LOTE NUEVO                                   "<<endl;
        cout<<"05 MODIFICAR UN REGISTRO DE UN LOTE ESPECIFICO         "<<endl;
        ///cout<<"06 DESCONTAR PRODUCTOS DE FACTURA                      "<<endl;
        cout<<"00 SALIR                                               "<<endl;
        cout<<"====================================================== "<<endl;
        cout<<" Opción:  ";    cin>>Opcion;
        switch(Opcion){
        case 1:
            {system("cls");
            Encab_Lote();
            lot.Leer_Lotes_Prod(-1);}
        break;
        case 2:
            {int CodProd;
            system("cls");
            cout<<"Ingrese el Código del Producto: "; cin>>CodProd;
            Encab_Lote();
            lot.Leer_Lotes_Prod(CodProd);}
            system("pause");
        break;
        case 3:
            {system("cls");
            Encab_Lote();
            lot.Leer_Lotes_Prod(-2);
            system("pause");}
        break;
        case 4:{
            lot.Cargar_Lotes_Prod();
            lot.Grabar_Lotes_Prod(-1);}
        break;
        case 5:
            {system("cls");
            int Lote;
            cout<<"INGRESE LOTE A MODIFICAR: "; cin>>Lote;
            lot.ModificarLote(Lote);}
        break;
        case 6:{
            cout<<" DESCONTAR LOS PRODUCTOS DE LA FACTURA DE LOS LOTES..............."<<endl;
            int Factura;
            cout<<"FACTURA NRO:  "; cin>>Factura;
            Descuento_Lote(Factura);
        }
        break;
        case 0:
            return;
        break;
        default:{
            cout<<"INGRESE UN VALOR DEL MENU";
            system("pause");}
        break;
        }
    }
}

int Lotes_Prod::NuevoID(){
    FILE *N= fopen("archivos/Lotes.dat", "rb");
    int Nuevo;
    if(N == NULL) {
        cout<<"error lote.dat";
        system("pause");
        return 1;
    }
    fseek(N, -1 * sizeof(*this), SEEK_END);
    while(fread(this, sizeof *this, 1, N)){
        Nuevo = getLId()+1;
    }
    fclose(N);
    return Nuevo;
}

void Lotes_Prod::ModificarLote(int Lote){
    FILE *L= fopen("archivos/Lotes.dat", "rb");
    if(L==NULL){ return;}
    int posic=-1;
    while(fread(this, sizeof *this, 1, L)){
        posic++;
        if(getLId() == Lote){
            while(true){
                int op;
                system("cls");
                Encab_Lote();
                MuestroLote();
                cout<<"==================================================="<<endl<<endl;

                cout<<"==================================================="<<endl;
                cout<<"=======INDIQUE EL CAMPO QUE DESEA MODIFICAR:======="<<endl;
                cout<<"==================================================="<<endl;
                cout<<"1= Código del Producto............................."<<endl;
                cout<<"2= Cantidad de Producto............................"<<endl;
                cout<<"3= Fecha del Vencimiento..........................."<<endl;
                cout<<"4= Estado del Producto............................."<<endl;
                cout<<"5= Nro Pedido......................................"<<endl;
                ///cout<<"6= Nro Id Lote....................................."<<endl;
                cout<<"0= Terminar........................................"<<endl;
                ///cout<<"9= DESCONTAR LA FACTURA DE LOS LOTES..............."<<endl;  /// SE UTILIZO PARA ARMAR LA LOGICA DEL DESCUENTO DE LOTES
                cout<<"==================================================="<<endl;
                cout<<"Ingrese opción: "; cin>>op;
                switch(op){
                    case 1:
                        {int CodProd;
                        cout<<"Codigo del Producto: ";
                        cin>>CodProd;
                        setLCodProd(CodProd);
                        Grabar_Lotes_Prod(posic);}
                    break;
                    case 2:
                        {int Cant;
                        cout<<"Cantidad de Producto: ";
                        cin>>Cant;
                        setLCantidad(Cant);
                        Grabar_Lotes_Prod(posic);}
                    break;
                    case 3:
                        {cout<<"Fecha Vencimiento: ";
                        LFe_Vto.Cargar_Fecha_Vencimiento();
                        Grabar_Lotes_Prod(posic);}
                    break;
                    case 4:
                        {bool estado;
                        cout<<"Estado 1=ACTIVO, 0=NO ACTIVO   ";
                        cin>>estado;

                        Fecha a, b;///aca veo las fechas hoy y la de vencimiento
                            b.setDia(getLFe_Vto().getDia());
                            b.setMes(getLFe_Vto().getMes());
                            b.setAnio(getLFe_Vto().getAnio());
                            a.setFechaHoy();
                            int verdadero;
                            if(a<b){
                                verdadero = 1;
                            }else {
                                verdadero = 0;
                            }
                        if(estado == 1 && verdadero == 1){
                                setLEstado_true();
                            }else{
                                setLEstado_false();
                            }
                        Grabar_Lotes_Prod(posic);}
                    break;
                    case 5:
                        {int Pedido;
                        cout<<"Ingrese el Nro Pedido: "; cin>>Pedido;
                        setLpedidoId(Pedido);
                        Grabar_Lotes_Prod(posic);}
                    break;
                    case 6:
                        {
                        cout<<"Ingrese el Lote_Id:  "; cin>>LId;
                        setLid(LId);
                        Grabar_Lotes_Prod(posic);}
                    break;
                    case 0:
                        return;
                    break;
                    default:
                    break;
                }
            }
        }
    }
}

void Descuento_Lote(int fact){
    Ventas ven;
    Lotes_Prod Prod;
    FILE *V = fopen("archivos/Ventas.dat", "rb");
    if(V==NULL) {
        cout<<"ERROR VENTAS.DAT  "<<endl;
        return;
    }
    while(fread(&ven, sizeof(Ventas), 1, V)){
        if(ven.getNro_Fact() == fact){
            int Cant = ven.getCant_Producto();
            do{
                int pos = Busco_Pos(ven.getCod_Producto()); ///Tengo la posicion del CodProd, mas viejo y estado ==1
                if(pos >= 0){
                    Prod = Leo_Lotes(pos, Cant);
                    if(Prod.getLCantidad() > Cant){
                        Prod.Suma_Cantidad(Cant);   ///ACA TENGO QUE PREGUNTAR SI LO QUE TIENE EN LOTES ES MENOR O NO Ó LLEVAR ESTO A DESCUENTO LOTE Y HACERLO AHÍ.....
                        Prod.Grabar_Lotes_Prod(pos);
                        Cant =0;
                    }else{
                        if(Prod.getLCantidad() == Cant){
                            Prod.Suma_Cantidad(Cant);
                            Prod.setLEstado_false();
                            Prod.Grabar_Lotes_Prod(pos);
                            Cant =0;
                        }else{
                            if(Prod.getLCantidad() < Cant){
                                Cant -= Prod.getLCantidad();
                                Prod.Suma_Cantidad(Prod.getLCantidad());
                                Prod.setLEstado_false();
                                Prod.Grabar_Lotes_Prod(pos);
                                Cant -=Prod.getLCantidad();
                            }
                        }
                    }
                }else{
                    Cant = 0;
                }
            }while(Cant > 0);
        }
    }
                cout<<"FINALIZO EL WHILE"<<endl;
                system("pause");
}

int Busco_Pos(int Codigo){///busco en lotes con CodProd y mas viejo
    int Pos=-1, dia=0, mes, anio, Coincide;
    Lotes_Prod lot;
    FILE *L = fopen("archivos/Lotes.dat", "rb");
    if(L == NULL){
        return Pos;
    }
    while(fread(&lot, sizeof(Lotes_Prod), 1, L)){
        Pos++;
        if(lot.getLCodProd() == Codigo && lot.getLEstado()== 1){
            if(dia==0){
                anio = lot.getLFe_Vto().getAnio();
                mes=lot.getLFe_Vto().getMes();
                dia=lot.getLFe_Vto().getDia();
                Coincide = Pos;
            }else{
                if(anio > lot.getLFe_Vto().getAnio()){
                anio = lot.getLFe_Vto().getAnio();
                mes  = lot.getLFe_Vto().getMes();
                dia  = lot.getLFe_Vto().getDia();
                Coincide = Pos;
                }else{
                    if(anio == lot.getLFe_Vto().getAnio() && mes > lot.getLFe_Vto().getMes()){
                anio = lot.getLFe_Vto().getAnio();
                mes  = lot.getLFe_Vto().getMes();
                dia  = lot.getLFe_Vto().getDia();
                Coincide = Pos;
                }else{
                    if(anio == lot.getLFe_Vto().getAnio() && mes == lot.getLFe_Vto().getMes()
                       && dia > lot.getLFe_Vto().getDia()){
                anio = lot.getLFe_Vto().getAnio();
                mes  = lot.getLFe_Vto().getMes();
                dia  = lot.getLFe_Vto().getDia();
                Coincide = Pos;
                }
                }
                }
            }
        }
    }
    fclose(L);
    return Coincide;
}

Lotes_Prod Leo_Lotes(int pos, int Cant){
    Lotes_Prod Lot;
    FILE *L = fopen("archivos/Lotes.dat", "rb");
    if(L == NULL){
        return Lot;
    }
    fseek(L, pos*sizeof(Lotes_Prod), SEEK_SET);
    fread(&Lot, sizeof(Lotes_Prod), 1, L);
    cout<<"Muestro lote: "<<endl;
    Lot.MuestroLote();
    return Lot;
    fclose(L);
}

void Lotes_Prod::Suma_Cantidad(int Pos, int Cant){
    FILE *Lot = fopen("archivos/Lotes.dat", "rb+");
    if(Lot == NULL){
      cout<<"NO ENTRO EN LOTES RB+"<<endl;
      system("pause");
      return;
    }
    fseek(Lot, Pos * sizeof Lot, SEEK_SET);
    fread(this, sizeof this, 1, Lot);
    Encab_Lote();
    MuestroLote();
    system("pause");
    if(fwrite(this, sizeof this, 1, Lot)){
        cout<<"grabo"<<endl;
        system("pause");
    }else{
        cout<<"ERROR EN LA GUARDA"<<endl;
        system("pause");
    }
}

void Encab_Lote(){
    cout <<"==================================================="<<endl;
    cout << left;
    cout << "========MUESTRA DE LOTE=============================="<<endl;
    cout << setw(5)<<" LId  "<<setw(9)<<"Cod_Prod"<<setw(5)<<"Cant  "<<setw(14)<<" Fecha     "<<setw(8)<<"Estado"<<setw(9)<<"Id Pedido"<<endl;
    cout << "====================================================="<<endl;
}

void Lotes_Prod::MuestroLote(){   ///     CONSTRUCTOR
    cout << right;
    cout << setw(4)<<LId;
    cout << setw(7)<<LCodProd;
    ///cout << setw(7)<<LPedidoId;
    cout << setw(8)<<LCantidad;
    cout << setw(5);
    cout << getLFe_Vto().getDia();
    cout << "/";
    cout << setw(2);
    cout << getLFe_Vto().getMes();
    cout << "/";
    cout << setw(4);
    cout << getLFe_Vto().getAnio();
    cout << setw(7)<<LEstado;
    cout << setw(7)<<LPedidoId<<endl;
}

void Lotes_Prod::Cargar_Lotes_Prod(){
    cout<<"Lote_ID: ";
    setLid(NuevoID());
    cout<<getLId()<<endl;
    cout<<"Lote CodProducto: ";
    cin>>LCodProd;
    while(ValidarIDProducto(LCodProd) == false){
        cout<<"El código de Producto no existe"<<endl;
        cout<<">>>Reingrese el código del Producto: ";
        cout<<">>>Lote CodProducto: "; cin>>LCodProd;
        ///if(ValidarIDProducto(LCodProd) == true) return;
    }
    cout<<"Lote Cantidad: "; cin>>LCantidad;
    while(!(LCantidad>0 && LCantidad< 120)){
        cout<<">>> Reingrese Lote Cantidad ";
        cout<<">>> Lote Cantidad: "; cin>>LCantidad;
    }
    cout<<"Fecha Vto: ";
    LFe_Vto.Cargar_Fecha();
    setLEstado_true();

    ///cout<<"Estado: "; cin>>LEstado;
}

bool Lotes_Prod::AltaPedido(int numPedido){
    char respuesta='S';
    cout<<"Lote_ID: ";
    setLid(NuevoID());
    cout<<getLId()<<endl;
    setLpedidoId(numPedido);

    while(respuesta=='s'||respuesta=='S'){

        cout<<"Lote CodProducto: ";
        cin>>LCodProd;
        while(ValidarIDProducto(LCodProd) == false){
            cout<<"El código de Producto no existe"<<endl;
            cout<<">>>Reingrese el código del Producto: ";
            cout<<">>>Lote CodProducto: "; cin>>LCodProd;
            ///if(ValidarIDProducto(LCodProd) == true) return;
        }
        cout<<"Lote Cantidad: "; cin>>LCantidad;
        while(!(LCantidad>0 && LCantidad< 120)){
            cout<<">>> Reingrese Lote Cantidad ";
            cout<<">>> Lote Cantidad: "; cin>>LCantidad;
        }
        cout<<"Fecha Vto: ";
        if(LFe_Vto.Cargar_Fecha_Vencimiento()){///en caso de fecha valida  guarda el producto

            Grabar_Lotes_Prod(-1);
            setLEstado_true();

        }
        cout<<endl<<"Desea cargar mas productos?(S/N)";
        cin>>respuesta;
    }


}

bool Lotes_Prod::Grabar_Lotes_Prod(int pos){
    bool grabo;
    if(pos==-1){
        FILE *L= fopen("archivos/Lotes.dat", "ab");
        if(L==NULL){ return false;}
        bool grabo = fwrite(this, sizeof *this, 1, L);
        fclose(L);
        return grabo;
    }else{
        FILE *L= fopen("archivos/Lotes.dat", "rb+");
        if(L==NULL){ return false;}
        fseek(L, pos * sizeof *this, SEEK_SET);
        bool grabo = fwrite(this, sizeof *this, 1, L);
        fclose(L);
        return grabo;
    }
    return grabo;
}

bool Lotes_Prod::Leer_Lotes_Prod(int CodProd=-1){ ///-1 LOTES ACTIVOS, -2 TOTAL, >=0 POR CODPROD, -3 CUENTO CANTIDAD EN LOTES
    FILE *L= fopen("archivos/Lotes.dat", "rb");
    if(L==NULL){ return false;}
    if(CodProd == -1){
        while(fread(this, sizeof *this, 1, L)){
            if(getLEstado() == 1){
                MuestroLote();
            }
        }
        cout<<"==================================================="<<endl;
        cout<<"Mostro lotes Activos del archivo."<<endl;
    }else{
        if(CodProd == -2){
            while(fread(this, sizeof *this, 1, L)){
                MuestroLote();
            }
            cout<<"==================================================="<<endl;
            cout<<"Mostro lotes del archivo completo."<<endl;
            return true;
        }else{
            while(fread(this, sizeof *this, 1, L)){
                if(getLEstado() == 1 && getLCodProd()==CodProd){
                    MuestroLote();
                }
            }
            cout<<"==================================================="<<endl;
            cout<<"Mostro lotes del PRODUCTO seleccionado del archivo."<<endl;
            return true;
        }
    }
    system("pause");
    return true;
}

void Lotes_Prod::setSumo_Cantidad(int Lote, int Cant){
    int Pos=-1;
    FILE *L = fopen("archvos/Lotes.dat", "rb+");
    if(L == NULL){ return;}
    while(fread(this, sizeof this, 1, L)){
        Pos++;
        if(LId == Lote){
            cout<<"LCantidad: "<<LCantidad;
            LCantidad -= Cant;
            Grabar_Lotes_Prod(Pos);
        }
    }
}

int Lotes_Prod::Cuento_CantProd_Lotes(int CodProd){ /// CUENTO LA CANTIDAD DE PRODUCTO NRO DADO EN TODOS LOS LOTES
    int Cantidad=0;
    FILE *L= fopen("archivos/Lotes.dat", "rb");
    if(L==NULL){ return -1;}

    while(fread(this, sizeof *this, 1, L)){
        if(CodProd == LCodProd){
            Cantidad += getLCantidad();
        }
    }
    fclose(L);
    return Cantidad;
}
