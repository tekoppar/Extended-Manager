#pragma once

enum class JsonObjectValueType {
	String = 0,
	Boolean = 1,
	Int = 2,
	Float = 3,
	Array = 4,
	Dictionary = 5,
	JsonObjectPointer = 6
};

enum class JsonObjectType {
	JsonObject = 0,
	Array = 1,
	Dictionary = 2
};

class TemJsonObjectValue;
class TemJsonObject;

class TemJsonObjectData {
public:
	JsonObjectValueType Type = JsonObjectValueType::String;
	std::string ObjectName = "";
	std::string string = "";
	bool boolean = false;
	float floatingpoint = 0.0f;
	int integer = 0;
	TemJsonObject* jsonobject = nullptr;

	void Set(std::string value);
	void Set(bool value);
	void Set(float value);
	void Set(int value);
	void Set(TemJsonObject* value);
	std::string GetS();
	bool GetB();
	float GetF();
	int GetI();
};

class TemJsonObjectValue {
public:
	JsonObjectValueType Type = JsonObjectValueType::String;
	TemJsonObjectData data;
	std::vector<TemJsonObjectData> vector;
	std::unordered_map<std::string, TemJsonObjectData> unorderedmap;

	void Set(std::vector<TemJsonObjectData> value);
	void Set(std::string value1, TemJsonObjectData value2);
	std::vector<TemJsonObjectData> GetV();
	std::unordered_map<std::string, TemJsonObjectData> GetD();
};

class TemJsonObject {
public:
	JsonObjectType Type = JsonObjectType::JsonObject;
	TemJsonObjectValue value;
};

class SimpleJson
{
public:
	static std::vector<TemJsonObject> ParseJsonFromString(std::string);
private:
	static std::vector<TemJsonObject> ParseToJsonObjects(std::string json);
	static void GetJsonValue(std::string& json, std::string& value, int& index);
	static void GetJsonName(std::string& json, std::string& value, int& index);
	static JsonObjectValueType GetJsonObjectType(std::string& value);
	static JsonObjectValueType IsIntegerOrFloat(std::string& s);
	static std::vector<std::string> SplitValues(char start, char end, std::string& values);
	static bool IsDigit(char& s);
};

