#pragma once
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

#define TMap std::map

using FString = std::string;
using FText = std::string;
using int32 = int;

class FBullCowGame;
struct FBullCowCount;
enum class EGuessStatus;

enum class EGuessStatus
{
	Ok,
	Not_Isogramm,
	Invalid_Input,
	Wrong_Length
};

//Tutte le variabili inizializzate a 0
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
public:

	FBullCowGame();
	~FBullCowGame();
	/* Mia Implementazione come qualsiasi altra funzione o variabile commentata, da rivedere
	void PlayGame();
	bool AskToPlayAgain();
	void PrintIntro();
	void SetPlayerInput();
	void SetDifficulty();
	*/

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWorldLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString &) const;
	FText GetValidGuess();
	
	void Reset(); // TODO metti un tipo di ritorno più utile
	void PrintgameSummary();
	void PrintIntro();
	bool AskToPlayAgain();
	void PlayGame();
	FBullCowCount SubmitValidGuess(FString &);


private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;
	/*
	short Difficulty = 0;
	FString PlayerGuess = "";
	*/
};