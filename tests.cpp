// Compilar usando:
//	g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>
//	valgrind --leak-check=full ./tests

#include "Driver.h"
#include "mini_test.h"
//#include "aed2.h"//*
//#include "TiposJuego.h"
//#include "Juego.h"



using namespace aed2;

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
   bool verdad = (Coordenada(0,2) == Coordenada(0,1)) ;


  Nat cantd = cc.Cardinal();
   Conj<Coordenada>::const_Iterador itcon = cc.CrearIt();

  while(itcon.HaySiguiente()){
//      std::cout <<"coord en cc : " << itcon.Siguiente().latitud << "," << itcon.Siguiente().longitud << std::endl;
     itcon.Avanzar();
  }
 Driver d(cc);
}

void test_agregar_jugadores(){
    Conj<Coordenada> cc;
  cc.Agregar(Coordenada(0,0));
  cc.Agregar(Coordenada(0,1));
  cc.Agregar(Coordenada(0,2));
  cc.Agregar(Coordenada(1,2));
  cc.Agregar(Coordenada(10,0));
  cc.Agregar(Coordenada(1,4));

   Driver d(cc);
    std::cout << "jugador agregado : " << d.agregarJugador() << endl;
}

void test_agregar_pokemones(){
 Conj<Coordenada> c;
  Coordenada ca(0,0);               //10                                                  (10,0)
  c.Agregar(ca);                    // 9
    Coordenada cb(0,1); //p         // 8
  c.Agregar(cb);                    // 7
    Coordenada cd(0,2);             // 6
  c.Agregar(cd);                    // 5
    Coordenada ce(1,2);             // 4
  c.Agregar(ce);                    // 3
    Coordenada cf(10,0);//q         // 2
  c.Agregar(cf);                    // 1           (1,2)     (1,4)(1,5)(1,6)
    Coordenada cg(1,4);             // 0 (0,0)(0,1)(0,2)
  c.Agregar(cg);                    //     0    1    2    3    4    5    6    7    8    9    10
    Coordenada ch(1,6);//r
  c.Agregar(ch);
    Coordenada ci(1,5);
  c.Agregar(ci);
   Driver d(c);
   Pokemon p = "juan";
   Pokemon q = "pedro";
   Pokemon r = "juan";
   d.agregarPokemon(r,ch);
   d.agregarPokemon(p,cb);
   d.agregarPokemon(q,cf);
   d.agregarJugador();//1
   d.agregarJugador();//2
   d.agregarJugador();//3
   d.agregarJugador();//4
}

void test_conectarse(){
Conj<Coordenada> c;
  Coordenada ca(0,0);               //10                                                  (10,0)
  c.Agregar(ca);                    // 9
    Coordenada cb(0,1); //p         // 8
  c.Agregar(cb);                    // 7
    Coordenada cd(0,2);             // 6
  c.Agregar(cd);                    // 5
    Coordenada ce(1,2);             // 4
  c.Agregar(ce);                    // 3
    Coordenada cf(10,0);//q         // 2
  c.Agregar(cf);                    // 1           (1,2)     (1,4)(1,5)(1,6)
    Coordenada cg(1,4);             // 0 (0,0)(0,1)(0,2)
  c.Agregar(cg);                    //     0    1    2    3    4    5    6    7    8    9    10
    Coordenada ch(1,6);//r
  c.Agregar(ch);
    Coordenada ci(1,5);
  c.Agregar(ci);
   Driver d(c);
   Pokemon p = "juan";
   Pokemon q = "pedro";
   Pokemon r = "juan";
   d.agregarPokemon(r,ch);
   d.agregarPokemon(p,cb);
   d.agregarPokemon(q,cf);
   d.agregarJugador();//1
   d.agregarJugador();//2
   d.agregarJugador();//3
   d.agregarJugador();//4
   d.conectarse(1,ca);
   d.conectarse(2,cd);
   d.conectarse(3,ch);
   d.conectarse(4,ca);
   d.desconectarse(4);
}

void test_moverse(){
Conj<Coordenada> c;


  Coordenada ca(0,0);               //10                                                  (10,0)
  c.Agregar(ca);                    // 9
    Coordenada cb(0,1); //p         // 8
  c.Agregar(cb);                    // 7
    Coordenada cd(0,2);             // 6
  c.Agregar(cd);                    // 5
    Coordenada ce(1,2);             // 4
  c.Agregar(ce);                    // 3
    Coordenada cf(10,0);//q         // 2
  c.Agregar(cf);                    // 1           (1,2)     (1,4)(1,5)(1,6)
    Coordenada cg(1,4);             // 0 (0,0)(0,1)(0,2)
  c.Agregar(cg);                    //     0    1    2    3    4    5    6    7    8    9    10
    Coordenada ch(1,6);//r
  c.Agregar(ch);
    Coordenada ci(1,5);
  c.Agregar(ci);

/*
  c.Agregar(Coordenada(0,0));               //10                                                  (10,0)
Coordenada ca(0,0);                      // 9
c.Agregar(Coordenada(0,1)); //p         // 8
Coordenada cb(0,1);                    // 7
c.Agregar(Coordenada(0,2));             // 6
Coordenada cd(0,2);                    // 5
c.Agregar(Coordenada(1,2));             // 4
 Coordenada ce(1,2);                  // 3
    Coordenada cf(10,0);//q         // 2
  c.Agregar(cf);                    // 1           (1,2)     (1,4)(1,5)(1,6)
    Coordenada cg(1,4);             // 0 (0,0)(0,1)(0,2)
  c.Agregar(cg);                    //     0    1    2    3    4    5    6    7    8    9    10
    Coordenada ch(1,6);//r
  c.Agregar(ch);
    Coordenada ci(1,5);
  c.Agregar(ci);
  */

  bool verdad = (ci == cf) ;


  Nat cantd = c.Cardinal();
   Driver d(c);
   Pokemon p = "juan";
   Pokemon q = "pedro";
   Pokemon r = "juan";
   d.agregarPokemon(r,ch);
   d.agregarPokemon(p,cb);
   d.agregarPokemon(q,cf);
   d.agregarJugador();//1
   d.agregarJugador();//2
   d.agregarJugador();//3
   d.agregarJugador();//4
   d.conectarse(1,ca);
   d.conectarse(2,cd);
   d.conectarse(3,ch);
   d.conectarse(4,ca);
   d.desconectarse(4);
   d.moverse(3,ch);
   Conj<Coordenada>::const_Iterador itj = d.mapa().CrearIt();
   cout<<"cantidad posiciones mapa : "<<d.mapa().Cardinal()<<endl;
   /*
   while(itj.HaySiguiente()){
    cout<<"pos en mapa de juego: ("<<itj.Siguiente().latitud()<<","<<itj.Siguiente().longitud()<<")"<<endl;
    itj.Avanzar();
   }
   */
}

