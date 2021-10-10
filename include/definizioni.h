// File con definizione di varialbili e costanti di programma

// Definizione COSTANTI di programma
// VGAX_WIDTH larghezza massima max 120
// VGAX_EIGHT altezza della risoluziona max 60
// solo due bit per colore 00-nero, 01-rosso, 10-verde, 11-giallo
#define VGAX_WIDTH 120
#define VGAX_EIGHT 60
#define HALF_SIZE int(VGAX_HEIGHT / 2)
#define BARRA_Y (VGAX_HEIGHT - 3) // pixel dal fondo per altezza barra

// costanti per i 4 colori della libreira
// solo due bit per colore - primo set combinazioni
#define NERO 0	 // codice per colore nero
#define ROSSO 1	 // codice per colore rosso
#define VERDE 2	 // codice per colore verde
#define GIALLO 3 // codice per colore giallo

// set 1 colori - nero, rosso, verde, giallo - default alla accensione
// set 2 colori - nero, rosso, blu, viola
// set 3 colori - nero, verde, blu, azzurro
// set 4 colori - nero, rosso, azzurro, bianco
// set 5 colori - nero, giallo, blu, bianco

byte indiceSetcolori = 0; // se colori iniziale, può poi variare da 0 a 4, cioè la riga della matrice

byte matriceColori[5][4] = {
	{1, 0, 1, 0},
	{1, 0, 0, 1},
	{0, 1, 1, 0},
	{1, 0, 1, 1},
	{1, 1, 0, 1},
};

#define BARRA_L 5			  // lunghezza pixel barra
#define ALIENI_RIGHE 3		  // numero di righe di alieni
#define ALIENI_COLONNE 8	  // numero di alieni su una riga (colonne)
#define RITARDO_PONG 30		  // millisecondi di RITARDO_SHORT per uso in vga.millis
#define RITARDO_PULS 250	  // millisecondi di RITARDO_SHORT per uso in vga.millis
#define RITARDO_SPARO 8		  // millisecondi di RITARDO_SHORT per uso in vga.millis
#define RITARDO_SCHERMATA 250 // millisecondi di RITARDO_SHORT per uso in vga.millis
#define DEBOUNCE_PULS 200	  // millisecondi di ritardo per debounce software dei pulsanti

#define INIZIO_SX_MENU 5 // numero di pixel da sinistra per stampa testi dei menù
#define STEP_MENU 6		 // numero di pixel tra una riga e la successiva

// Definizione di variabili globali di programma
static char scrollX = -VGAX_WIDTH;
int statoMenu = 00;	 // variabile che indicato il livello / stato del menù, 00 è il livello iniziale
int rigaStringa = 0; // variabile per disegno righe nei menù

/*  tabella note e frequenze
	III	IV	V	VI
Do	131	262	523	1047
Do#	139	277	554	1109
Re	147	294	587	1175
Re#	156	311	622	1245
Mi	165	330	659	1319
Fa	175	349	698	1397
Fa#	185	370	740	1480
Sol	196	392	784	1568
Sol#	208	415	831	1661
La	220	440	880	1760
La#	233	466	932	1865
Si	247	494	988	1976
*/
#define NOTA_GAMEOVER 131	  // DO
#define NOTA_SPARO_ALIENO 165 // MI
#define NOTA_SPARO_IO 196	  // SOL
