#ifndef TIPOSJUEGO_H_
#define TIPOSJUEGO_H_

#include "aed2/TiposBasicos.h"

typedef unsigned int Jugador;
typedef std::string Pokemon;
using namespace aed2;

struct Coordenada
{
	Coordenada(Nat latitud, Nat longitud) : latitud(latitud), longitud(longitud) {}

    // Esto antes estaba dentro de private entonces tiraba error cuando se hacia c1.latitud y lo cambie asi que tiene mas sentido para mi
    Nat latitud;
    Nat longitud;
};

// Le tuve que agregar inline pq me tiraba "multiple definitions"
inline bool operator == (const Coordenada& c1, const Coordenada& c2){
 return c1.latitud == c2.latitud and c1.longitud == c2.longitud;
}

// Le tuve que agregar inline pq me tiraba "multiple definitions"
inline bool operator != (const Coordenada& c1, const Coordenada& c2){
    return not (c1 == c2);
}

#endif