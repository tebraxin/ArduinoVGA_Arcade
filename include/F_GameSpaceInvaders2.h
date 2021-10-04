// Funzione del gioco SpaceInvadersvero e proprio

void scriviPunteggio(int P_punteggio, int P_coordX, int P_coordY, int P_colore);

#define RIMBALZO 50   // millisecondi per dobouce pulsanti
#define TEMPO_SPARO 0 // MILLIS DI RITARDO PER COLPI SPARATI

void menu_31_GameSpaceInvaders2()
{
    unsigned long int t_sx = vga.millis();            // tempi per debounce software
    unsigned long int t_dx = vga.millis();            // tempi per debounce software
    unsigned long int t_ok = vga.millis();            // tempi per debounce software
    unsigned long int t_sparoIO = vga.millis();       // tempi per debounce software
    unsigned long int t_sparoIOxx = vga.millis();     // tempi per debounce software
    unsigned long int t_sparaALIENO = vga.millis();   // tempi per debounce software
    unsigned long int t_sparaALIENOxx = vga.millis(); // tempi per debounce software
    int xcolpoIO;                                     // coordinata X di partenza MIO colpo dalla barra
    int ycolpoIO = BARRA_Y;                           // coordinata Y di partenza MIO colpo dalla barra
    bool sparoIO = false;                             // memorizzo se ho sparato
    bool sparaALIENO = false;                         // memorizzo se ha sparato l'alieno
    bool colpito = false;                             // memorizzo se sono stato colpito da un colpo alieno
    int posPotX = int(VGAX_WIDTH / 2);                // metto la barra al centro per movimento con pulsanti
    int passoAlieniX = 0;                             // pixel tra un alieno e il successivo in riga
    int alienox = 0;
    int yfuoco = 30;
    int puntiGioco = 0; // punteggio iniziale del gioco
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    disegnaAlieni(ALIENI_RIGHE, ALIENI_COLONNE);
    vga.delay(RITARDO_SCHERMATA * 1); // pausa iniziale di 3 secondi
    do
    {
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, punti, 5, 3, VERDE);
        if (digitalRead(PIN_SX))                  // movimento barra a sinistra con pulsante
            if ((vga.millis() - t_sx) > RIMBALZO) // debounce software pulsante SX
            {
                posPotX--;
                t_sx = vga.millis();
            }

        if (digitalRead(PIN_DX))                  // movimento barra a destra con pulsante
            if ((vga.millis() - t_dx) > RIMBALZO) // debounce software pulsante DX
            {
                posPotX++;
                t_dx = vga.millis();
            }

        if (digitalRead(PIN_OK))                  // sparo io un colpo agli alieni dalla barra
            if ((vga.millis() - t_ok) > RIMBALZO) // debounce software pulsante OK
            {
                sparoIO = true;
                xcolpoIO = posPotX + 2; // memorizzo coordinata inizio sparo
                t_ok = vga.millis();
            }

        posPotX = constrain(posPotX, 4, VGAX_WIDTH - BARRA_L * 2 - 1); // evito che la barra esca dal monitor

        if (sparoIO)
        {
            if ((vga.millis() - t_sparoIO) > TEMPO_SPARO)
            {
                if ((vga.getpixel(xcolpoIO, (ycolpoIO)) == NERO) && (ycolpoIO > 5))
                {
                    vga.putpixel(xcolpoIO, ycolpoIO, ROSSO);
                }
                else if ((vga.getpixel(xcolpoIO, (ycolpoIO)) == VERDE) || (ycolpoIO < 5))
                {
                    if (vga.getpixel(xcolpoIO, (ycolpoIO)) == VERDE)
                    {
                        scriviPunteggio(puntiGioco, 40, 3, NERO);
                        puntiGioco++;
                        scriviPunteggio(puntiGioco, 40, 3, VERDE);
                    }
                    vga.putpixel(xcolpoIO, ycolpoIO, NERO);
                    vga.putpixel(xcolpoIO, ycolpoIO + 1, NERO);
                    sparoIO = false;
                    ycolpoIO = BARRA_Y;
                }
                if ((vga.millis() - t_sparoIOxx) > TEMPO_SPARO)
                {
                    vga.putpixel(xcolpoIO, ycolpoIO + 1, NERO);
                    t_sparoIOxx = vga.millis();
                }
                ycolpoIO--;
                t_sparoIO = vga.millis();
            }
        }

        for (int xbarra = posPotX; xbarra <= (posPotX + BARRA_L); xbarra++) // ciclo per disegno barra
            vga.putpixel(xbarra, BARRA_Y, GIALLO);                          // ciclo per disegno barra

        if ((random(0, 1000) > 998) && (!sparaALIENO))
        {
            sparaALIENO = true;
            passoAlieniX = int(VGAX_WIDTH / ALIENI_COLONNE - 2); // pixel tra un alieno e il successivo in riga
            alienox = passoAlieniX * random(1, ALIENI_COLONNE + 1);
            yfuoco = 30;
        }

        if (sparaALIENO)
        {
            if ((vga.millis() - t_sparaALIENO) > 20)
            {
                vga.putpixel(alienox, yfuoco, NERO);
                yfuoco++;
                vga.putpixel(alienox, yfuoco, ROSSO);
                t_sparaALIENO = vga.millis();
            }

            colpito = ((alienox >= posPotX) && (alienox <= posPotX + BARRA_L) && (yfuoco = BARRA_Y));

            if (yfuoco >= BARRA_Y)
            {
                sparaALIENO = false;
                vga.putpixel(alienox, yfuoco, NERO);
                yfuoco = 30;
            }

            if (colpito) // la coordinata x del coplo alieno è nella barra
            {
                vga.tone(200);
                vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, colpitoGamerOver, 15, 35, ROSSO);
                vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiSXindietro, 10, 50, GIALLO);
                statoMenu = 21;
                do
                {
                    if (digitalRead(PIN_SX))                       // debounce software pulsante DX
                        if ((vga.millis() - t_sx) > DEBOUNCE_PULS) // debounce software pulsante DX                    {
                            break;
                } while (digitalRead(PIN_SX) == 0);
                vga.noTone();
            }
        }

        for (int xbarra = posPotX; xbarra <= (posPotX + BARRA_L); xbarra++) // ciclo per cancella barra
            vga.putpixel(xbarra, BARRA_Y, NERO);                            // ciclo per cancella barra

        if (colpito)
            break;

        if ((digitalRead(PIN_SX) == 1) && (digitalRead(PIN_DX) == 1) && (digitalRead(PIN_OK) == 1)) // premere SX + DX + OK per uscire
        {
            vga.delay(RITARDO_PULS);
            statoMenu = 21; // torno al menù precedente
            break;          // uscita dal ciclo while
        }
    } while (1);
}