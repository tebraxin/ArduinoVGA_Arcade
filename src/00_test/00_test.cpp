// inclusione framewrok Arduino per VSCode
#include <Arduino.h>

// Inclusione file configurazone pin arduino
#include "config_pins.h"

// 10.09.21 sl prova linee vga
// VGAX_WIDTH larghezza massima max 120
// VGAX_EIGHT altezza della risoluziona max 60
// solo due bit per colore 00-nero, 01-rosso, 10-verde, 11-giallo

#include <VGAX.h>
VGAX vga;
static const char str0[] PROGMEM = " Space Invaders";
static const char str1[] PROGMEM = " by tebraxin";

//font generated from BITFONZI - by Sandro Maffiodo
#define FNT_NANOFONT_HEIGHT 6
#define FNT_NANOFONT_SYMBOLS_COUNT 95
//data size=570 bytes
const unsigned char fnt_nanofont_data[FNT_NANOFONT_SYMBOLS_COUNT][1 + FNT_NANOFONT_HEIGHT] PROGMEM = {
    {
        1,
        128,
        128,
        128,
        0,
        128,
        0,
    }, //glyph '!' code=0
    {
        3,
        160,
        160,
        0,
        0,
        0,
        0,
    }, //glyph '"' code=1
    {
        5,
        80,
        248,
        80,
        248,
        80,
        0,
    }, //glyph '#' code=2
    {
        5,
        120,
        160,
        112,
        40,
        240,
        0,
    }, //glyph '$' code=3
    {
        5,
        136,
        16,
        32,
        64,
        136,
        0,
    }, //glyph '%' code=4
    {
        5,
        96,
        144,
        104,
        144,
        104,
        0,
    }, //glyph '&' code=5
    {
        2,
        128,
        64,
        0,
        0,
        0,
        0,
    }, //glyph ''' code=6
    {
        2,
        64,
        128,
        128,
        128,
        64,
        0,
    }, //glyph '(' code=7
    {
        2,
        128,
        64,
        64,
        64,
        128,
        0,
    }, //glyph ')' code=8
    {
        3,
        0,
        160,
        64,
        160,
        0,
        0,
    }, //glyph '*' code=9
    {
        3,
        0,
        64,
        224,
        64,
        0,
        0,
    }, //glyph '+' code=10
    {
        2,
        0,
        0,
        0,
        0,
        128,
        64,
    }, //glyph ',' code=11
    {
        3,
        0,
        0,
        224,
        0,
        0,
        0,
    }, //glyph '-' code=12
    {
        1,
        0,
        0,
        0,
        0,
        128,
        0,
    }, //glyph '.' code=13
    {
        5,
        8,
        16,
        32,
        64,
        128,
        0,
    }, //glyph '/' code=14
    {
        4,
        96,
        144,
        144,
        144,
        96,
        0,
    }, //glyph '0' code=15
    {
        3,
        64,
        192,
        64,
        64,
        224,
        0,
    }, //glyph '1' code=16
    {
        4,
        224,
        16,
        96,
        128,
        240,
        0,
    }, //glyph '2' code=17
    {
        4,
        224,
        16,
        96,
        16,
        224,
        0,
    }, //glyph '3' code=18
    {
        4,
        144,
        144,
        240,
        16,
        16,
        0,
    }, //glyph '4' code=19
    {
        4,
        240,
        128,
        224,
        16,
        224,
        0,
    }, //glyph '5' code=20
    {
        4,
        96,
        128,
        224,
        144,
        96,
        0,
    }, //glyph '6' code=21
    {
        4,
        240,
        16,
        32,
        64,
        64,
        0,
    }, //glyph '7' code=22
    {
        4,
        96,
        144,
        96,
        144,
        96,
        0,
    }, //glyph '8' code=23
    {
        4,
        96,
        144,
        112,
        16,
        96,
        0,
    }, //glyph '9' code=24
    {
        1,
        0,
        128,
        0,
        128,
        0,
        0,
    }, //glyph ':' code=25
    {
        2,
        0,
        128,
        0,
        0,
        128,
        64,
    }, //glyph ';' code=26
    {
        3,
        32,
        64,
        128,
        64,
        32,
        0,
    }, //glyph '<' code=27
    {
        3,
        0,
        224,
        0,
        224,
        0,
        0,
    }, //glyph '=' code=28
    {
        3,
        128,
        64,
        32,
        64,
        128,
        0,
    }, //glyph '>' code=29
    {
        4,
        224,
        16,
        96,
        0,
        64,
        0,
    }, //glyph '?' code=30
    {
        4,
        96,
        144,
        176,
        128,
        112,
        0,
    }, //glyph '@' code=31
    {
        4,
        96,
        144,
        240,
        144,
        144,
        0,
    }, //glyph 'A' code=32
    {
        4,
        224,
        144,
        224,
        144,
        224,
        0,
    }, //glyph 'B' code=33
    {
        4,
        112,
        128,
        128,
        128,
        112,
        0,
    }, //glyph 'C' code=34
    {
        4,
        224,
        144,
        144,
        144,
        224,
        0,
    }, //glyph 'D' code=35
    {
        4,
        240,
        128,
        224,
        128,
        240,
        0,
    }, //glyph 'E' code=36
    {
        4,
        240,
        128,
        224,
        128,
        128,
        0,
    }, //glyph 'F' code=37
    {
        4,
        112,
        128,
        176,
        144,
        112,
        0,
    }, //glyph 'G' code=38
    {
        4,
        144,
        144,
        240,
        144,
        144,
        0,
    }, //glyph 'H' code=39
    {
        3,
        224,
        64,
        64,
        64,
        224,
        0,
    }, //glyph 'I' code=40
    {
        4,
        240,
        16,
        16,
        144,
        96,
        0,
    }, //glyph 'J' code=41
    {
        4,
        144,
        160,
        192,
        160,
        144,
        0,
    }, //glyph 'K' code=42
    {
        4,
        128,
        128,
        128,
        128,
        240,
        0,
    }, //glyph 'L' code=43
    {
        5,
        136,
        216,
        168,
        136,
        136,
        0,
    }, //glyph 'M' code=44
    {
        4,
        144,
        208,
        176,
        144,
        144,
        0,
    }, //glyph 'N' code=45
    {
        4,
        96,
        144,
        144,
        144,
        96,
        0,
    }, //glyph 'O' code=46
    {
        4,
        224,
        144,
        224,
        128,
        128,
        0,
    }, //glyph 'P' code=47
    {
        4,
        96,
        144,
        144,
        144,
        96,
        16,
    }, //glyph 'Q' code=48
    {
        4,
        224,
        144,
        224,
        160,
        144,
        0,
    }, //glyph 'R' code=49
    {
        4,
        112,
        128,
        96,
        16,
        224,
        0,
    }, //glyph 'S' code=50
    {
        3,
        224,
        64,
        64,
        64,
        64,
        0,
    }, //glyph 'T' code=51
    {
        4,
        144,
        144,
        144,
        144,
        96,
        0,
    }, //glyph 'U' code=52
    {
        3,
        160,
        160,
        160,
        160,
        64,
        0,
    }, //glyph 'V' code=53
    {
        5,
        136,
        168,
        168,
        168,
        80,
        0,
    }, //glyph 'W' code=54
    {
        4,
        144,
        144,
        96,
        144,
        144,
        0,
    }, //glyph 'X' code=55
    {
        3,
        160,
        160,
        64,
        64,
        64,
        0,
    }, //glyph 'Y' code=56
    {
        4,
        240,
        16,
        96,
        128,
        240,
        0,
    }, //glyph 'Z' code=57
    {
        2,
        192,
        128,
        128,
        128,
        192,
        0,
    }, //glyph '[' code=58
    {
        5,
        128,
        64,
        32,
        16,
        8,
        0,
    }, //glyph '\' code=59
    {
        2,
        192,
        64,
        64,
        64,
        192,
        0,
    }, //glyph ']' code=60
    {
        5,
        32,
        80,
        136,
        0,
        0,
        0,
    }, //glyph '^' code=61
    {
        4,
        0,
        0,
        0,
        0,
        240,
        0,
    }, //glyph '_' code=62
    {
        2,
        128,
        64,
        0,
        0,
        0,
        0,
    }, //glyph '`' code=63
    {
        3,
        0,
        224,
        32,
        224,
        224,
        0,
    }, //glyph 'a' code=64
    {
        3,
        128,
        224,
        160,
        160,
        224,
        0,
    }, //glyph 'b' code=65
    {
        3,
        0,
        224,
        128,
        128,
        224,
        0,
    }, //glyph 'c' code=66
    {
        3,
        32,
        224,
        160,
        160,
        224,
        0,
    }, //glyph 'd' code=67
    {
        3,
        0,
        224,
        224,
        128,
        224,
        0,
    }, //glyph 'e' code=68
    {
        2,
        64,
        128,
        192,
        128,
        128,
        0,
    }, //glyph 'f' code=69
    {
        3,
        0,
        224,
        160,
        224,
        32,
        224,
    }, //glyph 'g' code=70
    {
        3,
        128,
        224,
        160,
        160,
        160,
        0,
    }, //glyph 'h' code=71
    {
        1,
        128,
        0,
        128,
        128,
        128,
        0,
    }, //glyph 'i' code=72
    {
        2,
        0,
        192,
        64,
        64,
        64,
        128,
    }, //glyph 'j' code=73
    {
        3,
        128,
        160,
        192,
        160,
        160,
        0,
    }, //glyph 'k' code=74
    {
        1,
        128,
        128,
        128,
        128,
        128,
        0,
    }, //glyph 'l' code=75
    {
        5,
        0,
        248,
        168,
        168,
        168,
        0,
    }, //glyph 'm' code=76
    {
        3,
        0,
        224,
        160,
        160,
        160,
        0,
    }, //glyph 'n' code=77
    {
        3,
        0,
        224,
        160,
        160,
        224,
        0,
    }, //glyph 'o' code=78
    {
        3,
        0,
        224,
        160,
        160,
        224,
        128,
    }, //glyph 'p' code=79
    {
        3,
        0,
        224,
        160,
        160,
        224,
        32,
    }, //glyph 'q' code=80
    {
        3,
        0,
        224,
        128,
        128,
        128,
        0,
    }, //glyph 'r' code=81
    {
        2,
        0,
        192,
        128,
        64,
        192,
        0,
    }, //glyph 's' code=82
    {
        3,
        64,
        224,
        64,
        64,
        64,
        0,
    }, //glyph 't' code=83
    {
        3,
        0,
        160,
        160,
        160,
        224,
        0,
    }, //glyph 'u' code=84
    {
        3,
        0,
        160,
        160,
        160,
        64,
        0,
    }, //glyph 'v' code=85
    {
        5,
        0,
        168,
        168,
        168,
        80,
        0,
    }, //glyph 'w' code=86
    {
        3,
        0,
        160,
        64,
        160,
        160,
        0,
    }, //glyph 'x' code=87
    {
        3,
        0,
        160,
        160,
        224,
        32,
        224,
    }, //glyph 'y' code=88
    {
        2,
        0,
        192,
        64,
        128,
        192,
        0,
    }, //glyph 'z' code=89
    {
        3,
        96,
        64,
        192,
        64,
        96,
        0,
    }, //glyph '{' code=90
    {
        1,
        128,
        128,
        128,
        128,
        128,
        0,
    }, //glyph '|' code=91
    {
        3,
        192,
        64,
        96,
        64,
        192,
        0,
    }, //glyph '}' code=92
    {
        3,
        96,
        192,
        0,
        0,
        0,
        0,
    }, //glyph '~' code=93
    {
        4,
        48,
        64,
        224,
        64,
        240,
        0,
    }, //glyph '£' code=94
};

