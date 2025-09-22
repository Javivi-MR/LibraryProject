#include "usuario-pedido.hpp"

void Usuario_Pedido::asocia(Usuario& u, Pedido& p)
{
    usuarios_[&u].insert(&p);
    pedidos_[&p] = &u;
}

void Usuario_Pedido::asocia(Pedido& p, Usuario& u)
{
    asocia(u,p);
}
