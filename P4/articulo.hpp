#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <iostream>
#include <set>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

//aniadido P4 autores y cambio en articulo
class Autor
{
    public:
        Autor(const Cadena& nom,const Cadena& apell,const Cadena& dir) noexcept;

        const Cadena& nombre() const { return nombre_; }
        const Cadena& apellidos() const { return apellido_; }
        const Cadena& direccion() const { return direccion_; }
        
    private:
        Cadena nombre_,apellido_,direccion_;
};

class Articulo
{
    public:
        typedef std::set<Autor*> Autores; //P4
        //Constructor
        Articulo(Autores& au,const Cadena& ref, const Cadena& titu, const Fecha& fechaPubli, double prec);
        //metodos observadores
        const Cadena referencia() const {return codigoRef_;}
        const Cadena titulo() const {return titulo_;}
        const Fecha f_publi() const {return fechaPubli_;}
        const double precio() const {return precio_;}
        const Autores autores() const {return autores_;}
        //metodos asignadores
        double& precio() {return precio_;}
        

        class Autores_vacios {}; //excepcion P4
        virtual void impresion_especifica(std::ostream& os) const = 0; //metodo virtual
        virtual ~Articulo() = default; //abstraccion

    private:    
        Autores autores_;
        Cadena codigoRef_;
        Cadena titulo_;
        Fecha fechaPubli_;
        double precio_;
};  

ostream& operator<<(std::ostream& os,const Articulo& A);

class ArticuloAlmacenable: public Articulo
{
    public:
        ArticuloAlmacenable(Autores& au,const Cadena& ref, const Cadena& titu, const Fecha& fechaPubli, double prec, unsigned Ej = 0);
        const unsigned stock() const {return stock_;}
        unsigned& stock() {return stock_;}

        virtual void impresion_especifica(std::ostream& os) const = 0; //metodo virtual
        virtual ~ArticuloAlmacenable() = default;

    protected:
        unsigned stock_;
};

class Libro: public ArticuloAlmacenable
{
    public:
        Libro(Autores& au,const Cadena& ref, const Cadena& titu, const Fecha& fechaPubli, double prec, unsigned numPag,unsigned Ej = 0);

        const unsigned n_pag() const {return numPag_;}

        void impresion_especifica(std::ostream& os) const;
        ~Libro() = default;

    private:
        const unsigned numPag_;
};

class Cederron: public ArticuloAlmacenable
{
    public:
        Cederron(Autores& au,const Cadena& ref, const Cadena& titu, const Fecha& fechaPubli, double prec, unsigned tama,unsigned Ej = 0);

        const unsigned tam() const {return tamano_;}

        void impresion_especifica(std::ostream& os) const;
        ~Cederron() = default;

    private:
        const unsigned tamano_;
};

class LibroDigital: public Articulo
{
    public:
        LibroDigital(Autores& au,const Cadena& ref, const Cadena& titu, const Fecha& fechaPubli, double prec, const Fecha& fechaExp);

        const Fecha f_expir() const { return fechaExp_;}

        void impresion_especifica(std::ostream& os) const;
        ~LibroDigital() = default;

    private:
        const Fecha fechaExp_;
};

#endif //ARTICULO_HPP
