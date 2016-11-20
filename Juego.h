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

    Juego(Mapa &m);
    ~Juego();

    Juego& crearJuego(Mapa &mapa);
    void agregarPokemon(Pokemon &p, Coordenada &coor);
    void agregarJugador(Jugador &j);
    void conectarse(Jugador &j, Coordenada &coor);
    void desconectarse(Jugador &j);
    void moverse(Jugador &j, Coordenada &coor);
    const Mapa& mapa() const;
    const Conj<Jugador>::Iterador& jugadores() const;
    const bool& estaConectado(const Jugador &j) const;
    const Nat& sanciones(const Jugador &j) const;
    const Coordenada& posicion(const Jugador &j) const;
    const DiccString<Nat>::Iterador& pokemons() const;
    const Conj<Jugador>& expulsados() const;
    const Conj<Coordenada>& posConPokemons() const;
    const Pokemon& pokemonEnPos(const Coordenada &coor) const;
    const Nat& cantMovimientosParaCaptura(const Coordenada &coor) const;
    const bool& puedoAgregarPokemon(const Coordenada &coor) const;
    const bool& hayPokemonCercano(const Coordenada &coor) const;
    const Coordenada& posPokemonCercano(const Coordenada &coor) const;
    const std::vector<Jugador>& entrenadoresPosibles(const Coordenada& coor, const std::vector<Jugador> &js) const;
    const Nat& indiceRareza(const Pokemon &p) const;
    const Nat& cantPokemonsTotales() const;
    const Nat& cantMismaEspecie(const Pokemon &p) const;

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
        ConjPrior jugadoresEnZona;
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
        ConjPrior::Iterador itJugadoresEnZona;
    };

    struct EstadoPokemon {
        Nat cantTotalEspecie;
        Conj<Coordenada> posiciones;
    };

};

#endif //ALGO2_TP3_POKEMON_GO_JUEGO_H
