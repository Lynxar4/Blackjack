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
};

void hit(std::vector<Card>& deck, double& balance, const double& betAmount);
void stand(std::vector<Card>& deck, double& balance, const double& betAmount);

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

double getValidNumber(const double& balance)
{
	while (true)
	{
		double num{};
		std::cin >> num;
		if (!std::cin)
		{
			std::cout << "Invalid input. Please enter a number.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else if (num > balance)
		{
			std::cout << "You can't bet more then your balance\n";
			continue;
		}
		else if (num == 0)
		{
			std::cout << "You have to bet mate, this is a gambling game\n";
			continue;
		}
		else if (num < 0)
		{
			std::cout << "Why are you entering negative numbers??\n";
			continue;
		}
		return num;
	}
}

void choice(std::vector<Card>& deck, double& balance, const double& betAmount)
{
	std::cout << "Do you want to hit or stand?\n";
	char input{ getValidInput('h', 's')};

	if (input == 'h')
	{
		hit(deck, balance, betAmount);
	}
	else if (input == 's')
	{
		stand(deck, balance, betAmount);
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

Card getRandomCard(std::vector<Card>& deck)
{
	int randIndex{ Random::get(0, static_cast<int>(deck.size()) - 1) };
	Card newCard{deck[randIndex] };
	deck.erase(deck.begin() + randIndex);
	return newCard;
}

void aceChecker(Card& card)
{
	if (card.cardName == "Ace")
	{
		if (card.value + total > 21)
		{
			card.value = 1;
		}
	}
}

void dealerAddCard(std::vector<Card>& deck)
{
	Card newCard{ getRandomCard(deck) };
	
	++dealerAdditionalCards;
	std::string cardNumber{cardNumberPrinter(dealerAdditionalCards)};
	std::cout << "Dealer's " << cardNumber << " card: ";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << newCard.cardName << '\n';
	aceChecker(newCard);
	dealerTotal += newCard.value;
}

void addBalance(double& balance, const double& betAmount)
{
	balance += betAmount;
	std::cout << "balance: $" << balance << '\n';
}

void addBalance21(double& balance, const double& betAmount)
{
	balance += betAmount * 1.5;
	std::cout << "balance: $" << balance << '\n';
}
void removeBalance(double& balance, const double& betAmount)
{
	balance -= betAmount;
	std::cout << "balance: $" << balance << '\n';
}

void stand(std::vector<Card>& deck, double& balance, const double& betAmount)
{
	Card dealerCard2{ getRandomCard(deck) };
	aceChecker(dealerCard2);
	dealerTotal += dealerCard2.value;
	std::cout << "Dealer's second card: ";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << dealerCard2.cardName << '\n';

	while (dealerTotal <= 16)
	{
		dealerAddCard(deck);
	}

	std::cout << "Dealer's total: " << dealerTotal << '\n';

	if (dealerTotal > 21)
	{
		std::cout << "congratulations, you won!\n";
		addBalance(balance, betAmount);
	}
	else if (total > dealerTotal)
	{
		std::cout << "congratulations, you won!\n";
		addBalance(balance, betAmount);
	}
	else if (total < dealerTotal)
	{
		std::cout << "You lost, skill issue.\n";
		removeBalance(balance, betAmount);
	}
	else
	{
		std::cout << "you tied!\n";
		std::cout << "balance: $" << balance << '\n';
	}
}

void hit(std::vector<Card>& deck, double& balance, const double& betAmount)
{
	Card newCard{ getRandomCard(deck) };

	++additionalCards;
	std::string cardNumber{ cardNumberPrinter(additionalCards) };
	std::cout << "Here is your " << cardNumber << " card: ";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << newCard.cardName << '\n';
	aceChecker(newCard);
	total += newCard.value;
	std::cout << "Total: " << total << '\n';

	if (total > 21)
	{
		std::cout << "You lost, skill issue.\n";
		removeBalance(balance, betAmount);
	}
	else if (total == 21)
	{
		std::cout << "congratulations, you won!\n";
		addBalance21(balance, betAmount);
	}
	else
	{
		choice(deck, balance, betAmount);
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
		std::this_thread::sleep_for(std::chrono::seconds(2));
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

std::vector<Card> createDeck()
{
	std::array<std::string, 4> suits{ "heart", "club", "diamond", "spade" };
	std::array<std::string, 13> cardValueNames{ "Ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "Jack", "Queen", "King" };
	std::array<int, 13> cardValues{ 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};


	std::vector<Card> fullDeck{};
	for (int i{ 0 }; i < suits.size(); ++i)
	{
		for (int j{ 0 }; j < cardValues.size(); ++j)
		{
			fullDeck.emplace_back(Card{ cardValues[j], cardValueNames[j], suits[i] });
		}
	}
	return fullDeck;
}

double bet(const double& balance)
{
	std::cout << "Choose how much to bet\n";
	double amount{ getValidNumber(balance) };
	return amount;
}

bool checkGameOver(const double& balance)
{
	if (balance >= 500)
	{
		std::cout << "Congratulations you beat the game!";
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return true;
	}
	else if (balance <= 0)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "You're out of money. Goodbye buddy.";
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return true;
	}
	return false;
}

void intro()
{
	std::cout << "Hi, welcome to Blackjack | Goal: Get $500\n";
	std::cout << "Starting balance: $100\n";
	double balance{ 100 };

	std::vector<Card> deck{ createDeck() };
	while (true)
	{
		double betAmount{ bet(balance) };
		std::cout << "Here is your first card: ";
		Card card1{ getRandomCard(deck)};
		std::cout << card1.cardName << '\n';
		total += card1.value;

		std::cout << "Here is your second card: ";
		Card card2{ getRandomCard(deck) };
		std::cout << card2.cardName << '\n';
		aceChecker(card2);
		total += card2.value;

		if (total == 21)
		{
			std::cout << "congratulations you won!\n";
			addBalance21(balance, betAmount);
			if (checkGameOver(balance))
			{
				return;
			}
			if (playAgain())
			{
				clearScreen();
				continue;
			}
			return;
		}

		std::cout << "Total: " << total << "\n\n";

		std::cout << "Dealer's first card: ";
		Card dealerCard1{ getRandomCard(deck)};
		std::cout << dealerCard1.cardName << '\n';
		dealerTotal += dealerCard1.value;
		std::cout << "Dealer's second card: hidden\n\n";

		choice(deck, balance, betAmount);

		if (checkGameOver(balance))
		{
			return;
		}

		if (playAgain())
		{
			deck = createDeck();
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