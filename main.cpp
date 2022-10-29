#include <iostream>
#include <string>
#include <algorithm>
#include "FMastermind.h"

using FText = std::string;
using int32 = int;

int main()
{

	FMastermindGame MastermindGame;
	// Introduzione al gioco
	MastermindGame.PrintIntro();

	//Prende in input una parola tramite la funzione GetGuess() e stampa la ripetzione della parola inserita dal giocatore, il tutto avviene all'interno di PrintGuess()
	//PlayGame() si limita solamente a chiamarla più volte tramite un ciclo for
	do {
		MastermindGame.PlayGame();
	} while (MastermindGame.AskToPlayAgain());

	return 0;
}
