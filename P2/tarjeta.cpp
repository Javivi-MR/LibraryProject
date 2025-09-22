#include "tarjeta.hpp"
#include <cstring>
#include <cctype> //Referencia pricipal https://cplusplus.com/reference/cctype/
#include <iostream>
#include <iomanip>
#include <algorithm>

//----------------------------------- Clase Numero -----------------------------------

bool luhn(const Cadena &numero);

Numero::Numero(const Cadena& num)
{
    int j = 0;
    char Caux [num.length() + 1];

    for(int i = 0 ; i < num.length() ; i++)
    {
        if(isalpha(num[i])) //Si el caracter es alfanumerico
        {
            throw Incorrecto(DIGITOS);
        }
        if(isdigit(num[i]))
        {
            Caux[j] = num[i];
            j++;
        }
    }

    Caux[j] = '\0';
    n_ = Caux;

    if(n_.length() < 13 || n_.length() > 19)
    {
        throw Incorrecto(LONGITUD);
    }
    if(!luhn(n_))
    {
        throw Incorrecto(NO_VALIDO);
    }
}

Numero::operator const char*() const
{
    return n_.c_str();
}

Numero::~Numero()
{
    this->n_.~Cadena();
}

bool operator<(const Numero& N1,const Numero& N2)
{
    return strcmp(N1,N2) < 0;
}

//----------------------------------- Clase Tarjeta -----------------------------------

Tarjeta::Numeros Tarjeta::numeros_;

Tarjeta::Tarjeta(const Numero& num,Usuario& u,const Fecha& F):num_(num),pu_(&u),f_cad_(F),activa_(true)
{
    Fecha actual;
    if(F < actual)
    {
        throw Caducada(F);
    }

    switch(num[0])
    {
        case '3':
            
            switch(num[1])
            {
                case '4': case '7':
                    tipo_ = AmericanExpress;
                    break;
                default:
                    tipo_ = JGB;
                    break;
            }
            break;

        case '4':
            
            tipo_ = VISA;
            break;
        
        case '5':

            tipo_ = Mastercard;
            break;

        case '6':

            tipo_ = Maestro;
            break;

        default:
            tipo_ = Otro;
            break;
    }
    
    pair<set<Numero>::iterator,bool> p = numeros_.insert(num);

    if(!p.second)
    {
        throw Num_duplicado(num);
    }
    
    u.es_titular_de(*this);
}

bool Tarjeta::activa(bool estado)
{
    this->activa_ = estado;
    return estado;
}

void Tarjeta::anula_titular()
{
    this->pu_ = nullptr;
}

Tarjeta::~Tarjeta()
{
	
    this->numeros_.erase(num_);
    this->num_.~Numero();
    if(pu_ != nullptr)
    	this->pu_->no_es_titular_de(*this);
    this->pu_ = nullptr;
    this->f_cad_.~Fecha();
}

ostream& operator<<(ostream& os, const Tarjeta& T)
{
    switch(T.tipo())
    {
        case Tarjeta::Tipo::AmericanExpress:
            os << "AmericanExpress" << endl;
            break;
        case Tarjeta::Tipo::VISA:
            os << "VISA" << endl;
            break;
        case Tarjeta::Tipo::Mastercard:
            os << "Mastercard" << endl;
            break;
        case Tarjeta::Tipo::Maestro:
            os << "Maestro" << endl;
            break;
        case Tarjeta::Tipo::JGB:
            os << "JGB" << endl;
            break;
        default:
            os << "Tipo de tarjeta no reconocida" << endl;
            break;
    }
    
    char* nombre = new char[T.titular()->nombre().length()];
	char* apellido = new char[T.titular()->apellidos().length()];
	
	for(int i = 0 ; i < T.titular()->nombre().length() ; i++)
	{
		nombre[i] = std::toupper(T.titular()->nombre()[i]);
	}

	for(int i = 0 ; i < T.titular()->apellidos().length() ; i++)
	{
		apellido[i] = std::toupper(T.titular()->apellidos()[i]);
	}

    os << T.numero() << endl;
    os << nombre << " " << apellido << endl;
    os << "Caduca: " << std::setfill('0') << std::setw(2) << T.caducidad().mes() << "/" << std::setw(2) << T.caducidad().anno()%100 << endl;

    return os;
}

bool operator<(const Tarjeta& T1,const Tarjeta& T2)
{
    return T1.numero() < T2.numero();
}
