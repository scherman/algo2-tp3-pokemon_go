#include "Juego.h"


const Nat& maxLat(const Mapa &m);
const Nat& maxLong(const Mapa &m);
/*
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

Jugador Juego::agregarJugador(Jugador &j) {
    EstadoJugador estadoJugadorNoConectado = {true, false, 0, Coordenada(0,0), Vacio(),0, CrearIt(Conj()), crearIt(ConjPrior())};
    AgregarAtras(_jugadores, estadoJugadorNoConectado);
    Iterador it = AgregarRapido(_jugadoresActivos, Longitud(_jugadores));
    (_jugadores)[Longitud(_jugadores)].itJugadoresActivos = it;
    return Longitud(_jugadores)+1;
}

void Juego::conectarse(Jugador &j, Coordenada &coor) {
    (_jugadores)[j].conectado = true;
    (_jugadores)[j].recienCreado = false;
    (_jugadores)[j].posicion = coor;
    if(hayPokemonCercano(coor)){
        Coordenada posPokemon = posPokemonCercano(coor);
        (_mapa)[Latitud(posPokemon)][Longitud(posPokemon)].cantMovimientos = 0;
        (_mapa)[Latitud(posPokemon)][Longitud(posPokemon)].jugadoresEnZona[j].itJugadoresEnZona
        = Agregar((_mapa)[Latitud(posPokemon)][Longitud(posPokemon)].jugadoresEnZona,(_jugadores)[j].cantCapturados,j);
    }
}
//Agregar no devuelve un Iterador...

void Juego::desconectarse(Jugador &j) {
    (_jugadores)[j].conectado = false;
    if(hayPokemonCercano(_jugadores[j].posicion)){
        EliminarSiguienteElem(_jugadores[j].itJugadoresEnZona);
        (_jugadores)[j].itJugadoresEnZona = CrearIt(ConjPrior());
    }
}

void Juego::moverse(Jugador &j, Coordenada &coor) {

}

const Mapa &Juego::mapa() const {
    Vector<Vector<Parcela>> Mapa = Vector(Vector());
    Nat i = 0;
    Nat j = 0;
    while(i < Longitud(_mapa)){
        while(j < Longitud(_mapa)){
            if(_mapa[i][j].definida == true){
                AgregarRapido(Mapa, Coordenada(i,j));
            }
            j++;
        }
        i++;
    }
}

const Conj<Jugador>::Iterador &Juego::jugadores() const {
    return CrearIt(_jugadoresActivos);
}

const bool &Juego::estaConectado(const Jugador &j) const {
    return _jugadores[j].conectado;
}

const Nat &Juego::sanciones(const Jugador &j) const {
    return _jugadores[j].sanciones;
}

const Coordenada &Juego::posicion(const Jugador &j) const {
    return _jugadores[j].posicion;
}

const DiccString<Nat>::Iterador &Juego::pokemons(const Jugador &j) const {
    return CrearIt(_jugadores[j].capturados);
}

const Conj<Jugador> &Juego::expulsados() const {
    Conj<Nat> res = Conj();
    Nat i = 0;
    while(i < Longitud(_jugadores)){
        if(_jugadores[i].sanciones == 5){
            AgregarRapido(res, _jugadores[i]);
        }
        i++;
    }
    return res;
}

const Conj<Coordenada> &Juego::posConPokemons() const {
    return _posicionesPokemons;
}

const Pokemon &Juego::pokemonEnPos(const Coordenada &coor) const {
    return _mapa[Latitud(coor)][Longitud(coor)].pokemon;
}

const Nat &Juego::cantMovimientosParaCaptura(const Coordenada &coor) const {
    return _mapa[Latitud(coor)][Longitud(coor)].cantMovimientos;
}

const bool &Juego::puedoAgregarPokemon(const Coordenada &coor) const {
    bool res = false;
    if(_mapa[Latitud(coor)][Longitud(coor)].definido){
        if(_mapa[Latitud(coor)][Longitud(coor)].pokemon == ""){
            res = true;
        }
    }
    return res;
}

const bool &Juego::hayPokemonCercano(const Coordenada &coor) const {
    bool res = false;
    Conj<Coordenada>::Iterador it = CrearIt(posicionesAledañas(coor));
    while(haySiguiente(it)){
        if(_mapa[Latitud(Siguiente(it))][Longitud(Siguiente(it))].pokemon != ""){
            return true;
        }
        else{
            Avanzar(it);
        }
    }
    return res;
}

const Coordenada &Juego::posPokemonCercano(const Coordenada &coor) const {
//requiere que haya un pokemonCercano
    Conj<Coordenada>::Iterador it = CrearIt(posicionesAledañas(coor));
    while(haySiguiente(it)){
        if(_mapa[Latitud(Siguiente(it))][Longitud(Siguiente(it))].pokemon != ""){
            return Siguiente(it);
        }
        else{
            Avanzar(it);
        }
    }
}

const std::vector<Jugador> &Juego::entrenadoresPosibles(const Coordenada &coor, const std::vector<Jugador> &js) const {
    //en el tp usamos un Iterador para js pero ahora es un vector...Antes usabamos un conjunto. Tendriamos que usar Conj.h?
    Vector<Jugador> res = Vector();
    while()
}

const Nat &Juego::indiceRareza(const Pokemon &p) const {
}

const Nat &Juego::cantPokemonsTotales() const {
}

const Nat &Juego::cantMismaEspecie(const Pokemon &p) const {
}

const Conj<Coordenada> &Juego::posicionesAledañas(const Coordenada &coor) const{

}
 */