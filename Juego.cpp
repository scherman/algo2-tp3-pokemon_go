
#include "Juego.h"


Nat maxLat(const Mapa &m){
Conj<Coordenadatp3>::const_Iterador it = m.coordenadas().CrearIt();
Nat masAlto = 0;
while(it.HaySiguiente()){
    if (masAlto < it.Siguiente().Latitud())
        masAlto = it.Siguiente().Latitud();
    it.Avanzar();
}
return masAlto;
}
Nat maxLong(const Mapa &m){
Conj<Coordenadatp3>::const_Iterador it = m.coordenadas().CrearIt();
Nat masAncho = 0;
while(it.HaySiguiente()){
    if (masAncho < it.Siguiente().Longitud())
        masAncho = it.Siguiente().Longitud();
    it.Avanzar();
}
return masAncho;
}

Juego::Juego(Mapa &m) {
    Nat mLat = maxLat(m);
    Nat mLong = maxLong(m);
    Nat lat = 0;
    Nat lon = 0;
    Vector<Vector<bool> > caminos;
    while(lat <= mLat){ //creamos matriz caminos de false
        Vector<bool> filaCamino;
        lon = 0;
        while(lon <= mLong){
            filaCamino.AgregarAtras(false);
            lon++;
        }
        caminos.AgregarAtras(filaCamino);
        lat++;
    }
    lat = 0;
    lon = 0;
    while(lat <= mLat){ //definimos en mapa de juego coordenadas validas
        Vector<Parcela> fila;
        lon = 0;
        while(lon <= mLong){
            Parcela parcelaNoDef ;
            if(m.posExistente(Coordenadatp3(lat,lon))){                
                parcelaNoDef.conexiones = caminos;
                parcelaNoDef.definida = true;
                Conj<Coordenadatp3>::const_Iterador itDos = m.coordenadas().CrearIt();
                while(itDos.HaySiguiente()){
                    if (m.hayCamino(Coordenadatp3(lat,lon),itDos.Siguiente())){
                       parcelaNoDef.conexiones[itDos.Siguiente().Latitud()][itDos.Siguiente().Longitud()] = true;
                    }
                itDos.Avanzar();
                }
                fila.AgregarAtras(parcelaNoDef);
            } else {
                fila.AgregarAtras(parcelaNoDef);
            }
            lon++;
        }
        _mapa.AgregarAtras(fila);
        lat++;
    }

    _cantTotalPokemones = 0;
}

Juego::~Juego() {

}



void Juego::agregarPokemon(Pokemon &p,Coordenadatp3 &coor) {
    // Agrego pokemon en j.pokemones
    EstadoPokemon estadoPokemon = {0, Conj<Coordenadatp3>()};
    if (_pokemones.Definido(p)) {
        estadoPokemon = _pokemones.Significado(p);
    }
    Conj<Coordenadatp3>::Iterador itPokemones = estadoPokemon.posiciones.AgregarRapido(coor);
    estadoPokemon.cantTotalEspecie++;
    _pokemones.DefinirRapido(p, estadoPokemon);

    // Agrego pokemon en j.posicionesPokemones
    Conj<Coordenadatp3>::Iterador itPosicionesPokemones = _posicionesPokemons.AgregarRapido(coor);

    // Agrego pokemon en j.mapa
    Parcela parcela = _mapa[coor.Latitud()][coor.Longitud()];
    parcela.hayPokemon = true;
    parcela.pokemon = p;
    parcela.itPosicionesPokemon = itPosicionesPokemones;
    Conj<Coordenadatp3>::const_Iterador posicionesEnZona = posicionesAledanias(coor).CrearIt();
    while (posicionesEnZona.HaySiguiente()) {
        Coordenadatp3 actual = posicionesEnZona.Siguiente();
        Conj<Jugador>::Iterador itJugadoresEnPosicion = _mapa[actual.Latitud()][actual.Longitud()].jugadoresEnPosicion.CrearIt();
        while (itJugadoresEnPosicion.HaySiguiente()) {
            Jugador jugador = itJugadoresEnPosicion.Siguiente();
            ConjPrior::Iterador itJugadoresEnZona = parcela.jugadoresEnZona.Agregar(_jugadores[jugador].cantCapturados, jugador);
            _jugadores[jugador].itJugadoresEnZona = itJugadoresEnZona;
            itJugadoresEnPosicion.Avanzar();
        }
        posicionesEnZona.Avanzar();
    }
    parcela.cantMovimientos = 0;

    // Sumo 1 en j.cantTotalPokemones
    _cantTotalPokemones++;
}

Jugador Juego::agregarJugador() {
    DiccString<Nat> vacio;
    Conj<Jugador>::Iterador itConj;
    ConjPrior::Iterador itConjPrior;
    EstadoJugador estadoJugadorNoConectado = {true, false, 0, Coordenadatp3(0,0), vacio, 0, itConj, itConjPrior};
    _jugadores.AgregarAtras(estadoJugadorNoConectado);
    Conj<Jugador>::Iterador it = _jugadoresActivos.AgregarRapido(_jugadores.Longitud());
    _jugadores[_jugadores.Longitud()].itJugadoresActivos = it;
    return _jugadores.Longitud()+1;
}

