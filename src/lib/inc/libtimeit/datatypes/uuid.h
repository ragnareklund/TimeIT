//
// Created by hoglet on 11/11/2020.
//
#ifndef TIMEIT_UUID_H
#define TIMEIT_UUID_H

#include <optional>

namespace libtimeit
{
using namespace std;

class UUID
{
public:
	UUID();
	static optional<UUID> from_string(string uuid);

	bool operator==(const UUID &rhs) const;
	bool operator!=(const UUID &rhs) const;
	[[nodiscard]] const char *c_str() const;
	[[nodiscard]] string to_string() const;
	explicit operator std::string() const;
private:
	string id;
	explicit UUID(string basic_string);
};

}
#endif