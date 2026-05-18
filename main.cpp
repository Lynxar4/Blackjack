#include <iostream>
#include <array>
#include <limits>
#include <string_view>
#include "Random.h"

static int total{};
static int additionalCards{ 0 };
static int dealerAdditionalCards{ 0 };
static int dealerTotal{ 0 };

struct Card
{
	int value{};
	std::string cardName{};

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
	std::array<Card, 14> cardValues
	{
		Card{1, "one"}, Card{2, "two"}, Card{3, "three"}, Card{4, "four"}, Card{5, "five"},
		Card{6, "six"}, Card{7, "seven"}, Card{8, "eight"}, Card{9, "nine"}, Card{10, "ten"},
		Card{10, "Jack"}, Card{10, "Queen"}, Card{10, "King"}, Card{11, "Ace"}
	};
}

void hit();
void stand();

std::string getValidInput(std::string_view condition1, std::string_view condition2)
{
	std::string input{};
	std::cin >> input;
	while (input != condition1 && input != condition2)
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Type '" << condition1 << "' or '" << condition2 << "'\n";
		std::cin >> input;
	}
	return input;
}

void choice()
{
	std::cout << "Do you want to hit or stand?\n";
	std::string input{ getValidInput("hit", "stand") };

	if (input == "hit")
	{
		hit();
	}
	else if (input == "stand")
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

void dealerAddCard()
{
	int randIndex{ Random::get(0, 13) };
	Card newCard{ Blackjack::cardValues[randIndex] };
	
	++dealerAdditionalCards;
	std::string cardNumber{cardNumberPrinter(dealerAdditionalCards)};
	std::cout << "Dealer's " << cardNumber << " card: " << newCard.cardName << '\n';
	newCard.dealerAceChecker();
	dealerTotal += newCard.value;
	std::cout << "Dealer's total: " << dealerTotal << '\n';
}

void stand()
{
	int randIndex{ Random::get(0, 13) };
	Card dealerCard{ Blackjack::cardValues[randIndex] };
	dealerCard.aceChecker();
	dealerTotal += dealerCard.value;
	std::cout << "Dealer's second card: " << dealerCard.cardName << '\n';

	while (dealerTotal <= 16)
	{
		dealerAddCard();
	}
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
	int randIndex{ Random::get(0, 13) };
	Card newCard{ Blackjack::cardValues[randIndex] };

	++additionalCards;
	std::string cardNumber{ cardNumberPrinter(additionalCards) };
	std::cout << "Here is your " << cardNumber << " card: ";
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

void intro()
{
	while (true)
	{
		std::cout << "Here is your first card: ";
		int randIndex1{ Random::get(0, 13) };
		Card card1{ Blackjack::cardValues[randIndex1] };
		std::cout << card1.cardName << '\n';
		total += card1.value;

		std::cout << "Here is your second card: ";
		int randIndex2{ Random::get(0, 13) };
		Card card2{ Blackjack::cardValues[randIndex2] };
		std::cout << card2.cardName << '\n';
		card2.aceChecker();
		total += card2.value;

		if (total == 21)
		{
			std::cout << "congratulations you won!\n";
			return;
		}

		std::cout << "Total: " << total << "\n\n";

		std::cout << "Dealer's first card: ";
		int randIndex3{ Random::get(0, 13) };
		Card dealerCard1{ Blackjack::cardValues[randIndex3] };
		std::cout << dealerCard1.cardName << '\n';
		dealerTotal += dealerCard1.value;

		std::cout << "Dealer's second card: hidden\n";
		choice();

		std::cout << "Do you want to play again? Type 'yes' or 'no'\n";
		std::string input{ getValidInput("yes", "no") };
		if (input == "yes")
		{
			total = 0;
			dealerTotal = 0;
			continue;
		}
		else if (input == "no")
		{
			std::cout << "You quit the game like a noob.\n";
			return;
		}
	}

}

int main()
{
	intro();
}