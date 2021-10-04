// 14.09.21 SL
// Prima versione in prova per Space inavders

// inclusione framewrok Arduino per VSCode
#include <Arduino.h>

// Inclusione file configurazone pin arduino
#include "config_pins.h"
#include "definizioni.h"

// Inclusione libreria VGAX, vedi platformio.ini
// VGAX_WIDTH larghezza massima max 120
// VGAX_EIGHT altezza della risoluziona max 60
// solo due bit per colore 00-nero, 01-rosso, 10-verde, 11-giallo
#include <VGAX.h>
VGAX vga;
// static const char str_SpaceInvaders[] PROGMEM = "SpaceInvaders";

// Iclusione file con il font dalla libreria
#include "vga_font.h"
// Iclusione file con le stringhe di testo da stampare
#include "vga_stringhe.h"

// Inclusione funzioni
#include "F_disegnaBordi.h"
#include "F_muoviPotBarra.h"
#include "F_disegnaAlieni.h"
// #include "F_GameSpaceInvaders.h"
#include "F_GameSpaceInvaders2.h"
#include "F_GamePong.h"
#include "F_GameSnake.h"
#include "F_scriviPunteggio.h"

void setup()
{
    // Serial.begin(9600);
    // led su scheda sviluppo
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(2, LOW);
    // ingresso pulsante su scheda viluppo
    pinMode(PIN_PULS, INPUT_PULLUP);
    // ingresso pulsante di sparo
    pinMode(PIN_SW, INPUT);
    // ingressi pulsanti di comando sx, dx, ok
    pinMode(PIN_OK, INPUT);
    pinMode(PIN_SX, INPUT);
    pinMode(PIN_DX, INPUT);

    vga.begin();
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    rigaStringa = 0;
    scrollX = 0;
    unsigned long int t = 0;
    do
    {
        if ((vga.millis() - t) > 50) // millisecondi di ritardo - non bloccante
        {
            vga.clear(NERO);
            disegnaBordi(ROSSO);
            vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, ArduinoConsoleGame, scrollX, 20, VERDE);
            vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, byTebraxin, scrollX, 40, GIALLO);
            scrollX++;
            t = vga.millis(); // 20 millisecondi di ritardo - non bloccante
            // vga.tone(random(150, 300));
        }
        if (scrollX == VGAX_WIDTH)
            scrollX = -VGAX_WIDTH / 2;
    } while ((digitalRead(PIN_SX) == 0) && (digitalRead(PIN_DX) == 0) && (digitalRead(PIN_OK) == 0)); // se premo uno dei tre tasti esco dal setup
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    // vga.noTone();
}

void menu_00_principale() // Inizio funzione per richiamo menù principale
{
    vga.delay(RITARDO_SCHERMATA);
    unsigned long int t_ok = 0;
    unsigned long int t_sx = 0;
    bool puls_ok = false;
    bool puls_sx = false;
    rigaStringa = 0;
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, ArduinoConsoleGame, INIZIO_SX_MENU, rigaStringa += STEP_MENU, VERDE);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, byTebraxin, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiOKcontinuare, INIZIO_SX_MENU, rigaStringa += STEP_MENU, VERDE);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiSXcopyright, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    do
    {
        puls_ok = digitalRead(PIN_OK); // debounce software pulsante OK
        if (puls_ok)                   // debounce software pulsante OK
        {
            if ((vga.millis() - t_ok * 2) > DEBOUNCE_PULS)
            {
                puls_ok = true;
                t_ok = vga.millis();
                statoMenu = 11; // passo al menù selezione
                break;          // passo al menù selezione
            }
            else
                puls_ok = false;
        }

        puls_sx = digitalRead(PIN_SX); // debounce software pulsante SX
        if (puls_sx)                   // debounce software pulsante SX
        {
            if ((vga.millis() - t_sx) > DEBOUNCE_PULS)
            {
                puls_sx = true;
                t_sx = vga.millis();
                statoMenu = 12; // passo al menù copyright
                break;          // passo al menù copyright
            }
            else
                puls_sx = false;
        }

    } while (!(puls_ok || puls_sx));
} // Fine funzione per richiamo menù principale

