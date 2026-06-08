#include "DataStream.h"

namespace DataStream
{
	void writeString(std::ostream& os, const std::string& str)
	{
		os << str.length() << " ";
		if (!str.empty())
		{
			os.write(str.c_str(), str.length());
		}
		os << "\n";
	}

	std::string readString(std::istream& is)
	{
		size_t len;
		is >> len;
		is.get();
		
		std::string str;
		if (len > 0)
		{
			str.resize(len);
			is.read(str.data(), len);
		}
		is.get();
		return str;
	}

	void writeInt(std::ostream& os, int val)
	{
		os << val << "\n";
	}

	int readInt(std::istream& is)
	{
		int val;
		is >> val;
		return val;
	}

	void writeSizeT(std::ostream& os, size_t val)
	{
		os << val << "\n";
	}

	size_t readSizeT(std::istream& is)
	{
		size_t val;
		is >> val;
		return val;
	}

	void writeDouble(std::ostream& os, double val)
	{
		os << val << "\n";
	}

	double readDouble(std::istream& is)
	{
		double val;
		is >> val;
		return val;
	}

	void writeBool(std::ostream& os, bool val)
	{
		os << (val ? 1 : 0) << "\n";
	}

	bool readBool(std::istream& is)
	{
		int val;
		is >> val;
		return val != 0;
	}
}

