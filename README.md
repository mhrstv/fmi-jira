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

An example of an object entry inside **users.txt** looks like this:
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

An example of an entry inside **projects.txt** looks like this:
```text
1            <- Total number of projects saved
11 OOP_Project <- Project Name: Length 11, "OOP_Project"
0            <- Project Description length (0 = empty)
1            <- Project Status Enum (1 = Active)
3            <- Total number of members
4 Ivan       <- Member 1: Length 4, "Ivan"
5 Maria      <- Member 2: Length 5, "Maria"
8 DrPetrov   <- Member 3: Length 8, "DrPetrov"
1            <- Total number of stages
6 Stage1     <- Stage Name: Length 6, "Stage1"
10 01/01/2026 <- Stage Start Date
10 01/01/2026 <- Stage End Date
1            <- Number of tasks in this stage
101          <- ID of task in this stage
```

An example of an entry inside **tasks.txt** looks like this:
```text
1            <- Total number of tasks saved across all projects
11 OOP_Project <- Project this task belongs to
101          <- Task ID (FMI-101)
12 Random title        <- Title: length 12, "Random title"
24 Random description  <- Description: length 24, "Random description"
1            <- Task Type Enum (1 = Feature)
2            <- Task Priority Enum (2 = High)
3            <- Task Status Enum (3 = Done)
4 Ivan       <- Assignee Username
10 01/01/2026 <- Deadline
0            <- Points
6            <- Grade
1            <- Approved boolean (true)
1            <- Number of comments
4 Ivan       <- Comment Author
3 Random comment        <- Comment content
10 01/01/2026 <- Comment date
1            <- Number of tags
7 backend    <- Tag "backend"
9            <- Number of change history entries
```
