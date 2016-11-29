#ifndef COORD_H
#define	COORD_H

#include <iostream>
#include "aed2.h"


using namespace std;
using namespace aed2;


class Coordenadatp3{
    public:
     Coordenadatp3();
     Coordenadatp3(const Coordenadatp3 & otro);
     Coordenadatp3& operator=(const Coordenadatp3 & otro);
     Coordenadatp3(Nat lat,Nat lon);
     Nat Latitud()const;
     Nat Longitud() const;
     Nat DistEuclidea(const Coordenadatp3 & otro) const;
     void CoordenadaArriba();
     void CoordenadaAbajo();
     void CoordenadaALaIzquierda();
     void CoordenadaALaDerecha();
     bool operator == (const Coordenadatp3& otro) const;

    private:
        Nat latitud;
        Nat longitud;

};

#endif
