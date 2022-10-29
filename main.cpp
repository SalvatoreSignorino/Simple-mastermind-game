#include <iostream>
#include <string>
#include <algorithm>
#include "FBullAndCowGame.h"

using FText = std::string;
using int32 = int;

int main()
{

	FBullCowGame BCGame;
	// Introduzione al gioco
	BCGame.PrintIntro();

	//Prende in input una parola tramite la funzione GetGuess() e stampa la ripetzione della parola inserita dal giocatore, il tutto avviene all'interno di PrintGuess()
	//PlayGame() si limita solamente a chiamarla pi� volte tramite un ciclo for
	do {
		BCGame.PlayGame();
	} while (BCGame.AskToPlayAgain());

	return 0;
}
