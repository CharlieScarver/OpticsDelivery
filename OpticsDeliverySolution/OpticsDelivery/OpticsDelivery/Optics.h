#pragma once
#include <string>

class Optics {
private:
	std::string type;
	float thickness;
	float diopter;
	std::string material;

	Optics();
public:
	Optics(std::string type, float thickness, float diopter, std::string material);
	Optics(const Optics &o);

	std::string GetType();
	void SetType(std::string type);

	float GetThickness() const;
	void SetThickness(float thickness);

	float GetDiopter() const;
	void SetDiopter(float diopter);

	std::string GetMaterial();
	void SetMaterial(std::string material);

	bool operator==(const Optics& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Optics& opt);
};
