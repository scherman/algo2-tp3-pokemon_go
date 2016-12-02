#include "Juego.h"

using namespace std;
using namespace aed2;
//typedef Coordenada Coordenadatp3 ;
//algoritmos:
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
/**/
Juego::Juego(Mapa &m): elmap(m) {
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
                //Parcela* parcelaNoDef = new Parcela;
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

     lat = 0;
     lon = 0;
     while(lat <= mLat){
        lon = 0;
        while(lon <= mLong){
    //posiciones aledanias
              int i = lat-2;
              int latmax = lat+2;//++
              int lonmax = lon+2;//++
              while(i <= latmax){
              //Nat clong = coor.Longitud();
              int j = lon-2;
                while (j <= lonmax){
                   if(i >= 0 && i < _mapa.Longitud() && j >= 0 && j < _mapa[i].Longitud()){
                     Coordenadatp3  nueva(i,j);
                     if (m.posExistente(nueva) && Coordenadatp3(lat,lon).DistEuclidea(nueva) <= 4)
                        _mapa[lat][lon].posAledanias.AgregarRapido(nueva);
                   }
                   j++;
                   }
                i++;
                }

            lon++;
        }
      lat++;
    }

    _cantTotalPokemones = 0;
}

Juego::~Juego() {

}



void Juego::agregarPokemon(const Pokemon &p,const Coordenadatp3 &coor) { //++ agregar condicional en funcion definido de
    //diccstring ++
    //coor es pos existente en mapa
    // Agrego pokemon en j.pokemones
    EstadoPokemon estadoPokemon = {0, Conj<Coordenadatp3>()};
    if ( _pokemones.Definido(p) ) {
        estadoPokemon = _pokemones.Significado(p);
        _pokemones.Borrar(p);
    }
    /*Conj<Coordenadatp3>::Iterador itPokemones =*/ estadoPokemon.posiciones.AgregarRapido(coor);//modificado ++
    estadoPokemon.cantTotalEspecie++;
    _pokemones.DefinirRapido(p, estadoPokemon);//se muere aca estado poke. pedir memoria ++
    // Agrego pokemon en j.posicionesPokemones
    //Conj<Coordenadatp3>::Iterador itPosicionesPokemones = _posicionesPokemons.AgregarRapido(coor);//suprimido ++
    // Agrego pokemon en j.mapa
    //Parcela parcela = _mapa[coor.Latitud()][coor.Longitud()]; //suprimido+
    _mapa[coor.Latitud()][coor.Longitud()].hayPokemon = true; //agregado +
    //parcela.hayPokemon = true; //suprimido +
    //parcela.pokemon = p; //suprimido +
    _mapa[coor.Latitud()][coor.Longitud()].pokemon = p; //agregado +
    //parcela.itPosicionesPokemon = itPosicionesPokemones; //suprimido +
    _mapa[coor.Latitud()][coor.Longitud()].itPosicionesPokemon = _posicionesPokemons.AgregarRapido(coor); // agregado +
    Conj<Coordenadatp3>::const_Iterador posicionesEnZona  = this->posicionesAledanias(coor).CrearIt();
    while (posicionesEnZona.HaySiguiente()) {
        Coordenadatp3 actual = posicionesEnZona.Siguiente();
        Conj<Jugador>::Iterador itJugadoresEnPosicion = _mapa[actual.Latitud()][actual.Longitud()].
        jugadoresEnPosicion.CrearIt();
        while (itJugadoresEnPosicion.HaySiguiente()) {
            Jugador jugador = itJugadoresEnPosicion.Siguiente();
            _jugadores[jugador-1].itJugadoresEnZona = _mapa[coor.Latitud()][coor.Longitud()]
            .jugadoresEnZona.Agregar(_jugadores[jugador-1].cantCapturados, jugador); //modificado +
            itJugadoresEnPosicion.Avanzar();
        }
        posicionesEnZona.Avanzar();
    }
    _mapa[coor.Latitud()][coor.Longitud()].cantMovimientos = 0;
    // Sumo 1 en j.cantTotalPokemones
    _cantTotalPokemones++;
}

