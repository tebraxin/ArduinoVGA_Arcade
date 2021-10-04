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