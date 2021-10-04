// Funzione del gioco SpaceInvadersvero e proprio

void menu_31_GameSpaceInvaders()
{
    unsigned long int t_sx = 0;
    unsigned long int t_dx = 0;
    bool colpito; // variabile che calcolo dopo
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    disegnaAlieni(ALIENI_RIGHE, ALIENI_COLONNE);
    vga.delay(RITARDO_SCHERMATA * 3);  // pausa iniziale di 3 secondi
    int posPotX = int(VGAX_WIDTH / 2); // metto la barra al centro per movimento con pulsanti
    do
    {
        // int posPotX = analogRead(PIN_POTX); // movimento barra con potenziometro
        // posPotX = map(posPotX, 0, 1023, 1, VGAX_WIDTH - BARRA_L - 2);

        if (digitalRead(PIN_SX))         // movimento barra a sinistra con pulsante
            if (vga.millis() - t_sx > 1) // debounce software pulsante
            {
                posPotX--;
                t_sx = vga.millis();
            }

        if (digitalRead(PIN_DX))         // movimento barra a destra con pulsante
            if (vga.millis() - t_dx > 1) // debounce software pulsante
            {
                posPotX++;
                t_dx = vga.millis();
            }

        for (int xbarra = posPotX; xbarra <= (posPotX + BARRA_L); xbarra++) // ciclo per disegno barra
            vga.putpixel(xbarra, BARRA_Y, GIALLO);                          // ciclo per disegno barra

        if (digitalRead(PIN_OK) == 1) // sparo un colpo agli alieni
        {
            // for (int xbarra = posPotX; xbarra <= (posPotX + BARRA_L); xbarra++) // ciclo per disegno barra
            //  vga.putpixel(xbarra, BARRA_Y, GIALLO);                          // ciclo per disegno barra
            int ycolpo = BARRA_Y - 1; // coordinata Y di partenza colpo dalla barra
            int xcolpo = posPotX + 2; // coordinata X di partenza colpo dalla barra
            while ((vga.getpixel(xcolpo, ycolpo) == NERO) && (ycolpo >= 3))
            {
                vga.putpixel(xcolpo, ycolpo, ROSSO);     // disegno pixel colpo
                vga.delay(RITARDO_SPARO);                // disegno pixel colpo
                vga.putpixel(posPotX + 2, ycolpo, NERO); // cancello pixel colpo
                ycolpo--;                                // vado verso in alto
            }
            if (vga.getpixel(xcolpo, ycolpo) == VERDE)   // controllo se ho preso un alieno verde
                vga.putpixel(posPotX + 2, ycolpo, NERO); // cancello pixel alieno
            // for (int xbarra = posPotX; xbarra <= (posPotX + BARRA_L); xbarra++) // ciclo per cancella barra
            // vga.putpixel(xbarra, BARRA_Y, NERO);                            // ciclo per cancella barra
        }

        if (random(0, 1000) > 998)
        {
            int xbarra;
            int yfuoco;
            // for (xbarra = posPotX; xbarra <= (posPotX + BARRA_L); xbarra++) // ciclo per disegna barra
            // vga.putpixel(xbarra, BARRA_Y, GIALLO);                      // ciclo per disegna barra

            int passoAlieniX = int(VGAX_WIDTH / ALIENI_COLONNE - 2); // pixel tra un alieno e il successivo in riga
            int alienox = passoAlieniX * random(1, ALIENI_COLONNE + 1);
            int alienoY = 30;
            for (yfuoco = alienoY; yfuoco <= BARRA_Y; yfuoco++)
            {
                vga.putpixel(alienox, yfuoco, ROSSO);
                vga.delay(RITARDO_SPARO);
                vga.putpixel(alienox, yfuoco, NERO);
            }
            // for (int xbarra = posPotX; xbarra <= (posPotX + BARRA_L); xbarra++) // ciclo per cancella barra
            // vga.putpixel(xbarra, BARRA_Y, NERO);                            // ciclo per cancella barra

            colpito = ((alienox >= posPotX) && (alienox <= posPotX + BARRA_L) && (yfuoco = BARRA_Y));

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