/**
 * @file cabecera.h
 * @brief funciones de cabecera
 * @author Juan Carlos López Morales
 * @date 30/5/2019
 * @version 1.9
 */

#ifndef _CABECERA_H
#define _CABECERA_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
/**
 * @class   Cabecera
 * @brief  Dibuja los datos del jugador en el juego
 */
class Cabecera {
sf::RectangleShape *cell;
sf::Font font;
sf::Text *text;
string valorcabecera;


public:
/**
 * @brief Constructor de cabecera
 * @param sizex tamaño en el eje x de la cabecera
 * @param sizey tamaño en el eje y de la cabecera
 * @param vida vidas del jugador actuales
 * @param fase fase del jugador actual
 * @param huecos huecos disponibles para rellenar por el jugador
 * @param position espacio donde insertar el texto en la cabecera
 * @post se inicializan las variables de la cabecera
 */
Cabecera(int sizex, int sizey, int vida, int fase, int huecos, int position);
/**
 * @brief dibuja la cabecera
 * @param windows variable de la SFML que gestiona la ventana
 * @post a y b tienen sus valores intercambiados
 */
void draw(sf::RenderWindow &windows);
/**
 * @brief Actualiza el texto
 * @param text texto nuevo de la cabecera
 */
void updateText(std::string text);
/**
 * @brief Destructor de la cabecera
 */
~Cabecera(void);
};

#endif
