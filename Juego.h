//
// Created by jscherman on 19/11/16.
//

#ifndef ALGO2_TP3_POKEMON_GO_JUEGO_H
#define ALGO2_TP3_POKEMON_GO_JUEGO_H

#include <vector>
#include "aed2/TiposBasicos.h"
#include "DiccString.h"
#include "TiposJuego.h"
#include "aed2/Conj.h"

using namespace aed2;

class Juego {

public:

private:

    struct Parcela;
    struct EstadoJugador;
    struct EstadoPokemon;

    std::vector<std::vector<Parcela>> mapa;
    std::vector<EstadoJugador> jugadores;
    DiccString<EstadoPokemon> pokemones;
    Conj<Coordenada> posicionesPokemons;
    Nat cantTotalPokemones;
    Conj<Jugador> jugadoresActivos;

    struct Parcela {
        bool definida;
        std::vector<std::vector<bool>> conexiones;
        bool hayPokemon;
        Pokemon pokemon;
        Conj<Coordenada>::Iterador itPosicionesPokemon;
        Conj<Jugador> jugadoresEnPosicion;
//        ConjPr jugadoresEnZona; IMPLEMENTAR CONJPR!
        Nat cantMovimientos;
    };

    struct EstadoJugador{
        bool recienCreado;
        bool conectado;
        Nat sanciones;
        Coordenada posicion;
        DiccString<Nat> capturados;
        Nat cantCapturados;
        Conj<Jugador>::Iterador itJugadoresActivos;
//        ItConjPr itJugadoresEnZona IMPLEMENTAR!
    };

    struct EstadoPokemon {
        Nat cantTotalEspecie;
        Conj<Coordenada> posiciones;
    };

};


#endif //ALGO2_TP3_POKEMON_GO_JUEGO_H
