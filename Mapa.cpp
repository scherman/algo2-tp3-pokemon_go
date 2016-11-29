
#include "Mapa.h"

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

