
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "Menu.h"

using namespace std;

inline void SetPosRect(SDL_Rect& a, Uint32 x, Uint32 y, Uint32 w, Uint32 h)
{
    a.x = x; a.y = y; a.w = w; a.h = h;
}

void AnimarSeleccion(Menu& a, SDL_Surface* sur)
{
    a.SetColorLetraSelect(0, 0, 255);
    a.SetColorLineaCursor(1245);
    a.Actualizar(sur);
    SDL_Delay(100);
    a.SetColorLineaCursor(78945);
    a.SetColorLetraSelect(255, 0, 0);
    a.Actualizar(sur);
    SDL_Delay(100);

}

Menu::Menu(Uint8 NumSelecciones, Uint32 altoOpcion, Uint32 anchocursor)
{
    if (TTF_Init() == 0)
        atexit(TTF_Quit);
    this->PosCursor = 0; //posicion del cursor predeterminada a 0
    this->ConImgFondo = false;
    this->ConCursorPersonalizado = false;
    this->colocadosnombre = false;
    this->AltoOpcion = altoOpcion;
    this->AnchoCursor = anchocursor;
    this->MaxNumSelecciones = NumSelecciones;
    this->Letra.r = 255;
    this->Letra.g = 255;
    this->Letra.b = 255;
    this->LetraSelect.r = 255;
    this->LetraSelect.g = 0;
    this->LetraSelect.b = 0;
    this->ColorFondo = false;
    this->ConLineaPersonalizada = false;

    /*
      Establece nombres de opciones predeterminadas segun el numero de selecciones que dio el usuario

    */
    char* tmp = new char[strlen("Predeterminada") * NumSelecciones + NumSelecciones + 1];
    sprintf(tmp, "%s", ""); //se inicializa tmp
    char* tmp2 = new char[strlen("Predeterminada") + 3];
    for (int i = 0; i < NumSelecciones; i++)
    {
        if (i != (NumSelecciones - 1)) //si no es e ultimo 
            sprintf(tmp2, "%s%d%s", "Predeterminada", i, ",");
        else
            sprintf(tmp2, "%s%d", "Predeterminada", i);
        strcat(tmp, tmp2); //se agrega a tmp

    }
    SetNombres(tmp);
    delete[]tmp; //se libera la memoria
    delete[]tmp2;
    this->fuente = 0;
    this->PosMenu.x = 0;
    this->PosMenu.y = 0;
    this->confuente = false;
    this->PosMenu.w = this->AnchoCursor * NumSelecciones * 2;
    this->PosMenu.h = this->AltoOpcion * NumSelecciones * 2;
}
void Menu::SetColorBackground(Uint32 colorBack) //establece el color de fondo de el menu
{
    this->ColorBackground = colorBack;
    this->ColorFondo = true;
}
void Menu::SetMenuPos(Uint32 x, Uint32 y, Uint32 w, Uint32 h)
{
    this->PosMenu.x = x;
    this->PosMenu.y = y;
    this->PosMenu.w = w;
    this->PosMenu.h = h;

}
void Menu::SetColorCursor(Uint32 colorCursor) //establece el color de fondo de el cursor
{
    this->ColorCursor = colorCursor;
}
void Menu::SetColorLineaCursor(Uint32 Color) //establece el color de fondo de la linea formada por la posicion del cursor
{
    this->ColorLineaCursor = Color;
}
void Menu::SetColorLetra(Uint8 r, Uint8 g, Uint8 b)
{
    this->Letra.r = r;
    this->Letra.g = g;
    this->Letra.b = b;
}
void Menu::SetColorLetraSelect(Uint8 r, Uint8 g, Uint8 b)
{
    this->LetraSelect.r = r;
    this->LetraSelect.g = g;
    this->LetraSelect.b = b;
}


void Menu::SetImgFondo(char* fondo)
{
    if (this->ConImgFondo == false)
    {
        this->ConImgFondo = true;
        this->Fondo = IMG_Load(fondo);
        this->Fondo = SDL_DisplayFormat(this->Fondo);
        if (Fondo == NULL)
        {
            cerr << "Error con " << fondo << endl;
            this->ConImgFondo = false;
        }
    }

}
void Menu::SetImgCursor(char* cursor)
{
    if (this->ConCursorPersonalizado == false)
    {
        this->ConCursorPersonalizado = true;
        this->Cursor = IMG_Load(cursor);
        this->Cursor = SDL_DisplayFormat(this->Cursor);

        if (Cursor == NULL)
        {
            cerr << "Error con " << cursor << endl;
            this->ConCursorPersonalizado = false;
        }
    }
}
void Menu::SetImgCursor(char* cursor, SDL_Surface* screen, Uint8 r, Uint8 g, Uint8 b)
{
    if (this->ConCursorPersonalizado == false)
    {
        this->ConCursorPersonalizado = true;
        this->Cursor = IMG_Load(cursor);
        this->Cursor = SDL_DisplayFormat(this->Cursor);
        SDL_SetColorKey(Cursor, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, r, g, b));
        if (Cursor == NULL)
        {
            cerr << "Error con " << cursor << endl;
            this->ConCursorPersonalizado = false;
        }
    }
}


void Menu::SetImgLinea(char* Linea2) //establece la imagen de fondo para el menu
{
    if (this->ConLineaPersonalizada == false)
    {
        this->ConLineaPersonalizada = true;
        SDL_Surface* tmp = IMG_Load(Linea2);
        this->Linea = SDL_DisplayFormat(tmp);
        if (Linea == NULL)
        {
            cerr << "Error con " << Linea2 << endl;
            this->ConLineaPersonalizada = false;
        }
    }

}

