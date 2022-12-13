#pragma once
#include <string>

class DeliveryCompany {
	std::string bulstat;
	std::string name;
	std::string address;
	std::string phone_number;

	DeliveryCompany();
public:
	DeliveryCompany(std::string bulstat, std::string name, std::string address, std::string phone_number);
	DeliveryCompany(const DeliveryCompany& o);

	std::string GetBulstat();
	void SetBulstat(std::string bulstat);

	std::string GetName();
	void SetName(std::string name);

	std::string GetAddress();
	void SetAddress(std::string address);

	std::string GetPhoneNumber();
	void SetPhoneNumber(std::string phone_number);

	bool operator==(const DeliveryCompany& rhs);
	friend std::ostream& operator<<(std::ostream& os, const DeliveryCompany& dc);
};
