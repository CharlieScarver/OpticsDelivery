#include <iostream>
#include <limits>
#include <vector>

#include "DeliveryCompany.h"
#include "Optics.h"

#define COMMANDS_COUNT 7

void printCommands()
{
	std::cout << "=== Commands ===" << std::endl;
	std::cout << "1) Add a new delivery company" << std::endl;
	std::cout << "2) Add a new optics piece" << std::endl;
	std::cout << "3) List all delivery companies" << std::endl;
	std::cout << "4) List all optics" << std::endl;
	std::cout << "5) Link delivery company and the optics it delivers?" << std::endl;
	std::cout << "6) Delete delivery company/optics" << std::endl;
	std::cout << "7) Place an order" << std::endl;
	std::cout << "8) Exit" << std::endl;
}

void clearStdin()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool isAlphaNumeric(std::string str)
{
	for (auto it = str.begin(); it != str.end(); it++) {
		if (!isalnum(*it)) {
			return false;
		}
	}

	return true;
}

void inputFloat(std::string message, float& input)
{
	bool repeat;
	do {
		repeat = false;
		std::cout << message << std::endl << "> ";
		if (!(std::cin >> input)) {
			std::cout << "Error: Invalid value" << std::endl;
			repeat = true;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (repeat);
	std::cout << input << std::endl;
}

void inputAlnumString(std::string message, std::string& input)
{
	bool repeat;
	do {
		repeat = false;
		std::cout << message << std::endl << "> ";
		if (!(std::cin >> input) || !isAlphaNumeric(input)) {
			std::cout << "Error: Invalid value" << std::endl;
			repeat = true;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (repeat);
	std::cout << input << std::endl;
}

DeliveryCompany* commandAddCompany()
{
	std::cout << std::endl << "===== Add a new delivery company =====" << std::endl;
	std::string bulstat;
	std::string name;
	std::string address;
	std::string phone_number;

	inputAlnumString("Enter bulstat (alphanumeric string): ", bulstat);
	inputAlnumString("Enter name (alphanumeric string): ", name);
	inputAlnumString("Enter address (alphanumeric string): ", address);
	inputAlnumString("Enter phone_number (alphanumeric string): ", phone_number);

	DeliveryCompany* delivery_comp = new DeliveryCompany(bulstat, name, address, phone_number);
	return delivery_comp;
}

Optics* commandAddOptics()
{
	std::cout << std::endl << "===== Add a new optics piece =====" << std::endl;
	std::string type;
	float thickness;
	float diopter;
	std::string material;

	inputAlnumString("Enter type (alphanumeric string): ", type);
	inputFloat("Enter thickness (float): ", thickness);
	inputFloat("Enter diopter (float): ", diopter);
	inputAlnumString("Enter material (alphanumeric string): ", material);

	Optics* optics = new Optics(type, thickness, diopter, material);
	return optics;
}

void commandListCompanies(const std::vector<DeliveryCompany*>& companies)
{
	std::cout << std::endl << "===== List all delivery companies =====" << std::endl;
	int i = 0;
	for (auto it = companies.begin(); it != companies.end(); it++, i++)
	{
		std::cout << "[" << i << "] = " << *(*it) << std::endl;
	}
}

int main() {
	std::cout << "Kek" << std::endl;

	std::vector<DeliveryCompany*> companies;
	std::vector<Optics*> optics;

	// TODO: Read from file if there is one

	int choice;
	bool repeat = false;
	char pause;
	do {
		printCommands();
		std::cout << "Choose an item from the menu (integer): " << std::endl << "> ";
		if (!(std::cin >> choice)) {
			std::cout << "Error: Invalid value" << std::endl;
			repeat = true;
			clearStdin();
		}

		switch (choice)
		{
		case 1:
			companies.push_back(commandAddCompany());
			break;
		case 2:
			optics.push_back(commandAddOptics());
			break;
		case 3:
			commandListCompanies(companies);
			break;
		default:
			break;
		}
		std::cout << std::endl << "Press any key to continue..." << std::endl;
		std::cin.get();
		clearStdin();
	} while ((choice > 0 && choice <= COMMANDS_COUNT) || repeat);

	// TODO: Write to file

	// Free allocated memory
	for (auto it = companies.begin(); it != companies.end(); it++)
	{
		delete* it;
	}
	for (auto it = optics.begin(); it != optics.end(); it++)
	{
		delete* it;
	}

	std::cout << "Goodbye" << std::endl;
	return 0;
}
