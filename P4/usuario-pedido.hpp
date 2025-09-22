#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include "usuario.hpp"
#include "pedido.hpp"

class Pedido;

class Usuario_Pedido
{
    public:
        typedef std::set<Pedido*> SetPedidos;

        void asocia(Usuario& u, Pedido& p);
        void asocia(Pedido& p,Usuario& u);

        const SetPedidos pedidos(Usuario& u) {return usuarios_[&u];}
        const Usuario* cliente (Pedido& p) {return pedidos_[&p];}

    private:
        std::map<Usuario*,SetPedidos> usuarios_; //diccionario usuarios y conjunto de pedidos 
        std::map<Pedido*,Usuario*> pedidos_;

};  

#endif // USUARIO_PEDIDO_HPP
