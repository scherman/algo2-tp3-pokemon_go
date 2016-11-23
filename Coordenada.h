#ifndef COORD_H
#define	COORD_H

#include <iostream>
#include "aed2.h"


using namespace std;
using namespace aed2;

namespace tp3{//comienzo namespace tp3

class Coordenada{
    public:
     Coordenada();
     Coordenada(const Coordenada & otro);
     Coordenada& operator=(const Coordenada & otro);
     Coordenada(Nat lat,Nat lon);
     Nat Latitud()const;
     Nat Longitud() const;
     Nat DistEuclidea(const Coordenada & otro);
     void CoordenadaArriba();
     void CoordenadaAbajo();
     void CoordenadaALaIzquierda();
     void CoordenadaALaDerecha();
     bool operator == (const Coordenada& otro) const;

    private:
        Nat latitud;
        Nat longitud;

};

Coordenada::Coordenada(){
latitud = 0;
longitud = 0;
}

Coordenada::Coordenada(const Coordenada & otro):
latitud(otro.latitud),longitud(otro.longitud)
{}

Coordenada& Coordenada::operator=(const Coordenada & otro){
latitud = otro.latitud;
longitud = otro.longitud;
return *this;
}

Coordenada::Coordenada(Nat lat,Nat lon){
latitud = lat;
longitud = lon;
}

Nat Coordenada::Latitud()const{
return latitud;
}

Nat Coordenada::Longitud() const{
return longitud;
}

Nat Coordenada::DistEuclidea(const Coordenada & otro){
    Nat latAux = 0;
    Nat lonAux = 0;
if(latitud > otro.Latitud())
    latAux = (latitud - otro.Latitud())*(latitud - otro.Latitud());
else
    latAux = (otro.Latitud() - latitud)*(otro.Latitud() - latitud);

if(longitud > otro.Longitud())
    lonAux = (longitud - otro.Longitud())*(longitud - otro.Longitud());
else
    lonAux = (otro.Longitud() - longitud)*(otro.Longitud() - longitud);

return latAux + lonAux;
}

void Coordenada::CoordenadaArriba(){
latitud = latitud + 1;
}

void Coordenada::CoordenadaAbajo(){
latitud = latitud - 1;
}

void Coordenada::CoordenadaALaIzquierda(){
longitud = longitud - 1;
}

void Coordenada::CoordenadaALaDerecha(){
longitud = longitud + 1;
}

bool Coordenada::operator == (const Coordenada& otro) const{
return latitud == otro.latitud && longitud == otro.longitud;
}

}//fin namespace tp3
#endif
