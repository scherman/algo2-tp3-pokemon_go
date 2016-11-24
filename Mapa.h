#ifndef ALGO2_TP3_POKEMON_GO_MAPA_H
#define ALGO2_TP3_POKEMON_GO_MAPA_H
//#include "TiposJuego.h"
#include "aed2.h"
#include "Coordenada.h"

using  namespace tp3;
using namespace aed2;

class Mapa  {
public :
    Mapa();

    ~Mapa();

    Mapa(const Mapa &);

    void agregarCoor(Coordenada coor);

    const Conj<Coordenada>& coordenadas() const;

     bool posExistente(Coordenada coor) const;

     bool hayCamino(Coordenada coor1, Coordenada coor2) const;

private:
        Conj<Coordenada> validas;

static bool existeCamino(Coordenada coor1,Coordenada coor2,  Conj<Coordenada> & c){

    if( coor1 == coor2){ //caso base
      return true; //aniadir booleano que informe si ya se encontro camino
    }else
      if (c.EsVacio())  //caso base
        return false;
      else {
        Coordenada arriba = coor1;
        Coordenada abajo = coor1;
        Coordenada izquierda = coor1;
        Coordenada derecha = coor1;
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

void Mapa::agregarCoor(Coordenada coor){
validas.AgregarRapido(coor);
}

const Conj<Coordenada>& Mapa::coordenadas() const{
return validas;
}

bool Mapa::posExistente(Coordenada coor) const{
return validas.Pertenece(coor);
}

bool Mapa::hayCamino(Coordenada coor1, Coordenada coor2) const{
Conj<Coordenada> nuevo(validas);
nuevo.Eliminar(coor1);
return existeCamino(coor1,coor2, nuevo);
}


#endif //ALGO2_TP3_POKEMON_GO_MAPA_H


