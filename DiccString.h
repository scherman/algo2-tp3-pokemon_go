////
//// Created by jscherman on 19/11/16.
////
//
//#ifndef ALGO2_TP3_POKEMON_GO_DICCSTRING_H
//#define ALGO2_TP3_POKEMON_GO_DICCSTRING_H
//
//template<class T>
//class DiccString {
//public:
//    class Iterador;
//};
//
//
//#endif //ALGO2_TP3_POKEMON_GO_DICCSTRING_H


#ifndef ALGO2_TP3_POKEMON_GO_DICCSTRING_H
#define ALGO2_TP3_POKEMON_GO_DICCSTRING_H

#include <iostream>
#include <cassert>
#include "aed2.h"

using namespace std;
using namespace aed2;

//namespace tp3{
template<class T>
class DiccString {
	struct tuplaCS; //forward declaration.
	public:
	  	class itDiccString;
	  	class const_itDiccString;
	  	friend class itConj;

		DiccString();
		~DiccString();
		void DefinirRapido(const String&,const T&);
		bool Definido(const String&) const;
		const T& Significado(const String&)const;
		T& Significado(const String&);
		const Conj<String>& Claves() const;
		void Borrar(const String&);
		//const String& Maximo()const;
		//const String& Minimo()const; 
		bool operator==(const DiccString<T>& otro)const;
		DiccString<T>& operator=(const DiccString<T>& otra);

		itDiccString CrearIt();
	    const_itDiccString CrearIt() const;

	    DiccString(const DiccString<T>& otro);
		
		class itDiccString{
	    	public:
           	  itDiccString();

              bool HaySiguiente() const;
              
              const String& SiguienteClave() const;
             
              T& SiguienteSignificado();

              void Avanzar();

	    	private:

	      		typename Conj< typename DiccString<T>::tuplaCS >::const_Iterador it;

	      		itDiccString(DiccString<T>* d);

             	friend class DiccString;
		};
		
		class const_itDiccString{
	    	public:
           	  const_itDiccString();

              bool HaySiguiente() const;
              
              const String& SiguienteClave() const;
             
              const T& SiguienteSignificado() const;

              void Avanzar();

	    	private:

	      		typename Conj< typename DiccString<T>::tuplaCS >::const_Iterador it;

	      		const_itDiccString(const DiccString<T>* d);

             	friend class DiccString;
		};
		
	private:
		
		struct tuplaCS{			
				String clave;
				T* significado;
				bool operator == (const tuplaCS& otra) const {
				  return (clave == otra.clave && (*(significado) == *(otra.significado)));
				}
		};


		struct Nodo {
			Nodo(Conj<String>& c,Conj<tuplaCS>& cs);
			~Nodo();
			struct infoNodo{			
		    	Nodo* prox;
				bool finPalabra;
				typename Conj<String>::Iterador itClave;
				typename Conj<tuplaCS>::Iterador itClaveYSign;
			};
			Arreglo<infoNodo> letras; 
		};

		Nodo* raiz;
		Conj<String> claves;
		Conj<tuplaCS> clavesYSignificados;
		
};

template<class T>
DiccString<T>::Nodo::Nodo(Conj<String>& c,Conj<tuplaCS>& cs){
	letras =  Arreglo< infoNodo >(256);
	Nat i = 0;
	while(i < 256){
		infoNodo iNodo;
		iNodo.prox = NULL;
		iNodo.finPalabra = false;
		iNodo.itClave = c.CrearIt(); 
		iNodo.itClaveYSign = cs.CrearIt();
		letras.Definir(i,iNodo);
		i++;
	}
}

template<class T>
DiccString<T>::Nodo::~Nodo() {
	Nat i = 0;
	while(i < 256){
		if(letras.Definido(i) && letras[i].prox != NULL){
			delete letras[i].prox;
		}
		i++;
	}
}

template<class T>
DiccString<T>::DiccString() {
	claves = Conj<String>();
	clavesYSignificados = Conj<tuplaCS>();
	raiz = NULL;
		
}

template<class T>
DiccString<T>::~DiccString(){
	typename Conj<tuplaCS>::const_Iterador it = clavesYSignificados.CrearIt();
	while(it.HaySiguiente()){
		delete it.Siguiente().significado;
		it.Avanzar();
	}
	delete raiz; 
	
}