Jugador Juego::agregarJugador() {
     DiccString<Nat> vacio;
    Conj<Jugador>::Iterador itConj;
    ConjPrior::Iterador itConjPrior;
    EstadoJugador estadoJugadorNoConectado = {true, false, 0, Coordenadatp3(0,0), vacio, 0, itConj, itConjPrior};
    Nat nuevo = _jugadores.Longitud();
    _jugadores.AgregarAtras(estadoJugadorNoConectado);
    //Conj<Jugador>::Iterador it = _jugadoresActivos.AgregarRapido(_jugadores.Longitud());
    _jugadores[nuevo].itJugadoresActivos = _jugadoresActivos.AgregarRapido(_jugadores.Longitud());//modificado ++
    return _jugadores.Longitud();
}

void Juego::conectarse(const Jugador &j,const Coordenadatp3 &coor) {
    (_jugadores)[j-1].conectado = true;
    (_jugadores)[j-1].recienCreado = false;
    (_jugadores)[j-1].posicion = coor;
    _jugadores[j-1].itJugadoresPosicion = _mapa[coor.Latitud()][coor.Longitud()].jugadoresEnPosicion.AgregarRapido(j);
    if(hayPokemonCercano(coor)){
        Coordenadatp3 posPokemon = posPokemonCercano(coor);
        (_mapa)[posPokemon.Latitud()][posPokemon.Longitud()].cantMovimientos = 0;
        (_jugadores)[j-1].itJugadoresEnZona
        = (_mapa)[posPokemon.Latitud()][posPokemon.Longitud()].jugadoresEnZona.Agregar(_jugadores[j-1].cantCapturados,j);
    }
}
//Agregar no devuelve un Iterador...

void Juego::desconectarse(const Jugador &j) {
    _jugadores[j-1].conectado = false;
    _jugadores[j-1].itJugadoresPosicion.EliminarSiguiente();
    if(hayPokemonCercano(_jugadores[j-1].posicion)){
        _jugadores[j-1].itJugadoresEnZona.EliminarSiguienteElem();
    }
}


