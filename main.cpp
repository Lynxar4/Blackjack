#include <iostream>
#include <vector>
#include "Random.h"
void hit();

static int total{};
static int additionalCards{ 3 };

void choice()
{
	std::cout << "Do you want to hit or stand?\n";
	std::string input{};
	std::cin >> input;

	if (input == "hit")
	{
		hit();
		++additionalCards;
	}
	else if (input == "stand")
	{
		//stand();
	}
}

void hit()
{
	std::string cardNumber{};

	switch (additionalCards)
	{
	case 3: cardNumber = "third";
			break;
	case 4: cardNumber = "fourth";
			break;
	case 5: cardNumber = "fifth";
			break;
	case 6: cardNumber = "sixth";
			break;
	}

	int newCard{ Random::get(1, 11) };

	std::cout << "Here is your " << cardNumber << " card: ";
	std::cout << newCard << '\n';
	total += newCard;
	std::cout << "Total: " << total << '\n';

	if (total > 21)
	{
		std::cout << "You Lost.";
	}
	else if (total == 21)
	{
		std::cout << "Congratulations you won!";
	}
	else
	{
		choice();
	}
}

void intro()
{
	std::cout << "Here is your first card: ";
	int card1{ Random::get(1, 11) };
	std::cout << card1 << '\n';
	total += card1;

	std::cout << "Here is your second card: ";
	int card2{ Random::get(1, 11) };
	std::cout << card2 << '\n';
	total += card2;

	std::cout << "Total: " << total << '\n';
	choice();
}

int main()
{
	intro();
}