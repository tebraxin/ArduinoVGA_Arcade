// funzione per muovere la barra con il potenziometro
void muoviPotBarra(int posXBarra)
{
    // ciclo per disegna barra
    for (int xbarra = posXBarra; xbarra <= (posXBarra + BARRA_L); xbarra++)
        vga.putpixel(xbarra, BARRA_Y, GIALLO);
    vga.delay(50);
    // ciclo per cancella barra
    for (int xbarra = posXBarra; xbarra <= posXBarra + BARRA_L; xbarra++)
        vga.putpixel(xbarra, BARRA_Y, NERO);
}