// Variabili di programma
unsigned long time1, time2 = 0;
unsigned long delta = 10000;
bool stato = LOW;
int pxx, pyy = 1;
int posPotX = 0; // posizione X della barra letta dal potenziometro

// Costanti di programma
#define HALF_SIZE int(VGAX_HEIGHT / 2)
#define BARRA_Y VGAX_HEIGHT - 3 // pixel dal fondo per altezza barra
// costanti per i 4 colori della libreira
// solo due bit per colore 00-nero, 01-rosso, 10-verde, 11-giallo
#define NERO 0           // codice per colore nero
#define ROSSO 1          // codice per colore rosso
#define VERDE 2          // codice per colore verde
#define GIALLO 3         // codice per colore giallo
#define BARRA_L 5        // lunghezza pixel barra
#define ALIENI_RIGHE 3   // numero di righe di alieni
#define ALIENI_COLONNE 8 // numero di alieni su una riga (colonne)
#define RITARDO_SHORT 10       // millisecondi di RITARDO_SHORT per uso in vga.millis

// funzione per disegnare i bordi in rosso su sfondo
void disegnaBordi(int colore)
{
    for (int plx = 0; plx < VGAX_WIDTH; plx++) // bordo alto
        vga.putpixel(plx, 0, colore);
    for (int ply = 0; ply < VGAX_HEIGHT; ply++) // bordo destro
        vga.putpixel(VGAX_WIDTH - 1, ply, colore);
    for (int plx = 0; plx < VGAX_WIDTH; plx++) // bordo basso
        vga.putpixel(plx, VGAX_HEIGHT - 1, colore);
    for (int ply = 0; ply < VGAX_HEIGHT; ply++) // bordo sinistro
        vga.putpixel(0, ply, colore);
}

