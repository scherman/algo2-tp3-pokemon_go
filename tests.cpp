// Compilar usando:
//	g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>
//	valgrind --leak-check=full ./tests

#include "Driver.h"
#include "mini_test.h"
#include "Juego.h"

using namespace aed2;
/*
void test_constructor_con_mapa() {
  Conj<Coordenada> cc;
  cc.Agregar(Coordenada(0,0));
  cc.Agregar(Coordenada(0,1));
  cc.Agregar(Coordenada(0,2));
  cc.Agregar(Coordenada(1,2));
  cc.Agregar(Coordenada(10,0));
  cc.Agregar(Coordenada(1,4));
  //  Comento porque metira un par de undefined references...
  //  Driver d(cc);
  //  ASSERT( d.mapa() == cc );
}*/

void test_constructor_con_mapa() {
  Mapa m;
  m.agregarCoor(Coordenadatp3(0,0));
  m.agregarCoor(Coordenadatp3(1,0));
  m.agregarCoor(Coordenadatp3(0,1));
  m.agregarCoor(Coordenadatp3(1,1));
  m.agregarCoor(Coordenadatp3(1,2));
  m.agregarCoor(Coordenadatp3(2,1));
  m.agregarCoor(Coordenadatp3(2,2));
  m.agregarCoor(Coordenadatp3(2,8));

  Juego game = Juego(m);
  ASSERT(game.mapa().coordenadas() == m.coordenadas());
}


void test_agregar_jugadores(){
  //para testear: estaConectado, conectarse, agregarJugador, sanciones, posiciones, expulsado, desconectar...
  //falta todo lo relacionado con mover/agregarPokemon
  Mapa m;
  m.agregarCoor(Coordenadatp3(0,0));
  m.agregarCoor(Coordenadatp3(1,0));
  m.agregarCoor(Coordenadatp3(0,1));
  m.agregarCoor(Coordenadatp3(1,1));
  m.agregarCoor(Coordenadatp3(1,2));
  m.agregarCoor(Coordenadatp3(2,1));
  m.agregarCoor(Coordenadatp3(2,2));
  m.agregarCoor(Coordenadatp3(0,2));
  m.agregarCoor(Coordenadatp3(2,0));
  m.agregarCoor(Coordenadatp3(3,2));
  m.agregarCoor(Coordenadatp3(2,3));
  m.agregarCoor(Coordenadatp3(3,3));
  m.agregarCoor(Coordenadatp3(0,3));
  m.agregarCoor(Coordenadatp3(3,0));
  m.agregarCoor(Coordenadatp3(1,3));
  m.agregarCoor(Coordenadatp3(3,1));
  m.agregarCoor(Coordenadatp3(0,4));
  m.agregarCoor(Coordenadatp3(1,4));
  m.agregarCoor(Coordenadatp3(2,4));
  m.agregarCoor(Coordenadatp3(3,4));
  m.agregarCoor(Coordenadatp3(4,4));
  m.agregarCoor(Coordenadatp3(4,0));
  m.agregarCoor(Coordenadatp3(4,1));
  m.agregarCoor(Coordenadatp3(4,2));
  m.agregarCoor(Coordenadatp3(4,3));
  m.agregarCoor(Coordenadatp3(0,5));
  m.agregarCoor(Coordenadatp3(1,5));
  m.agregarCoor(Coordenadatp3(2,5));
  m.agregarCoor(Coordenadatp3(3,5));
  m.agregarCoor(Coordenadatp3(4,5));
  m.agregarCoor(Coordenadatp3(5,5));
  m.agregarCoor(Coordenadatp3(6,5));
  m.agregarCoor(Coordenadatp3(0,6));
  m.agregarCoor(Coordenadatp3(1,6));
  m.agregarCoor(Coordenadatp3(2,6));
  m.agregarCoor(Coordenadatp3(3,6));
  m.agregarCoor(Coordenadatp3(4,6));
  m.agregarCoor(Coordenadatp3(5,6));
  m.agregarCoor(Coordenadatp3(6,6));
  m.agregarCoor(Coordenadatp3(5,0));
  m.agregarCoor(Coordenadatp3(5,1));
  m.agregarCoor(Coordenadatp3(5,2));
  m.agregarCoor(Coordenadatp3(5,3));
  m.agregarCoor(Coordenadatp3(5,4));
  m.agregarCoor(Coordenadatp3(6,0));
  m.agregarCoor(Coordenadatp3(6,1));
  m.agregarCoor(Coordenadatp3(6,2));
  m.agregarCoor(Coordenadatp3(6,3));
  m.agregarCoor(Coordenadatp3(6,4));
  Juego game = Juego(m);
  game.agregarJugador();
  game.agregarJugador();
  game.agregarJugador();
  game.agregarJugador();
  Juego game1 = Juego(m);
  game1.agregarJugador();
  game1.agregarJugador();
  game1.agregarJugador();
  game1.agregarJugador();
  Coordenadatp3 a = Coordenadatp3(1,2);
  Coordenadatp3 b = Coordenadatp3(4,6);
  Jugador j = 1;
  Jugador js = 2;
  Pokemon p = "pika";
  Pokemon q = "squirtle";
  Pokemon g = "gyarados";
  Coordenadatp3 a1 = Coordenadatp3(0,1);
  Coordenadatp3 b1 = Coordenadatp3(6,6);
  Coordenadatp3 c1 = Coordenadatp3(6,0);
  game.agregarPokemon(p, a1 );
  game.agregarPokemon(q, b1 );
  game.agregarPokemon(g, c1 );
  game.conectarse(j,a);
  game.conectarse(js, b);
 // Coordenadatp3 posPoke = game.posPokemonCercano(a);
  game.moverse(js,c1);
  /* hice mover a js de b a c1, tendria que aumentar, cantMovimientos de (0,1) o (1,2)? Solo aumenta
   * los movimientos para captura de b1, que no se si tendrian que aumentar directamente.
   */
  //game.moverse(js,b1);
  //game.moverse(js,c1);
  //game.moverse(js,b1);
  //game.moverse(js,c1);
  //game.moverse(js,b1);
  //game.moverse(js,c1);
  //game.moverse(js,b1);
  //game.desconectarse(j);
  //ASSERT( game.jugadores().Siguiente() == game1.jugadores().Siguiente() );
  //ASSERT(game.estaConectado(1) == false);
  ASSERT(game.cantMovimientosParaCaptura(a) == 1);
  //ASSERT( game.posicion(4) == Coordenadatp3(0,0) );
  //ASSERT( game.sanciones(4) == 0 );
  //ASSERT( game.expulsados() == Conj<Jugador>() );
}

