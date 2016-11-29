
#include "ConjPrior.h"


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



