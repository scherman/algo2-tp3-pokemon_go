#ifndef CONJPRIOR_H
#define	CONJPRIOR_H

#include <iostream>
#include "aed2.h"


using namespace std;
using namespace aed2;

class ConjPrior
{
  private:
      struct nodo;

  public:

    //clase exportada

    struct elem{
      Nat campo1 ;
      Nat campo2;
      elem( Nat a,Nat b) : campo1( a), campo2(b ){};
      bool operator == (  elem  h){
      return campo1 == h.campo1 && campo2 == h.campo2;
    }

    };

    //forward declarations
    class Iterador;
    class const_Iterador;
    //class elem;
    //struct nodo;
    //class const_Iterador;

    // Generadores

    ConjPrior();
    ~ConjPrior();
    ConjPrior(const ConjPrior& otro);  //este crea una copia del conjunto y no genera aliasing?

     ConjPrior& operator=(const ConjPrior& otro);//este crea copia y genera aliasing? ambos hacen lo mismo?

    Iterador Agregar(Nat cantPokesAtrap, Nat jugador);


    // Observadores

    bool Pertenece(Nat a, Nat b) const;

    Nat Cardinal() const;

    Nat Minimo() const ;
    Iterador CrearIt();
    const_Iterador CrearIt() const;

    //const_Iterador CrearIt() const;

    //esta funcion la agregamos aca, porque nos conviene acceder a
    //la representación.  Sino, no haria falta.
    bool operator == (const ConjPrior& otro) const;


    /************************************
    * Iterador de Conjunto, modificable *
    ************************************/
    class Iterador
    {
      public:

        Iterador();

        Iterador(const typename ConjPrior::Iterador& otra);

        Iterador& operator = (const typename ConjPrior::Iterador& otra);

        bool operator == (const typename ConjPrior::Iterador& otro) const;

        bool HaySiguienteElem() const;

        elem SiguienteElem() const;

        void AvanzarElem();

        void EliminarSiguienteElem();



      private:

        typename Lista< typename ConjPrior:: nodo*>::Iterador nodos;
        typename ConjPrior::nodo** prim;
        //funcion modificada *************************************
        Iterador(  ConjPrior * c )
        :  nodos(c->nodosDeArbol.CrearIt()),prim(&c->primero ){}
                 friend class ConjPrior::const_Iterador;

        friend typename ConjPrior::Iterador ConjPrior::CrearIt();
        //invoca Iterador sobre primero y nodosDeArbol

    };

    class const_Iterador
    {
      public:

        const_Iterador();

        const_Iterador(const typename ConjPrior::const_Iterador& otra);

        const_Iterador(const typename ConjPrior::Iterador& otra);

        const_Iterador& operator = (const typename ConjPrior::const_Iterador& otra);

        bool operator == (const typename ConjPrior::const_Iterador& otro) const;

        bool HaySiguienteElem() const;

        elem SiguienteElem() const;

        void AvanzarElem();


      private:

         typename Lista< typename ConjPrior:: nodo*>::const_Iterador nodos;
         typename ConjPrior::nodo* const* prim;
        //funcion modificada *************************************
         const_Iterador(  const ConjPrior * c )
         :  nodos(c->nodosDeArbol.CrearIt()),prim( &c->primero ){}
         friend typename ConjPrior::const_Iterador ConjPrior::CrearIt() const;
        //invoca Iterador sobre primero y nodosDeArbol

    };



  private:
       struct nodo
    {
        Nat clave;
        Nat significado;
        Nat ran;
        nodo * izq;
        nodo * der;
        nodo * padre;

        nodo(Nat c,Nat s,Nat r,nodo * i,nodo * d, nodo * p) {
        clave = c;
        significado = s;
        ran = r;
        izq = i;
        der = d;
        padre = p;
        };
         bool operator == ( const nodo&  h){
      return clave == h.clave && significado == h.significado && ran == h.ran; // &&
    }

    };



    nodo * primero;
    Lista<nodo *> nodosDeArbol;

    //operaciones auxiliares

    static nodo * fusionar(nodo * p,nodo * q){
    if (p == NULL)
        return q;
    else{
        if (q == NULL)
            return p;
        else
            return fusionarAux(p,q);
    }
    }

