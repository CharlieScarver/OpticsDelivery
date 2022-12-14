#pragma once
#include <string>
#include <vector>

#include "DeliveryCompany.h"
#include "Optics.h"

class CommandMenu {
private:
	std::vector<DeliveryCompany*> companies;
	std::vector<Optics*> optics;
public:
	CommandMenu();

	// Utility
	void printCommands() const;
	void clearStdin() const;
	bool isAlphaNumeric(std::string str) const;
	void inputFloat(std::string message, float& input, float min, float max) const;
	void inputAlnumString(std::string message, std::string& input) const;
	void loadFromFile();
	void saveToFile() const;

	// Commands
	void commandAddCompany();
	void commandAddOptics();
	void commandListCompanies() const;
	void commandListOptics() const;
	void commandPlaceOrder() const;

	void run();
};