template<class T>
void DiccString<T>::DefinirRapido(const String& c,const T& s){
	if (raiz == NULL) {
		raiz = new Nodo(claves, clavesYSignificados);
	}
	Nat i = 0;
	Nodo* pActual = raiz;
	Nat posicionDelCarater = (Nat)c[i];
	while(i < c.length()-1){
		if(pActual->letras[posicionDelCarater].prox == NULL){ 	
			Nodo* nuevoNodo = new Nodo(claves,clavesYSignificados);
			pActual->letras[posicionDelCarater].prox = nuevoNodo;
		}
		pActual = pActual->letras[posicionDelCarater].prox;
		i++;
		posicionDelCarater = (Nat)c[i];
	}
	typename Conj<String>::Iterador itc = claves.AgregarRapido(c);
	tuplaCS tcs;
	tcs.clave = c;
 	tcs.significado = new T(s); 
	typename Conj<tuplaCS>::Iterador itcs = clavesYSignificados.AgregarRapido(tcs);
	if(pActual->letras[posicionDelCarater].prox == NULL){
		pActual->letras[posicionDelCarater].prox = NULL;
		pActual->letras[posicionDelCarater].finPalabra = true;
		pActual->letras[posicionDelCarater].itClave = itc;
		pActual->letras[posicionDelCarater].itClaveYSign = itcs;
	}else{
		Nodo* proximo = pActual->letras[posicionDelCarater].prox;
		pActual->letras[posicionDelCarater].prox = proximo;
		pActual->letras[posicionDelCarater].finPalabra = true;
		pActual->letras[posicionDelCarater].itClave = itc;
		pActual->letras[posicionDelCarater].itClaveYSign = itcs;
	}
}

template<class T>
bool DiccString<T>::Definido(const String& c) const{
	Nat i = 0;
	Nodo* pActual = raiz;	
	Nat posicionDelCarater = (Nat)c[i];
	while(i < c.length() -1  && pActual->letras[posicionDelCarater].prox != NULL){
		pActual = pActual->letras[posicionDelCarater].prox;
		i++;
		posicionDelCarater = (Nat)c[i];
	}
	return (i + 1  == c.length()) && pActual->letras[posicionDelCarater].finPalabra;
}

template<class T>
const T& DiccString<T>::Significado(const String& c) const{
	Nat i = 0;
	Nodo* pActual = raiz;
	Nat posicionDelCarater = (Nat)c[i];
	while(i < c.length()-1){		
		pActual = pActual->letras[posicionDelCarater].prox;
		i++;
		posicionDelCarater = (Nat)c[i];
	}
	return *(pActual->letras[posicionDelCarater].itClaveYSign).Siguiente().significado;
}


template<class T>
T& DiccString<T>::Significado(const String& c){
	Nat i = 0;
	Nodo* pActual = raiz;
	Nat posicionDelCarater = (Nat)c[i];
	while(i < c.length()-1){		
		pActual = pActual->letras[posicionDelCarater].prox;
		i++;
		posicionDelCarater = (Nat)c[i];
	}
	return *(pActual->letras[posicionDelCarater].itClaveYSign).Siguiente().significado;
}





template<class T>
void DiccString<T>::Borrar(const String& c){
	Nat i = 0;
	Nat palDef = 0;
	bool tieneSiguiente = false;
	Nodo* pActual = raiz;
	Nodo* anterior = raiz;
	Nat posicionDelCarater = (Nat)c[i];
	while(i < c.length()-1){		
		anterior = pActual;
		if(pActual->letras[posicionDelCarater].finPalabra){
			palDef++;
		}
		pActual = pActual->letras[posicionDelCarater].prox;
		i++;
		posicionDelCarater = (Nat)c[i];
	}
	if(pActual->letras[posicionDelCarater].prox != NULL){
		tieneSiguiente = true;
	}
	if(palDef == 0 && !(tieneSiguiente)){
		pActual->letras[posicionDelCarater].itClave.EliminarSiguiente();
		delete pActual->letras[posicionDelCarater].itClaveYSign.Siguiente().significado;
		pActual->letras[posicionDelCarater].itClaveYSign.EliminarSiguiente();
		pActual->letras[posicionDelCarater].finPalabra = false;
		pActual->letras[posicionDelCarater].prox = NULL;
	}else{
		if( palDef == 0 && tieneSiguiente){
			pActual->letras[posicionDelCarater].itClave.EliminarSiguiente();
			delete pActual->letras[posicionDelCarater].itClaveYSign.Siguiente().significado;
			pActual->letras[posicionDelCarater].itClaveYSign.EliminarSiguiente();
			pActual->letras[posicionDelCarater].finPalabra = false;
		}else{
			pActual->letras[posicionDelCarater].itClave.EliminarSiguiente();
			delete pActual->letras[posicionDelCarater].itClaveYSign.Siguiente().significado;
			pActual->letras[posicionDelCarater].itClaveYSign.EliminarSiguiente();
			if(!(tieneSiguiente)){
				anterior->letras[(Nat)c[i-1]].prox = NULL;
			}
			pActual->letras[posicionDelCarater].finPalabra = false;
		}
	}
}


