#include <iostream>
using namespace std;
#include <ctime>
#include "Fecha.h"

Fecha::Fecha(){
    time_t tiempo;
    struct tm *tmPtr;
    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);
    anio=tmPtr->tm_year+1900;
    mes=tmPtr->tm_mon+1;
    dia=tmPtr->tm_mday;
}

Fecha Fecha::setFechaHoy(){
    time_t tiempo;
    struct tm *tmPtr;
    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);
    anio=tmPtr->tm_year+1900;
    mes=tmPtr->tm_mon+1;
    dia=tmPtr->tm_mday;
}

bool Fecha::Cargar_Fecha(){
    cout<<"Ingrese la fecha"<<endl;
    cout<<"\t dia    : ";
    cin>>dia;
    cout<<"\t mes    : ";
    cin>>mes;
    cout<<"\taño (4): ";
    cin>>anio;
    if((dia<=0)||(mes<=0)||(anio<=0)){///verificamos que la fecha no sea negativa
        return false;
    }
    ///fecha de ingreso no sea mayor a la fecha actual--con 3 preguntas ((anio), (anio y mes), (anio, mes y dia))
    Fecha uno;///creamos otra fecha para verificar
    if((anio>uno.anio)||((anio==uno.anio)&&(mes>uno.mes))||((anio==uno.anio)&&(mes>=uno.mes)&&(dia>uno.dia))){
        return false;
    }
return true;
}

bool Fecha::Cargar_Fecha_Vencimiento(){
    cout<<"Ingrese la fecha de vencimiento"<<endl;
    cout<<"\t dia    : ";
    cin>>dia;
    cout<<"\t mes    : ";
    cin>>mes;
    cout<<"\taño (4): ";
    cin>>anio;
    if((dia<=0)||(mes<=0)||(anio<=0)){///verificamos que la fecha no sea negativa
        return false;
    }
    ///fecha no sea mayor a la fecha actual--con 3 preguntas ((anio), (anio y mes), (anio, mes y dia))
    Fecha uno;///creamos otra fecha para verificar
    if((anio<uno.anio)||((anio==uno.anio)&&(mes<uno.mes))||((anio==uno.anio)&&(mes<=uno.mes)&&(dia<uno.dia))){
        return false;
    }
return true;
}

void Fecha::Mostrar_Fecha(){
    cout<<"\nFecha: "<<dia<<"/"<<mes<<"/"<<anio;
}

bool Fecha::RetornarFechaVencimiento(){
    ///fecha no sea mayor a la fecha actual--con 3 preguntas ((anio), (anio y mes), (anio, mes y dia))
    Fecha uno;///creamos otra fecha para verificar
    if((anio>uno.anio)||((anio==uno.anio)&&(mes>uno.mes))||((anio==uno.anio)&&(mes>=uno.mes)&&(dia>uno.dia))){
        return false;
    }
return true;
}
