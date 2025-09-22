#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <iomanip>

#include "articulo.hpp"
#include "pedido.hpp"


class Pedido;

class LineaPedido
{
    public:
        explicit LineaPedido(double p,unsigned c = 1): cantidad_(c), precio_venta_(p) {}
        const unsigned cantidad() const {return cantidad_;}
        const double precio_venta() const {return precio_venta_;}
    private:
        unsigned cantidad_;
        double precio_venta_;
};

std::ostream& operator<<(std::ostream& os,const LineaPedido& lp);

class OrdenaPedidos
{
	public:
		const bool operator()(Pedido* P1,Pedido* P2) const;
};

class OrdenaArticulos
{
	public:
		const bool operator()(Articulo* A1,Articulo* A2) const;
};

class Pedido_Articulo
{
    public:
        typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

        void pedir(Pedido& p,Articulo& a, double precio, unsigned cant = 1);
        void pedir(Articulo& a,Pedido& p, double precio, unsigned cant = 1);

        const ItemsPedido detalle(Pedido& p) {return PedidoArticulo_[&p];}
        const Pedidos ventas(Articulo& a) {return ArticuloPedido_[&a];};

        std::ostream& mostrarDetallePedidos(std::ostream &os);
        std::ostream& mostrarVentasArticulos(std::ostream &os);

    private:
        std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedidoArticulo_;
        std::map<Articulo*, Pedidos, OrdenaArticulos> ArticuloPedido_;

};

std::ostream& operator<<(std::ostream& os,const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator<<(std::ostream& os,const Pedido_Articulo::Pedidos& pe);

#endif //PEDIDO_ARTICULO_HPP
