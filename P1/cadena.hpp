#ifndef CADENA_HPP
#define CADENA_HPP

#include <iostream>
#include <string>

using namespace std;

class Cadena
{
    public:
        //constructores 
        explicit Cadena(int tamanno_ = 0, char c = ' ');
        Cadena(const Cadena& C);
        Cadena(Cadena&& C);
        Cadena(const char* C);
        //operadores =
        Cadena& operator=(const Cadena& C) = default;
        Cadena& operator=(Cadena&& C);
        //metodos observadores
        const size_t length() const {return tam_;}
        const char* c_str() const {return s_;}
        const char operator[](int i) const;
        const char at(int i) const;
        const Cadena substr(int i, int t) const;
        //metodos asignadores
        char& operator[](int i);
        char& at(int i);
        //metodos aritmeticos
        Cadena& operator+=(const Cadena& C);
        //iteradores
    	typedef char *iterator;
    	typedef const char *const_iterator;
    	typedef std::reverse_iterator <iterator> reverse_iterator;
    	typedef std::reverse_iterator <const_iterator> const_reverse_iterator;
		iterator begin(){return s_;}
    	const_iterator begin() const{return cbegin();}
    	const_iterator cbegin() const{return s_;}
    	reverse_iterator rbegin(){return reverse_iterator(end());}
    	const_reverse_iterator rbegin() const{return crbegin();}
    	const_reverse_iterator crbegin() const{return const_reverse_iterator(end());}
	
    	iterator end(){return s_ + tam_;}
    	const_iterator end() const{return cend();}
    	const_iterator cend() const{return s_ + tam_;}
    	reverse_iterator rend(){return reverse_iterator(begin());}
    	const_reverse_iterator rend() const{return crend();}
    	const_reverse_iterator crend() const{return const_reverse_iterator(begin());}

    private:
        char* s_;
        int tam_;
};
//operadores aritmeticos externos
Cadena operator+(const Cadena& C1, const Cadena& C2);
//operadores booleanos
bool operator<(const Cadena& C1, const Cadena& C2);
bool operator<=(const Cadena& C1, const Cadena& C2);
bool operator>(const Cadena& C1, const Cadena& C2);
bool operator>=(const Cadena& C1, const Cadena& C2);
bool operator==(const Cadena& C1, const Cadena& C2);
bool operator!=(const Cadena& C1, const Cadena& C2);
//operadores de flujo
ostream& operator<<(ostream& os, const Cadena& C);
istream& operator>>(istream& is, Cadena& C);

namespace std {
  template <> struct hash<Cadena> {
    size_t operator()(const Cadena& cad) const
    {return hash<std::string>{}(cad.c_str());}
  };
}

#endif
