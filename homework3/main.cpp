#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <set>
#include <map>
#include <vector>
#include <string>
#include "pugixml.hpp"


std::vector<std::string> split(const std::string& str, const std::vector<std::string>& delim)
{
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim[0], prev);
		for (int i = 1; i < delim.size(); i++)
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


class Transport_station
{
 private:
	int number_;
	std::string type_of_vehicle_;
	std::string name_stopping_;
	std::string object_type_;
	std::string the_official_name_;
	//std::string location_;
	std::vector<std::string> location_;
	//std::string sroutes_;
	std::vector<std::string> routes_;
	//std::string coordinates_;
	double latitude_, longitude_;
 public:
	Transport_station(
		int number = 0,
		std::string type_of_vehicle = "type_of_vehicle",
		std::string object_type = "object_type",
		std::string name_stopping = "name_stopping",
		std::string the_official_name = "the_official_name",
		std::string location = "location",
		std::string routes = "routes",
		std::string coordinates = "coordinates")
		: number_(number)
		, type_of_vehicle_(type_of_vehicle)
		, object_type_(object_type)
		, name_stopping_(name_stopping)
		, the_official_name_(the_official_name)
	{
		std::vector<std::string> sym1 = {","};
		std::vector<std::string> l = split(location, sym1);
		for (int i = 0; i < l.size(); i++)
		{
			location_.push_back((l[i]));
		}
		std::vector<std::string> sym2 = {".", ","};
		std::vector<std::string> r = split(routes, sym2);
		for (int i = 0; i < r.size(); i++)
		{
			routes_.push_back(r[i]);
		}
		std::vector<std::string> c = split(coordinates, sym1);
		latitude_ = std::stod(c[0]);
		longitude_ = std::stod(c[1]);
	}

	int number() const
	{
		return number_;
	}

	std::vector<std::string> locations() const
	{
		return location_;
	}

	std::string info() const
	{
		std::string sroutes;
		for (int i = 0; i < routes_.size(); i++)
		{
			sroutes += routes_[i] + " ";
		}
		std::string slocation;
		for (int i = 0; i < location_.size(); i++)
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
};


int main()
{

	system("chcp 65001");
	pugi::xml_document doc;
	// pugi::xml_parse_result result =
	doc.load_file("C:\\repos\\IS-2020-prog-2-sem\\homework3\\data.xml");
	pugi::xml_node nd = doc.child("dataset");

	std::vector<Transport_station> stations;
	std::set<std::string> transport_types;
	std::map<std::string, std::map< std::string, std::vector<int> > > routes;
	std::map<std::string, std::set<int> > streets;

	for (pugi::xml_node_iterator it = nd.begin(); it != nd.end(); ++it)
	{
		stations.push_back(Transport_station(
			std::stoi(it->child_value("number")),
			it->child_value("type_of_vehicle"),
			it->child_value("object_type"),
			it->child_value("name_stopping"),
			it->child_value("the_official_name"),
			it->child_value("location"),
			it->child_value("routes"),
			it->child_value("coordinates")
			));
		transport_types.insert(it->child_value("type_of_vehicle"));
		auto ts = &stations.back();
		for (int i = 0; i < ts->locations().size(); i++)
		{
			streets[ts->locations()[i]].insert(ts->number());
		}
	}

	std::map<std::string, std::set<int> >::iterator max_stations_street = streets.begin();
	for(std::map<std::string, std::set<int> >::iterator it = streets.begin(); it != streets.end(); it++)
	{
		if (it->second.size() > max_stations_street->second.size())
			max_stations_street = it;
	}
	std::cout << "Улица с наибольшим числом остановок: " << max_stations_street->first << " - " << max_stations_street->second.size() << " остановок" << std::endl;


	std::cout << stations.size() << std::endl;
	std::cout << streets.size() << std::endl;


	return 0;
}
