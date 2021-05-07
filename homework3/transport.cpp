#include "transport.h"

std::vector<std::string> split(const std::string& str, const std::vector<std::string>& delim)
{
	std::vector<std::string> tokens;
	size_t prev = 0, pos;
	do
	{
		pos = str.find(delim[0], prev);
		for (size_t i = 1; i < delim.size(); i++)
		{
			size_t pos1 = str.find(delim[i], prev);
			if (pos1 < pos)
				pos = pos1;

		}
		if (pos == std::string::npos) pos = str.length();
		std::string token = str.substr(prev, pos-prev);
		token.erase(remove(token.begin(), token.end(), ' '), token.end());
		if (!token.empty()) tokens.push_back(token);
		prev = pos + 1;
	}
	while (pos < str.length() && prev < str.length());
	return tokens;
}

Transport_station::Transport_station(
	int number,
	std::string type_of_vehicle,
	std::string object_type,
	std::string name_stopping,
	std::string the_official_name,
	std::string location,
	std::string routes,
	std::string coordinates)
	: number_(number)
	, type_of_vehicle_(type_of_vehicle)
	, object_type_(object_type)
	, name_stopping_(name_stopping)
	, the_official_name_(the_official_name)
{
	std::vector<std::string> sym1 = {","};
	std::vector<std::string> l = split(location, sym1);
	for (size_t i = 0; i < l.size(); i++)
	{
		location_.push_back((l[i]));
	}
	std::vector<std::string> sym2 = {".", ","};
	std::vector<std::string> r = split(routes, sym2);
	for (size_t i = 0; i < r.size(); i++)
	{
		routes_.push_back(r[i]);
	}
	std::vector<std::string> c = split(coordinates, sym1);
	latitude_ = std::stod(c[0]);
	longitude_ = std::stod(c[1]);
}

int Transport_station::number() const
{
	return number_;
}

std::string Transport_station::type_of_vehicle() const
{
	return type_of_vehicle_;
}

std::vector<std::string> Transport_station::locations() const
{
	return location_;
}

std::vector<std::string> Transport_station::routes() const
{
	return routes_;
}

double Transport_station::latitude() const
{
	return latitude_;
}

double Transport_station::longitude() const
{
	return longitude_;
}

std::string Transport_station::info() const
{
	std::string sroutes;
	for (size_t i = 0; i < routes_.size(); i++)
	{
		sroutes += routes_[i] + " ";
	}
	std::string slocation;
	for (size_t i = 0; i < location_.size(); i++)
	{
		slocation += location_[i];
	}

	return
		std::to_string(number_) + " " +
		type_of_vehicle_ + " " +
		name_stopping_ + " " +
		object_type_ + " " +
		the_official_name_ + " " +
		slocation + " " +
		sroutes + " " +
		std::to_string(latitude_) + "," + std::to_string(longitude_);
}