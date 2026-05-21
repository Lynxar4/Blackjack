#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <string_view>
#include <thread>
#include <chrono>
#include <cctype>
#include "Random.h"

static int total{};
static int additionalCards{ 0 };
static int dealerAdditionalCards{ 0 };
static int dealerTotal{ 0 };

struct Card
{
	int value{};
	std::string cardName{};
	std::string suit{};

	void aceChecker()
	{
		if (cardName == "Ace" && value + total > 21)
		{
			value = 1;
		}
	}

	void dealerAceChecker()
	{
		if (cardName == "Ace" && value + dealerTotal > 21)
		{
			value = 1;
		}
	}
};

namespace Blackjack
{
	std::vector<Card> cardValues
	{
		Card{1, "one"}, Card{2, "two"}, Card{3, "three"}, Card{4, "four"}, Card{5, "five"},
		Card{6, "six"}, Card{7, "seven"}, Card{8, "eight"}, Card{9, "nine"}, Card{10, "ten"},
		Card{10, "Jack"}, Card{10, "Queen"}, Card{10, "King"}, Card{11, "Ace"}
	};
}

void hit();
void stand();

char getValidInput(char condition1, char condition2)
{
	while (true)
	{
		char input{};
		std::cin >> input;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		input = std::tolower(input);
		if (input != condition1 && input != condition2)
		{
			std::cout << "Your input is not valid. Enter '" << condition1 << "' or '" << condition2 << "'\n";
			continue;
		}
		return input;
	}
}

void choice()
{
	std::cout << "Do you want to hit or stand?\n";
	char input{ getValidInput('h', 's')};

	if (input == 'h')
	{
		hit();
	}
	else if (input == 's')
	{
		stand();
	}
}

std::string cardNumberPrinter(int additionalCards)
{
	std::string cardNumber{};

	switch (additionalCards)
	{
	case 1:
		cardNumber = "third";
		break;
	case 2:
		cardNumber = "fourth";
		break;
	case 3:
		cardNumber = "fifth";
		break;
	case 4:
		cardNumber = "sixth";
		break;
	}
	return cardNumber;
}

Card getRandomCard()
{
	int randIndex{ Random::get(0, 13) };
	Card newCard{ Blackjack::cardValues[randIndex] };
	return newCard;
}

void dealerAddCard()
{
	Card newCard{ getRandomCard() };
	
	++dealerAdditionalCards;
	std::string cardNumber{cardNumberPrinter(dealerAdditionalCards)};
	std::cout << "Dealer's " << cardNumber << " card: ";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << newCard.cardName << '\n';
	newCard.dealerAceChecker();
	dealerTotal += newCard.value;
}

void stand()
{
	Card dealerCard2{ getRandomCard() };
	dealerCard2.aceChecker();
	dealerTotal += dealerCard2.value;
	std::cout << "Dealer's second card: ";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << dealerCard2.cardName << '\n';

	while (dealerTotal <= 16)
	{
		dealerAddCard();
	}

	std::cout << "Dealer's total: " << dealerTotal << '\n';

	if (dealerTotal > 21)
	{
		std::cout << "congratulations, you won!\n";
	}
	else if (total > dealerTotal)
	{
		std::cout << "congratulations, you won!\n";
	}
	else if (total < dealerTotal)
	{
		std::cout << "You lost, skill issue.\n";
	}
	else
	{
		std::cout << "you tied!\n";
	}
}

void hit()
{
	Card newCard{ getRandomCard() };

	++additionalCards;
	std::string cardNumber{ cardNumberPrinter(additionalCards) };
	std::cout << "Here is your " << cardNumber << " card: ";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << newCard.cardName << '\n';
	newCard.aceChecker();
	total += newCard.value;
	std::cout << "Total: " << total << '\n';

	if (total > 21)
	{
		std::cout << "You lost, skill issue.\n";
	}
	else if (total == 21)
	{
		std::cout << "congratulations, you won!\n";
	}
	else
	{
		choice();
	}
}

bool playAgain()
{
	std::cout << "Do you want to play again? Type 'yes' or 'no'\n";
	char input{ getValidInput('y', 'n')};
	if (input == 'y')
	{
		std::cout << '\n';
		total = 0;
		dealerTotal = 0;
		dealerAdditionalCards = 0;
		additionalCards = 0;
		return true;
	}
	else if (input == 'n')
	{
		std::cout << "You quit the game like a noob.\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return false;
	}
}

void clearScreen()
{
	for (int i{ 0 }; i < 30; i++)
	{
		std::cout << '\n';
	}
}

void intro()
{
	while (true)
	{
		std::cout << "Here is your first card: ";
		Card card1{ getRandomCard()};
		std::cout << card1.cardName << '\n';
		total += card1.value;

		std::cout << "Here is your second card: ";
		Card card2{ getRandomCard() };
		std::cout << card2.cardName << '\n';
		card2.aceChecker();
		total += card2.value;

		if (total == 21)
		{
			std::cout << "congratulations you won!\n";
			if (playAgain())
			{
				clearScreen();
				continue;
			}
			return;
		}

		std::cout << "Total: " << total << "\n\n";

		std::cout << "Dealer's first card: ";
		Card dealerCard1{ getRandomCard()};
		std::cout << dealerCard1.cardName << '\n';
		dealerTotal += dealerCard1.value;

		std::cout << "Dealer's second card: hidden\n\n";
		choice();

		if (playAgain())
		{
			clearScreen();
			continue;
		}
		return;
	}

}

int main()
{
	intro();
}