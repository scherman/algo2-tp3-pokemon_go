#ifndef TIPOSJUEGO_H_
#define TIPOSJUEGO_H_

#include "aed2/TiposBasicos.h"

typedef unsigned int Jugador;
typedef std::string Pokemon;
using namespace aed2;

class Coordenada
{
public:
	Coordenada(Nat latitud, Nat longitud) : _latitud(latitud), _longitud(longitud) {}

    const Nat& latitud() const {return _latitud;};
    const Nat& longitud() const {return _latitud;};
    const Nat& distEuclidea(const Coordenada &coor) const;
    const Coordenada& coordenadaArriba() const;
    const Coordenada& coordenadaAbajo() const;
    const Coordenada& coordenadaIzquierda() const;
    const Coordenada& coordenadaDerecha() const;

    bool operator == (const Coordenada &coor) const{
        return latitud() == coor.latitud() and longitud() == coor.longitud();
    }

private:
    Nat _latitud;
    Nat _longitud;
};

#endif