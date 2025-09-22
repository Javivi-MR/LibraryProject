#include "cadena.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <iterator>
#include <iomanip>


Cadena::Cadena(int tamanno,char c): s_(new char[tamanno]), tam_(tamanno)
{
    for(int i = 0 ; i < tamanno ; i++)
    {
        s_[i] = c;
    }
}

Cadena::Cadena(const Cadena& C): s_(new char[C.length()]),tam_(C.length())
{
	strcpy(s_,C.c_str());
}

Cadena::Cadena(Cadena&& C):s_(C.s_),tam_(C.tam_)
{
    C.s_ = nullptr;
    C.tam_ = 0;
}

Cadena::Cadena(const char* C): s_(new char[strlen(C)]),tam_(strlen(C)) 
{
    strcpy(s_,C);
}

Cadena& Cadena::operator=(Cadena&& C)
{
    delete[] this->s_;
    this->s_ = new char[C.tam_ + 1];
    strcpy(this->s_,C.s_);
    this->tam_ = C.tam_;
    C.s_ = nullptr;
    C.tam_ = 0;

    return *this;
}

const char Cadena::operator[](int i) const
{
    return s_[i];
}

const char Cadena::at(int i) const
{
    if(i < 0 || i >= tam_)
    {
        throw std::out_of_range("Error, el indice esta fuera de rango");
    }
    else
    {
        return s_[i];
    }
}

char& Cadena::operator[](int i)
{
    return s_[i];
}

char& Cadena::at(int i)
{
    if(i < 0 || i >= tam_)
    {
        throw std::out_of_range("Error, el indice esta fuera de rango");
    }
    else
    {
        return s_[i];
    }    
}

const Cadena Cadena::substr(int i, int t) const
{
    if(i < 0 ||i >= tam_ || t < 0 || i + t >= tam_)
    {
        throw std::out_of_range("Error, el indice o tamanno esta fuera de rango");
    }
    else
    {
        Cadena Caux(t);
        for(int j = 0 ; j < t ; j++)
        {
            Caux[j] = s_[j+i];
        }
        return Caux;
    }
}

Cadena& Cadena::operator+=(const Cadena& C)
{
    char* aux = new char[this->tam_ + 1];
    this -> tam_ += C.length();
    strcpy(aux,this->s_);
    delete[] this->s_;
    this-> s_ = new char[this -> tam_];
    strcpy(this->s_,aux);
    strcat(this->s_,C.c_str());
    delete[] aux;
    return *this;
}

Cadena operator+(const Cadena& C1, const Cadena& C2)
{
    char* aux = new char[C1.length() + C2.length() + 1];
    strcpy(aux,C1.c_str());
    strcat(aux,C2.c_str());

    Cadena C(aux);
    delete[] aux;
    return C;
}

bool operator<(const Cadena& C1, const Cadena& C2)
{
    return (strcmp(C1.c_str(),C2.c_str()) < 0);
}

bool operator>(const Cadena& C1, const Cadena& C2)
{
    return (strcmp(C1.c_str(),C2.c_str()) > 0);
}

bool operator==(const Cadena& C1, const Cadena& C2)
{
    return (strcmp(C1.c_str(),C2.c_str()) == 0);
}

bool operator!=(const Cadena& C1, const Cadena& C2)
{
    return !(C1==C2);
}

bool operator<=(const Cadena& C1, const Cadena& C2)
{
    return (C1 < C2 || C1 == C2);
}

bool operator>=(const Cadena& C1, const Cadena& C2)
{
    return (C1 > C2 || C1 == C2);
}

ostream& operator<<(ostream& os, const Cadena& C)
{
    os << C.c_str();

    return os;
}

istream& operator>>(istream& is, Cadena& C)
{
    char* aux = new char[33]{'\0'};
    is >> setw(33) >> aux;
    C = Cadena(aux);
	
    delete[] aux;
    return is;
}

