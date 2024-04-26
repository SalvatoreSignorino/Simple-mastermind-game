#include "FMastermind.h"


// Constructors and destructors
FMastermindGame::FMastermindGame()
{
	/*
	r = red;
	g = green;
	b = blue;
	c = cyan;
	y = yellow;
	m = magenta;
	p = purple; 
	*/
	ColorPool = {'r', 'g', 'b', 'c', 'y', 'm', 'p'};
	SetGame();
}

FMastermindGame::~FMastermindGame()
{
}

// Getter functions
int32 FMastermindGame::GetCurrentTry() const { return this->MyCurrentTry; }
int32 FMastermindGame::GetHiddenWorldLength() const { return MyHiddenWord.length(); }
bool FMastermindGame::IsGameWon() const { return this->bGameWon; }
int32 FMastermindGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 10} };
	return WordLengthToMaxTries.at(this->GetHiddenWorldLength());
}

EGuessStatus FMastermindGame::CheckGuessValidity(FString &PlayerGuess) const
{

	if(PlayerGuess.length() != this->GetHiddenWorldLength()) // se il tentativo non ha la dimensione giusta
	{
		return EGuessStatus::Wrong_Length;
	}

	if(PlayerGuess.find_first_not_of("bcgmpry") != std::string::npos){
		return EGuessStatus::Invalid_Input;
	}
	
	return EGuessStatus::Ok;
}

void FMastermindGame::Reset()
{
	// const FString HIDDEN_WORD = "rrcy";

	// this->MyHiddenWord = HIDDEN_WORD;
	setDifficulty();
	this->MyHiddenWord = "";
	this->GenerateHiddenWord();
	this->MyCurrentTry = 1;
	this->bGameWon = false;
}

void FMastermindGame::SetGame()
{
	std::cout << "Benvenuto nel gioco di Mastermind!\n" << std::endl;
	setDifficulty();
	this->MyHiddenWord = "";
	this->GenerateHiddenWord();
	this->MyCurrentTry = 1;
	this->bGameWon = false;
}

void FMastermindGame::PrintGameSummary()
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
}

void FMastermindGame::PrintColorList()
{
	std::cout << "I colori a tua disposizione sono:\n";
	std::cout << "\tr = red;" << std::endl;
	std::cout << "\tg = green;" << std::endl;
	std::cout << "\tb = blue;" << std::endl;
	std::cout << "\tc = cyan;" << std::endl;
	std::cout << "\ty = yellow;" << std::endl;
	std::cout << "\tm = magenta;" << std::endl;
	std::cout << "\tp = purple;" << std::endl;
}

bool FMastermindGame::AskToPlayAgain()
{
	FText Response;
	std::cout << "Vuoi giocare di nuovo (s/n)? ";
	getline(std::cin, Response);

	std::transform(Response.begin(), Response.end(), Response.begin(), [](unsigned char c) { return std::tolower(c); });

	std::cout << std::endl;

	if(Response[0] == 's'){
		this->Reset();
	}

	return Response[0] == 's';
}

void FMastermindGame::PlayGame()
{

	std::cout << "Riesci ad indovinare una combinazione di " << this->GetHiddenWorldLength() << " caratteri?\n" << std::endl;
	int32 MaxTries = this->GetMaxTries();

	while (!this->IsGameWon() && (this->GetCurrentTry() <= this->GetMaxTries())) {

		this->PrintColorList();

		FText PlayerGuess = this->GetValidGuess();

		// TODO dentro GetGuess() devo validare l'input del giocatore finchè non immette una stringa valida,
		// ricevendo in ritorno il risultato della parola immessa
		FMastermindCount BullCowCount = this->SubmitValidGuess(PlayerGuess);
		//Stampo i numeri di lettere giuste al posto giusto e lettere giuste al posto sbagliato
		std::cout << "Lettere giuste al posto giusto: " << BullCowCount.Bulls << std::endl;
		std::cout << "Lettere giuste al posto sbagliato: " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}

	this->PrintGameSummary();
}

// Una funzione per trovare le lettere giuste al posto giusto e le lettere giuste al posto sbagliato, assumendo di avere un input valido
FMastermindCount FMastermindGame::SubmitValidGuess(FString &PlayerGuess)
{
	FMastermindCount BullCowCount;
	int WordLength = this->GetHiddenWorldLength(); // Avendo già controllato l'input del giocatore so che la lunghezza della parola nascosta è la stessa della parola data in input

	TMap<FString, int32> colorsHiddenWord = {{"r", 0}, {"g", 0}, {"b", 0}, {"c", 0}, {"y", 0}, {"m", 0}, {"p", 0}};
	TMap<FString, int32> colorsPlayerGuess = {{"r", 0}, {"g", 0}, {"b", 0}, {"c", 0}, {"y", 0}, {"m", 0}, {"p", 0}};

	for(size_t i = 0; i < PlayerGuess.size(); i++){
		if(PlayerGuess.at(i) == MyHiddenWord.at(i)){
			BullCowCount.Bulls++;
		}
		else{
			colorsHiddenWord.at(FString(1, MyHiddenWord.at(i)))++;
			colorsPlayerGuess.at(FString(1, PlayerGuess.at(i)))++;
		}
	}

	for(auto it_m1 = colorsHiddenWord.cbegin(), end_m1 = colorsHiddenWord.cend(), it_m2 = colorsPlayerGuess.cbegin(), end_m2 = colorsPlayerGuess.cend(); it_m1 != end_m1 || it_m2 != end_m2;){
		BullCowCount.Cows += std::min(it_m1->second, it_m2->second);
		it_m1++;
		it_m2++;
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
FText FMastermindGame::GetValidGuess()
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
		case EGuessStatus::Invalid_Input:
			std::cout << "Per favore inserisci una parola formata dalle sole lettere dei colori e non altri caratteri!" << std::endl;
			this->PrintColorList();
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Per favore inserisci una parola di lunghezza " << this->GetHiddenWorldLength() << std::endl;
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::Ok); // Il loop continua finché non si hanno errori dovuti all'input del giocatore

	return Guess;
}

void FMastermindGame::GenerateHiddenWord()
{

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(0, ColorPool.size() - 1);

	for(size_t i = 0; i < this->Difficulty; i++){
		int randomColorIndex = dis(gen);
		MyHiddenWord.append(FString(1, ColorPool.at(randomColorIndex)));
	}
	
	std::shuffle(MyHiddenWord.begin(), MyHiddenWord.end(), std::default_random_engine(seed));

}

void FMastermindGame::setDifficulty()
{

	std::cout << "A che difficoltà vuoi giocare? Una combinazione da 3 o 4 colori?" << std::endl;

	EGuessStatus Status = EGuessStatus::Invalid_Input;

	std::string userInputStr;

	do
	{
		if (!(std::cin >> this->Difficulty)) {
			// Se l'input non è un numero, cancella il flag di errore e scarta l'input
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Valore inserito non valido. Per favore inserisci un numero, nello specifico 3 o 4" << std::endl;
			Status = EGuessStatus::Invalid_Input;
		} else if (this->Difficulty != 3 && this->Difficulty != 4) {
			// Se l'input non è né 3 né 4, richiedi all'utente di reinserire il numero
			std::cout << "Numero inserito non valido. Per favore inserisci 3 o 4 come valore" << std::endl;
			Status = EGuessStatus::Invalid_Input;
		} else {
			// Input valido
			Status = EGuessStatus::Ok;
		}

	} while (Status != EGuessStatus::Ok); // Il loop continua finché non si hanno errori dovuti all'input del giocatore
	while ((getchar()) != '\n');
}
