@echo off
g++ -c src/main.cpp -I"C:\Programing\C++\Library\SFML_GCC\include" -DSFML_STATIC
g++ main.o -o game -L "C:\Programing\C++\Library\SFML_GCC\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main -lsfml-audio