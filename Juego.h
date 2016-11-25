//
// Created by jscherman on 19/11/16.
//

#ifndef ALGO2_TP3_POKEMON_GO_JUEGO_H
#define ALGO2_TP3_POKEMON_GO_JUEGO_H

#include "Vector.h"
#include "TiposBasicos.h"
#include "DiccString.h"
#include "TiposJuego.h"
#include "Conj.h"
#include "Mapa.h"
#include "ConjPrior.h"

using namespace aed2;

class Juego {

public:

    Juego(Mapa &m);
    ~Juego();

    Juego& crearJuego(Mapa &mapa);
    void agregarPokemon(Pokemon &p, Coordenada &coor);
    Jugador agregarJugador();
    //en el disenio no nos pasan ningun parametro. El nuevo jugador sera el largo de _jugadores
    //Jugador agregarJugador(Jugador &j);
    void conectarse(Jugador &j, Coordenada &coor);
    void desconectarse(Jugador &j);
    void moverse(Jugador &j, Coordenada &coor);
    const Mapa& mapa() const;
    const Conj<Jugador>::const_Iterador& jugadores() const;
    //no me dejaba devolver Iterador, creo que no hay problema de devolver const_Iterador...
    //const Conj<Jugador>::Iterador& jugadores() const;
    const bool& estaConectado(const Jugador &j) const;
    const Nat& sanciones(const Jugador &j) const;
    const Coordenada& posicion(const Jugador &j) const;
    const DiccString<String>::Iterador& pokemons(const Jugador &j) const;
    const Conj<Jugador>& expulsados() const;
    const Conj<Coordenada>& posConPokemons() const;
    const Pokemon& pokemonEnPos(const Coordenada &coor) const;
    const Nat& cantMovimientosParaCaptura(const Coordenada &coor) const;
    const bool& puedoAgregarPokemon(const Coordenada &coor) const;
    const bool& hayPokemonCercano(const Coordenada &coor) const;
    const Coordenada& posPokemonCercano(const Coordenada &coor) const;
    const Vector<Jugador>& entrenadoresPosibles(const Coordenada& coor, const Vector<Jugador> &js) const;
    const Nat& indiceRareza(const Pokemon &p) const;
    const Nat& cantPokemonsTotales() const;
    const Nat& cantMismaEspecie(const Pokemon &p) const;
    const Conj<Coordenada>& posicionesAledañas(const Coordenada &coor) const;

private:

    struct Parcela;
    struct EstadoJugador;
    struct EstadoPokemon;

    Vector<Vector<Parcela>> _mapa;
    Vector<EstadoJugador> _jugadores;
    DiccString<EstadoPokemon> _pokemones;
    Conj<Coordenada> _posicionesPokemons;
    Nat _cantTotalPokemones;
    Conj<Jugador> _jugadoresActivos;

    struct Parcela {
        bool definida;
        Vector<Vector<bool>> conexiones;
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
        DiccString<String> capturados;
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
