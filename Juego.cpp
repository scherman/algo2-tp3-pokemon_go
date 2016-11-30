
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
    //cambie la parte en que se modificaba el mapa.
    //se estaba creando una variable parcela, a la que se le asiganba la pos del mapa
    //pero al ser por copia, no modificaba los valores originales del mapa.
    EstadoPokemon estadoPokemon = {0, Conj<Coordenadatp3>()};
    //if (_pokemones.Definido(p)) {
    //    estadoPokemon = _pokemones.Significado(p);
    //}
    Conj<Coordenadatp3>::Iterador itPokemones = estadoPokemon.posiciones.AgregarRapido(coor);
    estadoPokemon.cantTotalEspecie++;
	if (_pokemones.Definido(p)) {
		EstadoPokemon estadoDicc = _pokemones.Significado(p);
		estadoDicc.posiciones.AgregarRapido(coor);
		estadoDicc.cantTotalEspecie++;
	}
	else
		_pokemones.DefinirRapido(p, estadoPokemon);

    // Agrego pokemon en j.posicionesPokemones
    Conj<Coordenadatp3>::Iterador itPosicionesPokemones = _posicionesPokemons.AgregarRapido(coor);

    // Agrego pokemon en j.mapa
   // Parcela parcela = _mapa[coor.Latitud()][coor.Longitud()];
    _mapa[coor.Latitud()][coor.Longitud()].hayPokemon = true;
    _mapa[coor.Latitud()][coor.Longitud()].pokemon = p;
    _mapa[coor.Latitud()][coor.Longitud()].itPosicionesPokemon = itPosicionesPokemones;
    // parcela.hayPokemon = true;
    //parcela.pokemon = p;
    //parcela.itPosicionesPokemon = itPosicionesPokemones;
    Conj<Coordenadatp3>::const_Iterador posicionesEnZona = posicionesAledanias(coor).CrearIt();
    while (posicionesEnZona.HaySiguiente()) {
        Coordenadatp3 actual = posicionesEnZona.Siguiente();
        Conj<Jugador>::Iterador itJugadoresEnPosicion = _mapa[actual.Latitud()][actual.Longitud()].jugadoresEnPosicion.CrearIt();
        while (itJugadoresEnPosicion.HaySiguiente()) {
            Jugador jugador = itJugadoresEnPosicion.Siguiente();
            ConjPrior::Iterador itJugadoresEnZona = _mapa[coor.Latitud()][coor.Longitud()].jugadoresEnZona.Agregar(_jugadores[jugador].cantCapturados, jugador);
            _jugadores[jugador].itJugadoresEnZona = itJugadoresEnZona;
            itJugadoresEnPosicion.Avanzar();
        }
        posicionesEnZona.Avanzar();
    }
    _mapa[coor.Latitud()][coor.Longitud()].cantMovimientos = 0;

    // Sumo 1 en j.cantTotalPokemones
    _cantTotalPokemones++;
}

Jugador Juego::agregarJugador() {
    //no habria basura al inicializar?
    DiccString<Nat> vacio;
    Conj<Jugador>::Iterador itConj;
    ConjPrior::Iterador itConjPrior;
    EstadoJugador estadoJugadorNoConectado = {true, false, 0, Coordenadatp3(0,0), vacio, 0, itConj, itConjPrior};
    _jugadores.AgregarAtras(estadoJugadorNoConectado);
    Conj<Jugador>::Iterador it = _jugadoresActivos.AgregarRapido(_jugadores.Longitud());
    _jugadores[_jugadores.Longitud() - 1].itJugadoresActivos = it;
    return _jugadores.Longitud();
}

void Juego::conectarse(Jugador &j,Coordenadatp3 &coor) {
    (_jugadores)[j-1].conectado = true;
    (_jugadores)[j-1].recienCreado = false;
    (_jugadores)[j-1].posicion = coor;
    if(hayPokemonCercano(coor)){
        Coordenadatp3 posPokemon = posPokemonCercano(coor);
        (_mapa)[posPokemon.Latitud()][posPokemon.Longitud()].cantMovimientos = 0;
        (_jugadores)[j-1].itJugadoresEnZona
        = (_mapa)[posPokemon.Latitud()][posPokemon.Longitud()].jugadoresEnZona.Agregar(_jugadores[j-1].cantCapturados,j);
    }
}

void Juego::desconectarse(Jugador &j) {
    _jugadores[j-1].conectado = false;
    if(hayPokemonCercano(_jugadores[j].posicion)){
        _jugadores[j-1].itJugadoresEnZona.EliminarSiguienteElem();
        _jugadores[j-1].itJugadoresEnZona = ConjPrior().CrearIt();
    }
}