// funzione per disegnare pixel random con suono alla pressione del tasto sulla board
void randomPixel()
{
    vga.putpixel(pxx, pyy, GIALLO); // disegno pixel
    vga.delay(500);
    time1 = time2;
    vga.putpixel(pxx, pyy, NERO);     // cancello pixel
    pxx = random(1, VGAX_WIDTH - 1);  // nuova coordinata casuale
    pyy = random(1, VGAX_HEIGHT - 1); // nuova coordinata casuale
}

// funzione per disegno barra da 5 pixel
void barra()
{
    int cx = 1;                             // parto da sinistra
    while (cx < (VGAX_WIDTH - BARRA_L - 1)) // mi fermo prima della fine per la barra
    {
        for (int xbarra = cx; xbarra <= cx + BARRA_L; xbarra++) // ciclo per disegno barra
            vga.putpixel(xbarra, HALF_SIZE, GIALLO);
        vga.delay(RITARDO_SHORT * 5);
        for (int xbarra = cx; xbarra <= cx + BARRA_L; xbarra++) // ciclo per cancella barra
            vga.putpixel(xbarra, HALF_SIZE, NERO);
        cx++; // spostamento a destra di un pixel
    }
}

// funzione per disegnare un pixel che si sposta da sinistra a destra e viceverse
void sinistraDestra()
{
    int cx = 1; // parto da sinistra
    while (cx < (VGAX_WIDTH - 1))
    {
        vga.putpixel(cx, HALF_SIZE, GIALLO);
        vga.delay(RITARDO_SHORT * 5);
        vga.putpixel(cx, HALF_SIZE, NERO);
        cx++;
        // int scarico = digitalRead(PIN_PULS);
    }
}

