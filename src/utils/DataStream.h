#pragma once
#include <string>
#include <iostream>

namespace DataStream
{
	// Saves a string
	void writeString(std::ostream& os, const std::string& str);
	
	// Loads a string
	std::string readString(std::istream& is);

	void writeInt(std::ostream& os, int val);
	int readInt(std::istream& is);

	void writeSizeT(std::ostream& os, size_t val);
	size_t readSizeT(std::istream& is);

	void writeDouble(std::ostream& os, double val);
	double readDouble(std::istream& is);

	void writeBool(std::ostream& os, bool val);
	bool readBool(std::istream& is);
}

