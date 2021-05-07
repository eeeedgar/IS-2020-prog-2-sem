#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <set>
#include <map>
#include <vector>
#include <string>
#include "pugixml.hpp"

#include "transport.h"

using namespace std;

int main()
{
	system("chcp 65001");
	pugi::xml_document doc;
	// pugi::xml_parse_result result =
	doc.load_file("C:\\repos\\IS-2020-prog-2-sem\\homework3\\data.xml");
	pugi::xml_node nd = doc.child("dataset");

	std::vector<Transport_station> stations; // просто список станций
	std::set<std::string> transport_types; // словарь названий транспорта
	//std::map<std::string, std::map< std::string, std::vector<int> > > routes; // словарь
	std::map<std::string, std::set<int> > streets; // словарь : название улицы - словарь номеров станций

	map<string, map<string, vector<int> > > routes; // вид транспорта - маршрут - вектор номеров остановок

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
		for (size_t i = 0; i < ts->locations().size(); i++)
		{
			streets[ts->locations()[i]].insert(ts->number());
		}
		for (int i = 0; i < stations[stations.size() - 1].routes().size(); i++)
		{
			routes[it->child_value("type_of_vehicle")][stations[stations.size() - 1].routes()[i]].push_back(stations[stations.size() - 1].number());
		}
	}

	map<string, map<string, vector<int>>>::iterator max_station_transport_route = routes.begin();
	cout << endl;
	for (auto& transport : transport_types)
	{
		int max_len = 0;
		string num_max_route = "";
		for (auto& [route, vec] : routes[transport])
		{
			if (vec.size() > max_len)
			{
				max_len = vec.size();
				num_max_route = route;
			}
		}
		cout << transport  << ": номер маршрута с наибольшим количеством остановок: " << num_max_route << ", количество остановок: " << max_len << "." << endl;
	}
	cout << endl;

	for (auto& transport : transport_types)
	{
		int max_len = 0;
		string num_max_route = "";
		for (auto& [route, vec] : routes[transport])
		{
			double len = 0;
			for (size_t i = 0; i < vec.size() - 1; i++)
			{
				double w1 = stations[vec[i]].latitude();
				double w2 = stations[vec[i + 1]].latitude();
				double l1 = stations[vec[i]].longitude();
				double l2 = stations[vec[i + 1]].longitude();

				len += sqrt(pow(l1 - l2, 2) + pow(w1 - w2, 2));

			}
			if (len > max_len)
			{
				max_len = len;
				num_max_route = route;
			}
		}
		cout << transport  << ": номер маршрута с наибольшей длиной: " << num_max_route << "." << endl;
	}

	string max_stations_street = "";
	int max_stations_on_street = 0;
	for (auto& [street, stats] : streets)
	{
		if (stats.size() > max_stations_on_street)
		{
			max_stations_on_street = stats.size();
			max_stations_street = street;
		}
	}
	std::cout << "\nУлица с наибольшим числом остановок: " << max_stations_street << " - " << max_stations_on_street << " остановок" << "." << std::endl;

	std::cout << stations.size() << std::endl;
	std::cout << streets.size() << std::endl;

	return 0;
}
