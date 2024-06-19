# **BUSCAMINAS C++**

Un proyecto escolar que simula el juego de Buscaminas escrito en c++, utilizando la librería SFML.
El juego consiste en despejar todas las casillas de una pantalla que no oculten una mina.

Algunas casillas tienen un número, el cual indica la cantidad de minas que hay en las casillas circundantes. Así, si una casilla tiene el número 3, significa que de las ocho casillas que hay alrededor (si no es en una esquina o borde) hay 3 con minas y 5 sin minas. Si se descubre una casilla sin número indica que ninguna de las casillas vecinas tiene mina y éstas se descubren automáticamente.

Si se descubre una casilla con una mina se pierde la partida.

Se puede poner una marca en las casillas que el jugador piensa que hay minas para ayudar a descubrir las que están cerca.

## Caracteristicas

- Incluye 3 dificultades (Fácil, intermedio y díficil)
+ Nivel Fácil: Tablero de 10*10 y 10 Minas
+ Nivel Intermedio: Tablero de 20*20 y 20 Minas
+ Nivel Díficil: Tablero de 30*30 y 30 Minas
- Programa minimalista
- Controles básicos

## Instalación
Para utilizar este programa necesitas los siguientes requisitos:
+ Instalar o utilizar un compilador de C++(MinGW, Visual C++, etc)
+ Instalar SFML, puedes hacerlo desde su página(https://www.sfml-dev.org/download.php), o desde un compilador como MinGW
+ Descargar este repositorio, puedes usar este comando: git clone https://github.com/ioshua8aM/Buscaminas.git
+ Instala cmake, lo necesitaras para compilar el proyecto
+ Usa el makefile para counstruir el programa
+ Ejecuta el programa

## Capturas de pantalla
+ ![Captura1]("C:\Users\user\Pictures\Screenshots\Captura1.png")
+ ![Captura2]("C:\Users\user\Pictures\Screenshots\Captura2.png")
+ ![Captura3]("C:\Users\user\Pictures\Screenshots\Captura3.png")

## Video de ejecución
+ https://youtu.be/B8lb8bZ8ZbE
```bash
Give examples