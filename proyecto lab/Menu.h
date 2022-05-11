#ifndef MENU_H_
#define MENU_H_
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
using namespace std;
/*
  Name: Menu creator 1.0
  Copyright: GPLV3
  Author:  Manuel González
  Date: 14/05/11 12:31
  Description: crea un menu en la cual se mostraran unas opciones las que el usuario tendra por escojer
  Correo:deathmanuel@gmail.com
*/


class Menu
{

public:
    Menu(Uint8 NumSelecciones, Uint32 altoOpcion, Uint32 anchocursor); //establece el numero de opciones a escojer por el usuario
    void SetColorBackground(Uint32 colorBack); //establece el color de fondo de el menu
    void SetColorCursor(Uint32 colorCursor); //establece el color de fondo de el cursor (si nno se va a colocar una imagen como cursor)
    void SetColorLineaCursor(Uint32 Color); //establece el color de la linea que guiara a el usuario a ecojer su opcion
    void SetImgFondo(char* fondo); //establece la imagen de fondo para el menu 
    void SetImgLinea(char* Linea2); //establece la imagen de fondo para el menu
    void SetImgCursor(char* cursor); //establece la imagen de fondo para el cursor
    void SetImgCursor(char* cursor, SDL_Surface* screen, Uint8 r, Uint8 g, Uint8 b); //establece la imagen de fondo para el cursor con color de fondo
    void SetPosCursor(Uint8 IdOpcion); //establece la posicion del cursor en el menu
    void AddPosCursor(int valor); //agrega +-1 a la posicion del cursor de menu
    void SetNombres(char* Nombres); //establece los nombres de que se mostraran en el menu (ejemplo:Nuevo juego,Abrir)
    void SetFuente(char* Fuente); //establece la fuente con la que se dibujaran los nombres de opciones
    void SetColorLetra(Uint8 r, Uint8 g, Uint8 b); //establece el color de la letra de los nombres
    void SetColorLetraSelect(Uint8 r, Uint8 g, Uint8 b); //establece el color de la letra que tiene seleccionada el cursor
    void SetMenuPos(Uint32 x, Uint32 y, Uint32 w, Uint32 h); //establece la posicion de l menu en el framebuffer
    void SetMaxSelecciones(Uint8 Valor); //establece el limite de opciones que el usuario puede escoger
    Uint8 GetPosCursor(); //regresa la posicion de el cursor
    void GetTextCursor(char* contenedor); //regresa el texto de la posicion de el cursor 
    void Actualizar(SDL_Surface* superficie); //Dibuja en la pantalla y actualiza los datos de el menu
    ~Menu();
private:
    Uint8 PosCursor; //guarda la posicion de el cursor en el menu
    SDL_Rect PosMenu; //guarda los datos de el tamaño y posicion de el menu en la pantalla
    Uint32 AltoOpcion; //guarda el alto de la opcion
    Uint32 AnchoCursor; //guarda el ancho de el cursor
    Uint8 MaxNumSelecciones; //guarda el maximo de selecciones que puede seleccionar el usuario
    Uint32 ColorBackground; //guarda el color de fondo
    Uint32 ColorLineaCursor; //guarda el color de la linea de el cursor
    Uint32 ColorCursor; //guarda el color de el cursor
    SDL_Color Letra; //guarda el color de la letra
    SDL_Color LetraSelect; //guarda el color de la letra que tiene la posicion de el cursor
    SDL_Surface* Cursor;
    SDL_Surface* Fondo;
    SDL_Surface* Linea;
    char* NombreOpciones; //guarda el nombre de las opciones que vera el usuario
    char TextActivo[100]; //guarda el texto actual que tiene la poscion de el cursor
    bool ConImgFondo; //guarda si el usuario selecciono una imagen de fondo para su menu
    bool ConCursorPersonalizado;//guarda si el usuario selecciono una imagen para el cursor
    bool colocadosnombre;//guarda si el usuario ingreso los nombres para el menu
    bool confuente; //guarda si el usuario selecciono una fuente para su programa
    bool ColorFondo;
    bool ConLineaPersonalizada;
    TTF_Font* fuente; //obligatoria de iniciar guarda la fuente seleccionada por el usuario
};
/*
            Funciones utiles
*/
void   AnimarSeleccion(Menu& a, SDL_Surface* sur); //Alterna el color de fondo de la linea de el cursor y el de la fuente

#endif /* MENU_H_ */

