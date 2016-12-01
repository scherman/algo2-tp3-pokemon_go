#include "Driver.h"

// Instanciar un mapa y un juego 

Driver::Driver(const Conj<Coordenada> &cs) : _juego(_mapa) {
    for (Conj<Coordenada>::const_Iterador it = cs.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
        Coordenada actual = it.Siguiente();
        Coordenadatp3 coor = Coordenadatp3(actual.latitud(), actual.longitud());
        _mapa.agregarCoor(coor);
    }
}

Driver::~Driver() {
}

void Driver::agregarPokemon(const Pokemon &p, const Coordenada &c) {
    Coordenadatp3 coor(c.latitud(), c.longitud());
    _juego.agregarPokemon(p, coor);
}


Jugador Driver::agregarJugador() {
    return _juego.agregarJugador();
}

void Driver::conectarse(const Jugador &j, const Coordenada &c) {
    Coordenadatp3 coor(c.latitud(), c.longitud());
    _juego.conectarse(j, coor);
}

void Driver::desconectarse(const Jugador &j) {
    _juego.desconectarse(j);
}

void Driver::moverse(const Jugador &j, const Coordenada &c) {
    Coordenadatp3 coor(c.latitud(), c.longitud());
    _juego.moverse(j, coor);
}

Conj<Coordenada> Driver::mapa() const {
    Conj<Coordenada> conj;
    for (Conj<Coordenadatp3>::const_Iterador it = _mapa.coordenadas().CrearIt(); it.HaySiguiente(); it.Avanzar()) {
        Coordenada coor(it.Siguiente().Latitud(), it.Siguiente().Longitud());
        conj.AgregarRapido(coor);
    }
    return conj;
}

bool Driver::hayCamino(const Coordenada &c1, const Coordenada &c2) const {
    Coordenadatp3 coor1(c1.latitud(), c1.longitud());
    Coordenadatp3 coor2(c2.latitud(), c2.longitud());
    return _mapa.hayCamino(coor1, coor2);
}

bool Driver::posExistente(const Coordenada &c) const {
    Coordenadatp3 coor(c.latitud(), c.longitud());
    return _mapa.posExistente(coor);
}

Conj<Jugador> Driver::jugadores() const {
    Conj<Jugador> conj;
    for (Conj<Jugador>::const_Iterador it = _juego.jugadores(); it.HaySiguiente(); it.Avanzar()) {
        conj.AgregarRapido(it.Siguiente());
    }
    return conj;
}

bool Driver::estaConectado(const Jugador &j) const {
    return _juego.estaConectado(j);
}

Nat Driver::sanciones(const Jugador &j) const {
    return _juego.sanciones(j);
}

Coordenada Driver::posicion(const Jugador &j) const {
    Coordenadatp3 coor = _juego.posicion(j);
    return Coordenada(coor.Latitud(), coor.Longitud());
}

Dicc<Pokemon, Nat> Driver::pokemons(const Jugador &j) const {
    Dicc<Pokemon, Nat> pokemons;
    for (DiccString<Nat>::const_itDiccString it = _juego.pokemons(j); it.HaySiguiente(); it.Avanzar()) {
        pokemons.Definir(it.SiguienteClave(), it.SiguienteSignificado());
    }
    return pokemons;
}

Conj<Jugador> Driver::expulsados() const {
    return _juego.expulsados();
}

Conj<Coordenada> Driver::posConPokemons() const {
    Conj<Coordenada> conj;
    for (Conj<Coordenadatp3>::const_Iterador it = _juego.posConPokemons().CrearIt(); it.HaySiguiente(); it.Avanzar()) {
        Coordenadatp3 actual = it.Siguiente();
        Coordenada coor(actual.Latitud(), actual.Longitud());
        conj.AgregarRapido(coor);
    }
    return conj;
}

Pokemon Driver::pokemonEnPos(const Coordenada &c) const {
    Coordenadatp3 coor (c.latitud(), c.longitud());
    return _juego.pokemonEnPos(coor);
}

Nat Driver::cantMovimientosParaCaptura(const Coordenada &c) const {
    Coordenadatp3 coor(c.latitud(), c.longitud());
    return _juego.cantMovimientosParaCaptura(coor);
}

bool Driver::puedoAgregarPokemon(const Coordenada &c) const {
    Coordenadatp3 coor(c.latitud(), c.longitud());
    return _juego.puedoAgregarPokemon(coor);
}

bool Driver::hayPokemonCercano(const Coordenada &c) const {
    Coordenadatp3 coor(c.latitud(), c.longitud());
    return _juego.hayPokemonCercano(coor);
}

Coordenada Driver::posPokemonCercano(const Coordenada &c) const {
    Coordenadatp3 coor(c.latitud(), c.longitud());
    Coordenadatp3 pos = _juego.posPokemonCercano(coor);
    return Coordenada(pos.Latitud(), pos.Longitud());
}

Conj<Jugador> Driver::entrenadoresPosibles(const Coordenada &c) const {
    Coordenadatp3 coor(c.latitud(), c.longitud());
    return _juego.entrenadoresPosibles(coor);
}

Nat Driver::indiceRareza(const Pokemon &p) const {
    return _juego.indiceRareza(p);
}

Nat Driver::cantPokemonsTotales() const {
    return _juego.cantPokemonsTotales();
}

Nat Driver::cantMismaEspecie(const Pokemon &p) const {
    return _juego.cantMismaEspecie(p);
}