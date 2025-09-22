#include <iostream>
#include <iomanip>
#include "articulo.hpp"

ostream& operator<<(ostream& os, const Articulo& A)
{
    os << "[" << A.referencia() << "] \"" << A.titulo() << "\", " << A.f_publi().anno() << ". " << A.precio() << " €";
    return os;
}

Articulo::~Articulo()
{
    this->codigoRef_.~Cadena();
    this->titulo_.~Cadena();
    this->fechaPubli_.~Fecha();
    this->precio_ = 0;
    this->numEj_ = 0;
}
