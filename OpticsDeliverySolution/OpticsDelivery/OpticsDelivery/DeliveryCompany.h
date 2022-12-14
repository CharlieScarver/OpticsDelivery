#pragma once
#include <string>
#include <vector>
#include "Optics.h"

class DeliveryCompany {
	std::string bulstat;
	std::string name;
	std::string address;
	std::string phone_number;
	std::vector<Optics*> deliverables;

	DeliveryCompany();
public:
	DeliveryCompany(std::string bulstat, std::string name, std::string address, std::string phone_number);
	DeliveryCompany(const DeliveryCompany& o);

	std::string GetBulstat() const;
	void SetBulstat(std::string bulstat);

	std::string GetName() const;
	void SetName(std::string name);

	std::string GetAddress() const;
	void SetAddress(std::string address);

	std::string GetPhoneNumber() const;
	void SetPhoneNumber(std::string phone_number);
	
	//const std::vector<Optics*>& GetDeliverables() const;
	const std::vector<Optics*>& GetDeliverables() const;
	bool AddDeliverable(Optics *optics);
	Optics* RemoveDeliverable(Optics *optics);

	bool operator==(const DeliveryCompany& rhs);
	friend std::ostream& operator<<(std::ostream& os, const DeliveryCompany& dc);
};