    static nodo * fusionarAux(nodo * p, nodo *q){
    if (p->clave >= q->clave){
        p->padre = q;
        if (q->der == NULL)
            q->der = p;
        else
            q->der = fusionarAux(p,q->der); //modificado - original: fusionarAux(q->der,p)
        if ((q->izq != NULL && (q->izq->ran < q->der->ran))|| q->izq == NULL ){
            nodo * aux = q->izq;
            q->izq = q->der;
            q->der = aux;
        }
        if (q->der != NULL )
            q->ran = q->der->ran + 1;
        else
            q->ran = 1;
        return q;
    } else {
        q->padre = p;
        if (p->der == NULL)
            p->der = q;
        else
            p->der = fusionarAux(q,p->der); //modificado - original: fusionarAux(p->der,q)
        if ((p->izq != NULL && (p->izq->ran < p->der->ran))|| p->izq == NULL ){
            nodo * aux = p->izq;
            p->izq = p->der;
            p->der = aux;
        }
        if (p->der != NULL )
            p->ran = p->der->ran + 1;
        else
            p->ran = 1;
        return p;
    }
    }
     //probablemente nodo * p deba cambiarse por nodo ** p
    static void eliminarMin(nodo * /*&*/*p,typename Lista< typename ConjPrior:: nodo*>::Iterador& itL ,nodo ** cabeza){
    nodo * izqAux = (*p)->izq;
    nodo * derAux = (*p)->der;
    nodo * padreAux = (*p)->padre;
    nodo * copiaOriginal = *p;
    if (padreAux != NULL){
        if (padreAux->izq == *p){
            *p = fusionar(izqAux,derAux) ;
            padreAux->izq = *p;
            if (*p != NULL)
               (*p)->padre = padreAux;
        }else{
            *p = fusionar(izqAux,derAux)  ;
            padreAux->der = *p;
            if (*p != NULL)
               (*p)->padre = padreAux;
        }
    }else{
        *p = fusionar(izqAux,derAux);
        *cabeza = *p ;
        if (*p != NULL)
          (*p)->padre = NULL;
    }
    itL.EliminarSiguiente();
    delete copiaOriginal;
    }
};
//algoritmos  *******************************************************************************************+



    ConjPrior::ConjPrior(){
    primero = NULL;

    }

    ConjPrior::~ConjPrior(){
     //Lista<typename ConjPrior::nodo*>::Iterador it = nodosDeArbol.CrearIt();
     typename ConjPrior::Iterador it;

     while (Cardinal() != 0){
        it = (*this).CrearIt();
        it.EliminarSiguienteElem();
     }
    }

    ConjPrior& ConjPrior::operator=(const ConjPrior& otro){

    typename ConjPrior::Iterador itaux = CrearIt();
    while (itaux.HaySiguienteElem()){
        itaux.EliminarSiguienteElem();
        //itaux.AvanzarElem();
    }

    primero = NULL;
    if (otro.primero == NULL)
        return *this;
    else{
     typename ConjPrior::const_Iterador it = otro.CrearIt();
     elem e(otro.primero->clave,otro.primero->significado);
     bool encontrado = false;
     while(it.HaySiguienteElem() && !encontrado){
        if (it.SiguienteElem() == e)
            encontrado = true;
        else
            it.AvanzarElem();
     }
     Nat cant = otro.Cardinal();
     while(it.HaySiguienteElem()){
        Agregar(it.SiguienteElem().campo1,it.SiguienteElem().campo2);
        it.AvanzarElem();
        cant--;
     }
     if (cant > 0){
        it = otro.CrearIt();
        while(it.HaySiguienteElem() && cant > 0){
          Agregar(it.SiguienteElem().campo1,it.SiguienteElem().campo2);
          it.AvanzarElem();
           cant--;
        }
     }
     return *this;
    }
   }


    ConjPrior::ConjPrior(const ConjPrior& otro){

     typename ConjPrior::Iterador itaux = CrearIt();
    while (itaux.HaySiguienteElem()){
        itaux.EliminarSiguienteElem();
        //itaux.AvanzarElem();
    }
    primero = NULL;
    if (otro.primero != NULL){

     typename ConjPrior::const_Iterador it = otro.CrearIt();
     elem e(otro.primero->clave,otro.primero->significado);
     bool encontrado = false;
     while(it.HaySiguienteElem() && !encontrado){
        if (it.SiguienteElem() == e)
            encontrado = true;
        else
            it.AvanzarElem();
     }
     Nat cant = otro.Cardinal();
     while(it.HaySiguienteElem()){
        Agregar(it.SiguienteElem().campo1,it.SiguienteElem().campo2);
        it.AvanzarElem();
        cant--;
     }
     if (cant > 0){
        it = otro.CrearIt();
        while(it.HaySiguienteElem() && cant > 0){
          Agregar(it.SiguienteElem().campo1,it.SiguienteElem().campo2);
          it.AvanzarElem();
           cant--;
        }
     }

    }
 }

    bool ConjPrior::operator == (const ConjPrior& otro) const{
        if (primero == NULL )
            return otro.primero == NULL;
        else{
        bool requisito = otro.primero != NULL;
          typename Lista< typename ConjPrior:: nodo*>::const_Iterador itOtro = otro.nodosDeArbol.CrearIt();
          typename Lista< typename ConjPrior:: nodo*>::const_Iterador it = nodosDeArbol.CrearIt();
          while(it.HaySiguiente() && requisito){
            if (*it.Siguiente() == *itOtro.Siguiente())
               requisito = requisito && true;
            else
               requisito = false;
            it.Avanzar();
            itOtro.Avanzar();
          }
         return requisito && *primero == *otro.primero ;
        }
    }


    typename ConjPrior::Iterador ConjPrior::Agregar(Nat cantPokesAtrap, Nat jugador){
    nodo * nuevo = new nodo (cantPokesAtrap,jugador,0,NULL,NULL,NULL);
    if (primero == NULL)
        primero = nuevo;
    else
        primero = fusionar(nuevo,primero);

    nodosDeArbol.AgregarAdelante(nuevo);

     return CrearIt();
    }

    bool ConjPrior::Pertenece(Nat a, Nat b) const{
    Lista<typename ConjPrior::nodo*>::const_Iterador it = nodosDeArbol.CrearIt();
    bool esta = false;
    while (it.HaySiguiente() && !esta) {
        if (it.Siguiente()->clave == a && it.Siguiente()->significado == b)
            esta = true;
        it.Avanzar();

    }
    return esta;
    }


    Nat ConjPrior::Cardinal() const{
    return nodosDeArbol.Longitud();
    }

    Nat ConjPrior::Minimo() const {

    return primero->significado;
    }

    typename ConjPrior::Iterador ConjPrior::CrearIt(){
             //invoca Iterador sobre primero y nodosDeArbol
    return Iterador(this);
    }

    //crearit de constiterador
     typename ConjPrior::const_Iterador ConjPrior::CrearIt() const{
             //invoca Iterador sobre primero y nodosDeArbol
    return const_Iterador(this);
    }

    //algoritmos del iterador *****************************************************************************+
    ConjPrior::Iterador::Iterador(){
    prim = NULL;
    }

    typename ConjPrior::Iterador& ConjPrior::Iterador::operator = (const typename ConjPrior::Iterador& otra){
     nodos = otra.nodos;
      prim = otra.prim;
      return *this;
    };

    void ConjPrior::Iterador::AvanzarElem(){

     //pre: vale haySiguienteElem()
        nodos.Avanzar();
     //post: iterador apunta al siguiente en la lista interna nodos

    }

    ConjPrior::Iterador::Iterador(const typename ConjPrior::Iterador& otra):
     nodos(otra.nodos), prim(otra.prim)
    {
    };

    bool ConjPrior::Iterador::operator == (const typename ConjPrior::Iterador& otro) const{
    return  nodos == otro.nodos && prim == otro.prim;
    };

    bool ConjPrior::Iterador::HaySiguienteElem() const{
    return nodos.HaySiguiente();
    };

    typename ConjPrior::elem ConjPrior::Iterador::SiguienteElem() const{

     return elem(nodos.Siguiente()->clave,nodos.Siguiente()->significado);

    };


    void ConjPrior::Iterador::EliminarSiguienteElem(){
         nodo ** aux = &nodos.Siguiente(); //probablemente aux deba ser nodo ** y reciba &
         nodo * padreAux = (*aux)->padre;
         eliminarMin(aux,nodos,prim);
         while (padreAux != NULL){
            if (padreAux->izq != NULL && padreAux->der != NULL){
                if(padreAux->izq->ran < padreAux->der->ran){
                    nodo * aux2 = padreAux->izq;
                    padreAux->izq = padreAux->der;
                    padreAux->der = aux2;
                    padreAux->ran = 1+ ((padreAux->izq->ran < padreAux->der->ran) ? padreAux->izq->ran : padreAux->der->ran);
                }
            } else {
                if(padreAux->izq == NULL && padreAux->der != NULL){
                    padreAux->izq = padreAux->der;
                    padreAux->der = NULL;
                    padreAux->ran = 1;
                } else {
                    if (padreAux->izq != NULL && padreAux->der == NULL )
                        padreAux->ran = 1;
                    else{
                        padreAux->ran = 0;
                    }
                }
            }
            padreAux = padreAux->padre;
         }
    };
    //algoritmos de const_iterador ***************************************************************

    ConjPrior::const_Iterador::const_Iterador(){
    prim = NULL;
    }

    typename ConjPrior::const_Iterador& ConjPrior::const_Iterador::operator = (const typename ConjPrior::const_Iterador& otra){
     nodos = otra.nodos;
      prim = otra.prim;
      return *this;
    };

    void ConjPrior::const_Iterador::AvanzarElem(){

     //pre: vale haySiguienteElem()
        nodos.Avanzar();
     //post: iterador apunta al siguiente en la lista interna nodos

    }

    ConjPrior::const_Iterador::const_Iterador(const typename ConjPrior::const_Iterador& otra):
     nodos(otra.nodos), prim(otra.prim)
    {
    };

    ConjPrior::const_Iterador::const_Iterador(const typename ConjPrior::Iterador& otra):
     nodos(otra.nodos), prim(otra.prim)
    {
    };

    bool ConjPrior::const_Iterador::operator == (const typename ConjPrior::const_Iterador& otro) const{
    return  nodos == otro.nodos && prim == otro.prim;
    };

    bool ConjPrior::const_Iterador::HaySiguienteElem() const{
    return nodos.HaySiguiente();
    };

    typename ConjPrior::elem ConjPrior::const_Iterador::SiguienteElem() const{

     return elem(nodos.Siguiente()->clave,nodos.Siguiente()->significado);

    };



#endif
