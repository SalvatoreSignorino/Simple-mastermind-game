#include "FMastermind.h"

#define TMAP std::map

using FString = std::string;
using FText = std::string;
using int32 = int;


// Constructors and destructors
FMastermindGame::FMastermindGame()
{
	Reset();
}
FMastermindGame::~FMastermindGame()
{
}

// Getter functions
int32 FMastermindGame::GetCurrentTry() const { return this->MyCurrentTry; }
int32 FMastermindGame::GetHiddenWorldLength() const { return MyHiddenWord.length(); }
bool FMastermindGame::IsGameWon() const { return this->bGameWon; }
int32 FMastermindGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3, 3}, {4, 4}, {5, 4}, {6, 5}, {7, 6}, {8, 20}, {9, 8} };
	return WordLengthToMaxTries[this->GetHiddenWorldLength()];
}

EGuessStatus FMastermindGame::CheckGuessValidity(FString &PlayerGuess) const
{
	if (false) // se il tentativo non è un isogramma
	{
		return EGuessStatus::Not_Isogramm;
	}
	else if(PlayerGuess.length() != this->GetHiddenWorldLength()) // se il tentativo non ha la dimensione giusta
	{
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::Ok;
	}
}

void FMastermindGame::Reset()
{
	const FString HIDDEN_WORD = "bifronte";
	
	this->MyHiddenWord = HIDDEN_WORD;
	this->MyCurrentTry = 1;
	this->bGameWon = false;
}

void FMastermindGame::PrintgameSummary()
{
	if (bGameWon) {
		std::cout << "Complimenti, hai vinto il gioco in ";
		if (this->GetCurrentTry() == 1) {
			std::cout << this->GetCurrentTry() << " turno!\n" << std::endl;
		}
		else {
			std::cout<< this->GetCurrentTry() << " turni!\n" << std::endl;;
		}
	}
	else {
		std::cout << "Mi dispiace, ritenta e avrai maggiore fortuna, oppure abbassa il livello di difficoltà se era troppo difficile\n" << std::endl;;
	}
}

void FMastermindGame::PrintIntro()
{
	std::cout << "Benvenuto nel gioco di Mastermind!\n" << std::endl;
	std::cout << "Riesci ad indovinare una parola di " << this->GetHiddenWorldLength() << " caratteri?\n" << std::endl;
}

bool FMastermindGame::AskToPlayAgain()
{
	FText Response;
	std::cout << "Vuoi giocare di nuovo (s/n)? ";
	getline(std::cin, Response);

	std::transform(Response.begin(), Response.end(), Response.begin(), [](unsigned char c) { return std::tolower(c); });

	std::cout << std::endl;

	return Response[0] == 's';
}

void FMastermindGame::PlayGame()
{
	int32 MaxTries = this->GetMaxTries();

	while (!this->IsGameWon() && (this->GetCurrentTry() <= this->GetMaxTries())) {

		FText PlayerGuess = this->GetValidGuess();

		// TODO dentro GetGuess() devo validare l'input del giocatore finchè non immette una stringa valida,
		// ricevendo in ritorno il risultato della parola immessa
		FMastermindCount BullCowCount = this->SubmitValidGuess(PlayerGuess);
		//Stampo i numeri di lettere giuste al posto giusto e lettere giuste al posto sbagliato
		std::cout << "Lettere giuste al posto giusto: " << BullCowCount.Bulls << std::endl;
		std::cout << "Lettere giuste al posto sbagliato: " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}

	this->PrintgameSummary();
}

// Una funzione per trovare le lettere giuste al posto giusto e le lettere giuste al posto sbagliato, assumendo di avere un input valido
FMastermindCount FMastermindGame::SubmitValidGuess(FString &PlayerGuess)
{
	FMastermindCount BullCowCount;
	int32 WordLength = this->GetHiddenWorldLength(); // Assumo che la lunghezza della parola nascosta sia la stessa della parola data in input dal giocatore

	// Controlla tutte le lettere della parola del giocatore con quelle della parola nascosta
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// confronta le lettere immesse dal giocatore
		for (int32 PGChar = 0; PGChar < WordLength; PGChar++)
		{
			// Se sono uguali				

			if (MyHiddenWord[MHWChar] == PlayerGuess[PGChar])
			{
				// se le lettere sono allo stesso posto incrementa Bulls
				if (PGChar == MHWChar)
					BullCowCount.Bulls++;
				
				// Altrimenti
				else
					BullCowCount.Cows++;	//incrementa Cows
			}

		}

	}

	if (BullCowCount.Bulls == WordLength) {
		this->bGameWon = true;
		return BullCowCount;
	}
	else {
		this->MyCurrentTry++;
		return BullCowCount;
	}
}

// Si entra in un loop finché il giocatore non inserisce un input valido
std::string FMastermindGame::GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Input;
	FText Guess = "";

	do
	{
		std::cout << "Tentativo: " << this->GetCurrentTry() << " di " << this->GetMaxTries() << " : ";

		// Per standard di codifica di Unreal le variabili vanno messe con la prima lettera in maiuscolo, cosa strana...


		getline(std::cin, Guess);
		std::transform(Guess.begin(), Guess.end(), Guess.begin(), [](unsigned char c) { return std::tolower(c); });

		Status = this->CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Ok:
			break;
		case EGuessStatus::Not_Isogramm:
			break;
		case EGuessStatus::Invalid_Input:
			std::cout << "Per favore inserisci una parola formata da sole lettere e non altri caratteri\n" << std::endl;
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Per favore inserisci una parola di lunghezza " << this->GetHiddenWorldLength() << std::endl;
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::Ok); // Il loop continua finch� non si hanno errori dovuti all'input del giocatore

	return Guess;
}