void Juego::moverse(Jugador &j,Coordenadatp3 &coor) {
	/*Creo que falta aumentar los cantMovimientosParaCaptura de todos aquellos jugadores
	 * que estan esperando capturar y no son los que se movieron, siempre y cuando el que se
	 * movio sea de otra zona o no se haya movido a la zona de estos jugadores(caso ya contemplado)*/

    Coordenadatp3 posAnterior = _jugadores[j-1].posicion;
	bool eliminadoDeZona = false;
	if (hayPokemonCercano(posAnterior)) {
		if (!(hayPokemonCercano(coor) && posPokemonCercano(posAnterior) == posPokemonCercano(coor))) {
            _jugadores[j-1].itJugadoresEnZona.EliminarSiguienteElem();
			//necesario esta linea? la de abajo
            _jugadores[j-1].itJugadoresEnZona = ConjPrior().CrearIt();
			eliminadoDeZona = true;
		}
	}
	if ((!_mapa[posAnterior.Latitud()][posAnterior.Longitud()].conexiones[coor.Latitud()][coor.Longitud()]) || posAnterior.DistEuclidea(coor) > 100) {
		_jugadores[j-1].sanciones = _jugadores[j-1].sanciones + 1;
		if (_jugadores[j-1].sanciones == 5) {
			_jugadores[j-1].conectado = false;
			_cantTotalPokemones = _cantTotalPokemones - _jugadores[j-1].cantCapturados;
			_jugadores[j-1].cantCapturados = 0;
			Conj<string>::const_Iterador itCapturados = _jugadores[j-1].capturados.Claves().CrearIt();
			while (itCapturados.HaySiguiente())
			{
				string clave = itCapturados.Siguiente();
				if (_pokemones.Significado(clave).cantTotalEspecie == _jugadores[j-1].capturados.Significado(clave))
					_pokemones.Borrar(clave);
				else
					_pokemones.Significado(clave).cantTotalEspecie = _pokemones.Significado(clave).cantTotalEspecie - _jugadores[j-1].capturados.Significado(clave);
				itCapturados.Avanzar();
				_jugadores[j-1].capturados.Borrar(clave);
			}
			_jugadores[j-1].itJugadoresActivos.EliminarSiguiente();
			if (!eliminadoDeZona && _jugadores[j-1].itJugadoresActivos.HaySiguiente())
				_jugadores[j-1].itJugadoresEnZona.EliminarSiguienteElem();
		}
	}
    //agregue esta linea porque al hacer eliminarSiguiente en la linea 217, despues hacia it.Avanzar y eso rompia todo
    //Al hacer un nuevo conjunto se soluciona, no entiendo bien porque...
    Conj<Coordenadatp3> pokes = _posicionesPokemons;
	Conj<Coordenadatp3>::Iterador it = pokes.CrearIt();
	while (it.HaySiguiente()) {
        //no avanzaba el iterador
        //no entraba a la posicion del pokemon que no era ni posAnterior ni la nueva posicion, por lo tanto
        //no actualizabas cantMovimientos para las demas posiciones que no se veian afectadas.
        //Ahi se soluciona el tema, pero creo que el primer if estaria de mas. Por las dudas lo dejo, y lo miras vos
        //y acomodalo si queres. Le agregue el HayPokemonCercano(it.Siguiente()), que es algo obvio ya que
        //estas iterando posiciones de pokemons no mas. Por eso se podria sacar.
		if (hayPokemonCercano(it.Siguiente()) || (hayPokemonCercano(posAnterior) && posPokemonCercano(posAnterior) == it.Siguiente()) || !hayPokemonCercano(posAnterior)) {
			if (hayPokemonCercano(coor) && posPokemonCercano(coor) == it.Siguiente()) {
				Coordenadatp3 posPok = posPokemonCercano(coor);
				//Segun el tp en realidad es jugadoresEnZona
				_jugadores[j-1].itJugadoresActivos = _mapa[posPok.Latitud()][posPok.Longitud()].jugadoresEnPosicion.Agregar(_jugadores[j-1].cantCapturados);
				_mapa[posPok.Latitud()][posPok.Longitud()].cantMovimientos = 0;
                //faltaba agregar al jugador al itJugadoresEnZona.
                _jugadores[j-1].itJugadoresEnZona = _mapa[posPok.Latitud()][posPok.Longitud()].jugadoresEnZona.Agregar(_jugadores[j-1].cantCapturados,j);
                it.Avanzar();
			}
			else {
				Coordenadatp3 posPok = it.Siguiente();
				_mapa[posPok.Latitud()][posPok.Longitud()].cantMovimientos = _mapa[posPok.Latitud()][posPok.Longitud()].cantMovimientos + 1;
				if (_mapa[posPok.Latitud()][posPok.Longitud()].cantMovimientos == 10 && _mapa[posPok.Latitud()][posPok.Longitud()].jugadoresEnZona.Cardinal() != 0) {
					Parcela pos = _mapa[posPok.Latitud()][posPok.Longitud()];
                    //estabas usandoo pos para cambiar los valores internos y tengo entendido que al pasarlo por copia
                    //no se cambian los valores internos. No estoy del todo seguro pero en AgregarJugadores pasaba eso.
                    _mapa[posPok.Latitud()][posPok.Longitud()].hayPokemon = false;
                    _mapa[posPok.Latitud()][posPok.Longitud()].itPosicionesPokemon.EliminarSiguiente();
					Jugador jugadorCapturante = _mapa[posPok.Latitud()][posPok.Longitud()].jugadoresEnZona.Minimo() - 1;
                    _mapa[posPok.Latitud()][posPok.Longitud()].jugadoresEnZona = ConjPrior();
					DiccString<Nat> dicc = _jugadores[jugadorCapturante].capturados;
					if (dicc.Definido(pos.pokemon)){
                        _jugadores[jugadorCapturante].capturados.Significado(_mapa[posPok.Latitud()][posPok.Longitud()].pokemon) = dicc.Significado(pos.pokemon) + 1;
                    }
					else{
                        _jugadores[jugadorCapturante].capturados.DefinirRapido(_mapa[posPok.Latitud()][posPok.Longitud()].pokemon, 1);
                        _mapa[posPok.Latitud()][posPok.Longitud()].cantMovimientos = 0;
					    _jugadores[jugadorCapturante].cantCapturados = _jugadores[jugadorCapturante].cantCapturados + 1;
                        it.Avanzar();
                    }
				}
                else{
                    it.Avanzar();
                }
			}
		}
        else{
            it.Avanzar();
        }
	}
	_jugadores[j-1].posicion = coor;
}