void spara2()
{                                                                       // nuova funzione con ciclo while per sparo
    for (int xbarra = posPotX; xbarra <= (posPotX + BARRA_L); xbarra++) // ciclo per disegno barra
        vga.putpixel(xbarra, BARRA_Y, GIALLO);
    int ycolpo = BARRA_Y - 1;
    int xcolpo = posPotX + 2;
    while ((vga.getpixel(xcolpo, ycolpo) == NERO) && (ycolpo >= 3))
    {
        vga.putpixel(xcolpo, ycolpo, ROSSO); // disegno pixel colpo
        vga.tone(random(150, 200));
        vga.delay(RITARDO_SHORT * 1);
        vga.putpixel(posPotX + 2, ycolpo, NERO); // cancello pixel colpo
        ycolpo--;
    }
    if (vga.getpixel(xcolpo, ycolpo) == VERDE)
    {
        vga.putpixel(posPotX + 2, ycolpo, NERO); // cancello pixel colpo
        vga.tone(250);
        vga.delay(RITARDO_SHORT * 5);
    }
    vga.noTone();
    for (int xbarra = posPotX; xbarra <= (posPotX + BARRA_L); xbarra++) // ciclo per disegno barra
        vga.putpixel(xbarra, BARRA_Y, NERO);
}