void Juego::moverse(const Jugador &j,const Coordenadatp3 &coor) {//agregar condicional if para caso no conectado
	Coordenadatp3 posAnterior = _jugadores[j-1].posicion;
	bool sancionado = false;
	if ((!_mapa[posAnterior.Latitud()][posAnterior.Longitud()].conexiones[coor.Latitud()][coor.Longitud()]) ||
     posAnterior.DistEuclidea(coor) > 100) {//sancionamos
		_jugadores[j-1].sanciones = _jugadores[j-1].sanciones + 1;
		sancionado = true;
		if (_jugadores[j-1].sanciones == 5) {// eliminamos //
			_jugadores[j-1].conectado = false;
           expuls.AgregarRapido(j);
          _jugadores[j-1].itJugadoresPosicion.EliminarSiguiente();//sacamos de parcela
			_cantTotalPokemones = _cantTotalPokemones - _jugadores[j-1].cantCapturados;//  cuidado con resta//
			_jugadores[j-1].cantCapturados = 0;
			Conj<string>::const_Iterador itCapturados = _jugadores[j-1].capturados.Claves().CrearIt();
			while (itCapturados.HaySiguiente())
			{
				string clave = itCapturados.Siguiente();//borramos pokemones de totales
				if (_pokemones.Significado(clave).cantTotalEspecie == _jugadores[j-1].capturados.Significado(clave))
					_pokemones.Borrar(clave);
				else{
                    Nat aux1 = _pokemones.Significado(clave).cantTotalEspecie - _jugadores[j-1].capturados.Significado(clave);
                    EstadoPokemon aux = {aux1, _pokemones.Significado(clave).posiciones};
					_pokemones.Borrar(clave);
                    _pokemones.DefinirRapido(clave, aux);
				}
				itCapturados.Avanzar();
				_jugadores[j-1].capturados.Borrar(clave);
			}
			_jugadores[j-1].itJugadoresActivos.EliminarSiguiente();
			if (/*!eliminadoDeZona &&*/ hayPokemonCercano(posAnterior)){
				_jugadores[j-1].itJugadoresEnZona.EliminarSiguienteElem();
			}
		}
	}
	if (hayPokemonCercano(posAnterior) && !sancionado) {//eliminamos de entorno de poke anterior
		if (!(hayPokemonCercano(coor) && posPokemonCercano(posAnterior) == posPokemonCercano(coor))) {
            if(_jugadores[j-1].itJugadoresEnZona.HaySiguienteElem())
			   _jugadores[j-1].itJugadoresEnZona.EliminarSiguienteElem();
		}
	}

	if(_jugadores[j-1].conectado && !(posAnterior == coor) && !sancionado){//lo cambiamos de parcela
	    _jugadores[j-1].itJugadoresPosicion.EliminarSiguiente();
	    _jugadores[j-1].itJugadoresPosicion = _mapa[coor.Latitud()][coor.Longitud()].jugadoresEnPosicion.AgregarRapido(j);
	}

	Conj<Coordenadatp3>::Iterador it = _posicionesPokemons.CrearIt();
	while (it.HaySiguiente() && _jugadores[j-1].conectado && !sancionado) {
		if( ((hayPokemonCercano(posAnterior) && !(posPokemonCercano(posAnterior) == it.Siguiente())) ||
           !hayPokemonCercano(posAnterior)) && (hayPokemonCercano(coor) &&
                posPokemonCercano(coor) == it.Siguiente()) ){//se agrega a zona de pokemon .caso : cae en entorno de poke
				Coordenadatp3 posPok = posPokemonCercano(coor);
				_jugadores[j-1].itJugadoresEnZona = _mapa[posPok.Latitud()][posPok.Longitud()].
                    jugadoresEnZona.Agregar(_jugadores[j-1].cantCapturados,j);
				_mapa[posPok.Latitud()][posPok.Longitud()].cantMovimientos = 0;
			}
			else {//caso : cae fuera de entorno de poke
				Coordenadatp3 posPok = it.Siguiente();
				_mapa[posPok.Latitud()][posPok.Longitud()].cantMovimientos = _mapa[posPok.Latitud()][posPok.Longitud()].
				     cantMovimientos + 1;
				if (_mapa[posPok.Latitud()][posPok.Longitud()].cantMovimientos == 10 && //se captura pokemon
                    _mapa[posPok.Latitud()][posPok.Longitud()].jugadoresEnZona.Cardinal() != 0) {
					_mapa[posPok.Latitud()][posPok.Longitud()].hayPokemon = false;
	                //_mapa[posPok.Latitud()][posPok.Longitud()].itPosicionesPokemon.EliminarSiguiente();
	                //_pokemones.Significado(pokemonEnPos(posPok)).posiciones.Eliminar(posPok);
                    it.EliminarSiguiente();//modificado
					Jugador jugadorCapturante = _mapa[posPok.Latitud()][posPok.Longitud()].jugadoresEnZona.Minimo();
					ConjPrior::Iterador zona = _mapa[posPok.Latitud()][posPok.Longitud()].jugadoresEnZona.CrearIt();
                    while(zona.HaySiguienteElem()){//limpiamos zona
                        zona.EliminarSiguienteElem();
                    }
                    Pokemon pok = _mapa[posPok.Latitud()][posPok.Longitud()].pokemon;
					if (_jugadores[jugadorCapturante-1].capturados.Definido(pok)){//actualizamos cant capturados
                         Nat num = _jugadores[jugadorCapturante-1].capturados.Significado(pok) + 1;
                         _jugadores[jugadorCapturante-1].capturados.Borrar(pok);
                         _jugadores[jugadorCapturante-1].capturados.DefinirRapido(pok,num);
					}else
                    _jugadores[jugadorCapturante-1].capturados.DefinirRapido(pok, 1);
                    _mapa[posPok.Latitud()][posPok.Longitud()].pokemon = "";
					_mapa[posPok.Latitud()][posPok.Longitud()].cantMovimientos = 0;
					_jugadores[jugadorCapturante-1].cantCapturados = _jugadores[jugadorCapturante-1].cantCapturados + 1;
				}
			}
        if(it.HaySiguiente())
		   it.Avanzar();
	}
	if (!sancionado)
	 _jugadores[j-1].posicion = coor;

}


