#include <iostream>
#include "Juego.h"


using namespace std;

int main()
{

   Mapa cc;                      // lat
Coordenadatp3 t(1,2);            //
cc.agregarCoor(t);               //
Coordenadatp3 a(0,2);            //  8                                    (8,7)
 cc.agregarCoor(a);              //  7
   Coordenadatp3 b(0,0);         //  6
   cc.agregarCoor(b);            //  5 (5,0)(5,1)
   Coordenadatp3 c(0,1);//p      //  4
  cc.agregarCoor(c);             //  3
Coordenadatp3 d(5,0);            //  2                                    (2,7)
cc.agregarCoor(d);               //  1           (1,2)
Coordenadatp3 e(5,1);            //  0 (0,0)(0,1)(0,2)
cc.agregarCoor(e);               //      0    1    2    3    4    5    6    7    8   long
 Coordenadatp3 y(2,7);//p
 cc.agregarCoor(y);
 Coordenadatp3 w(8,7);//p
 cc.agregarCoor(w);
 cout<<"cantidad de elementos de mapa : "<<cc.coordenadas().Cardinal()<<endl;
  Juego j(cc);


  cout<<"cantidad de elementos de mapa de juego : "<<j.mapa().coordenadas().Cardinal()<<endl;
  Mapa k = j.mapa();
  if(k.hayCamino(a,d))
    cout<<"hay camino entre a y b"<<endl;
  else
    cout<<"no hay camino entre a y b"<<endl;
    if(j.mapa().posExistente(c))
    cout<<"es pos de mapa de juego"<<endl;
  else
    cout<<"no es pos de mapa de juego"<<endl;
   cout<<"pokemon en pos a es : "<<j.pokemonEnPos(a)<<endl;
      cout<<"cant movimientos para captura en pos a es : "<<j.cantMovimientosParaCaptura(a)<<endl;
//test agregarpokemon . testear mas casos
j.agregarJugador();

j.agregarPokemon("juancito",c); //c(0,1);
//test puedoagregarpokemon
if(j.puedoAgregarPokemon(y))
   j.agregarPokemon("perez",y);
if(j.puedoAgregarPokemon(w))
   j.agregarPokemon("juancito",w);
cout<<"rareza de perez : "<<j.indiceRareza("perez")<<endl;

Conj<Coordenadatp3>::const_Iterador con = j.posConPokemons().CrearIt();
while(con.HaySiguiente()){
    cout<<"en pos : ("<<con.Siguiente().Latitud()<<","<<con.Siguiente().Longitud()<<")"<<"esta poke : "<<
    j.pokemonEnPos(con.Siguiente())<<endl;
    con.Avanzar();
}

cout<<"cantidad misma especie de poke juancito : "<<j.cantMismaEspecie("juancito")<<endl;
cout<<"cantidad misma especie de poke perez : "<<j.cantMismaEspecie("perez")<<endl;

cout<<"pokemon en pos a es : "<<j.pokemonEnPos(c)<<endl;
      cout<<"cant movimientos para captura en pos a es : "<<j.cantMovimientosParaCaptura(c)<<endl;
      //test posiciones aledanias .testear mas casos
    cout<<"cantidad de elementos en posiciones aledanias a poke es : "<<j.posicionesAledanias(c).Cardinal()<<endl;
Conj<Coordenadatp3>::const_Iterador itt = j.posicionesAledanias(Coordenadatp3(20,1)).CrearIt();
if(itt.HaySiguiente()){
while(itt.HaySiguiente()){
    cout<<"pos aledanias a pos cualquiera : ("<<itt.Siguiente().Latitud()<<","<<itt.Siguiente().Longitud()<<")"<<endl;
    itt.Avanzar();
}
} else
cout<<"no hay posiciones"<<endl;

Conj<Jugador>::const_Iterador q = j.jugadores();
while(q.HaySiguiente()){
    cout<<"jugador en juego : "<<q.Siguiente()<<endl;
    q.Avanzar();
}
j.conectarse(1,b);//b(0,0);
if(j.estaConectado(1))
    cout<<"jugador a esta conectado"<<endl;
else
    cout<<"jugador a no esta conectado"<<endl;
/*
* Coordenadatp3 cor = j.posPokemonCercano(c);
* cout<<"pos de pokemon cercano : ("<<cor.Latitud()<<","<<cor.Longitud()<<")"<<endl;
*/
//test entrenadores posibles
j.agregarJugador();
j.conectarse(2,a);
j.agregarJugador();
j.conectarse(3,t);
//test desconectarse
//j.desconectarse(1);
//j.desconectarse(2);
//j.desconectarse(3);

Conj<Jugador>::const_Iterador z = j.entrenadoresPosibles(c).CrearIt();
while(z.HaySiguiente()){
    cout<<"entrenador pos : "<<z.Siguiente()<<endl;
    z.Avanzar();
}


//test diccstring
DiccString<Nat> dic ;
//dic.DefinirRapido("juan",2);
dic.DefinirRapido("juancito",2);
dic.DefinirRapido("jose",3);
if(dic.Definido("juancito"))
    cout<<" elem a definido"<<endl;
else
    cout<<"no elem a definido"<<endl;

//dic.Borrar("juancito");
//dic.Borrar("jose");
if(dic.Definido("jose"))
    cout<<" elem definido despues de borrar"<<endl;
else
    cout<<"elem borrado"<<endl;

DiccString<Nat>::itDiccString itd = dic.CrearIt();
cout<<"elems de dic : "<<endl;
while(itd.HaySiguiente()){
    cout<<"("<<itd.SiguienteClave()<<" , "<<itd.SiguienteSignificado()<<")"<<endl;
    itd.Avanzar();
}


//testeo moverse ++++++++++++++++++++++++++ testear mas casos +++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++ testear si borra los pokemones capturados ++++++++++++++++++++++++



/*
j.moverse(2,d);

cout<<"sanciones de jugador : "<<j.sanciones(2)<<endl;
cout<<"esta conectado : "<<j.estaConectado(2)<<endl;
//testeo cantidad movimientos para captura
cout<<"cantidad movimientos para captura : "<<j.cantMovimientosParaCaptura(c)<<endl;
//movemos 5 veces
j.moverse(2,e);
cout<<"cantidad movimientos para captura : "<<j.cantMovimientosParaCaptura(c)<<endl;

j.moverse(2,d);
cout<<"cantidad movimientos para captura : "<<j.cantMovimientosParaCaptura(c)<<endl;

j.moverse(2,e);
cout<<"cantidad movimientos para captura : "<<j.cantMovimientosParaCaptura(c)<<endl;

j.moverse(2,d);
j.moverse(2,e);
j.moverse(2,d);
j.moverse(2,e);
j.moverse(2,d);
j.moverse(2,e);
cout<<"1 - cantidad movimientos para captura : "<<j.cantMovimientosParaCaptura(c)<<endl;

cout<<"posicion de jugador despues de moverse : ("<<j.posicion(2).Latitud()<<","<<j.posicion(2).Longitud()<<")"<<endl;

//testeo sanciones
cout<<"sanciones de jugador movido: "<<j.sanciones(2)<<endl;
cout<<"esta conectado jugador sancionado : "<<j.estaConectado(2)<<endl;

//testeo pokemones de jugador .
DiccString<Nat>::const_itDiccString itds = j.pokemons(1);
while(itds.HaySiguiente()){
    cout<<"pokemon capturado por jugador 1 y cantidad: "<<itds.SiguienteClave()<<","<<itds.SiguienteSignificado()<<endl;
    itds.Avanzar();
}
//test cantpokemonestotales
cout<<" pokemones totales : "<<j.cantPokemonsTotales()<<endl;
cout<<"cantidad de pokemones restantes : "<<j.posConPokemons().Cardinal()<<endl;
 con = j.posConPokemons().CrearIt();
while(con.HaySiguiente()){
    cout<<"en pos : ("<<con.Siguiente().Latitud()<<","<<con.Siguiente().Longitud()<<")"<<"esta poke : "<<
    j.pokemonEnPos(con.Siguiente())<<endl;
    con.Avanzar();
}
cout<<"cantidad de expulsados : "<<j.expulsados().Cardinal()<<endl;

//test conjPrior
j.moverse(1,w);
j.moverse(2,w);
j.moverse(3,b);
j.moverse(3,t);
j.moverse(3,b);
j.moverse(3,t);
j.moverse(3,b);
//j.desconectarse(2);
j.moverse(3,t);
j.moverse(3,b);
j.moverse(3,t);
j.moverse(3,b);
//j.conectarse(2,w);
j.moverse(3,t);
cout<<"2 - cantidad movimientos para captura a poke en w : "<<j.cantMovimientosParaCaptura(w)<<endl;

DiccString<Nat>::const_itDiccString itds2 = j.pokemons(1);
while(itds2.HaySiguiente()){
    cout<<"pokemon capturado por jugador 1 y cantidad: "<<itds2.SiguienteClave()<<","<<itds2.SiguienteSignificado()<<endl;
    itds2.Avanzar();
}
DiccString<Nat>::const_itDiccString itds3 = j.pokemons(2);
while(itds3.HaySiguiente()){
    cout<<"pokemon capturado por jugador 2 y cantidad: "<<itds3.SiguienteClave()<<","<<itds3.SiguienteSignificado()<<endl;
    itds3.Avanzar();
}

cout<<"pokemones totales : "<<j.cantPokemonsTotales()<<endl;
cout<<"cantidad de pokemones restantes : "<<j.posConPokemons().Cardinal()<<endl;
j.moverse(2,a);
j.moverse(2,w);
j.moverse(2,a);
cout<<"3 - sanciones de jugador movido: "<<j.sanciones(2)<<endl;
cout<<" pokemones totales : "<<j.cantPokemonsTotales()<<endl;
cout<<"cantidad de pokemones restantes : "<<j.posConPokemons().Cardinal()<<endl;

//test cantmismaespecie
cout<<"cantidad misma especie de poke juancito : "<<j.cantMismaEspecie("juancito")<<endl;
cout<<"cantidad misma especie de poke perez : "<<j.cantMismaEspecie("perez")<<endl;
j.moverse(1,b);
j.moverse(1,w);
j.moverse(1,b);
j.moverse(1,w);
j.moverse(1,b);

cout<<"sanciones de jugador movido: "<<j.sanciones(1)<<endl;
cout<<"pokemones totales : "<<j.cantPokemonsTotales()<<endl;

cout<<"cantidad misma especie de poke juancito : "<<j.cantMismaEspecie("juancito")<<endl;
cout<<"cantidad misma especie de poke perez : "<<j.cantMismaEspecie("perez")<<endl;
//test expulsados
cout<<"cantidad de expulsados : "<<j.expulsados().Cardinal()<<endl;
//cout<<"cantidad de pokemones restantes : "<<j.posConPokemons().Cardinal()<<endl;
 con = j.posConPokemons().CrearIt();
while(con.HaySiguiente()){
    cout<<"en pos : ("<<con.Siguiente().Latitud()<<","<<con.Siguiente().Longitud()<<")"<<"esta poke : "<<
    j.pokemonEnPos(con.Siguiente())<<endl;
    con.Avanzar();
}
//test rareza
cout<<"rareza de perez : "<<j.indiceRareza("perez")<<endl;
*/
}
