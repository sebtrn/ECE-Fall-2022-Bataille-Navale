cmake_minimum_required(VERSION 3.23)
project(Bataille_Navale_2022_2023 C)

set(CMAKE_C_STANDARD 99)

add_executable(Bataille_Navale_2022_2023 main.c ship.h ship.c grille.h grille.c player.h player.c menu.h menu.c saisie.c array.c array.h header.h game.h game.c)
