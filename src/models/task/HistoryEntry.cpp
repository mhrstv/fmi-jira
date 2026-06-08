#include "HistoryEntry.h"
#include "../../users/User.h"
#include "../../app/AppData.h"
#include "../../utils/DataStream.h"

HistoryEntry::HistoryEntry(const User* changedBy, const std::string& field, const std::string& oldValue, const std::string& newValue, const Date& timestamp)
	: changedBy(changedBy), field(field), oldValue(oldValue), newValue(newValue), timestamp(timestamp) { }

const User* HistoryEntry::getChangedBy() const
{
	return changedBy;
}

const std::string& HistoryEntry::getField() const
{
	return field;
}

const std::string& HistoryEntry::getOldValue() const
{
	return oldValue;
}

const std::string& HistoryEntry::getNewValue() const
{
	return newValue;
}

const Date& HistoryEntry::getTimestamp() const
{
	return timestamp;
}

void HistoryEntry::save(std::ostream& os) const
{
	DataStream::writeString(os, changedBy ? changedBy->getUsername() : "System");
	DataStream::writeString(os, field);
	DataStream::writeString(os, oldValue);
	DataStream::writeString(os, newValue);
	DataStream::writeString(os, timestamp.toString());
}

HistoryEntry HistoryEntry::load(std::istream& is, const AppData& context)
{
	std::string changedByName = DataStream::readString(is);
	std::string field = DataStream::readString(is);
	std::string oldVal = DataStream::readString(is);
	std::string newVal = DataStream::readString(is);
	Date date = Date::parse(DataStream::readString(is));
	
	const User* changedBy = nullptr;
	if (changedByName != "System")
	{
		changedBy = context.findUser(changedByName);
	}
	return HistoryEntry(changedBy, field, oldVal, newVal, date);
}

std::ostream& operator<<(std::ostream& os, const HistoryEntry& entry)
{
	os << "[" << entry.timestamp.toString() << "] ";
	if (entry.changedBy)
	{
		os << entry.changedBy->getUsername() << " ";
	}
	os << "changed " << entry.field;
	if (!entry.oldValue.empty() && !entry.newValue.empty())
	{
		os << " from '" << entry.oldValue << "' to '" << entry.newValue << "'";
	}
	else if (!entry.newValue.empty())
	{
		os << " to '" << entry.newValue << "'";
	}
	return os;
}