void test_agregar_pokemones(){
  Mapa m;
  m.agregarCoor(Coordenadatp3(0,0));
  m.agregarCoor(Coordenadatp3(1,0));
  m.agregarCoor(Coordenadatp3(0,1));
  m.agregarCoor(Coordenadatp3(1,1));
  m.agregarCoor(Coordenadatp3(1,2));
  m.agregarCoor(Coordenadatp3(2,1));
  m.agregarCoor(Coordenadatp3(2,2));
  m.agregarCoor(Coordenadatp3(0,2));
  m.agregarCoor(Coordenadatp3(2,0));
  m.agregarCoor(Coordenadatp3(3,2));
  m.agregarCoor(Coordenadatp3(2,3));
  m.agregarCoor(Coordenadatp3(3,3));
  m.agregarCoor(Coordenadatp3(0,3));
  m.agregarCoor(Coordenadatp3(3,0));
  m.agregarCoor(Coordenadatp3(1,3));
  m.agregarCoor(Coordenadatp3(3,1));
  m.agregarCoor(Coordenadatp3(0,4));
  m.agregarCoor(Coordenadatp3(1,4));
  m.agregarCoor(Coordenadatp3(2,4));
  m.agregarCoor(Coordenadatp3(3,4));
  m.agregarCoor(Coordenadatp3(4,4));
  m.agregarCoor(Coordenadatp3(4,0));
  m.agregarCoor(Coordenadatp3(4,1));
  m.agregarCoor(Coordenadatp3(4,2));
  m.agregarCoor(Coordenadatp3(4,3));
  m.agregarCoor(Coordenadatp3(0,5));
  m.agregarCoor(Coordenadatp3(1,5));
  m.agregarCoor(Coordenadatp3(2,5));
  m.agregarCoor(Coordenadatp3(3,5));
  m.agregarCoor(Coordenadatp3(4,5));
  m.agregarCoor(Coordenadatp3(5,5));
  m.agregarCoor(Coordenadatp3(6,5));
  m.agregarCoor(Coordenadatp3(0,6));
  m.agregarCoor(Coordenadatp3(1,6));
  m.agregarCoor(Coordenadatp3(2,6));
  m.agregarCoor(Coordenadatp3(3,6));
  m.agregarCoor(Coordenadatp3(4,6));
  m.agregarCoor(Coordenadatp3(5,6));
  m.agregarCoor(Coordenadatp3(6,6));
  m.agregarCoor(Coordenadatp3(5,0));
  m.agregarCoor(Coordenadatp3(5,1));
  m.agregarCoor(Coordenadatp3(5,2));
  m.agregarCoor(Coordenadatp3(5,3));
  m.agregarCoor(Coordenadatp3(5,4));
  m.agregarCoor(Coordenadatp3(6,0));
  m.agregarCoor(Coordenadatp3(6,1));
  m.agregarCoor(Coordenadatp3(6,2));
  m.agregarCoor(Coordenadatp3(6,3));
  m.agregarCoor(Coordenadatp3(6,4));


  Juego game = Juego(m);
  Pokemon p = "pika";
  Pokemon q = "squirtle";
  Pokemon g = "gyarados";
  Coordenadatp3 a = Coordenadatp3(0,1);
  Coordenadatp3 b = Coordenadatp3(6,6);
  Coordenadatp3 c = Coordenadatp3(6,0);
  game.agregarPokemon(p, a );
  game.agregarPokemon(q, b );
  game.agregarPokemon(g, c );
  //segmentation fault, al mirar Definido en Arreglo.
 // ASSERT( game.cantMismaEspecie(p) == 1 );
 // ASSERT(game.cantPokemonsTotales() == 3 );
  ASSERT(game.cantPokemonsTotales() == 3);
}

