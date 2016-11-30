cmake_minimum_required(VERSION 3.5)
project(algo2_tp3_pokemon_go)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES tests.cpp Juego.cpp Driver.h Driver.cpp Juego.h DiccString.cpp DiccString.h Mapa.h ConjPrior.h ConjPrior.cpp Coordenadatp3.cpp Mapa.cpp)
add_executable(algo2_tp3_pokemon_go ${SOURCE_FILES})