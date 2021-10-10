// funzione per impostare i set di colori cambiando l euscite a relè

void impostaColori(byte setColor)
{
    for (byte rele = 0; rele <= 3; rele++)
        digitalWrite((16 + rele), (1 - matriceColori[setColor][rele]));
}