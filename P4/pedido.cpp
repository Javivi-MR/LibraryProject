#include "pedido.hpp"

unsigned Pedido::cantidadPedidos_{0};

Pedido::Pedido(Usuario_Pedido& us_pe, Pedido_Articulo& pe_ar, Usuario& u,const Tarjeta& t,const Fecha& f): numero_(cantidadPedidos_ + 1), tarjeta_(&t), total_(0)
{
    if(u.n_articulos() == 0)
    {
        throw(Pedido::Vacio(u));
    }
    if(t.titular() != &u)
    {
        throw(Pedido::Impostor(u));
    }
    if(t.caducidad() <= f)
    {
        throw(Tarjeta::Caducada(t.caducidad()));
    }
    if(!t.activa())
    {
        throw(Tarjeta::Desactivada());
    }

    for(auto it : u.compra())
    {
        if(ArticuloAlmacenable* actual{dynamic_cast<ArticuloAlmacenable*>(it.first)})
        {
            if(actual->stock() < it.second)
            {
                const_cast<Usuario::Articulos&>(u.compra()).clear();
                throw(Pedido::SinStock(*it.first));
            }
        }

    }
    
    Usuario::Articulos carro{u.compra()};
    unsigned cantprod = 0;

    for(auto it : carro)
    {
        if(ArticuloAlmacenable* actual{dynamic_cast<ArticuloAlmacenable*>(it.first)})
        {
            unsigned cantidad = it.second;
            double precio = actual->precio();
            //restamos lo comprado al stock
            actual->stock() -= cantidad;
            total_ += precio*cantidad;

            pe_ar.pedir(*this, *actual, precio, cantidad);
            u.compra(*actual,0);
            cantprod++;
        }
        if(LibroDigital* actual{dynamic_cast<LibroDigital*>(it.first)})
        {
            if(actual->f_expir() < f)
            {
                continue;
            }
            
            unsigned cantidad = it.second;
            double precio = actual->precio();
            total_ += precio*cantidad;

            pe_ar.pedir(*this, *actual, precio, cantidad);
            u.compra(*actual,0);
            cantprod++;
        }
    }

    if(cantprod == 0)
    {
        throw(Pedido::Vacio(u));
    }

    us_pe.asocia(*this,u);

    cantidadPedidos_++;
}

std::ostream& operator<<(std::ostream& os, const Pedido &P)
{
    os << "Núm. pedido: " << P.numero() << std::endl;
    os << "Fecha:" << P.fecha() << std::endl;
    os << "Pagado con: " << P.tarjeta()->tipo() << " n.º: " << P.tarjeta()->numero() << std::endl;
    os << std::fixed <<"Importe: " << std::setprecision(2) << P.total() << " €" << std::endl;
    
    return os;
}
