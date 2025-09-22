#ifndef TARJETA_HPP
#define TARJETA_HPP

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"
#include <iostream>
#include <set>

using namespace std;

class Usuario;

class Numero
{
    public:
        //constructor
        Numero(const Cadena& num);
        //Clase y datos necesarios para las expeciones
        enum Razon {LONGITUD,DIGITOS,NO_VALIDO};
        class Incorrecto
        {
            public:
                Incorrecto(const Razon& r): r_(r){}
                const Razon razon() const {return r_;}
            private:
                Razon r_;
        };
        //conversion 
        operator const char*() const;
        //destructor
        ~Numero();
    private:
        Cadena n_;
};

bool operator<(const Numero& N1,const Numero& N2);

class Tarjeta
{
    public:
        //enumeracion publica
        enum Tipo {Otro,VISA,Mastercard,Maestro,JGB,AmericanExpress};
        typedef set<Numero> Numeros;
        //constructor
        Tarjeta(const Numero& num, Usuario& u,const Fecha& F);
        Tarjeta(const Tarjeta& T) = delete; //prohibe copiar
        Tarjeta& operator=(const Tarjeta& T) = delete;  //prohibe asignar
        //clases para excepciones
        class Caducada
        {
            public:
                Caducada(const Fecha& fc): f_(fc) {}
                const Fecha cuando() const {return f_;}
            private:
                Fecha f_;
        };
        class Num_duplicado
        {
            public:
                Num_duplicado(const Numero& num):numd_(num) {}
                const Numero que() const {return numd_;}
            private:
                Numero numd_;
        };
        class Desactivada {}; //P3
        //metodos observadores
        const Tipo tipo() const {return tipo_;}
        const Numero numero() const {return num_;}
        const Usuario* titular() const {return pu_;}
        const Fecha caducidad() const {return f_cad_;}
        const bool activa() const {return activa_;}
        //modificadores
        bool activa(bool estado);
        void anula_titular();
        //destructor
        ~Tarjeta();

    private:
        Tipo tipo_;
        Numero num_;
        Usuario* pu_;
        Fecha f_cad_;
        bool activa_;
        static Numeros numeros_;
};
//operador de flujo
ostream& operator<<(ostream& os, const Tarjeta& T);
ostream& operator<<(ostream& os,Tarjeta::Tipo T); //P3
//operador menor que 
bool operator<(const Tarjeta& T1,const Tarjeta& T2);


#endif //TARJETA_HPP