const Mapa &Juego::mapa() const {
    Mapa* m = new Mapa;
    Nat i = 0;
    Nat j = 0;
    while(i < _mapa.Longitud()){//i itera sobre las columnas de mapa
        j = 0;
        while(j < _mapa[i].Longitud()){
            if(_mapa[i][j].definida){
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
    return _jugadores[j-1].conectado;
}

const Nat Juego::sanciones(const Jugador &j) const {
    return _jugadores[j-1].sanciones;
}

const Coordenadatp3 &Juego::posicion(const Jugador &j) const {
    return _jugadores[j-1].posicion;
}

const DiccString<Nat>::const_itDiccString Juego::pokemons(const Jugador &j) const {
    return _jugadores[j-1].capturados.CrearItConst();
}

const Conj<Jugador> Juego::expulsados() const {
    Conj<Nat> res = Conj<Nat>();
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
        Coordenadatp3 a = it.Siguiente();
        if(_mapa[it.Siguiente().Latitud()][it.Siguiente().Longitud()].pokemon != ""){
             return it.Siguiente();
        }
        else{
            it.Avanzar();
        }
    }
}
 const Conj<Jugador>& Juego::entrenadoresPosibles(const Coordenadatp3& coor) const{
    //en el tp usamos un Iterador para js pero ahora es un vector...Antes usabamos un conjunto. Tendriamos que usar Conj.h?
        Conj<Jugador>* c = new Conj<Jugador>;
        Conj<Jugador>::const_Iterador it = _jugadoresActivos.CrearIt();
        while(it.HaySiguiente()){
            Nat jug = it.Siguiente();
            Coordenadatp3 tp = _jugadores[jug-1].posicion;
            bool conectado = _jugadores[jug-1].conectado;
            if ((*this).hayPokemonCercano(tp) && conectado){
                if(((*this).posPokemonCercano(tp) == coor) && _mapa[coor.Latitud()][coor.Longitud()].
                   conexiones[tp.Latitud()][tp.Longitud()]){
                    (*c).AgregarRapido(jug);
                }
            }
            it.Avanzar();
        }
        return *c;
}

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
            if (mapa().posExistente(nueva) && coor.DistEuclidea(nueva) <= 4)
                (*nuevo).AgregarRapido(nueva);
        }
        j++;
    }
    i++;
}
return *nuevo;
}
