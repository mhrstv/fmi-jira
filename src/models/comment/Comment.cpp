#include "Comment.h"
#include "../../users/User.h"
#include "../../app/AppData.h"
#include "../../utils/DataStream.h"
#include "../../exceptions/ValidationException.h"

Comment::Comment(const User* author, const std::string& content, const Date& date) : author(author), content(content), creationDate(date)
{
	if (!author)
	{
		throw ValidationException("Comment author cannot be null.");
	}
	if (content.empty())
	{
		throw ValidationException("Comment content cannot be empty.");
	}
}

const User* Comment::getAuthor() const
{
	return author;
}

const std::string& Comment::getContent() const
{
	return content;
}

const Date& Comment::getCreationDate() const
{
	return creationDate;
}

void Comment::save(std::ostream& os) const
{
	DataStream::writeString(os, author ? author->getUsername() : "");
	DataStream::writeString(os, content);
	DataStream::writeString(os, creationDate.toString());
}

Comment Comment::load(std::istream& is, const AppData& context)
{
	std::string authorName = DataStream::readString(is);
	std::string content = DataStream::readString(is);
	Date date = Date::parse(DataStream::readString(is));
	
	const User* author = context.findUser(authorName);
	return Comment(author, content, date);
}

std::ostream& operator<<(std::ostream& os, const Comment& comment)
{
	os << "[" << comment.creationDate.toString() << "] "
		<< comment.author->getUsername() << ": "
		<< comment.content;
	return os;
}