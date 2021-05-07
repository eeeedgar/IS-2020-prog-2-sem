#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_

#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <math.h>

std::vector<std::string> split(const std::string& str, const std::vector<std::string>& delim);

class Transport_station
{
 private:
	int number_;
	std::string type_of_vehicle_;
	std::string name_stopping_;
	std::string object_type_;
	std::string the_official_name_;
	std::vector<std::string> location_;
	std::vector<std::string> routes_;
	double latitude_, longitude_;
 public:
	explicit Transport_station(
		int = 0,
		std::string = "type_of_vehicle",
		std::string = "object_type",
		std::string = "name_stopping",
		std::string = "the_official_name",
		std::string = "location",
		std::string = "routes",
		std::string = "coordinates");

	int number() const;
	std::string type_of_vehicle() const;
	std::vector<std::string> locations() const;
	std::vector<std::string> routes() const;
	double latitude() const;
	double longitude() const;
	std::string info() const;
};
/*
class Route
{
 private:
	std::vector<Transport_station> stations;
	std::map
};
 */

#endif //_TRANSPORT_H_
