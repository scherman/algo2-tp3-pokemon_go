#include "Juego.h"

const Nat& maxLat(const Mapa &m);
const Nat& maxLong(const Mapa &m);

Juego::Juego(Mapa &m) {
    Nat mLat = maxLat(m);
    Nat mLong = maxLong(m);
    
}

Juego::~Juego() {

}

Juego &Juego::crearJuego(Mapa &mapa) {

}

void Juego::agregarPokemon(Pokemon &p, Coordenada &coor) {

}

void Juego::agregarJugador(Jugador &j) {

}

void Juego::conectarse(Jugador &j, Coordenada &coor) {

}

void Juego::desconectarse(Jugador &j) {

}

void Juego::moverse(Jugador &j, Coordenada &coor) {

}

const Mapa &Juego::mapa() const {
}

const Conj<Jugador>::Iterador &Juego::jugadores() const {
}

const bool &Juego::estaConectado(const Jugador &j) const {
}

const Nat &Juego::sanciones(const Jugador &j) const {
}

const Coordenada &Juego::posicion(const Jugador &j) const {
}

const DiccString<Nat>::Iterador &Juego::pokemons() const {
}

const Conj<Jugador> &Juego::expulsados() const {
}

const Conj<Coordenada> &Juego::posConPokemons() const {
}

const Pokemon &Juego::pokemonEnPos(const Coordenada &coor) const {
}

const Nat &Juego::cantMovimientosParaCaptura(const Coordenada &coor) const {
}

const bool &Juego::puedoAgregarPokemon(const Coordenada &coor) const {
}

const bool &Juego::hayPokemonCercano(const Coordenada &coor) const {
}

const Coordenada &Juego::posPokemonCercano(const Coordenada &coor) const {
}

const std::vector<Jugador> &Juego::entrenadoresPosibles(const Coordenada &coor, const std::vector<Jugador> &js) const {
}

const Nat &Juego::indiceRareza(const Pokemon &p) const {
}

const Nat &Juego::cantPokemonsTotales() const {
}

const Nat &Juego::cantMismaEspecie(const Pokemon &p) const {
}