template<class T>
const Conj<String>& DiccString<T>::Claves() const{
    return claves;
}

//template<class T>
//const String& DiccString<T>::Maximo()const{
//	Nodo* pActual = raiz;
//	Nat i = 255;
//	while(i >= 0){
//		if(pActual->letras[i].prox == NULL && pActual->letras[i].finPalabra == false){
//			i--;
//		}else{
//			if(pActual->letras[i].prox == NULL && pActual->letras[i].finPalabra == true){
//				return pActual->letras[i].itClave.Siguiente();
//			}else{
//				pActual = pActual->letras[i].prox;
//				i = 255;
//			}
//		}
//	}
//}
//
//template<class T>
//const String& DiccString<T>::Minimo()const{
//	Nodo* pActual = raiz;
//	Nat i = 0;
//	while(i < 256 ){
//		if(pActual->letras[i].prox == NULL && pActual->letras[i].finPalabra == false){
//			i++;
//		}else{
//			if(pActual->letras[i].prox != NULL && pActual->letras[i].finPalabra == false){
//				pActual = pActual->letras[i].prox;
//				i = 0;
//			}else{
//				return pActual->letras[i].itClave.Siguiente();
//			}
//		}
//	}
//}


template<class T>
DiccString<T>::itDiccString::itDiccString(DiccString<T> *d): it(d->clavesYSignificados.CrearIt()) {}

template<class T>
typename DiccString<T>::itDiccString DiccString<T>::CrearIt(){
    return itDiccString(this);
}  

template<class T>
void  DiccString<T>::itDiccString::Avanzar(){
	it.Avanzar();
}


template<class T>              
const String&  DiccString<T>::itDiccString::SiguienteClave() const{
	return it.Siguiente().clave ;
}

template<class T>
 T&  DiccString<T>::itDiccString::SiguienteSignificado(){
	return *(it.Siguiente().significado) ;
}


template<class T>
bool  DiccString<T>::itDiccString::HaySiguiente() const{
	return it.HaySiguiente();
}
	

template<class T>
bool DiccString<T>::operator==(const DiccString<T>& otro)const{
			//return (claves == otro.claves && clavesYSignificados == otro.clavesYSignificados);
	DiccString<T>::const_itDiccString it = otro.CrearIt();
	while(it.HaySiguiente()){
		if(!(Definido(it.SiguienteClave()) && Significado(it.SiguienteClave()) == it.SiguienteSignificado())){
			return false;
		}
		it.Avanzar();
	}
	DiccString<T>::const_itDiccString it2 = CrearIt();
	while(it2.HaySiguiente()){
		if(!(otro.Definido(it2.SiguienteClave()) && otro.Significado(it2.SiguienteClave()) == it2.SiguienteSignificado())){
			return false;
		}
		it2.Avanzar();
	}
	return true;
}

template<class T>
DiccString<T>& DiccString<T>::operator=(const DiccString<T>& otra)
{
	claves = Conj<String>();
	clavesYSignificados = Conj<tuplaCS>();
	raiz = new Nodo(claves,clavesYSignificados);
	DiccString<T>::const_itDiccString it = otra.CrearIt();
	while(it.HaySiguiente()){
		String clave = String(it.SiguienteClave());
		T dat = T(it.SiguienteSignificado());
		DefinirRapido(clave,dat);
		it.Avanzar();
	}
	return *this;
}

template<class T>
DiccString<T>::const_itDiccString::const_itDiccString(const DiccString<T> *d): it(d->clavesYSignificados.CrearIt()) {}

template<class T>
typename DiccString<T>::const_itDiccString DiccString<T>::CrearIt()const{
    return const_itDiccString(this);
}  

template<class T>
void  DiccString<T>::const_itDiccString::Avanzar(){
	it.Avanzar();
}


template<class T>              
const String&  DiccString<T>::const_itDiccString::SiguienteClave() const{
	return it.Siguiente().clave ;
}

template<class T>
const T&  DiccString<T>::const_itDiccString::SiguienteSignificado()const{
	return *(it.Siguiente().significado) ;
}


template<class T>
bool  DiccString<T>::const_itDiccString::HaySiguiente() const{
	return it.HaySiguiente();
}
	
template<class T>	
DiccString<T>::DiccString(const DiccString<T>& otro) {
	claves = Conj<String>();
	clavesYSignificados = Conj<tuplaCS>();
	raiz = new Nodo(claves,clavesYSignificados);
	DiccString<T>::const_itDiccString it = otro.CrearIt();
	while(it.HaySiguiente()){
		String clave = String(it.SiguienteClave());
		T dat = T(it.SiguienteSignificado());
		DefinirRapido(clave,dat);
		it.Avanzar();
	}
}






//}
#endif //ALGO2_TP3_POKEMON_GO_DICCSTRING_H