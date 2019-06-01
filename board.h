/**
 * @file board.h
 * @brief funciones de board
 * @author Juan Carlos López Morales
 * @date 30/5/2019
 * @version 1.9
 */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "cabecera.h"
#include <unistd.h>

using namespace std;


/**
 * @class   Board
 * @fn      Se encarga de hacer el tablero
 * @brief   Dibuja la matriz tablero en el juego
 */
class Board {
sf::RectangleShape **cells;
int nrows, ncols;
int size;
int faseactual=1;
int vidas=3;
sf::RectangleShape *current;
int x=-1;
int y=-1;
int valoresnulos=0;
int **matriz;
int original[9][9];
int nivel=1;
sf::Font font;
sf::Text **text;
string valor_casilla;
bool puedoborrar=false;
bool numero_mal_colocado;
bool ganar=false;
Cabecera *cabecera;
const int thickness=2.0;
sf::SoundBuffer buffer;
sf::Sound sound;


public:
/**
 * @brief Constructor de board
 * @param nrows numero de filas del sudoku
 * @param ncols numero de columnas del sudoku
 * @param size tamaño del tablero
 */
Board(int nrows, int ncols, int size);
/**
 * @brief Da color al tablero
 * @param nrows numero de filas del sudoku
 * @param ncols numero de columnas del sudoku
 */
void color(int nrows, int ncols);
/**
 * @brief dibuja la cabecera
 * @param windows variable de la SFML que gestiona la ventana
 * @post a y b tienen sus valores intercambiados
 */
void draw(sf::RenderWindow &windows);
/**
 * @brief establece la celda actual
 * @param posx posición en el eje x actual
 * @param posy posición en el eje y actual
 * @post la celda actual quedará marcada en azul
 */
void action(int posx, int posy);
/**
 * @brief Modifica la la casilla actual a través del teclado
 * @param px posición en el eje x actual
 * @param py posición en el eje y actual
 */
void actionByKeyboard(int px, int py);
/**
 * @brief Carga los valores del nivel en una matriz
 * @param fase numero de la fase actual
 */
void carga_nivel(int fase);
/**
 * @brief actualiza la matriz del tablero
 * @param num numero que queremos insertar en la casilla actual
 * @post a y b tienen sus valores intercambiados
 */
void update_board(int num);
/**
 * @brief crea las celdas y texto del tablero
 * @param nrows numero de filas del sudoku
 * @param ncols numero de columnas del sudoku
 * @param size tamaño del tablero
 */
void draw_and_text_board(int nrows,int ncols,int size);
/**
 * @brief comprueba que los valores del tablero esten correctos
 */
void comprueba_casilla();
/**
 * @brief Cuenta las casillas del tablero inicial que estan vacias
 */
void contar_casillas_0();
/**
 * @brief Truco opcional para obtener 99 vidas
 */
void get_max_lifes();

/**
 * @brief Destructor del tablero
 */
~Board(void);
};
