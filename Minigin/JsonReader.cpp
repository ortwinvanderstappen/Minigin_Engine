#include "MiniginPCH.h"
#include "JsonReader.h"

#include <filereadstream.h>
#include <rapidjson.h>

rapidjson::Document* JsonReader::ReadJson(const std::string& filePath)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, filePath.c_str(), "r");

	if (pFile != nullptr)
	{
		// Get file size
		fseek(pFile, 0, SEEK_END);
		size_t const fileSize = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		// Read from file
		char* readBuffer = new char[fileSize];
		rapidjson::FileReadStream inputStream(pFile, readBuffer, sizeof(readBuffer));
		// Parse the input stream
		m_JsonDocument.ParseStream(inputStream);
		// Cleanup buffer
		delete[] readBuffer;
		// Close the file
		fclose(pFile);

		return &m_JsonDocument;
	}

	// Failed to read file
	std::cerr << "JsonReader: file with path " << filePath << " not found.\n";
	return nullptr;
}