// TODO: Agregar más tests

void test_moverse(){
  Mapa m;
  m.agregarCoor(Coordenadatp3(0,0));
  m.agregarCoor(Coordenadatp3(1,0));
  m.agregarCoor(Coordenadatp3(0,1));
  m.agregarCoor(Coordenadatp3(1,1));
  m.agregarCoor(Coordenadatp3(1,2));
  m.agregarCoor(Coordenadatp3(2,1));
  m.agregarCoor(Coordenadatp3(2,2));
  m.agregarCoor(Coordenadatp3(2,8));
  Juego game = Juego(m);
  game.agregarJugador();
  game.agregarJugador();
  game.agregarJugador();
  game.agregarJugador();
  Coordenadatp3 a = Coordenadatp3(2,3);
  Jugador b = 2;
  game.moverse(b, a);
  //ASSERT(game.posicion(2) == a );
  ASSERT(game.estaConectado(2) == false)
}

void test_posAledanias(){
  //testea posicionesAledanias(coor), se esta devolviendo incluso la coordenada que le pasamos.
  //creo que asi tiene que ser.
  //Anda
  Mapa m;
  m.agregarCoor(Coordenadatp3(0,0));
  m.agregarCoor(Coordenadatp3(1,0));
  m.agregarCoor(Coordenadatp3(0,1));
  m.agregarCoor(Coordenadatp3(1,1));
  m.agregarCoor(Coordenadatp3(1,2));
  m.agregarCoor(Coordenadatp3(2,1));
  m.agregarCoor(Coordenadatp3(2,2));
  m.agregarCoor(Coordenadatp3(0,2));
  m.agregarCoor(Coordenadatp3(2,0));
  m.agregarCoor(Coordenadatp3(3,2));
  m.agregarCoor(Coordenadatp3(2,3));
  m.agregarCoor(Coordenadatp3(3,3));
  m.agregarCoor(Coordenadatp3(0,3));
  m.agregarCoor(Coordenadatp3(3,0));
  m.agregarCoor(Coordenadatp3(1,3));
  m.agregarCoor(Coordenadatp3(3,1));
  m.agregarCoor(Coordenadatp3(0,4));
  m.agregarCoor(Coordenadatp3(1,4));
  m.agregarCoor(Coordenadatp3(2,4));
  m.agregarCoor(Coordenadatp3(3,4));
  m.agregarCoor(Coordenadatp3(4,4));
  m.agregarCoor(Coordenadatp3(4,0));
  m.agregarCoor(Coordenadatp3(4,1));
  m.agregarCoor(Coordenadatp3(4,2));
  m.agregarCoor(Coordenadatp3(4,3));
  m.agregarCoor(Coordenadatp3(2,8));
  Juego game = Juego(m);
  Coordenadatp3 a = Coordenadatp3(0,0);
  Conj<Coordenadatp3> conjA;
  //conjA.AgregarRapido(Coordenadatp3(4,2));
  conjA.AgregarRapido(Coordenadatp3(0,2));
  conjA.AgregarRapido(Coordenadatp3(0,0));
  //conjA.AgregarRapido(Coordenadatp3(1,2));
  //conjA.AgregarRapido(Coordenadatp3(3,2));
  //conjA.AgregarRapido(Coordenadatp3(1,3));
  //conjA.AgregarRapido(Coordenadatp3(2,3));
  //conjA.AgregarRapido(Coordenadatp3(3,3));
  conjA.AgregarRapido(Coordenadatp3(1,1));
  conjA.AgregarRapido(Coordenadatp3(0,1));
  conjA.AgregarRapido(Coordenadatp3(1,0));
  //conjA.AgregarRapido(Coordenadatp3(2,1));
  //conjA.AgregarRapido(Coordenadatp3(3,1));
  conjA.AgregarRapido(Coordenadatp3(2,0));
  //conjA.AgregarRapido(Coordenadatp3(2,4));
  //conjA.AgregarRapido(Coordenadatp3(2,2));


  ASSERT(game.posicionesAledanias(a) == conjA);
}


int main(int argc, char **argv)
{
 // RUN_TEST(test_constructor_con_mapa);
  RUN_TEST(test_agregar_jugadores);
//  RUN_TEST(test_agregar_pokemones);
//  RUN_TEST(test_moverse);
//  RUN_TEST(test_posAledanias);
  return 0;
}
