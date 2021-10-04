
void menu_33_GameSnake()
{
    unsigned long int t_snake = 0; // tempo per ritardo non bloccante
    unsigned long int t_sx = 0;    // tempo per ritardo non bloccante
    unsigned long int t_dx = 0;    // tempo per ritardo non bloccante
    // unsigned long int t_level = 0; // tempo per ritardo non bloccante
    bool gameover;
    int passo = 1;                               // step delle rotazioni
    int xSnake = random(10, (VGAX_WIDTH - 10));  // coordinata iniziale casuale del serpente
    int ySnake = random(10, (VGAX_HEIGHT - 10)); // coordinata iniziale casuale del serpente
    int divisorePuntiGioco = 5;                  // fattore di divisione per i punti altrimenti vanno troppo veloci
    int progressivoPuntiGioco = 0;               // valore assoluto dei punti
    int puntiGioco = 0;                          // punteggio iniziale del gioco
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    do
    {
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, punti, 5, 5, VERDE);
        if (digitalRead(PIN_SX)) // debounce software pulsante SX
            if ((vga.millis() - t_sx) > DEBOUNCE_PULS)
            {
                passo--; // giro a sinistra
                t_sx = vga.millis();
            }

        if (digitalRead(PIN_DX)) // debounce software pulsante DX
            if ((vga.millis() - t_dx) > DEBOUNCE_PULS)
            {
                passo++; // giro a sinistra
                t_dx = vga.millis();
            }

        if (passo > 4)
            passo = 1;
        if (passo < 1)
            passo = 4;

        if ((vga.millis() - t_snake) > 250)
        {
            switch (passo)
            {
            case 1:
                xSnake++;
                break;
            case 2:
                ySnake++;
                break;
            case 3:
                xSnake--;
                break;
            case 4:
                ySnake--;
                break;
            }

            gameover = ((ySnake == 0) || (xSnake == 0) || (ySnake == VGAX_EIGHT - 1) || (xSnake == VGAX_WIDTH - 1) || (vga.getpixel(xSnake, ySnake) == GIALLO));

            if (!gameover)
            {
                vga.putpixel(xSnake, ySnake, GIALLO);
                t_snake = vga.millis();
                progressivoPuntiGioco++;
                if (progressivoPuntiGioco % divisorePuntiGioco == 0)
                {
                    scriviPunteggio(puntiGioco, 40, 5, NERO);
                    puntiGioco++;
                    scriviPunteggio(puntiGioco, 40, 5, VERDE);
                }
            }

            if (gameover)
            {
                vga.tone(200);
                vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, colpitoGamerOver, 15, 35, ROSSO);
                vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, premiSXindietro, 10, 50, GIALLO);
                statoMenu = 23;
                do
                {
                    if (digitalRead(PIN_SX))                       // debounce software pulsante DX
                        if ((vga.millis() - t_sx) > DEBOUNCE_PULS) // debounce software pulsante DX
                            break;
                } while (digitalRead(PIN_SX) == 0);
                vga.noTone();
            }
        }

        if (gameover)
            break;

        if ((digitalRead(PIN_SX) == 1) && (digitalRead(PIN_DX) == 1) && (digitalRead(PIN_OK) == 1)) // premere SX + DX + OK per uscire
        {
            vga.delay(RITARDO_PULS);
            statoMenu = 23; // torno al menù precedente
            break;          // uscita dal ciclo while
        }
    } while (1);
}