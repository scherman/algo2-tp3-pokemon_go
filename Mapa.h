#ifndef ALGO2__POKEMON_GO_MAPA_H
#define ALGO2_TP3_POKEMON_GO_MAPA_H
//#include "TiposJuego.h"
#include "aed2.h"
#include "Coordenadatp3.h"

//using  namespace tp3;
using namespace aed2;

class Mapa  {
public :
    Mapa();

    ~Mapa();

    Mapa(const Mapa &);

    void agregarCoor(Coordenadatp3 coor);

    const Conj<Coordenadatp3>& coordenadas() const;

     bool posExistente(Coordenadatp3 coor) const;

     bool hayCamino(Coordenadatp3 coor1, Coordenadatp3 coor2) const;

private:
        Conj<Coordenadatp3> validas;

static bool existeCamino(Coordenadatp3 coor1,Coordenadatp3 coor2,  Conj<Coordenadatp3> & c){

    if( coor1 == coor2){ //caso base
      return true; //aniadir booleano que informe si ya se encontro camino
    }else
      if (c.EsVacio())  //caso base
        return false;
      else {
        Coordenadatp3 arriba = coor1;
        Coordenadatp3 abajo = coor1;
        Coordenadatp3 izquierda = coor1;
        Coordenadatp3 derecha = coor1;
        bool resultado = false;
        arriba.CoordenadaArriba();
        if (c.Pertenece(arriba)){//caso coorarriba
          c.Eliminar(arriba);
          resultado = existeCamino(arriba,coor2,c);
          if (resultado)
            return resultado;
        }
        abajo.CoordenadaAbajo();
        if(c.Pertenece(abajo)){//caso coorabajo
          c.Eliminar(abajo);
          resultado = existeCamino(abajo,coor2,c);
          if (resultado)
            return resultado;
        }
        izquierda.CoordenadaALaIzquierda();
        if(c.Pertenece(izquierda) ){//caso coorizquierda
          c.Eliminar(izquierda);
          resultado = existeCamino(izquierda,coor2,c);
          if (resultado)
            return resultado;
        }
        derecha.CoordenadaALaDerecha();
        if(c.Pertenece(derecha)  ){//caso coorderecha
          c.Eliminar(derecha);
          resultado = existeCamino(derecha,coor2,c);
          if (resultado)
            return resultado;
        }
        return resultado;
      }
}

};

Mapa::Mapa(){
}

Mapa::~Mapa(){
}

Mapa::Mapa(const Mapa & otro):
validas(otro.validas){
}

void Mapa::agregarCoor(Coordenadatp3 coor){
validas.AgregarRapido(coor);
}

const Conj<Coordenadatp3>& Mapa::coordenadas() const{
return validas;
}

bool Mapa::posExistente(Coordenadatp3 coor) const{
return validas.Pertenece(coor);
}

bool Mapa::hayCamino(Coordenadatp3 coor1, Coordenadatp3 coor2) const{
Conj<Coordenadatp3> nuevo(validas);
nuevo.Eliminar(coor1);
return existeCamino(coor1,coor2, nuevo);
}


#endif //ALGO2__POKEMON_GO_MAPA_H