void muoviPotBarra() // funzione per muovere la barra con il potenziometro
{
    posPotX = analogRead(PIN_POTX);
    posPotX = map(posPotX, 0, 1023, 1, VGAX_WIDTH - BARRA_L - 2);
    for (int xbarra = posPotX; xbarra <= (posPotX + BARRA_L); xbarra++) // ciclo per disegno barra
        vga.putpixel(xbarra, BARRA_Y, GIALLO);
    vga.delay(RITARDO_SHORT);
    for (int xbarra = posPotX; xbarra <= posPotX + BARRA_L; xbarra++) // ciclo per cancella barra
        vga.putpixel(xbarra, BARRA_Y, NERO);
}

void disegnaAlieni(int alieniRighe, int alieniColonne)
{ // funzione per disegnare gli alieni
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    int passoAlieniX = int(VGAX_WIDTH / alieniColonne - 2); // pixel tra un alieno e il successivo in riga
    int passoAlieniY = int(ALIENI_RIGHE * 3);               // pixel tra un alieno e il successivo in colonna

    for (int contaRighe = 1; contaRighe <= alieniRighe; contaRighe++) // ciclo esterno per disegno righe
    {
        for (int contaColonne = 1; contaColonne <= alieniColonne; contaColonne++)
        {
            int xAlieno = contaColonne * passoAlieniX;
            int yAlieno = contaRighe * passoAlieniY;
            vga.putpixel(xAlieno + 0, yAlieno + 0, VERDE);
            vga.putpixel(xAlieno + 0, yAlieno + 1, VERDE);
            vga.putpixel(xAlieno + 0, yAlieno + 2, VERDE);
            vga.putpixel(xAlieno - 1, yAlieno + 1, VERDE);
            vga.putpixel(xAlieno + 1, yAlieno + 1, VERDE);
            vga.putpixel(xAlieno - 2, yAlieno + 2, VERDE);
            vga.putpixel(xAlieno + 2, yAlieno + 2, VERDE);
        }
    }
}

void alienoSpara()
{
    for (int xbarra = posPotX; xbarra <= (posPotX + BARRA_L); xbarra++) // ciclo per disegno barra
        vga.putpixel(xbarra, BARRA_Y, GIALLO);
    int passoAlieniX = int(VGAX_WIDTH / ALIENI_COLONNE - 2); // pixel tra un alieno e il successivo in riga
    int alienox = passoAlieniX * random(1, ALIENI_COLONNE + 1);
    int alienoY = 30;
    for (int yfuoco = alienoY; yfuoco < BARRA_Y; yfuoco++)
    {
        vga.putpixel(alienox, yfuoco, ROSSO);
        vga.tone(100);
        vga.delay(RITARDO_SHORT);
        vga.putpixel(alienox, yfuoco, NERO);
    }
    vga.noTone();
    for (int xbarra = posPotX; xbarra <= (posPotX + BARRA_L); xbarra++) // ciclo per disegno barra
        vga.putpixel(xbarra, BARRA_Y, NERO);
}

void setup()
{
    Serial.begin(9600);
    vga.begin();
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    do
    {
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str0, 0, VGAX_HEIGHT / 2 - 3, 1);
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, str1, 0, VGAX_HEIGHT / 2 + 4, 2);
    } while (digitalRead(PIN_PULS) == HIGH);
    disegnaAlieni(ALIENI_RIGHE, ALIENI_COLONNE);
    pinMode(PIN_LED, OUTPUT); // led su scheda sviluppo
    digitalWrite(2, LOW);
    pinMode(PIN_PULS, INPUT_PULLUP); // ingresso pulsante su scheda viluppo
    pinMode(PIN_SW, INPUT);          // ingresso pulsante di sparo
    vga.noTone();
}

void loop()
{
    // randomPixel();
    // sinistraDestra();
    // barra();
    muoviPotBarra();
    // if (random(0, 100) > 99)
       // alienoSpara();
    if (digitalRead(PIN_SW) == 1)
        spara2();
    if (digitalRead(PIN_PULS) == 0)
    {
        vga.clear(NERO);
        disegnaBordi(ROSSO);
        disegnaAlieni(ALIENI_RIGHE, ALIENI_COLONNE);
    }
}