void menu_11_selezione() // Inizio funzione per selezione menù di gioco
{
    vga.delay(RITARDO_SCHERMATA);
    unsigned long int t_ok = 0;
    unsigned long int t_sx = 0;
    unsigned long int t_dx = 0;
    rigaStringa = 0;
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, menuSelezioneGioco, INIZIO_SX_MENU, rigaStringa += STEP_MENU, VERDE);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, giocoSpaceInvaders, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, giocoPong, INIZIO_SX_MENU, rigaStringa += STEP_MENU, VERDE);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, giocoSnake, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiSXindietro, INIZIO_SX_MENU, rigaStringa += STEP_MENU, VERDE);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiDXselezione, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiOKcontinuare, INIZIO_SX_MENU, rigaStringa += STEP_MENU, VERDE);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, giocoSelezionato, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra1, VGAX_WIDTH - 20, rigaStringa, GIALLO);
    int selezione = 1; // variabile che memorizza il menù selezionato
    do
    {
        if (digitalRead(PIN_DX))                       // debounce software pulsante DX
            if ((vga.millis() - t_dx) > DEBOUNCE_PULS) // debounce software pulsante DX
            {
                selezione++;       // seleziono il mneù successio
                if (selezione > 3) // controllo che non vada oltre il limite del menù
                    selezione = 1;
                switch (selezione)
                {
                case 1:
                    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra2, VGAX_WIDTH - 20, rigaStringa, NERO);
                    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra3, VGAX_WIDTH - 20, rigaStringa, NERO);
                    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra1, VGAX_WIDTH - 20, rigaStringa, GIALLO);
                    break;
                case 2:
                    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra1, VGAX_WIDTH - 20, rigaStringa, NERO);
                    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra3, VGAX_WIDTH - 20, rigaStringa, NERO);
                    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra2, VGAX_WIDTH - 20, rigaStringa, GIALLO);
                    break;
                case 3:
                    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra1, VGAX_WIDTH - 20, rigaStringa, NERO);
                    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra2, VGAX_WIDTH - 20, rigaStringa, NERO);
                    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra3, VGAX_WIDTH - 20, rigaStringa, GIALLO);
                    break;
                }
                t_dx = vga.millis();
            }

        if (digitalRead(PIN_OK))                       // debounce software pulsante OK
            if ((vga.millis() - t_ok) > DEBOUNCE_PULS) // debounce software pulsante OK
            {
                t_ok = vga.millis();
                switch (selezione)
                {
                case 1:
                    statoMenu = 21; // selezione gioco space invaders
                    break;
                case 2:
                    statoMenu = 22; // selezione gioco pong
                    break;
                case 3:
                    statoMenu = 23; // selezione gioco gioco3
                    break;
                }
                break; // uscita dal ciclo while
            }

        if (digitalRead(PIN_SX))                       // debounce software pulsante SX
            if ((vga.millis() - t_sx) > DEBOUNCE_PULS) // debounce software pulsante SX
            {
                t_sx = vga.millis();
                statoMenu = 00; // passo al menù principale
                break;          // passo al menù principale
            }
    } while (1);
} // Fine funzione per selezione menù di gioco

void menu_12_copyright() // Inizio funzione per display info copyright
{
    vga.delay(RITARDO_SCHERMATA);
    rigaStringa = 0;
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, menuCopyright, INIZIO_SX_MENU, rigaStringa += STEP_MENU, VERDE);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, fattoio, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, github, INIZIO_SX_MENU, rigaStringa += STEP_MENU, VERDE);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiSXindietro, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    do
    {
    } while (digitalRead(PIN_SX) == 0);
    statoMenu = 00; // torno al menù principale
} // Fine funzione per display info copyright

