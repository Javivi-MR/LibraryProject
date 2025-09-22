#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

using namespace std;

class Numero;
class Tarjeta;

class Clave
{
    public:
        //constructores
        Clave(const char* cad);
        //clase para excepciones
        enum Razon {CORTA,ERROR_CRYPT};
        class Incorrecta
        {
            public:
                Incorrecta(const Razon r): r_(r) {}
                const Razon razon() const {return r_;}
            private:
                Razon r_;
        };
        //metodos observadores
        const Cadena& clave() const {return pass_;}
        //metodo verificador
        const bool verifica(const char* cad) const;

    private:
        Cadena pass_;
};


class Usuario
{
    public:
        //sinonimos publicos
        typedef map<Numero,Tarjeta*> Tarjetas;
        typedef unordered_map<Articulo*,unsigned int> Articulos;
        typedef unordered_set<Cadena> Usuarios;
        //constructores
        Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& direcc, const Clave& pass);
        //clase de excepcion
        class Id_duplicado
        {
            public:
                Id_duplicado(const Cadena& idr): idr_(idr){}
                const Cadena idd() const {return idr_;}
            private:
                Cadena idr_;
        };
        //prohibir copia y asignacion
        Usuario(const Usuario& U) = delete;
        Usuario& operator=(const Usuario& U) = delete;
        //metodos observadores
        const Cadena id() const {return id_;}
        const Cadena nombre() const {return nombre_;}
        const Cadena apellidos() const {return apellido_;}
        const Cadena direccion() const {return direcc_;}
        const Tarjetas& tarjetas() const {return tarjetas_;}
        const Articulos& compra() const {return articulos_;}
        const Clave pass() const {return password_;}
        const unsigned int n_articulos() const;
        //metodos con tarjeta
        void es_titular_de(Tarjeta& T);
        void no_es_titular_de(Tarjeta& T);
        //metodos con articulo
        void compra(Articulo& A, unsigned int cantidad = 1);
        
        ~Usuario();

    private:
        Cadena id_;
        Cadena nombre_;
        Cadena apellido_;
        Cadena direcc_;
        Clave password_;
        Tarjetas tarjetas_;
        Articulos articulos_;
        static Usuarios usuarios_;
};
//operador de flujo
ostream& operator<<(ostream& os, const Usuario& U);
//Funcion mostrar carro
ostream& mostrar_carro(ostream& os, const Usuario& U);


#endif //USUARIO_HPP
