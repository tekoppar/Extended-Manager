#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "ManagerDef.h"
#include "Adresses.h"
#include <chrono>

#include "SimpleJson.h"

static const std::string startOfJsonObject = "\"";
static const std::string endOfJsonObject = "\":";
static const std::string newJsonObject = ",";
static const std::string endOfJsonObjectArray = "]";
static const std::string endOfJsonObjectDictionary = "}";

void TemJsonObjectData::Set(std::string value)
{
	this->string = value;
	this->Type = JsonObjectValueType::String;
}

void TemJsonObjectData::Set(bool value)
{
	this->boolean = value;
	this->Type = JsonObjectValueType::Boolean;
}

void TemJsonObjectData::Set(float value)
{
	this->floatingpoint = value;
	this->Type = JsonObjectValueType::Float;
}

void TemJsonObjectData::Set(int value)
{
	this->integer = value;
	this->Type = JsonObjectValueType::Int;
}

void TemJsonObjectData::Set(TemJsonObject* value)
{
	this->jsonobject = value;
	this->Type = JsonObjectValueType::JsonObjectPointer;
}

std::string TemJsonObjectData::GetS()
{
	return this->string;
}

bool TemJsonObjectData::GetB()
{
	return this->boolean;
}

float TemJsonObjectData::GetF()
{
	return this->floatingpoint;
}

int TemJsonObjectData::GetI()
{
	return this->integer;
}

void TemJsonObjectValue::Set(std::vector<TemJsonObjectData> value)
{
	this->vector = value;
	this->Type = JsonObjectValueType::Array;
}

std::vector<TemJsonObjectData> TemJsonObjectValue::GetV()
{
	return this->vector;
}

void TemJsonObjectValue::Set(std::string value1, TemJsonObjectData value2)
{
	this->unorderedmap[value1] = value2;
	this->Type = JsonObjectValueType::Dictionary;
}

std::unordered_map<std::string, TemJsonObjectData> TemJsonObjectValue::GetD()
{
	return this->unorderedmap;
}

std::vector<TemJsonObject> SimpleJson::ParseJsonFromString(std::string json)
{
	auto jsonObjects = SimpleJson::ParseToJsonObjects(json);

	return jsonObjects;
}

std::vector<TemJsonObject> SimpleJson::ParseToJsonObjects(std::string json)
{
	std::vector<TemJsonObject> results;
	JsonObjectValueType objectType = JsonObjectValueType::String;
	results.reserve(64);
	std::size_t position = 0;
	std::size_t startOfJsonObjectName = 0;
	std::size_t endOfJsonObjectName = 0;
	std::size_t endOfJsonValue = 0;
	std::string temp = "";
	std::string jsonValue = "";

	while (position < json.size())
	{
		SimpleJson::GetJsonName(json, temp, position);
		if (position == std::string::npos)
			break;

		SimpleJson::GetJsonValue(json, jsonValue, position);
		objectType = SimpleJson::GetJsonObjectType(jsonValue);

		TemJsonObject jsonObject = TemJsonObject();
		jsonObject.value.data.ObjectName = temp;

		switch (objectType)
		{

		default:
		case JsonObjectValueType::String:
		{
			std::string tempVal = jsonValue.substr(1, jsonValue.size() - 2);
			jsonObject.value.data.Set(tempVal);
		}
		break;

		case JsonObjectValueType::Boolean:
		{
			bool value = jsonValue == "true" ? true : false;
			jsonObject.value.data.Set(value);
		}
		break;

		case JsonObjectValueType::Float:
		{
			float value = std::stof(jsonValue);
			jsonObject.value.data.Set(value);
		}
		break;

		case JsonObjectValueType::Int:
		{
			int value = std::stoi(jsonValue);
			jsonObject.value.data.Set(value);
		}
		break;

		case JsonObjectValueType::Array:
		{
			std::string dictionary = "";
			if (jsonValue[0] == '[')
				dictionary = jsonValue.substr(1, jsonValue.size() - (jsonValue[jsonValue.size() - 1] == ']' ? 2 : 1));
			else
				dictionary = jsonValue;

			JsonObjectValueType valuesType = SimpleJson::GetJsonObjectType(dictionary);
			std::vector<TemJsonObjectData> dataValues;
			switch (valuesType)
			{
			case JsonObjectValueType::Dictionary:
			{
				auto splitValues = SplitValues('{', '}', dictionary);// sutil::SplitTemNeighbours(dictionary, "},{");
				TemJsonObjectData data;

				std::vector< TemJsonObject*> jsonobjects;
				for (auto& splitV : splitValues)
				{
					TemJsonObject* jsonDictionary = new TemJsonObject();
					std::vector<TemJsonObject> values = SimpleJson::ParseToJsonObjects(splitV);
					for (auto& value : values)
					{
						jsonDictionary->value.Set(value.value.data.ObjectName, value.value.data);
					}

					data.ObjectName = std::to_string(dataValues.size());
					data.Set(jsonDictionary);
					dataValues.push_back(data);
				}
				//data.Set(values[0], value.value.data);
			}
			break;

			default:
			{
				std::vector<std::string> values = sutil::SplitTem(dictionary, ",");
				for (auto& value : values)
				{
					TemJsonObjectData data;

					switch (valuesType)
					{
					case JsonObjectValueType::Boolean:
					{
						data.Set(value == "true" ? true : false);
					}
					break;

					case JsonObjectValueType::Float:
					{
						data.Set(std::stof(value));
					}
					break;

					case JsonObjectValueType::Int:
					{
						data.Set(std::stoi(value));
					}
					break;

					case JsonObjectValueType::String:
					{
						data.Set(value);
					}
					break;
					}

					data.ObjectName = std::to_string(dataValues.size());
					dataValues.push_back(data);
				}
			}
			break;
			}
			jsonObject.value.Set(dataValues);
		}
		break;

		case JsonObjectValueType::Dictionary:
		{
			std::string dictionary = jsonValue;

			std::vector<TemJsonObject> values = SimpleJson::ParseToJsonObjects(dictionary);

			for (auto& value : values)
			{
				jsonObject.value.Set(value.value.data.ObjectName, value.value.data);
			}
		}
		break;
		}

		results.push_back(jsonObject);
	}

	return results;
}

