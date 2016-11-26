//
// Created by jscherman on 19/11/16.
//

#ifndef ALGO2_TP3_POKEMON_GO_JUEGO_H
#define ALGO2_TP3_POKEMON_GO_JUEGO_H

#include "aed2/Vector.h"
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
    void agregarPokemon(Pokemon &p, Coordenadatp3 &coor);
    Jugador agregarJugador();
    //en el disenio no nos pasan ningun parametro. El nuevo jugador sera el largo de _jugadores
    //Jugador agregarJugador(Jugador &j);
    void conectarse(Jugador &j, Coordenadatp3 &coor);
    void desconectarse(Jugador &j);
    void moverse(Jugador &j, Coordenadatp3 &coor);
    const Mapa& mapa() const;
    const Conj<Jugador>::const_Iterador jugadores() const;
    //no me dejaba devolver Iterador, creo que no hay problema de devolver const_Iterador...
    //const Conj<Jugador>::Iterador& jugadores() const;
    const bool estaConectado(const Jugador &j) const;
    const Nat sanciones(const Jugador &j) const;
    const Coordenadatp3& posicion(const Jugador &j) const;
    const DiccString<Nat>::const_itDiccString pokemons(const Jugador &j) const;
    const Conj<Jugador> expulsados() const;
    const Conj<Coordenadatp3>& posConPokemons() const;
    const Pokemon& pokemonEnPos(const Coordenadatp3 &coor) const;
    const Nat cantMovimientosParaCaptura(const Coordenadatp3 &coor) const;
    const bool puedoAgregarPokemon(const Coordenadatp3 &coor) const;
    const bool hayPokemonCercano(const Coordenadatp3 &coor) const;
    const Coordenadatp3& posPokemonCercano(const Coordenadatp3 &coor) const;
    const Vector<Jugador>& entrenadoresPosibles(const Coordenadatp3& coor, const Vector<Jugador> &js) const;
    const Nat indiceRareza(const Pokemon &p) const;
    const Nat cantPokemonsTotales() const;
    const Nat cantMismaEspecie(const Pokemon &p) const;
    const Conj<Coordenadatp3>& posicionesAledanias(const Coordenadatp3 &coor) const;

private:

    struct Parcela;
    struct EstadoJugador;
    struct EstadoPokemon;

    Vector<Vector<Parcela> > _mapa;
    Vector<EstadoJugador> _jugadores;
    DiccString<EstadoPokemon> _pokemones;
    Conj<Coordenadatp3> _posicionesPokemons;
    Nat _cantTotalPokemones;
    Conj<Jugador> _jugadoresActivos;

    struct Parcela {
        bool definida;
        Vector<Vector<bool> > conexiones;
        bool hayPokemon;
        Pokemon pokemon;
        Conj<Coordenadatp3>::Iterador itPosicionesPokemon;
        Conj<Jugador> jugadoresEnPosicion;
        ConjPrior jugadoresEnZona;
        Nat cantMovimientos;
    };

    struct EstadoJugador{
        bool recienCreado;
        bool conectado;
        Nat sanciones;
        Coordenadatp3 posicion;
        DiccString<Nat> capturados;
        Nat cantCapturados;
        Conj<Jugador>::Iterador itJugadoresActivos;
        ConjPrior::Iterador itJugadoresEnZona;
    };

    struct EstadoPokemon {
        Nat cantTotalEspecie;
        Conj<Coordenadatp3> posiciones;

        bool operator == (const EstadoPokemon& b) {return (cantTotalEspecie == b.cantTotalEspecie) && (posiciones == b.posiciones);}


    };

};

#endif //ALGO2_TP3_POKEMON_GO_JUEGO_H
