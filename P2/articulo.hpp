#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <iostream>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

class Articulo
{
    public:
        //Constructor
        Articulo(const Cadena ref, const Cadena titu, const Fecha fechaPubli, double prec_, int Ej_ = 0): codigoRef_(ref), titulo_(titu), fechaPubli_(fechaPubli), precio_(prec_), numEj_(Ej_) {}
        //metodos observadores
        const Cadena referencia() const {return codigoRef_;}
        const Cadena titulo() const {return titulo_;}
        const Fecha f_publi() const {return fechaPubli_;}
        const double precio() const {return precio_;}
        const unsigned stock() const {return numEj_;}
        //metodos asignadores
        double& precio() {return precio_;}
        unsigned& stock() {return numEj_;}
        //destructor
        ~Articulo();

    private:    
        Cadena codigoRef_;
        Cadena titulo_;
        Fecha fechaPubli_;
        double precio_;
        unsigned numEj_;
};  

ostream& operator<<(ostream& os,const Articulo& A);

#endif //ARTICULO_HPP