void Juego::conectarse(Jugador &j,Coordenadatp3 &coor) {
    (_jugadores)[j].conectado = true;
    (_jugadores)[j].recienCreado = false;
    (_jugadores)[j].posicion = coor;
    if(hayPokemonCercano(coor)){
        Coordenadatp3 posPokemon = posPokemonCercano(coor);
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

void Juego::moverse(Jugador &j,Coordenadatp3 &coor) {

}

const Mapa &Juego::mapa() const {
    Mapa* m = new Mapa;
    Nat i = 0;
    Nat j = 0;
    while(i < _mapa.Longitud()){//i itera sobre las columnas de mapa
        j = 0;
        while(j < _mapa[i].Longitud()){
            if(_mapa[i][j].definida == true){
                (*m).agregarCoor( Coordenadatp3(i,j));
            }
            j++;
        }
        i++;
    }
    return *m;
}

const Conj<Jugador>::const_Iterador Juego::jugadores() const {
    return _jugadoresActivos.CrearIt();
}

const bool Juego::estaConectado(const Jugador &j) const {
    return _jugadores[j].conectado;
}

const Nat Juego::sanciones(const Jugador &j) const {
    return _jugadores[j].sanciones;
}

const Coordenadatp3 &Juego::posicion(const Jugador &j) const {
    return _jugadores[j].posicion;
}

const DiccString<Nat>::const_itDiccString Juego::pokemons(const Jugador &j) const {
    return _jugadores[j].capturados.CrearItConst();
}

const Conj<Jugador> Juego::expulsados() const {
    Conj<Nat> res;
    Nat i = 0;
    while(i < _jugadores.Longitud()){
        if(_jugadores[i].sanciones == 5){
            res.AgregarRapido(i);
        }
        i++;
    }
    return res;
}

const Conj<Coordenadatp3> &Juego::posConPokemons() const {
    return _posicionesPokemons;
}

const Pokemon &Juego::pokemonEnPos(const Coordenadatp3 &coor) const {
    return _mapa[coor.Latitud()][coor.Longitud()].pokemon;
}

const Nat Juego::cantMovimientosParaCaptura(const Coordenadatp3 &coor) const {
    return _mapa[coor.Latitud()][coor.Longitud()].cantMovimientos;
}

const bool Juego::puedoAgregarPokemon(const Coordenadatp3 &coor) const {
    bool res = false;
    if(_mapa[coor.Latitud()][coor.Longitud()].definida){
        if(_mapa[coor.Latitud()][coor.Longitud()].pokemon == ""){
            res = true;
        }
    }

    return res;
}

const bool Juego::hayPokemonCercano(const Coordenadatp3 &coor) const {
    //hay problema si uso const_Iterador?
    Conj<Coordenadatp3>::const_Iterador it = posicionesAledanias(coor).CrearIt();
    while(it.HaySiguiente()){
        if(_mapa[(it.Siguiente()).Latitud()][(it.Siguiente()).Longitud()].pokemon != ""){
            return true;
        }
        else{
            it.Avanzar();
        }
    }
    return false;
}

const Coordenadatp3 &Juego::posPokemonCercano(const Coordenadatp3 &coor) const {
//requiere que haya un pokemonCercano
    Conj<Coordenadatp3>::const_Iterador it = posicionesAledanias(coor).CrearIt();
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
const Nat Juego::indiceRareza(const Pokemon &p) const {
    EstadoPokemon estadoPokemon = _pokemones.Significado(p);
    return 100 - (estadoPokemon.cantTotalEspecie * 100) / _cantTotalPokemones;
}

const Nat Juego::cantPokemonsTotales() const {
    return _cantTotalPokemones;
}

const Nat Juego::cantMismaEspecie(const Pokemon &p) const {
    EstadoPokemon estadoPokemon = _pokemones.Significado(p);
    return estadoPokemon.cantTotalEspecie;
}


const Conj<Coordenadatp3> &Juego::posicionesAledanias(const Coordenadatp3 &coor) const{
Conj<Coordenadatp3> * nuevo = new Conj<Coordenadatp3>;
int lataux = coor.Latitud();
int lonaux = coor.Longitud();
int i = lataux-2;
while(i <= lataux+2){
    //Nat clong = coor.Longitud();
    int j = lonaux-2;
    while (j <= lonaux+2){
        if(i >= 0 && i < _mapa.Longitud() && j >= 0 && j < _mapa[i].Longitud()){
            Coordenadatp3 nueva(i,j);
            if (mapa().posExistente(nueva) && coor.DistEuclidea(nueva) <= 2)
                (*nuevo).AgregarRapido(nueva);
        }
        j++;
    }
    i++;
}
return *nuevo;
}