void SimpleJson::GetJsonName(std::string& json, std::string& value, std::size_t& index)
{
	std::size_t startIndex = json.find(startOfJsonObject, index);

	if (startIndex != std::string::npos)
	{
		std::size_t endIndex = json.find(endOfJsonObject, startIndex + 1);
		index = endIndex + 1;

		if (json[startIndex] == '"')
			startIndex++;

		if (json[endIndex] == ':')
			endIndex--;

		if (json[endIndex] == '"')
			endIndex--;

		value = json.substr(startIndex, endIndex - (startIndex - 1));
	}
	else
	{
		index = startIndex;
	}
}

void SimpleJson::GetJsonValue(std::string& json, std::string& value, std::size_t& index)
{
	std::size_t foundMoreObjectIndex = 0;
	std::size_t foundStartObjects = 0;
	std::size_t foundEndObjects = 0;
	if (json[index] == ':')
		index++;

	std::size_t endIndex = std::string::npos;
	if (json[index] == '{')
	{
		foundStartObjects++;

		std::size_t loopIndex = 1;
		while (foundStartObjects != foundEndObjects)
		{
			char charFound = json[index + loopIndex];

			if (charFound == '{')
			{
				foundStartObjects++;
				foundMoreObjectIndex = index + loopIndex;
			}
			else if (charFound == '}')
			{
				foundEndObjects++;
				endIndex = index + loopIndex;
			}

			loopIndex++;

			if (index + loopIndex >= json.size())
			{
				index = endIndex;
				return;
			}

			if (foundStartObjects == foundEndObjects && (endIndex > foundMoreObjectIndex || foundMoreObjectIndex == -1))
				goto EndLoop1;
		}

	EndLoop1:
		if (endIndex != std::string::npos && json[endIndex] == '}')
			endIndex++;
	}
	else if (json[index] == '[')
	{
		foundStartObjects++;

		std::size_t loopIndex = 1;
		while (foundStartObjects != foundEndObjects)
		{
			char charFound = json[index + loopIndex];

			if (charFound == '[')
			{
				foundStartObjects++;
				foundMoreObjectIndex = index + loopIndex;
			}
			else if (charFound == ']')
			{
				foundEndObjects++;
				endIndex = index + loopIndex;
			}

			loopIndex++;

			if (index + loopIndex >= json.size())
			{
				index = endIndex;
				return;
			}

			if (foundStartObjects == foundEndObjects && (endIndex > foundMoreObjectIndex || foundMoreObjectIndex == -1))
				goto EndLoop2;
		}

	EndLoop2:
		if (endIndex != std::string::npos && json[endIndex] == ']')
			endIndex++;
	}
	else
	{
		endIndex = json.find(newJsonObject, index);

		if (endIndex == std::string::npos)
			endIndex = json.find(endOfJsonObjectArray, index);

		if (endIndex == std::string::npos)
			endIndex = json.find(endOfJsonObjectDictionary, index);
	}

	//if (json[endIndex - 1] == '"')
		//endIndex--;

	//if (json[index] == '"')
		//index++;

	if (endIndex != std::string::npos)
		value = json.substr(index, endIndex - index);

	index = endIndex;
}

