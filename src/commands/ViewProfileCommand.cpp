#include "ViewProfileCommand.h"
#include "../app/AppData.h"

ViewProfileCommand::ViewProfileCommand() : Command("view-profile", "View your profile information") { }

void ViewProfileCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	data.getCurrentUser()->displayInfo(data.out());
}