void Menu::SetPosCursor(Uint8 IdOpcion)
{
    if (IdOpcion <= MaxNumSelecciones)
    {
        this->PosCursor = IdOpcion;
    }
    else
        cerr << "valor no valido de idOpcion=" << IdOpcion << ".!" << endl;
}
void Menu::AddPosCursor(int valor) //solo acepta 1 y -1
{

    if (this->PosCursor < this->MaxNumSelecciones && !(valor % 1))
    {

        if (valor == -1 && this->PosCursor - 1 >= 0)
        {
            this->PosCursor += valor;
        }
        else if (valor == 1 && this->PosCursor + 1 < this->MaxNumSelecciones)
        {
            this->PosCursor += valor;
        }

    }
    else
        cerr << "valor no valido.!" << endl;
}
void Menu::SetMaxSelecciones(Uint8 Valor)
{
    if (Valor > (this->PosMenu.h / this->AltoOpcion))
        cerr << "Valor no valido.!\nvalor Tiene que ser menor o igual a :" << this->PosMenu.h / this->AltoOpcion << endl;
    else if (Valor <= this->PosMenu.h / this->AltoOpcion)
    {
        this->MaxNumSelecciones = static_cast<int>(Valor);
    }
}
Uint8 Menu::GetPosCursor()
{
    return this->PosCursor;
}



void Menu::GetTextCursor(char* contenedor)
{
    sprintf(contenedor, "%s", TextActivo);
}
void Menu::Actualizar(SDL_Surface* superficie)
{
    SDL_Rect tmp, tmp2;

    if (this->ConImgFondo == true)
    {
        SetPosRect(tmp, 0, 0, this->PosMenu.w, this->PosMenu.h);
        SetPosRect(tmp2, 0, 0, tmp.w, this->PosMenu.h);

        SDL_BlitSurface(Fondo, &tmp, superficie, &this->PosMenu);
    }
    else
    {
        if (this->ColorFondo == true)
            SDL_FillRect(superficie, &this->PosMenu, this->ColorBackground); //dibuja el cuadro de el menu
    }


    if (this->ConLineaPersonalizada == false)
    {

        SetPosRect(tmp, this->PosMenu.x + this->AnchoCursor, this->PosCursor * this->AltoOpcion + this->PosMenu.y, this->PosMenu.w - this->AnchoCursor, this->AltoOpcion);
        SDL_FillRect(superficie, &tmp, ColorLineaCursor); // el color de la franja que posiciona a el cursor
    }
    else
    {
        SetPosRect(tmp, this->PosMenu.x + this->AnchoCursor, this->PosCursor * this->AltoOpcion + this->PosMenu.y, this->PosMenu.w - this->AnchoCursor, this->AltoOpcion);
        SetPosRect(tmp2, 0, 0, this->PosMenu.w, this->AltoOpcion);

        SDL_BlitSurface(this->Linea, &tmp2, superficie, &tmp); // el color de la franja que posiciona a el cursor
    }
    SetPosRect(tmp, this->PosMenu.x, this->PosCursor * this->AltoOpcion + this->PosMenu.y, this->AnchoCursor, this->AltoOpcion);

    if (this->ConCursorPersonalizado == false)
        SDL_FillRect(superficie, &tmp, this->ColorCursor); //dibuja el cuadro de el cursor
    else
    {
        SetPosRect(tmp2, 0, 0, this->AnchoCursor, this->AltoOpcion);
        SDL_BlitSurface(Cursor, &tmp2, superficie, &tmp);
    }
    if (confuente == true)
    {
        char* proximo;
        int count = 0;
        SDL_Color color;
        tmp.x = tmp.x + this->AnchoCursor;
        char* tmpText = new char[strlen(this->NombreOpciones + 1)];
        sprintf(tmpText, "%s", NombreOpciones);
        for (proximo = strtok(tmpText, ","); proximo; count++) {
            // Desmembramos la cadena separada por comas
            tmp.y = count * this->AltoOpcion + this->PosMenu.y;
            SDL_Surface* ContTexto;
            if (tmp.y == this->PosCursor * this->AltoOpcion + this->PosMenu.y)
            {
                ContTexto = TTF_RenderText_Blended(fuente, proximo, LetraSelect);
                sprintf(TextActivo, "%s", proximo);
            }
            else// Renderizamos
            {
                ContTexto = TTF_RenderText_Blended(fuente, proximo, Letra);
            }
            tmp.w = ContTexto->w;
            tmp.h = ContTexto->h;
            SDL_BlitSurface(ContTexto, NULL, superficie, &tmp);
            SDL_FreeSurface(ContTexto);
            proximo = strtok(NULL, ",\0");
        }
        delete[]tmpText;
    }
    SDL_Flip(superficie);
}


void Menu::SetNombres(char* Nombres)
{

    if (this->colocadosnombre == true)
    {
        delete[] this->NombreOpciones;
    }
    this->colocadosnombre = true;
    this->NombreOpciones = new char[strlen(Nombres + 1)];
    sprintf(this->NombreOpciones, "%s", Nombres);

}

void Menu::SetFuente(char* Fuente)
{
    this->fuente = TTF_OpenFont(Fuente, (this->AltoOpcion) - AltoOpcion / 4);
    confuente = true;
}
Menu::~Menu()
{
    if (this->confuente == true)
    {
        delete[] this->NombreOpciones;
    }
    SDL_FreeSurface(Cursor);
    SDL_FreeSurface(Fondo);
}
