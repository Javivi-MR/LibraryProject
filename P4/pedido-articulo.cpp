#include "pedido-articulo.hpp"

const bool OrdenaPedidos::operator()(Pedido* P1,Pedido* P2) const
{
	return P1->numero() < P2->numero();
}

const bool OrdenaArticulos::operator()(Articulo* A1,Articulo* A2) const
{
	return A1->referencia() < A2->referencia();
}


std::ostream& operator<<(std::ostream& os,const LineaPedido& lp)
{
    os << std::fixed << std::setprecision(2) << lp.precio_venta() << " €\t" << lp.cantidad();
    return os;
}

void Pedido_Articulo::pedir(Pedido& p,Articulo& a, double precio, unsigned cant)
{
    PedidoArticulo_[&p].insert(std::make_pair(&a,LineaPedido(precio, cant)));
    ArticuloPedido_[&a].insert(std::make_pair(&p,LineaPedido(precio, cant)));
}

void Pedido_Articulo::pedir(Articulo& a,Pedido& p, double precio, unsigned cant)
{
    pedir(p,a,precio,cant);
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream &os)
{
    double total = 0;

    for(auto it = PedidoArticulo_.begin() ; it != PedidoArticulo_.end() ; it++)
    {
        os << "Pedido núm. " << it->first->numero() << std::endl;
        os << "Cliente: " << it->first->tarjeta()->titular()->nombre() << "\t" << "Fecha: " << it->first->fecha() << std::endl;
        os << it->second;
        total += it->first->total();
    }

    os << std::fixed << "TOTAL VENTAS: " << std::setprecision(2) << total << " €" << std::endl;

    return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream &os)
{
    for(auto it = ArticuloPedido_.begin() ; it != ArticuloPedido_.end() ; it++)
    {
        os << "Ventas de [" << it->first->referencia() << "] \"" << it->first->titulo() << "\"" << std::endl; 
        os << it->second;
    }
    
    return os;
}

std::ostream& operator<<(std::ostream& os,const Pedido_Articulo::ItemsPedido& ip)
{
    double total = 0;
    os << "  PVP    Cantidad        Artículo" << std::endl;
    os << "==================================================================" << std::endl;
    for(auto it = ip.begin(); it != ip.end(); it++)
    {
        os << std::fixed << std::setprecision(2) << it->second.precio_venta() << " € " << it->second.cantidad() << "\t\t";
        os << "[" << it->first->referencia() << "] \"" << it->first->titulo() << "\"" << std::endl;
        total += (it->second.precio_venta() * it->second.cantidad());
    }
    os << "==================================================================" << std::endl;
    os << std::fixed << "Total/t" << std::setprecision(2) << total << std::endl;

    return os;
}

std::ostream& operator<<(std::ostream& os,const Pedido_Articulo::Pedidos& pe)
{
    double total = 0;
    unsigned totalprod = 0;
    os << "[Pedidos: " << pe.size() << "]" << std::endl;
    os << "==================================================================" << std::endl;
    os << "  PVP    Cantidad        Fecha de venta" << std::endl;
    os << "==================================================================" << std::endl;
    for(auto it = pe.begin(); it != pe.end(); it++)
    {
        os <<  it->second.precio_venta() << " € " << it->second.cantidad() << "\t\t" << it->first->fecha() << std::endl;
        total += (it->second.precio_venta() * it->second.cantidad());
        totalprod += it->second.cantidad();
    }  
    os << "==================================================================" << std::endl;
    os << std::fixed << std::setprecision(2) << total << " €\t" << totalprod << std::endl;

    return os;
}
