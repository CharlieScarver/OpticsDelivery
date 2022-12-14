#include <iostream>
#include <limits>
#include <fstream>
#include "CommandMenu.h"

#define COMMANDS_COUNT 5
#define SAVE_FILE "save_file.txt" 
#define BACKUP_FILE "backup.txt" 

CommandMenu::CommandMenu()
{
}

void CommandMenu::printCommands() const
{
	std::cout << "=== Commands ===" << std::endl;
	std::cout << "1) Add a new delivery company" << std::endl;
	std::cout << "2) Add a new optics piece" << std::endl;
	std::cout << "3) List all delivery companies" << std::endl;
	std::cout << "4) List all optics" << std::endl;
	std::cout << "5) Place an order" << std::endl;
	std::cout << "6) Exit" << std::endl;
}

void CommandMenu::clearStdin() const
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool CommandMenu::isAlphaNumeric(std::string str) const
{
	for (auto it = str.begin(); it != str.end(); it++) {
		if (!isalnum(*it) && *it != ' ' && *it != '.') {
			return false;
		}
	}

	return true;
}

void CommandMenu::inputFloat(std::string message, float& input, float min, float max) const
{
	bool repeat;
	do {
		repeat = false;
		std::cout << message << std::endl << "> ";
		if (!(std::cin >> input) || input < min || input > max) {
			std::cout << "Error: Invalid value" << std::endl;
			repeat = true;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (repeat);
}

void CommandMenu::inputAlnumString(std::string message, std::string& input) const
{
	// Clear leading whitespaces
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	bool repeat;
	do {
		repeat = false;
		std::cout << message << std::endl << "> ";
		if (!std::getline(std::cin, input) || !isAlphaNumeric(input)) {
			std::cout << "Error: Invalid value" << std::endl;
			repeat = true;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (repeat);
}

void CommandMenu::loadFromFile()
{
	std::cout << "Checking for a save file to load..." << std::endl;

	std::ifstream save_read;
	save_read.open(SAVE_FILE, std::ios_base::in);

	if (save_read.fail()) {
		std::cout << "Save file missing or could not be loaded" << std::endl;
		save_read.close();
		return;
	}

	std::cout << "Loading from the save file..." << std::endl;

	std::string line;
	while (std::getline(save_read, line, '\n'))
	{
		size_t pos = line.find("(");
		if (pos == std::string::npos) {
			std::cout << "Skipping line \"" << line << "\" - Couldn't parse" << std::endl;
			save_read.close();
			return;
		}

		std::string type = line.substr(0, pos);
		std::string sub_line = line.substr(pos + 1);
		if (type == "DeliveryCompany")
		{
			size_t next_pos = sub_line.find(",");
			if (next_pos == std::string::npos) {
				std::cout << "Skipping line \"" << line << "\" - Couldn't parse" << std::endl;
				save_read.close();
				return;
			}
			std::string bulstat = sub_line.substr(0, next_pos);
			sub_line = sub_line.substr(next_pos + 1);

			next_pos = sub_line.find(",");
			std::string name = sub_line.substr(0, next_pos);
			sub_line = sub_line.substr(next_pos + 1);

			next_pos = sub_line.find(",");
			std::string address = sub_line.substr(0, next_pos);
			sub_line = sub_line.substr(next_pos + 1);

			next_pos = sub_line.find(")");
			std::string phone_number = sub_line.substr(0, next_pos);

			DeliveryCompany *company = new DeliveryCompany(bulstat, name, address, phone_number);
			this->companies.push_back(company);
		}
		else if (type == "Optics")
		{
			size_t next_pos = sub_line.find(",");
			if (next_pos == std::string::npos) {
				std::cout << "Skipping line \"" << line << "\" - Couldn't parse" << std::endl;
				save_read.close();
				return;
			}
			std::string opt_type = sub_line.substr(0, next_pos);
			sub_line = sub_line.substr(next_pos + 1);

			next_pos = sub_line.find(",");
			float thickness = std::stof(sub_line.substr(0, next_pos));
			sub_line = sub_line.substr(next_pos + 1);

			next_pos = sub_line.find(",");
			float diopter = std::stof(sub_line.substr(0, next_pos));
			sub_line = sub_line.substr(next_pos + 1);

			next_pos = sub_line.find(",");
			std::string material = sub_line.substr(0, next_pos);
			sub_line = sub_line.substr(next_pos + 1);

			next_pos = sub_line.find(")");
			float price = std::stof(sub_line.substr(0, next_pos));

			Optics *optics = new Optics(opt_type, thickness, diopter, material, price);
			this->optics.push_back(optics);
		}
	}

	save_read.close();
	std::cout << "Save file loaded successfully" << std::endl;
}

void CommandMenu::saveToFile() const
{
	std::cout << "Saving..." << std::endl;

	bool skip_backup = false;

	std::ifstream save_read;
	std::ofstream save_write;

	// Make sure the file exists
	save_write.open(SAVE_FILE, std::ios_base::out);
	save_write.close();

	save_read.open(SAVE_FILE, std::ios_base::in);

	if (save_read.fail()) {
		std::cout << "Error opening save file!" << std::endl;
		skip_backup = true;
		save_read.close();
		return;
	}

	// Copy the current save file content to the backup file in case something goes wrong
	std::ofstream backup;
	backup.open(BACKUP_FILE, std::ios_base::out);

	if (backup.fail()) {
		std::cout << "Error opening backup file!" << std::endl;
		skip_backup = true;
		backup.close();
		return;
	}

	std::string line;
	while (std::getline(save_read, line, '\n'))
	{
		backup << line;
	}
	backup.close();
	save_read.close();

	// Write the current state to the save file
	save_write.open(SAVE_FILE, std::ios_base::out);
	for (auto it = this->companies.begin(); it != this->companies.end(); it++)
	{
		save_write << *(*it) << std::endl;
	}
	for (auto it = this->optics.begin(); it != this->optics.end(); it++)
	{
		save_write << *(*it) << std::endl;
	}
	save_write.close();

	std::cout << "Saved successfully" << std::endl;
}

void CommandMenu::commandAddCompany()
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
	this->companies.push_back(delivery_comp);
}

void CommandMenu::commandAddOptics()
{
	std::cout << std::endl << "===== Add a new optics piece =====" << std::endl;
	std::string type;
	float thickness;
	float diopter;
	std::string material;
	float price;

	inputAlnumString("Enter type (alphanumeric string): ", type);
	inputFloat("Enter thickness (float): ", thickness, 0, 100);
	inputFloat("Enter diopter (float): ", diopter, -100, 100);
	inputAlnumString("Enter material (alphanumeric string): ", material);
	inputFloat("Enter price (float): ", price, 0, 99999);

	Optics* optics = new Optics(type, thickness, diopter, material, price);
	this->optics.push_back(optics);
}

void CommandMenu::commandListCompanies() const
{
	std::cout << std::endl << "===== List all delivery companies =====" << std::endl;
	int i = 0;
	for (auto it = this->companies.begin(); it != this->companies.end(); it++, i++)
	{
		std::cout << "[" << i << "] = " << *(*it) << std::endl;
	}
}

void CommandMenu::commandListOptics() const
{
	std::cout << std::endl << "===== List all optics pieces =====" << std::endl;
	int i = 0;
	for (auto it = this->optics.begin(); it != this->optics.end(); it++, i++)
	{
		std::cout << "[" << i << "] = " << *(*it) << std::endl;
	}
}

void CommandMenu::commandPlaceOrder() const
{
	float choice;
	this->commandListCompanies();
	inputFloat("Choose a delivery company from the list (integer): ", choice, 0, this->companies.size());
	DeliveryCompany* company = this->companies[choice];

	std::string confirm;
	std::vector<Optics*> order;
	float price_total = 0;
	do {
		this->commandListOptics();
		inputFloat("Choose optics to buy from the list (integer): ", choice, 0, this->optics.size());
		Optics* opt = this->optics[choice];
		order.push_back(opt);
		price_total += opt->GetPrice();

		inputAlnumString("Do you want to add more optics to the order? (y/n)", confirm);
	} while (confirm == "y");

	std::cout << std::endl;
	std::cout << "=== Order Receipt ===" << std::endl;
	std::cout << "Delivery company: " << company->GetName() << std::endl;
	std::cout << "Items: " << std::endl;
	int i = 0;
	for (auto it = order.begin(); it != order.end(); it++, i++)
	{
		Optics* op = *it;
		std::cout << "\t" << i << ". " << op->GetType() << "\t\tThickness: " << op->GetThickness() 
			<< "mm  Dpt: " << op->GetDiopter() << "\t\t|  Price: " << op->GetPrice() << std::endl;
	}
	std::cout << "------------" << std::endl;
	std::cout << "Total: " << price_total << std::endl << std::endl;
}

void CommandMenu::run() {
	// DeliveryCompany dc("", "", "", "");
	// Optics op("", 1, 1, "");
	//const std::vector<Optics*>& deliv = dc.GetDeliverables().pop_back();

	// Load state from save file if there is one
	this->loadFromFile();

	int choice;
	bool repeat = false;
	do {
		this->printCommands();
		std::cout << "Choose an item from the menu (integer): " << std::endl << "> ";
		if (!(std::cin >> choice)) {
			std::cout << "Error: Invalid value" << std::endl;
			repeat = true;
			this->clearStdin();
		}

		switch (choice)
		{
		case 1:
			this->commandAddCompany();
			this->saveToFile();
			break;
		case 2:
			this->commandAddOptics();
			this->saveToFile();
			break;
		case 3:
			this->commandListCompanies();
			break;
		case 4:
			this->commandListOptics();
			break;
		case 5:
			this->commandPlaceOrder();
			break;
		default:
			break;
		}

		//std::cout << std::endl << "Press Enter to continue..." << std::endl;
		//std::cin.get();
		this->clearStdin();
	} while ((choice > 0 && choice <= COMMANDS_COUNT) || repeat);

	// Free allocated memory
	for (auto it = this->companies.begin(); it != this->companies.end(); it++)
	{
		delete* it;
	}
	for (auto it = this->optics.begin(); it != this->optics.end(); it++)
	{
		delete* it;
	}

	std::cout << "Goodbye" << std::endl;
}
