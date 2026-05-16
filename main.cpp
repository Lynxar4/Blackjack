#include <iostream>
#include <vector>
#include <array>
#include "Random.h"

static int total{};
static int additionalCards{ 0 };
static int dealerAdditionalCards{ 0 };
static int dealerTotal{ 0 };

struct Card
{
	int value{};
	std::string cardName{};
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

void choice()
{
	std::cout << "Do you want to hit or stand?\n";
	std::string input{};
	std::cin >> input;

	if (input == "hit")
	{
		++additionalCards;
		hit();
	}
	else if (input == "stand")
	{
		stand();
	}
}

void dealerAddCard()
{
	int randIndex{ Random::get(0, 13) };
	Card newCard{ Blackjack::cardValues[randIndex] };
	
	++dealerAdditionalCards;
	std::string cardNumber{};
	switch (dealerAdditionalCards)
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

	std::cout << "Dealer's " << cardNumber << " card: " << newCard.cardName << '\n';
	dealerTotal += newCard.value;
	std::cout << "Dealer's total: " << dealerTotal << '\n';
}

void stand()
{
	int randIndex{ Random::get(0, 13) };
	Card dealerCard{ Blackjack::cardValues[randIndex] };
	dealerTotal += dealerCard.value;
	std::cout << "Dealer's second card: " << dealerCard.cardName << '\n';

	while (dealerTotal <= 16)
	{
		dealerAddCard();
	}
	if (dealerTotal > 21)
	{
		std::cout << "congratulations, you won!";
	}
	else if (total > dealerTotal)
	{
		std::cout << "congratulations, you won!";
	}
	else if (total < dealerTotal)
	{
		std::cout << "you lost, skill issue";
	}
	else
	{
		std::cout << "you tied!";
	}
}

void hit()
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

	int randIndex{ Random::get(0, 13) };
	Card newCard{ Blackjack::cardValues[randIndex] };

	std::cout << "Here is your " << cardNumber << " card: ";
	std::cout << newCard.cardName << '\n';
	total += newCard.value;
	std::cout << "Total: " << total << '\n';

	if (total > 21)
	{
		std::cout << "You Lost.";
	}
	else if (total == 21)
	{
		std::cout << "congratulations, you won!";
	}
	else
	{
		choice();
	}
}

void intro()
{
	std::cout << "Here is your first card: ";
	int randIndex1{ Random::get(0, 13)};
	Card card1{ Blackjack::cardValues[randIndex1] };
	std::cout << card1.cardName << '\n';
	total += card1.value;

	std::cout << "Here is your second card: ";
	int randIndex2{ Random::get(0, 13) };
	Card card2{ Blackjack::cardValues[randIndex2] };
	std::cout << card2.cardName << '\n';
	total += card2.value;

	if (total == 21)
	{
		std::cout << "congratulations you won!";
		return;
	}

	std::cout << "Total: " << total << '\n';

	std::cout << "Dealer's first card: ";
	int randIndex3{ Random::get(0, 13) };
	Card dealerCard1{ Blackjack::cardValues[randIndex3] };
	std::cout << dealerCard1.cardName << '\n';
	dealerTotal += dealerCard1.value;

	std::cout << "Dealer's second card: hidden\n";
	choice();
}

int main()
{
	intro();
}