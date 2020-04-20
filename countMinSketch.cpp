#include "countMinSketch.h"
#include "countMinSketch.h"
#include <map>
#include <algorithm>

MyCountMinSketch::MyCountMinSketch(int w, int d):
	m_depth(d),
	m_width(w)
{
	m_structure.resize(d);
	for (int i = 0; i < d; i++)
		m_structure[i].resize(w, 0);
}

void MyCountMinSketch::add(std::string& value)
{
	for (int i = 0; i < m_depth; i++)
		m_structure[i][myHash(value, i)]++;
}

int MyCountMinSketch::check(std::string value)
{
	int min = INT_MAX;
	for (int i = 0; i < m_depth; i++)
	{
		auto counter = m_structure[i][myHash(value, i)];
		if (counter < min)
			min = counter;
	}
	return min;
}

size_t MyCountMinSketch::myHash(std::string& value, int i)
{
	std::hash<std::string> hash;
	return (hash(value) * (i + 1) * m_width) % m_width;
}