#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

#define TMap std::map

using FString = std::string;
using FText = std::string;
using int32 = int;

class FMastermindGame;
struct FMastermindCount;
enum class EGuessStatus;

enum class EGuessStatus
{
	Ok,
	Invalid_Input,
	Wrong_Length
};

//Tutte le variabili inizializzate a 0
struct FMastermindCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FMastermindGame {
public:

	FMastermindGame();
	~FMastermindGame();
	/* Mia Implementazione come qualsiasi altra funzione o variabile commentata, da rivedere
	void SetPlayerInput();
	void SetDifficulty();
	*/

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWorldLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString &) const;
	FText GetValidGuess();
	void GenerateHiddenWord();
	void setDifficulty();
	
	void Reset(); // TODO metti un tipo di ritorno più utile
	void SetGame();
	void PrintGameSummary();
	void PrintIntro();
	void PrintColorList();
	bool AskToPlayAgain();
	void PlayGame();
	FMastermindCount SubmitValidGuess(FString &);


private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;
	FString ColorPool;
	short Difficulty = 4;
};