void test_entrenadoresPosibles() {
    Conj<Coordenada> cc;
    cc.Agregar(Coordenada(0,0));
    cc.Agregar(Coordenada(0,1));
    cc.Agregar(Coordenada(0,2));
    cc.Agregar(Coordenada(1,2));
    cc.Agregar(Coordenada(10,0));
    cc.Agregar(Coordenada(1,4));

    Driver driver (cc);
//    driver.agregarJugador();
//    driver.agregarJugador();
//    driver.conectarse(1, Coordenada(0,0));
//    driver.conectarse(2, Coordenada(0,2));
//    driver.agregarPokemon("Pikachu", Coordenada(0,1));
//    Conj<Jugador> jugadores = driver.entrenadoresPosibles(Coordenada(0,1));
//    ASSERT(jugadores.Cardinal() == 2);

    Mapa mapa;
    mapa.agregarCoor(Coordenadatp3(0,0));
    mapa.agregarCoor(Coordenadatp3(0,1));
    mapa.agregarCoor(Coordenadatp3(0,2));
    mapa.agregarCoor(Coordenadatp3(1,2));
    mapa.agregarCoor(Coordenadatp3(10,0));
    mapa.agregarCoor(Coordenadatp3(1,4));

	


    Juego juego(mapa);
    juego.agregarJugador();
    juego.agregarJugador();
    juego.conectarse(1, Coordenadatp3(0,0));
    juego.conectarse(2, Coordenadatp3(0,2));
    juego.agregarPokemon("Pikachu", Coordenadatp3(0,1));
    Conj<Jugador> jugadores = juego.entrenadoresPosibles(Coordenadatp3(0,1));

	Conj<Coordenadatp3> conj = juego.mapa().coordenadas();
	Conj<Coordenada> conjDos = driver.mapa();
    ASSERT(jugadores.Cardinal() == 2);
}



void test_capturar(){

    Conj<Coordenada> cc;
    cc.Agregar(Coordenada(0,0));
    cc.Agregar(Coordenada(0,1));
    cc.Agregar(Coordenada(0,2));
    cc.Agregar(Coordenada(1,2));
    cc.Agregar(Coordenada(10,0));
    cc.Agregar(Coordenada(9,0));
    cc.Agregar(Coordenada(8,0));
    cc.Agregar(Coordenada(7,0));
    cc.Agregar(Coordenada(6,0));
    cc.Agregar(Coordenada(5,0));
    cc.Agregar(Coordenada(4,0));
    cc.Agregar(Coordenada(3,0));
    cc.Agregar(Coordenada(2,0));
    cc.Agregar(Coordenada(1,0));
    cc.Agregar(Coordenada(1,4));

    Driver driver (cc);
    driver.agregarJugador();
    driver.agregarJugador();
    driver.agregarPokemon("Pikachu", Coordenada(0,1));
    driver.conectarse(1, Coordenada(0,0));
    driver.conectarse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(9,0));
    driver.moverse(2, Coordenada(8,0));
    driver.moverse(2, Coordenada(7,0));
    driver.moverse(2, Coordenada(7,0));
    driver.moverse(2, Coordenada(6,0));
    driver.moverse(2, Coordenada(5,0));
    driver.moverse(2, Coordenada(4,0));
    driver.moverse(2, Coordenada(3,0));
    driver.moverse(2, Coordenada(2,0));
    driver.moverse(2, Coordenada(1,0));
    // Voy acercando al jugador 2 a la zona del pokemon 1 ... Pero cant movs sigue contando a pesar de que estan en la misma zona!!!
    ASSERT(driver.pokemons(1).Definido("Pikachu") && driver.pokemons(1).Significado("Pikachu") == 1);
    ASSERT(driver.cantPokemonsTotales() == 1);
    ASSERT(driver.cantMismaEspecie("Pikachu") == 1);

    driver.moverse(2, Coordenada(10,0));

    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    driver.moverse(2, Coordenada(10,0));
    ASSERT(driver.pokemons(1).Definido("Pikachu") && driver.pokemons(1).Significado("Pikachu") == 1);
    ASSERT(driver.cantPokemonsTotales() == 1);
    ASSERT(driver.cantMismaEspecie("Pikachu") == 1);


}

int main(int argc, char **argv)
{
//    RUN_TEST(test_entrenadoresPosibles)
//  RUN_TEST(test_constructor_con_mapa);RUN_TEST(test_agregar_jugadores);
//  RUN_TEST(test_agregar_pokemones);
//  RUN_TEST(test_conectarse);
//  RUN_TEST(test_moverse);
    RUN_TEST(test_capturar);
    return 0;
}

