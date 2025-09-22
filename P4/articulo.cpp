#include <iostream>
#include <iomanip>
#include "articulo.hpp"

Autor::Autor(const Cadena& nom,const Cadena& apell,const Cadena& dir) noexcept: nombre_(nom),apellido_(apell),direccion_(dir) {}

Articulo::Articulo(Autores& au,const Cadena& ref, const Cadena& titu, const Fecha& fechaPubli, double prec): autores_(au),codigoRef_(ref), titulo_(titu), fechaPubli_(fechaPubli),precio_(prec)
{
    if(au.empty())
    {
        throw (Articulo::Autores_vacios());
    }
}

ostream& operator<<(std::ostream& os,const Articulo& A)
{
    unsigned cont = 1;
    os << "[" << A.referencia() << "] \"" << A.titulo() << "\", de ";
    for(auto it: A.autores())
    {
        os << it->apellidos();
        if(cont < A.autores().size())
        {
            os << ", ";
        }
        cont++; 
    }
    os << std::fixed << ". "<< A.f_publi().anno() << ". "<< std::setprecision(2) << A.precio() << " €" << std::endl << "\t";
    
    A.impresion_especifica(os);
    
    return os;
}

//------------------------------------------ArticuloAlmacenable------------------------------------------

ArticuloAlmacenable::ArticuloAlmacenable(Autores& au,const Cadena& ref, const Cadena& titu, const Fecha& fechaPubli, double prec, unsigned Ej): Articulo(au,ref,titu,fechaPubli,prec), stock_(Ej) {}

//------------------------------------------ArticuloAlmacenable------------------------------------------

//------------------------------------------Libro------------------------------------------

Libro::Libro(Autores& au,const Cadena& ref, const Cadena& titu, const Fecha& fechaPubli, double prec, unsigned numPag,unsigned Ej): ArticuloAlmacenable(au,ref,titu,fechaPubli,prec,Ej), numPag_(numPag) {}

void Libro::impresion_especifica(std::ostream& os) const
{
    os << n_pag() << " págs., " << stock() << " unidades.";
}

//------------------------------------------Libro------------------------------------------

//------------------------------------------Cederron------------------------------------------

Cederron::Cederron(Autores& au,const Cadena& ref, const Cadena& titu, const Fecha& fechaPubli, double prec, unsigned tama,unsigned Ej): ArticuloAlmacenable(au,ref,titu,fechaPubli,prec,Ej), tamano_(tama) {}

void Cederron::impresion_especifica(std::ostream& os) const
{
    os << tam() << " MB, " << stock() << " unidades.";
}
//------------------------------------------Cederron------------------------------------------

//------------------------------------------LibroDigital------------------------------------------

LibroDigital::LibroDigital(Autores& au,const Cadena& ref, const Cadena& titu, const Fecha& fechaPubli, double prec, const Fecha& fechaExp): Articulo(au,ref,titu,fechaPubli,prec), fechaExp_(fechaExp) {}

void LibroDigital::impresion_especifica(std::ostream& os) const
{
    os << "A la venta hasta el " << f_expir() << ".";
}

//------------------------------------------LibroDigital------------------------------------------
