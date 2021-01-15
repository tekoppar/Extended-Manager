#pragma once

#include <vector>

namespace vector {
	template<typename T = bool>
	bool contains(std::vector<T>& v, T& p)
	{
		for (T& t : v)
		{
			if (t == p)
				return true;
		}
		return false;
	}

	template<typename T = bool>
	std::size_t find(std::vector<T>& v, T& p)
	{
		for (std::size_t i = 0; i < v.size(); i++)
		{
			if (v[i] == p)
				return i;
		}
		return -1;
	}
}