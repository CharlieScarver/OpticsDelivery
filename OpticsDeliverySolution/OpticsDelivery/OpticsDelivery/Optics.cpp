#include "Optics.h"
#include <iostream> // operator<< 

Optics::Optics(std::string type, float thickness, float diopter, std::string material)
{
	this->type = type;
	this->thickness = thickness;
	this->diopter = diopter;
	this->material = material;
}

Optics::Optics(const Optics& o)
{
	this->type = o.type;
	this->thickness = o.thickness;
	this->diopter = o.diopter;
	this->material = o.material;
}

std::string Optics::GetType()
{
	return std::string();
}

void Optics::SetType(std::string type)
{
	this->type = type;
}

float Optics::GetThickness() const
{
	return this->thickness;
}

void Optics::SetThickness(float thickness)
{
	this->thickness = thickness;
}

float Optics::GetDiopter() const
{
	return this->diopter;
}

void Optics::SetDiopter(float diopter)
{
	this->diopter = diopter;
}

std::string Optics::GetMaterial()
{
	return this->material;
}

void Optics::SetMaterial(std::string material)
{
	this->material = material;
}

bool Optics::operator==(const Optics& rhs)
{
	return this->type == rhs.type &&
		this->thickness == rhs.thickness &&
		this->diopter == rhs.diopter &&
		this->material == rhs.material;
}

std::ostream& operator<<(std::ostream& os, const Optics& opt)
{
	return os << "Optics("
		<< opt.type << ","
		<< opt.thickness << ","
		<< opt.diopter << ", "
		<< opt.material << ")";
}