void menu_21_inizio_spaceinvaders()
{
    vga.delay(RITARDO_SCHERMATA);
    unsigned long int t_ok = 0;
    unsigned long int t_sx = 0;
    rigaStringa = 0;
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, menuSpaceInvaders, INIZIO_SX_MENU, rigaStringa += STEP_MENU, VERDE);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiOKcontinuare, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiSXindietro, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiSxDxOk, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    do
    {
        if (digitalRead(PIN_OK))                       // debounce software pulsante DX
            if ((vga.millis() - t_ok) > DEBOUNCE_PULS) // debounce software pulsante DX
            {
                statoMenu = 31; // stato gioco = livello menù
                break;          // uscita dal ciclo while
            }

        if (digitalRead(PIN_SX))                       // debounce software pulsante DX
            if ((vga.millis() - t_sx) > DEBOUNCE_PULS) // debounce software pulsante DX
            {
                statoMenu = 11; // torno al menù precedente
                break;          // uscita dal ciclo while
            }
    } while (1);
}

void menu_22_inizio_pong()
{
    vga.delay(RITARDO_SCHERMATA);
    unsigned long int t_ok = 0;
    unsigned long int t_sx = 0;
    rigaStringa = 0;
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, menuPong, INIZIO_SX_MENU, rigaStringa += STEP_MENU, VERDE);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiOKcontinuare, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiSXindietro, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiSxDxOk, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    do
    {
        if (digitalRead(PIN_OK))                       // debounce software pulsante DX
            if ((vga.millis() - t_ok) > DEBOUNCE_PULS) // debounce software pulsante DX
            {
                statoMenu = 32; // stato gioco = livello menù
                break;          // uscita dal ciclo while
            }

        if (digitalRead(PIN_SX))                       // debounce software pulsante DX
            if ((vga.millis() - t_sx) > DEBOUNCE_PULS) // debounce software pulsante DX
            {
                statoMenu = 11; // torno al menù precedente
                break;          // uscita dal ciclo while
            }
    } while (1);
}

void menu_23_inizio_snake()
{
    vga.delay(RITARDO_SCHERMATA);
    unsigned long int t_ok = 0;
    unsigned long int t_sx = 0;
    rigaStringa = 0;
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, menuSnake, INIZIO_SX_MENU, rigaStringa += STEP_MENU, VERDE);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiOKcontinuare, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiSXindietro, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiSxDxOk, INIZIO_SX_MENU, rigaStringa += STEP_MENU, GIALLO);
    do
    {
        if (digitalRead(PIN_OK))                       // debounce software pulsante DX
            if ((vga.millis() - t_ok) > DEBOUNCE_PULS) // debounce software pulsante DX
            {
                statoMenu = 33; // stato gioco = livello menù
                break;          // uscita dal ciclo while
            }

        if (digitalRead(PIN_SX))                       // debounce software pulsante DX
            if ((vga.millis() - t_sx) > DEBOUNCE_PULS) // debounce software pulsante DX
            {
                statoMenu = 11; // torno al menù precedente
                break;          // uscita dal ciclo while
            }
    } while (1);
}

void loop() // Inizio loop principale
{
    vga.delay(RITARDO_SCHERMATA);
    switch (statoMenu)
    {
    case 00:
        menu_00_principale(); // funzione per richiamo menù principale
        break;
    case 11:
        menu_11_selezione(); // funzione per selezione menù di gioco
        break;
    case 12:
        menu_12_copyright(); // funzione per display info copyright
        break;
    case 21:
        menu_21_inizio_spaceinvaders(); // menu inizio gioco space invaders
        break;
    case 31:
        // menu_31_GameSpaceInvaders(); // gioco vero e proprio
        menu_31_GameSpaceInvaders2(); // gioco vero e proprio
        break;
    case 22:
        menu_22_inizio_pong(); // menu inizio gioco pong
        break;
    case 32:
        menu_32_GamePong(); // gioco vero e proprio
        break;
    case 23:
        menu_23_inizio_snake(); // menu inizio gioco pong
        break;
    case 33:
        menu_33_GameSnake(); // gioco vero e proprio
        break;
    default:
        break;
    }
} // Fine loop principale