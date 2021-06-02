#pragma once
#include <document.h>

class JsonReader
{
public:
	JsonReader() = default;

	rapidjson::Document* ReadJson(const std::string& filePath);

private:
	rapidjson::Document m_JsonDocument;
};

