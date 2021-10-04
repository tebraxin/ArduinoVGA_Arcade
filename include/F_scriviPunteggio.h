// funzione per scivere il punteggio a video
// gli passo un intero a due cifre e le cooridnate x e y dove scrivere
// gli passo anche il colore
// vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, stringanumero, x, y, colore);

void scriviNumero(int numero, int coordX, int coordY, int colore)
{
    switch (numero)
    {
    case 0:
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra0, coordX, coordY, colore);
        break;
    case 1:
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra1, coordX, coordY, colore);
        break;
    case 2:
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra2, coordX, coordY, colore);
        break;
    case 3:
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra3, coordX, coordY, colore);
        break;
    case 4:
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra4, coordX, coordY, colore);
        break;
    case 5:
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra5, coordX, coordY, colore);
        break;
    case 6:
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra6, coordX, coordY, colore);
        break;
    case 7:
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra7, coordX, coordY, colore);
        break;
    case 8:
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra8, coordX, coordY, colore);
        break;
    case 9:
        vga.printPROGMEM((byte *)fnt_nanofont_data, FNT_NANOFONT_SYMBOLS_COUNT, FNT_NANOFONT_HEIGHT, 3, 1, Cifra9, coordX, coordY, colore);
        break;
    }
}

void scriviPunteggio(int P_punteggio, int P_coordX, int P_coordY, int P_colore)
{
    int P_decine = int(P_punteggio / 10);
    if (P_decine != 0)
        scriviNumero(P_decine, P_coordX, P_coordY, P_colore);
    int P_unita = int(P_punteggio % 10);
    scriviNumero(P_unita, P_coordX + 5, P_coordY, P_colore);
}