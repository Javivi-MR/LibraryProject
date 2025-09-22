#include "fecha.hpp"
#include <ctime>    //referencia principal https://cplusplus.com/reference/ctime/mktime/

using namespace std;


Fecha::Fecha(const int d,const int m,const int a): dia_(d), mes_(m), anno_(a)
{
	time_t t = time(nullptr);
	tm* dt = localtime(&t);
    if(dia_ == 0)
    {
        dia_ = dt->tm_mday;
    }
    if(mes_ == 0)
    {
        mes_ = dt->tm_mon + 1;
    }
    if(anno_ == 0)
    {
        anno_ = dt->tm_year + 1900;
    }
    if(anno_ < Fecha::AnnoMinimo || anno_ > Fecha::AnnoMaximo)
    {
        throw Fecha::Invalida("Error, anno fuera de rango");
    }
    if(mes_ < 1 || mes_ > 12)
    {
        throw Fecha::Invalida("Error, mes fuera de rango");
    }
    if(mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12)
    {
        if(dia_ < 1 || dia_ > 31)
        {
            throw Fecha::Invalida("Error, dia fuera de rango");
        }
    }
    if(mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11)
    {
        if(dia_ < 1 || dia_ > 30)
        {
            throw Fecha::Invalida("Error, dia fuera de rango");
        }        
    }
    if(mes_ == 2)
    {
        if(anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)) //bisiesto
        {
            if(dia_ < 1 || dia_ > 29)
            {
                throw Fecha::Invalida("Error, dia fuera de rango");
            }
        }
        else
        {
            if(dia_ < 1 || dia_ > 28)
            {
                throw Fecha::Invalida("Error, dia fuera de rango");
            }
        }
    }
}

Fecha::Fecha(const char* cad)
{
    int d = 0,m = 0,a = 0;
    int formato = sscanf(cad, "%d/%d/%d", &d,&m,&a);

    if(formato != 3)
    {
        throw Fecha::Invalida("Error, formato no valido");
    }
    else
    {
    	time_t t = time(nullptr);
		tm* dt = localtime(&t);
    	dia_ = d;
        mes_ = m;
        anno_ = a;
        if(d == 0)
        {
           	dia_ = dt->tm_mday;
        }
        if(m == 0)
        {
           	mes_ = dt->tm_mon + 1;
        }
        if(a == 0)
        {
           	anno_ = dt->tm_year + 1900;
        }
        if(anno_ < Fecha::AnnoMinimo || anno_ > Fecha::AnnoMaximo)
        {
        	throw Fecha::Invalida("Error, anno fuera de rango");
        }
        if(mes_ < 1 || mes_ > 12)
        {
           	throw Fecha::Invalida("Error, mes fuera de rango");
        }
        if(mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12)
        {
           	if(dia_ < 1 || dia_ > 31)
           	{
               	throw Fecha::Invalida("Error, dia fuera de rango");
           	}
        }
        if(mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11)
        {
           	if(dia_ < 1 || dia_ > 30)
           	{
               	throw Fecha::Invalida("Error, dia fuera de rango");
           	}        
        }
        if(mes_ == 2)
        {
           	if(anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)) //bisiesto
           	{
               	if(dia_ < 1 || dia_ > 29)
               	{
                   	throw Fecha::Invalida("Error, dia fuera de rango");
               	}
           	}
           	else
           	{
               	if(dia_ < 1 || dia_ > 28)
               	{
                   	throw Fecha::Invalida("Error, dia fuera de rango");
               	}
           	}
        }
    }
}

const char* Fecha::cadena() const
{
    setlocale(LC_ALL, "es_ES.UTF-8");
    char* cad = new char[80];
    tm t{0};

    t.tm_year = this -> anno_ - 1900;
    t.tm_mon = this -> mes_ - 1;
    t.tm_mday = this -> dia_;

    mktime(&t);

    strftime(cad, 80, "%A %e de %B de %Y", &t);
    
    return cad;
}


Fecha& Fecha::operator+=(int n)
{
	tm t{0};
    t.tm_mday = this -> dia_ + n;
    t.tm_mon = this -> mes_ - 1;
    t.tm_year = this -> anno_ - 1900;
	
    mktime(&t);

    this -> dia_ = t.tm_mday;
    this -> mes_ = t.tm_mon + 1;
    this -> anno_ = t.tm_year + 1900;

    if(this->anno_ < Fecha::AnnoMinimo || this->anno_ > Fecha::AnnoMaximo || (dia_ <= 0 && mes_ == 1 && anno_ == Fecha::AnnoMinimo) || (dia_ >= 32 && mes_ == 12 && anno_ == Fecha::AnnoMaximo))
    {
        throw Fecha::Invalida("Error, anno fuera de rango");
    }
    else
    {
        return *this;   
    }
}

Fecha& Fecha::operator-=(int n)
{
    return *this += -n;
}

Fecha& Fecha::operator++()
{
    return *this += 1;
}

Fecha& Fecha::operator--()
{
    return *this += -1;
}

Fecha Fecha::operator++(int)
{
    Fecha F(*this);
    *this += 1;
    return F;
}

Fecha Fecha::operator--(int)
{
    Fecha F(*this);
    *this += -1;
    return F;
}

Fecha operator+(const Fecha& F, int n)
{
    Fecha Faux(F);
    return Faux += n;
}

Fecha operator-(const Fecha& F, int n)
{
    Fecha Faux(F);
    return Faux += -n;
}

bool operator<(const Fecha& F1, const Fecha& F2)
{
    if(F1.anno() < F2.anno())
    {
        return true;
    }
    else
    {
        if(F1.anno() > F2.anno())
        {
            return false;
        }
        else    //annos iguales
        {
            if(F1.mes() < F2.mes())
            {
                return true;
            }
            else
            {
                if(F1.mes() > F2.mes())
                {
                    return false;
                }
                else   //mes iguales 
                {
                    if(F1.dia() < F2.dia())
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }
}

bool operator>(const Fecha& F1, const Fecha& F2)
{
    return F2 < F1;
}

bool operator==(const Fecha& F1, const Fecha& F2)
{
    return (F1.dia() == F2.dia() && F1.mes() == F2.mes() && F1.anno() == F2.anno());
}

bool operator!=(const Fecha& F1, const Fecha& F2)
{
    return !(F1 == F2);
}

bool operator<=(const Fecha& F1, const Fecha& F2)
{
    return ( F1 < F2 || F1 == F2 );
}

bool operator>=(const Fecha& F1, const Fecha& F2)
{
    return ( F1 > F2 || F1 == F2 );
}

ostream& operator<<(ostream& os, const Fecha& F)
{
    os << F.cadena();
    return os;
}

istream& operator>>(istream& is, Fecha& F)
{
    char* cad = new char[11];
    is.getline(cad,11);
    
    try
    {
        Fecha Faux(cad);
        F = Faux;
    }
    catch(Fecha::Invalida& i)
    {
        is.setstate(std::ios_base::failbit);
        throw i;
    }
    
    delete[] cad;
    return is;
}
