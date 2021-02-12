#include<iostream>

#include<cstdlib>

#include<cstdio>

#include<cstring>


using namespace std;


class Fecha{
    private:
        int dia, mes, anio;
    public:
        int getDia(){return dia;}
        int getMes(){return mes;}
        int getAnio(){return anio;}
        void setDia(int d){dia=d;}
        void setMes(int m){mes=m;}
        void setAnio(int a){anio=a;}
        void Cargar();
        void Mostrar();
        bool operator==(Fecha);
};

void Fecha::Cargar(){
    cout<<"DIA: ";
    cin>>dia;
    cout<<"MES: ";
    cin>>mes;
    cout<<"ANIO: ";
    cin>>anio;
}

void Fecha::Mostrar(){
    cout<<"DIA: ";
    cout<<dia<<"/";
    cout<<mes<<"/";
    cout<<anio;
}

/**int main(){
    Fecha a, b;
    a.Cargar();
    b.Cargar();
    if(a.getDia()==b.getDia() && a.getMes()==b.getMes() &&
    a.getAnio()==b.getAnio()) cout<<"IGUALES";
    else cout<<"DISTINTOS";
    return 0;
}*/

bool Fecha::operator==(Fecha aux){
    if(dia!=aux.dia)return false;
    if(mes!=aux.mes)return false;
    if(anio!=aux.anio)return false;
    return true;
}

int main(){
    Fecha a, b;
    a.Cargar();
    b.Cargar();
    if(a==b) cout<<"IGUALES";
    else cout<<"DISTINTOS";
    ///el objeto que llama a la función es "a", y el que se recibe como parámetro es "b":
    ///siempre el objeto que llama es el de la izquierda, y el parámetro es el valor de la derecha.
    ///Es como si pusieramos la siguiente instrucción if(a.operator==(b))
    return 0;
}
