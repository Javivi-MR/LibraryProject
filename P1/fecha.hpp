#ifndef FECHA_HPP
#define FECHA_HPP

#include <iostream>

using namespace std;

class Fecha
{
    public:
        //constructores
        explicit Fecha(const int d = 0,const int m = 0,const int a = 0);
        Fecha(const Fecha& F) = default;
        Fecha(const char* cad);
        Fecha& operator =(const Fecha& f) = default;
        //constantes
        static const int AnnoMinimo = 1902;
        static const int AnnoMaximo = 2037;
        //metodos observadores
        const int dia() const {return dia_;}
        const int mes() const {return mes_;}
        const int anno() const {return anno_;}
        //excepcion Invalida
        class Invalida
        {
            public:
                Invalida(const char* e): Error(e) {}
                const char* por_que() const {return Error;}
            private:
                const char* Error;
        };
        //transformar fecha en cadena
        const char* cadena() const;
        //operadores pre|post incremento|decremento y mas|menos igual
        Fecha& operator++();  //preincremento 
        Fecha& operator--(); //predecremento
        Fecha operator++(int);  //postincremento
        Fecha operator--(int);  //postdecremento
        Fecha& operator+=(int n); //mas igual
        Fecha& operator-=(int n); //menos igual
    private:
        int dia_,mes_,anno_;
};

//operadores aritmenticos
Fecha operator+(const Fecha& F,int n);
Fecha operator-(const Fecha& F,int n);
//operadores booleanos
bool operator<(const Fecha& F1, const Fecha& F2);
bool operator>(const Fecha& F1, const Fecha& F2);
bool operator<=(const Fecha& F1, const Fecha& F2);
bool operator>=(const Fecha& F1, const Fecha& F2);
bool operator==(const Fecha& F1, const Fecha& F2);
bool operator!=(const Fecha& F1, const Fecha& F2);
//operadores de flujo
ostream& operator<<(ostream& os, const Fecha& F);
istream& operator>>(istream& is, Fecha& F);

#endif //FECHA_HPP
