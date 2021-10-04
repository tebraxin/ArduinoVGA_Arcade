// Funzione per gioco Pong

void scriviPunteggio(int P_punteggio, int P_coordX, int P_coordY, int P_colore);

void menu_32_GamePong()
{
    unsigned long int t_sx = 0;
    unsigned long int t_dx = 0;
    bool pallaout;                              // variabile che calcolo dopo
    int xpalla = random(10, (VGAX_WIDTH - 10)); // mi fermo sul bordo per rimbalzare
    int ypalla = 10;                            // rimbalzo anche sulla barra
    int pallaDeltaX = 1;                        // pixel di incremento per coordinata palla x
    int pallaDeltaY = 1;                        // pixel di incremento per coordinata palla Y
    int posPotX = int(VGAX_WIDTH / 2);          // metto la barra al centro per movimento con pulsanti
    int puntiGioco = 0;                         // punteggio iniziale del gioco
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    do
    {
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, punti, 5, 5, VERDE);
        if (digitalRead(PIN_SX))         // movimento barra a sinistra con pulsante
            if (vga.millis() - t_sx > 1) // debounce software pulsante
            {
                posPotX -= 2;
                t_sx = vga.millis();
            }

        if (digitalRead(PIN_DX))         // movimento barra a destra con pulsante
            if (vga.millis() - t_dx > 1) // debounce software pulsante
            {
                posPotX += 2;
                t_dx = vga.millis();
            }

        posPotX = constrain(posPotX, 1, VGAX_WIDTH - BARRA_L * 2 - 2); // evito che la barra esca dal monitor

        for (int xbarra = posPotX; xbarra <= (posPotX + (BARRA_L * 2)); xbarra++) // ciclo per disegna barra
            vga.putpixel(xbarra, BARRA_Y, GIALLO);                                // ciclo per disegna barra

        vga.putpixel(xpalla, ypalla, VERDE); // disegno il pixel
        vga.delay(RITARDO_PONG);
        vga.putpixel(xpalla, ypalla, NERO); // cancello il pixel

        if (ypalla <= 1) // rimbalzo in verticale in alto
            pallaDeltaY = -pallaDeltaY;

        if ((xpalla >= (VGAX_WIDTH - 2)) || (xpalla <= 1)) // rimbalzo in orizzontale
            pallaDeltaX = -pallaDeltaX;

        if (ypalla >= BARRA_Y)                                              // controllo contatto barra
            if ((xpalla >= posPotX) && (xpalla <= posPotX + (BARRA_L * 2))) // sto forse toccando in orizzontale
            {
                pallaDeltaY = -pallaDeltaY;
                scriviPunteggio(puntiGioco, 40, 5, NERO);
                puntiGioco++;
                scriviPunteggio(puntiGioco, 40, 5, VERDE);
            }

        xpalla = xpalla + pallaDeltaX;
        ypalla = ypalla + pallaDeltaY;

        for (int xbarra = posPotX; xbarra <= (posPotX + (BARRA_L * 2)); xbarra++) // ciclo per cancella barra
            vga.putpixel(xbarra, BARRA_Y, NERO);                                  // ciclo per cancella barra

        pallaout = ((ypalla >= BARRA_Y) && ((xpalla < posPotX) || (xpalla > posPotX + (BARRA_L * 2))));

        if (pallaout) // palla uscita sotto la barra
        {
            vga.tone(200);
            vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, colpitoGamerOver, 15, 35, ROSSO);
            vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiSXindietro, 10, 50, GIALLO);
            statoMenu = 22;
            do
            {
                if (digitalRead(PIN_SX))                       // debounce software pulsante DX
                    if ((vga.millis() - t_sx) > DEBOUNCE_PULS) // debounce software pulsante DX
                        break;
            } while (digitalRead(PIN_SX) == 0);
            vga.noTone();
        }

        if (pallaout)
            break;

        if ((digitalRead(PIN_SX) == 1) && (digitalRead(PIN_DX) == 1) && (digitalRead(PIN_OK) == 1)) // premere SX + DX + OK per uscire
        {
            vga.delay(RITARDO_PULS);
            statoMenu = 22; // torno al menù precedente
            break;          // uscita dal ciclo while
        }
    } while (1);
}