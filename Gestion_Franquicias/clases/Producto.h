#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED
#include "Fecha.h"
#include <cstring>

class Producto{
    private:
        int ID;
        char Nombre[50];
        float Precio;
        int Cantidad;  /// eliminar
        int Cantidad_Minima;
        bool estado; /// eliminar
        Fecha Actual; ///emilinar
        Fecha Vencimiento; ///eliminar
    public:
        Producto();
        ~Producto();
        bool Cargar_Producto(); ///CUANDO SE CARGA POR PRIMERA VEZ
        void Mostrar_Producto(); ///Muestra la cabezera del producto
        void Mostrar(); ///Muestra la informacion de los archivos
        bool GuardarProducto();
        int Buscar_Producto_ID(int); ///busca el producto por ID y devuelve la posicion del producto
        int NumeroId();///retorna el ultimo numero de pedido creado
	bool ModificarProducto(int); ///recibe la posicion en memoria del producto
	bool ValidarCantidadProducto(int);///valida que la cantidad vendida no sobrepase la cantidad existente
        
	///get
        int getID(){return ID;}
        char *getNombre(){return Nombre;}
        float getPrecio(){return Precio;}
        int getCantidad(){return Cantidad;}
        bool getEstado(){return estado;}
        int getCantidad_Cod(int);
        
	///set
        void setID(int id){ ID = id;}
        void setNombre(char *nomb){strcpy(Nombre, nomb);}
        void setMod_Cantidad(int Modif) {Cantidad =0;}
        void setCantidad(int _cantidad){Cantidad=_cantidad;}
        void setCantidadMinima(int _cantidadMinima){Cantidad_Minima=_cantidadMinima;}
        void setEstado(int _estado){estado = 0;}
        void setPrecio(float _Precio){Precio =_Precio;}
};

bool ValidarIDProducto(int); ///validad que el ID no exista
bool Cargar_Producto(int);

#endif // PRODUCTO_H_INCLUDED
