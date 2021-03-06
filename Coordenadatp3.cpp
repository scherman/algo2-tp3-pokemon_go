
#include "Coordenadatp3.h"


Coordenadatp3::Coordenadatp3(){
latitud = 0;
longitud = 0;
}

Coordenadatp3::Coordenadatp3(const Coordenadatp3 & otro):
latitud(otro.latitud),longitud(otro.longitud)
{}

Coordenadatp3& Coordenadatp3::operator=(const Coordenadatp3 & otro){
latitud = otro.latitud;
longitud = otro.longitud;
return *this;
}

Coordenadatp3::Coordenadatp3(Nat lat,Nat lon){
latitud = lat;
longitud = lon;
}

Nat Coordenadatp3::Latitud()const{
return latitud;
}

Nat Coordenadatp3::Longitud() const{
return longitud;
}

Nat Coordenadatp3::DistEuclidea(const Coordenadatp3 & otro) const{//+++++++++++++++++++++++++++++++++++++++++++++
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

void Coordenadatp3::CoordenadaArriba(){
latitud = latitud + 1;
}

void Coordenadatp3::CoordenadaAbajo(){
latitud = latitud - 1;
}

void Coordenadatp3::CoordenadaALaIzquierda(){
longitud = longitud - 1;
}

void Coordenadatp3::CoordenadaALaDerecha(){
longitud = longitud + 1;
}

bool Coordenadatp3::operator == (const Coordenadatp3& otro) const{
return latitud == otro.latitud && longitud == otro.longitud;
}

bool Coordenadatp3::operator != (const Coordenadatp3& otro) const{
    return latitud != otro.latitud or longitud != otro.longitud;
}

