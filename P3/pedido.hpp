#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "tarjeta.hpp"
#include "usuario.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

class Pedido_Articulo;
class Usuario_Pedido;

class Pedido
{
    public:
        Pedido(Usuario_Pedido& us_pe, Pedido_Articulo& pe_ar, Usuario& u,const Tarjeta& t,const Fecha& f = Fecha(0,0,0));

        const unsigned numero() const {return numero_;}
        const Tarjeta* tarjeta() const {return tarjeta_;} 
        const Fecha fecha() const {return fecha_;}
        const double total() const {return total_;}
        static unsigned n_total_pedidos(){return cantidadPedidos_;}

        class Vacio
        {
            public:
                Vacio(Usuario& u):pu_(&u) {}
                const Usuario& usuario() const {return *pu_;}
            private:
                Usuario* pu_;
        };

        class Impostor
        {
            public:
                Impostor(Usuario& u):pu_(&u) {}
                const Usuario& usuario() const {return *pu_;}
            private:
                Usuario* pu_;
        };

        class SinStock
        {
            public:
                SinStock(Articulo& a): pa_(&a) {}
                const Articulo& articulo() const {return *pa_;}
            private:
                Articulo* pa_;
        };


    private:
        unsigned numero_;
        const Tarjeta* tarjeta_;
        Fecha fecha_;
        double total_;
        static unsigned cantidadPedidos_;
};

std::ostream& operator<<(std::ostream& os, const Pedido &P);

#endif //PEDIDO_HPP
