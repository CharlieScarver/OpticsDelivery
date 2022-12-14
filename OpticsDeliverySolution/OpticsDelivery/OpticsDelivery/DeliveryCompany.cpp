#include "DeliveryCompany.h"
#include <iostream> // operator<< 
#include <algorithm>

DeliveryCompany::DeliveryCompany(std::string bulstat, std::string name, std::string address, std::string phone_number)
{
	this->bulstat = bulstat;
	this->name = name;
	this->address = address;
	this->phone_number = phone_number;
}

DeliveryCompany::DeliveryCompany(const DeliveryCompany& o)
{
	this->bulstat = o.bulstat;
	this->name = o.name;
	this->address = o.address;
	this->phone_number = o.phone_number;
}

std::string DeliveryCompany::GetBulstat() const
{
	return this->bulstat;
}

void DeliveryCompany::SetBulstat(std::string bulstat)
{
	this->bulstat = bulstat;
}

std::string DeliveryCompany::GetName() const
{
	return this->name;
}

void DeliveryCompany::SetName(std::string name)
{
	this->name = name;
}

std::string DeliveryCompany::GetAddress() const
{
	return this->address;
}

void DeliveryCompany::SetAddress(std::string address)
{
	this->address = address;
}

std::string DeliveryCompany::GetPhoneNumber() const
{
	return this->phone_number;
}

void DeliveryCompany::SetPhoneNumber(std::string phone_number)
{
	this->phone_number = phone_number;
}
//const std::vector<Optics*>& DeliveryCompany::GetDeliverables() const
const std::vector<Optics*>& DeliveryCompany::GetDeliverables() const
{
	return this->deliverables;
}

bool DeliveryCompany::AddDeliverable(Optics* optics)
{
	auto it = std::find(this->deliverables.begin(), this->deliverables.end(), optics);
	// If item is not found, add it
	if (it == this->deliverables.end())
	{
		this->deliverables.push_back(optics);
		return true;
	}

	return false;
}

Optics* DeliveryCompany::RemoveDeliverable(Optics* optics)
{
	Optics* item = nullptr;
	auto it = std::find(this->deliverables.begin(), this->deliverables.end(), optics);
	// If item is found, remove it
	if (it != this->deliverables.end())
	{
		item = *it;
		this->deliverables.erase(it);
	}

	return item;
}

bool DeliveryCompany::operator==(const DeliveryCompany& rhs)
{
	return this->bulstat == rhs.bulstat &&
		this->name == rhs.name &&
		this->address == rhs.address &&
		this->phone_number == rhs.phone_number;
}

std::ostream& operator<<(std::ostream& os, const DeliveryCompany& dc)
{
	return os << "DeliveryCompany("
		<< dc.bulstat << ","
		<< dc.name << ","
		<< dc.address << ","
		<< dc.phone_number << ")";
}
