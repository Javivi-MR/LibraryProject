#include "usuario.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h> //para crypt()
#include <random>   //para rand()
#include <iomanip>

using namespace std;

//----------------------------------- Clase Clave -----------------------------------

Clave::Clave(const char* cad)
{
    if(strlen(cad) < 5)
    {
        throw Incorrecta(CORTA);
    }
    
    char* encrypt = new char[2];
    const char* semilla = "1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";

    encrypt[0] = semilla[rand()%62];
    encrypt[1] = semilla[rand()%62];

    if(crypt(cad,encrypt) == NULL)
    {
        throw Incorrecta(ERROR_CRYPT);
    }
    
    pass_ = crypt(cad,encrypt);
    
}

const bool Clave::verifica(const char* cad) const
{
    return strcmp(pass_.c_str(),crypt(cad,pass_.c_str())) == 0;
}

//----------------------------------- Clase Usuario -----------------------------------
Usuario::Usuarios Usuario::usuarios_;

Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& direcc, const Clave& pass): id_(id), nombre_(nom), apellido_(apell), direcc_(direcc), password_(pass)
{
    pair<unordered_set<Cadena>::iterator,bool> p = usuarios_.insert(id);
    if(!p.second)
    {
        throw Id_duplicado(id_);
    }
}

const unsigned int Usuario::n_articulos() const
{
    return articulos_.size();
}


void Usuario::es_titular_de(Tarjeta& T)
{
    if(this == T.titular())
    {
        tarjetas_.insert(make_pair(T.numero(),&T));
    }
}

void Usuario::no_es_titular_de(Tarjeta& T)
{
    T.anula_titular();
    tarjetas_.erase(T.numero());
}

void Usuario::compra(Articulo& A, unsigned int n)
{
    if(n==0)
    {
        articulos_.erase(&A);
    }
    else
    {
        articulos_[&A] = n;
    }
}

Usuario::~Usuario()
{
	for(auto i = tarjetas_.begin(); i != tarjetas_.end(); i++){

        i->second->anula_titular();
    }

    usuarios_.erase(id_);
}

ostream& operator<<(ostream& os, const Usuario& U)
{
    os << U.id() << " [" << U.pass().clave() << "] " <<  U.nombre() << " " << U.apellidos() << endl;
    os << U.direccion() << endl;
    os << "Tarjetas:" << endl;
    for(auto i = U.tarjetas().begin() ; i != U.tarjetas().end() ; i++)
    {
        os << *i->second << endl;
    }
    return os;
}

ostream& mostrar_carro(ostream& os, const Usuario& U)
{
    os << "Carrito de compra de " << U.id() << " [Artículos: " << U.n_articulos() << "]" << endl;
    os << " Cant.\t" << "Artículo" << endl;
    os << "===========================================================" << endl;
    for(auto i = U.compra().begin() ; i != U.compra().end() ; i++)
    {
        os << " " << i->second << "\t[" << i->first->referencia() << "] \"" << i->first->titulo() << "\", " << i->first->f_publi().anno() << ". " << std::setprecision(2) << std::fixed << i->first->precio() << " €" << endl;
    }
    return os;
}
