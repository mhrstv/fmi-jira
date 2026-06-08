#include "StudentReportCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/NotFoundException.h"
#include "../../users/Student.h"
#include "../../models/project/Project.h"
#include "../../models/task/Task.h"

StudentReportCommand::StudentReportCommand() : Command("student-report", "Generate a report for a student") { }

void StudentReportCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.empty())
	{
		throw ValidationException("Usage: student-report <student_username>");
	}

	std::string studentName = args[0];
	User* currentUser = data.getCurrentUser();
	if (currentUser->getRole() != Role::Lecturer && currentUser->getRole() != Role::Administrator)
	{
		throw PermissionException("Only Lecturers or Admins can generate student reports.");
	}

	User* targetUser = nullptr;
	for (const auto& user : data.getUsers())
	{
		if (user->getUsername() == studentName)
		{
			targetUser = user.get();
			break;
		}
	}
	if (!targetUser)
	{
		throw NotFoundException("User '" + studentName + "' not found.");
	}

	Student* student = dynamic_cast<Student*>(targetUser);
	if (!student)
	{
		throw ValidationException("User '" + studentName + "' is not a student.");
	}
	data.os() << "Completed tasks: " << student->getCompletedTasks() << "\n";
	
	double totalGrade = 0.0;
	int gradedTasks = 0;
	for (const auto& project : data.getProjects()) {
		for (const auto& task : project->getTasks()) {
			if (task->getAssignee() == student && task->getGrade() > 0.0) {
				totalGrade += task->getGrade();
				gradedTasks++;
			}
		}
	}
	double avgGrade = gradedTasks > 0 ? totalGrade / gradedTasks : 0.0;
	
	data.os() << "Average grade: " << avgGrade << "\n";
	data.os() << "Performance score: " << student->getPerformanceScore() << "\n";
}
