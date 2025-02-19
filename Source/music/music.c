#include "music.h"
#include "LPC17xx.h"
#include "../timer/timer.h"
// Funzione per riprodurre una nota
void playNote(NOTE note) {
    if (note.freq != 0) {
        // Impostiamo il timer con la frequenza della nota
        reset_timer(2);                // Reset Timer 0
        init_timer(2, note.freq);      // Inizializza Timer 0 con la frequenza della nota
        enable_timer(2);               // Abilita il Timer 0 per generare l'interrupt
    }

    // Impostiamo la durata della nota nel Timer 1
    reset_timer(3);                    // Reset Timer 1
    init_timer(3, note.duration);      // Inizializza Timer 1 con la durata della nota
    enable_timer(3);                   // Abilita Timer 1 per il controllo della durata
}

// Funzione per verificare se una nota è ancora in riproduzione
BOOL isNotePlaying(void) {
    return ((LPC_TIM2->TCR != 0) /*|| (LPC_TIM3->TCR != 0)*/); // Controlla se i timer sono attivi cioe se tim2 e spento e perche e stato disattivato dal timer 3 quindi la nota e finita
}