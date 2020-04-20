#pragma once

#include <vector>
#include <string>
#include <map>
#include <limits.h>

class MyCountMinSketch {
public:
	MyCountMinSketch(int w, int d);

	void add(std::string& value);
	int check(std::string value);

private:
	size_t myHash(std::string& value, int i);
	int m_depth;
	int m_width;
	std::vector<std::vector<int>> m_structure;
};