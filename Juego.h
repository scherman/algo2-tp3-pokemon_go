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
#include "Mapa.h"
#include "ConjPrior.h"

using namespace aed2;

class Juego {

public:

    Juego& crearJuego(Mapa &mapa);
    void agregarPokemon(Pokemon &p, Coordenada &coor);
    void agregarJugador(Jugador &j);
    void conectarse(Jugador &j, Coordenada &coor);
    void desconectarse(Jugador &j);
    void moverse(Jugador &j, Coordenada &coor);
    const Mapa& mapa();
    const Conj<Jugador>::Iterador& jugadores();
    const bool& estaConectado(Jugador &j);
    const Nat& sanciones(Jugador &j);
    const Coordenada& posicion(Jugador &j);
    const DiccString<Nat>::Iterador& pokemons();
    const Conj<Jugador>& expulsados();
    const Conj<Coordenada>& posConPokemons();
    const Pokemon& pokemonEnPos(Coordenada &coor);
    const Nat& cantMovimientosParaCaptura(Coordenada &coor);
    const bool& puedoAgregarPokemon(Coordenada &coor);
    const bool& hayPokemonCercano(Coordenada &coor);
    const Coordenada& posPokemonCercano(Coordenada &coor);
    const std::vector<Jugador>& entrenadoresPosibles(Coordenada& coor, std::vector<Jugador> &js);
    const Nat& indiceRareza(Pokemon &p);
    const Nat& cantPokemonsTotales();
    const Nat& cantMismaEspecie(Pokemon &p);

private:

    struct Parcela;
    struct EstadoJugador;
    struct EstadoPokemon;

    std::vector<std::vector<Parcela>> _mapa;
    std::vector<EstadoJugador> _jugadores;
    DiccString<EstadoPokemon> _pokemones;
    Conj<Coordenada> _posicionesPokemons;
    Nat _cantTotalPokemones;
    Conj<Jugador> _jugadoresActivos;

    struct Parcela {
        bool definida;
        std::vector<std::vector<bool>> conexiones;
        bool hayPokemon;
        Pokemon pokemon;
        Conj<Coordenada>::Iterador itPosicionesPokemon;
        Conj<Jugador> jugadoresEnPosicion;
        ConjPrior<Jugador> jugadoresEnZona;
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
        ConjPrior<Jugador>::Iterador itJugadoresEnZona;
    };

    struct EstadoPokemon {
        Nat cantTotalEspecie;
        Conj<Coordenada> posiciones;
    };

};


#endif //ALGO2_TP3_POKEMON_GO_JUEGO_H