const Mapa &Juego::mapa() const {//testear++++++++++++++++++++++++++++++

    return elmap;
}

 Conj<Jugador>::const_Iterador Juego::jugadores() const {
    return _jugadoresActivos.CrearIt();
}

 bool Juego::estaConectado(const Jugador &j) const {
    return _jugadores[j-1].conectado;//debe ser j-1
}

 Nat Juego::sanciones(const Jugador &j) const {
    return _jugadores[j-1].sanciones;
}

 Coordenadatp3 Juego::posicion(const Jugador &j) const {
    return _jugadores[j-1].posicion;
}


const DiccString<Nat>::const_itDiccString Juego::pokemons(const Jugador &j) const {

    return _jugadores[j-1].capturados.CrearItConst();

}

const Conj<Jugador>& Juego::expulsados() const {  //testear++++++++++++++++++++++++
    return expuls;
}

const Conj<Coordenadatp3> &Juego::posConPokemons() const {
    return _posicionesPokemons;
}

 Pokemon Juego::pokemonEnPos(const Coordenadatp3 &coor) const {
    return _mapa[coor.Latitud()][coor.Longitud()].pokemon;
}

 Nat Juego::cantMovimientosParaCaptura(const Coordenadatp3 &coor) const {
    return _mapa[coor.Latitud()][coor.Longitud()].cantMovimientos;
}


 bool Juego::puedoAgregarPokemon(const Coordenadatp3 &coor) const {
     if(_mapa[coor.Latitud()][coor.Longitud()].definida  ){
        Conj<Coordenadatp3>::const_Iterador cj = _posicionesPokemons.CrearIt();
        while(cj.HaySiguiente()){
          if(cj.Siguiente().DistEuclidea(coor) <= 25)
            return false;
          cj.Avanzar();
        }
        return true;
    } else
       return false;
}


  bool Juego::hayPokemonCercano(const Coordenadatp3 &coor) const {
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


  Coordenadatp3 Juego::posPokemonCercano(const Coordenadatp3 &coor) const {
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
    return it.Siguiente();
}

const Conj<Jugador> Juego::entrenadoresPosibles(const Coordenadatp3& coor) const{
    Conj<Jugador> c;
    Conj<Jugador>::const_Iterador it = _jugadoresActivos.CrearIt();
    while(it.HaySiguiente()){
        Nat jug = it.Siguiente();
        Coordenadatp3 tp = _jugadores[jug-1].posicion;
        bool conectado = _jugadores[jug-1].conectado;
        if ((*this).hayPokemonCercano(tp) && conectado){
            if(((*this).posPokemonCercano(tp) == coor) && _mapa[coor.Latitud()][coor.Longitud()].
               conexiones[tp.Latitud()][tp.Longitud()]){
                c.AgregarRapido(jug);
            }
        }
        it.Avanzar();
    }
    return c;
}


 Nat Juego::indiceRareza(const Pokemon &p) const {
    EstadoPokemon estadoPokemon = _pokemones.Significado(p);

    return 100 - ((estadoPokemon.cantTotalEspecie * 100) / _cantTotalPokemones);

}

 Nat Juego::cantPokemonsTotales() const {
   return _cantTotalPokemones;
   }

 Nat Juego::cantMismaEspecie(const Pokemon &p) const {
     if(!_pokemones.Definido(p))
        return 0;
     else{
        EstadoPokemon estadoPokemon = _pokemones.Significado(p);
        return estadoPokemon.cantTotalEspecie;
     }
}

const Conj<Coordenadatp3> &Juego::posicionesAledanias(const Coordenadatp3 &coor) const{//testear+++++++++++++++++++++
    return _mapa[coor.Latitud()][coor.Longitud()].posAledanias;

}
