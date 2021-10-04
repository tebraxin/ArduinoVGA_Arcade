// funzione per disegnare griglia di alieni
void disegnaAlieni(int alieniRighe, int alieniColonne)
{
    vga.clear(NERO);
    disegnaBordi(ROSSO);
    // pixel tra un alieno e il successivo in riga
    int passoAlieniX = int(VGAX_WIDTH / alieniColonne - 2);
    // pixel tra un alieno e il successivo in colonna
    int passoAlieniY = int(ALIENI_RIGHE * 3) + 2;
    // ciclo esterno per disegno righe
    for (int contaRighe = 1; contaRighe <= alieniRighe; contaRighe++)
    {
        // ciclo interno disegna colonne
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