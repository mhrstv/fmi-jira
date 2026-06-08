#include "HelpCommand.h"
#include "../../app/AppData.h"
#include "../../app/CommandDispatcher.h"
#include "../../users/User.h"
#include "../../enums/Role.h"

HelpCommand::HelpCommand() : Command("help", "Show available commands") { }

void HelpCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	data.os() << "FMI JIRA - Available commands:\n"
				<< "  help                         - Show this help message\n"
				<< "  close                        - Exit the application\n";

	User* u = data.getCurrentUser();
	if (!u)
	{
		data.os() << "  login <username> <password>  - Login to the system\n";
	}
	else
	{
		data.os() << "  logout                       - Logout from the system\n"
					<< "  view-profile                 - View your profile\n";

		Role r = u->getRole();
		if (r == Role::Administrator)
		{
			data.os() << "  register <user> <pass> <role> - Register a new user\n"
						<< "  create-project <name> <desc>  - Create a new project\n"
						<< "  add-user <proj> <user>        - Add user to project\n"
						<< "  archive-project <proj>        - Archive a project\n"
						<< "  save                          - Save system state\n"
						<< "  load                          - Load system state\n";
		}
		if (r == Role::Student || r == Role::TeachingAssistant || r == Role::Lecturer || r == Role::Administrator)
		{
			data.os() << "  list-projects                 - List projects you belong to\n"
						<< "  join-project <proj>           - Join an open project\n"
						<< "  create-task <proj> <t> <p> <n> <d> - Create a task\n"
						<< "  list-tasks <proj>             - List tasks in a project\n"
						<< "  my-tasks                      - List your assigned tasks\n"
						<< "  assign-task <task>            - Assign a task to yourself\n"
						<< "  change-status <task> <s>      - Change task status\n"
						<< "  add-comment <task> <content>  - Add comment to a task\n"
						<< "  add-tag <task> <tag>          - Add tag to a task\n"
						<< "  upcoming-tasks                - List your upcoming tasks\n"
						<< "  search-tasks <keyword>        - Search tasks\n"
						<< "  filter-tasks <status>         - Filter tasks by status\n";
		}
		if (r == Role::TeachingAssistant || r == Role::Lecturer || r == Role::Administrator)
		{
			data.os() << "  start-stage <proj> <stage>    - Start a project stage\n"
						<< "  finish-stage <proj> <stage>   - Finish a project stage\n"
						<< "  move-task <task> <stage>      - Move task to a stage\n"
						<< "  approve-task <task>           - Approve an implemented task\n"
						<< "  review-task <task>            - Request changes for a task\n"
						<< "  stage-report <proj> <stage>   - Generate a stage report\n";
		}
		if (r == Role::Lecturer || r == Role::Administrator)
		{
			data.os() << "  list-all-projects             - List all projects in system\n"
						<< "  list-all-tasks <proj>         - List all tasks (including backlog)\n"
						<< "  grade-task <task> <grade>     - Grade a completed task\n"
						<< "  finalize-project <proj>       - Finalize a project\n"
						<< "  student-report <user>         - Generate student report\n";
		}
	}
}

bool HelpCommand::requiresLogin() const
{
	return false;
}
