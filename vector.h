#pragma once
#include <iostream>
#include <vector>
#include <memory>

namespace Vector
{
	//Returns vector with first item of a given value erased
	template<typename tItemType>
	std::vector<tItemType> EraseItemValue(std::vector<tItemType>& in_vector, tItemType& in_value)
	{
		int index;
		for (int i = 0; i < in_vector.size(); i++)
		{
			if (in_vector[i] = in_value)
			{
				index = i;
				break;
			}
		}

		return in_vector.erase(in_vector.begin() + index);
	}

	//Returns index of first item with given value
	template<typename tItemType>
	int GetItemIndex(std::vector<tItemType>& in_vector, tItemType& in_value)
	{
		for (int i = 0; i < in_vector.size(); i++)
		{
			if (in_vector[i] = in_value)
			{
				return i;
			}
		}
	}
}
