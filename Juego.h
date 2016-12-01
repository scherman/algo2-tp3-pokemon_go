
#ifndef ALGO2_TP3_POKEMON_GO_JUEGO_H
#define ALGO2_TP3_POKEMON_GO_JUEGO_H

#include <vector>
#include "aed2.h"
#include "DiccString.h"
#include "TiposJuego.h"
#include "Mapa.h"
#include "ConjPrior.h"
#include "Coordenadatp3.h"
//typedef Coordenada Coordenadatp3 ;

using namespace aed2;
class Juego {

public:

    Juego(Mapa &m);//hecho
    ~Juego();
    void agregarPokemon(const Pokemon &p,const Coordenadatp3 &coor);
    Juego& crearJuego(Mapa &mapa);
    Jugador agregarJugador();
    void conectarse(const Jugador &j,const Coordenadatp3 &coor);
    void desconectarse(const Jugador &j);
    void moverse(const Jugador &j, const Coordenadatp3 &coor);
    const Mapa& mapa() const;//hecho
     Conj<Jugador>::const_Iterador jugadores() const;
     bool estaConectado(const Jugador &j) const;
     Nat sanciones(const Jugador &j) const;
     Coordenadatp3 posicion(const Jugador &j) const;
     const DiccString<Nat>::const_itDiccString  pokemons(const Jugador &j) const ;
    const Conj<Jugador>& expulsados() const;
    const Conj<Coordenadatp3>& posConPokemons() const;
     Pokemon pokemonEnPos(const Coordenadatp3 &coor) const;//hecho
     Nat cantMovimientosParaCaptura(const Coordenadatp3 &coor) const;//hecho
     bool puedoAgregarPokemon(const Coordenadatp3 &coor) const;
     bool hayPokemonCercano(const Coordenadatp3 &coor) const;
     Coordenadatp3 posPokemonCercano(const Coordenadatp3 &coor) const;
     const Conj<Jugador> entrenadoresPosibles(const Coordenadatp3& coor) const;
     Nat indiceRareza(const Pokemon &p) const;
     Nat cantPokemonsTotales() const;
     Nat cantMismaEspecie(const Pokemon &p) const;
    const Conj<Coordenadatp3>& posicionesAledanias(const Coordenadatp3 &coor) const;

private:

    struct Parcela;
    struct EstadoJugador;
    struct EstadoPokemon;

    Vector<Vector<Parcela > > _mapa;
    Vector<EstadoJugador> _jugadores;
    DiccString<EstadoPokemon> _pokemones;
    Conj<Coordenadatp3> _posicionesPokemons;
    Nat _cantTotalPokemones;
    Conj<Jugador> _jugadoresActivos;
    Mapa elmap ;
    Conj<Jugador> expuls;

    struct Parcela {
        bool definida;
        Vector<Vector<bool> > conexiones;
        bool hayPokemon;
        Pokemon pokemon;
        Conj<Coordenadatp3>::Iterador itPosicionesPokemon;
        Conj<Jugador> jugadoresEnPosicion;
        ConjPrior jugadoresEnZona;
        Nat cantMovimientos;
        Conj<Coordenadatp3> posAledanias;
        Parcela(){
        definida = false;
        hayPokemon = false;
        pokemon = "";
        cantMovimientos = 0;
        }
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
        Conj<Jugador>::Iterador itJugadoresPosicion;//agregado
    };

    struct EstadoPokemon {
        Nat cantTotalEspecie;
        Conj<Coordenadatp3> posiciones;
        bool operator == (const EstadoPokemon& b) {return (cantTotalEspecie == b.cantTotalEspecie) && (posiciones == b.posiciones);}
    };

};

#endif //ALGO2_TP3_POKEMON_GO_JUEGO_H
