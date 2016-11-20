//
// Created by jscherman on 19/11/16.
//

#ifndef ALGO2_TP3_POKEMON_GO_MAPA_H
#define ALGO2_TP3_POKEMON_GO_MAPA_H


#include "TiposJuego.h"
#include "aed2/Conj.h"

class Mapa : public Conj<Coordenada> {

    Mapa();
    ~Mapa();

    Mapa& crearMapa();
    void agregarCoor(Coordenada &coor);
    const Conj<Coordenada>& coordenadas() const;
    const bool& posExistente(Coordenada &coor);
    const bool& hayCamino(Coordenada &coor);

};


#endif //ALGO2_TP3_POKEMON_GO_MAPA_H
