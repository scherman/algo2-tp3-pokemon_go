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

Jugador Juego::agregarJugador() {
    EstadoJugador estadoJugadorNoConectado = {true, false, 0, Coordenada(0,0), DiccString(),0, Conj().CrearIt(), ConjPrior().CrearIt()};
    _jugadores.AgregarAtras(estadoJugadorNoConectado);
    Conj<Jugador>::Iterador it = _jugadoresActivos.AgregarRapido(_jugadores.Longitud());
    _jugadores[_jugadores.Longitud()].itJugadoresActivos = it;
    return _jugadores.Longitud()+1;
}

void Juego::conectarse(Jugador &j, Coordenada &coor) {
    (_jugadores)[j].conectado = true;
    (_jugadores)[j].recienCreado = false;
    (_jugadores)[j].posicion = coor;
    if(hayPokemonCercano(coor)){
        Coordenada posPokemon = posPokemonCercano(coor);
        (_mapa)[posPokemon.Latitud()][posPokemon.Longitud()].cantMovimientos = 0;
        (_jugadores)[j].itJugadoresEnZona
        = (_mapa)[posPokemon.Latitud()][posPokemon.Longitud()].jugadoresEnZona.Agregar(_jugadores[j].cantCapturados,j);
    }
}

void Juego::desconectarse(Jugador &j) {
    _jugadores[j].conectado = false;
    if(hayPokemonCercano(_jugadores[j].posicion)){
        _jugadores[j].itJugadoresEnZona.EliminarSiguienteElem();
        _jugadores[j].itJugadoresEnZona = ConjPrior().CrearIt();
    }
}

void Juego::moverse(Jugador &j, Coordenada &coor) {

}

const Mapa &Juego::mapa() const {
    //arreglar para cuando este hecho mapa
    Mapa nuevo = Mapa();
    Nat i = 0;
    Nat j = 0;
    while(i < _mapa.Longitud()){
        while(j < _mapa.Longitud()){
            if(_mapa[i][j].definida == true){
                nuevo.agregarCoor(Coordenada(i,j));
            }
            j++;
        }
        i++;
    }
}

const Conj<Jugador>::const_Iterador &Juego::jugadores() const {
    return _jugadoresActivos.CrearIt();
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

const DiccString<String>::itDiccString &Juego::pokemons(const Jugador &j) const {
    return _jugadores[j].capturados.CrearIt();
}

const Conj<Jugador> &Juego::expulsados() const {
    Conj<Nat> res = Conj();
    Nat i = 0;
    while(i < _jugadores.Longitud()){
        if(_jugadores[i].sanciones == 5){
            res.AgregarRapido(i);
        }
        i++;
    }
    return res;
}

const Conj<Coordenada> &Juego::posConPokemons() const {
    return _posicionesPokemons;
}

const Pokemon &Juego::pokemonEnPos(const Coordenada &coor) const {
    return _mapa[coor.Latitud()][coor.Longitud()].pokemon;
}

const Nat &Juego::cantMovimientosParaCaptura(const Coordenada &coor) const {
    return _mapa[coor.Latitud()][coor.Longitud()].cantMovimientos;
}

const bool &Juego::puedoAgregarPokemon(const Coordenada &coor) const {
    bool res = false;
    if(_mapa[coor.Latitud()][coor.Longitud()].definida){
        if(_mapa[coor.Latitud()][coor.Longitud()].pokemon == ""){
            res = true;
        }
    }
    return res;
}

const bool &Juego::hayPokemonCercano(const Coordenada &coor) const {
    bool res = false;
    //hay problema si uso const_Iterador?
    Conj<Coordenada>::const_Iterador it = posicionesAledañas(coor).CrearIt();
    while(it.HaySiguiente()){
        if(_mapa[(it.Siguiente()).Latitud()][(it.Siguiente()).Longitud()].pokemon != ""){
            return true;
        }
        else{
            it.Avanzar();
        }
    }
    return res;
}

const Coordenada &Juego::posPokemonCercano(const Coordenada &coor) const {
//requiere que haya un pokemonCercano
    Conj<Coordenada>::const_Iterador it = posicionesAledañas(coor).CrearIt();
    while(it.HaySiguiente()){
        if(_mapa[it.Siguiente().Latitud()][it.Siguiente().Longitud()].pokemon != ""){
            return it.Siguiente();
        }
        else{
            it.Avanzar();
        }
    }
}
/*
const Vector<Jugador> &Juego::entrenadoresPosibles(const Coordenada &coor, const Vector<Jugador> &js) const {
    //en el tp usamos un Iterador para js pero ahora es un vector...Antes usabamos un conjunto. Tendriamos que usar Conj.h?
    Vector<Jugador> res = Vector();
    while()
}
*/
const Nat &Juego::indiceRareza(const Pokemon &p) const {
}

const Nat &Juego::cantPokemonsTotales() const {
}

const Nat &Juego::cantMismaEspecie(const Pokemon &p) const {
}

const Conj<Coordenada> &Juego::posicionesAledañas(const Coordenada &coor) const{

}
