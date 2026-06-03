#include "Comment.h"
#include "../../users/User.h"
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

std::ostream& operator<<(std::ostream& os, const Comment& comment)
{
	os << "[" << comment.creationDate.toString() << "] "
		<< comment.author->getUsername() << ": "
		<< comment.content;
	return os;
}