std::vector<std::string> SimpleJson::SplitValues(char start, char end, std::string& values)
{
	std::size_t startIndex = 0;
	std::size_t endIndex = 0;
	std::size_t foundMoreObjectIndex = 0;
	std::size_t foundStartObjects = 0;
	std::size_t foundEndObjects = 0;
	std::vector<std::string> foundValues;

	if (values[startIndex] == start)
	{
	Restart:
		foundStartObjects++;

		std::size_t loopIndex = 1;
		while (foundStartObjects != foundEndObjects)
		{
			char charFound = values[startIndex + loopIndex];

			if (charFound == start)
			{
				foundStartObjects++;
				foundMoreObjectIndex = startIndex + loopIndex;
			}
			else if (charFound == end)
			{
				foundEndObjects++;
				endIndex = startIndex + loopIndex;
			}

			loopIndex++;

			if (startIndex + loopIndex >= values.size())
			{
				if (foundStartObjects == foundEndObjects && endIndex != std::string::npos)
				{
					endIndex = (values[endIndex + 1] == end ? endIndex + 1 : endIndex);
					startIndex = values[startIndex - 1] == start ? startIndex - 1 : startIndex;
					foundValues.push_back(values.substr(startIndex, endIndex - (startIndex - 1)));
				}
				return foundValues;
			}

			if (foundStartObjects == foundEndObjects && (endIndex > foundMoreObjectIndex || foundMoreObjectIndex == -1))
				goto EndLoop;
		}

	EndLoop:
		if (endIndex != std::string::npos && values[endIndex] == end)
			endIndex++;

		if (endIndex != std::string::npos)
			foundValues.push_back(values.substr(startIndex, endIndex - startIndex));
	}
	if (endIndex < values.size() && values[endIndex + 1] == start)
	{
		foundStartObjects = 0;
		foundEndObjects = 0;
		foundMoreObjectIndex = 0;
		startIndex = endIndex + 2;
		goto Restart;
	}

	return foundValues;
}

JsonObjectValueType SimpleJson::GetJsonObjectType(std::string& value)
{
	if (value[0] == '"')
	{
		return JsonObjectValueType::String;
	}
	else if (value[0] == '[')
	{
		return JsonObjectValueType::Array;
	}
	else if (value[0] == '{')
	{
		return JsonObjectValueType::Dictionary;
	}
	else if (value[0] == 'f' && value[1] == 'a' || value[0] == 't' && value[1] == 'r')
	{
		return JsonObjectValueType::Boolean;
	}
	else if (SimpleJson::IsIntegerOrFloat(value) == JsonObjectValueType::Float)
	{
		return JsonObjectValueType::Float;
	}
	else if (SimpleJson::IsIntegerOrFloat(value) == JsonObjectValueType::Int)
	{
		return JsonObjectValueType::Int;
	}

	return JsonObjectValueType::String;
}

JsonObjectValueType SimpleJson::IsIntegerOrFloat(std::string& s)
{
	if ((isdigit(s[0]) || s[0] == '-' && isdigit(s[1])) && isdigit(s[s.size() - 1]))
	{
		if (s.find(',') != std::string::npos || s.find('.') != std::string::npos)
			return JsonObjectValueType::Float;

		return JsonObjectValueType::Int;
	}

	return JsonObjectValueType::String;
}

bool SimpleJson::IsDigit(char& s)
{
	return s == '0' || s == '1' || s == '2' || s == '3' || s == '4' || s == '5' || s == '6' || s == '7' || s == '8' || s == '9';
}