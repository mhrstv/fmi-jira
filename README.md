# FMI JIRA

A CLI application for managing university projects, tasks, and teams - Jira but adapted for an academic environment.

## About

**FMI JIRA** is a console application for project management, developed as a course project for *Object-Oriented Programming (Practicum)* at the Faculty of Mathematics and Informatics, Sofia University (2025-2026).

## How to build and run

To build the project using CMake, open your terminal in the project folder and run:

1. Generate the build files:
   ```bash
   cmake -B build
   ```
2. Compile the application:
   ```bash
   cmake --build build
   ```
3. Run the executable:
   ```bash
   ./build/fmi-jira.exe
   ```

## Features

- Distinct capabilities for Students, Teaching Assistants, Lecturers, and Administrators.
- Create projects, manage team members, and track project status.
- Create tasks with specific types (Bug, Feature, Documentation) and priorities. Assign tasks to members, leave comments, and add tags.
- Organize tasks into project stages. Technical Assistants and Lecturers can start, finish, and generate reports on specific stages.
- Generate comprehensive performance reports for students based on their completed and in-progress tasks.


## Data storage

When you run the application, it automatically creates a `data/` folder in the same place where the executable was run. 

Inside the `data/` folder, it saves three text files:
- `users.txt`
- `projects.txt`
- `tasks.txt`

Your data is being loaded automatically from the latest save, however, the data does NOT auto-save. To save, you must be logged in as an admin and type "save" before closing the application.

### Data formatting
The data inside these `.txt` files is saved as raw text.
For example, a string like `"user1"` is saved as:
`5 user1` (where 5 is the length of the string).

An example of an object entry inside users.txt looks like this:
```text
1            <- Total number of users saved
1002         <- Generated ID for the user
5 user1      <- Username: Length 5, value "user1"
5 user1      <- Password: Length 5, value "user1"
0            <- Role enum (0 = Student)
0            <- Student's completed tasks
0            <- Student's in-progress tasks
0            <- Student's performance score
0            <- Number of tags
```
