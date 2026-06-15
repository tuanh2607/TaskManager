# TaskManager

An application that integrates data structures and algorithms to help you manage tasks efficiently.

## Features

- ✅ **Add, edit, delete tasks** - Manage your daily tasks
- ✅ **Priority levels** - 3 priority levels (1-3)
- ✅ **Deadline tracking** - Set deadlines with date/time validation
- ✅ **Overdue detection** - Automatic categorization of overdue/upcoming tasks
- ✅ **Search functionality** - Find tasks by title or deadline
- ✅ **Task history** - Track completed tasks
- ✅ **Pagination** - Browse tasks efficiently

## Data Structures Used

- **AVL Tree** - For efficient task storage and search
- **Hash Table** - For quick lookups
- **Priority Queue** - For task scheduling
- **Stack** - For undo your actions
- **Queue** - For deadline management 

## Requirements

- C++11 or higher
- GCC/G++ compiler
- Linux, macOS, or Windows

## Installation

### 1. Clone the repository
```bash
git clone https://github.com/tuanh2607/TaskManager.git
cd TaskManager
```

### 2. Compile the program

**Option A: Using g++ directly**
```bash
# Linux/macOS
g++ app/main.cpp -o TaskManager

# Windows (PowerShell)
g++ app\main.cpp -o TaskManager.exe
```

**Option B: Using Makefile**
```bash
make run
```

### 3. Run the application

**Linux/macOS:**
```bash
./TaskManager data.txt
```

**Windows:**
```bash
TaskManager.exe data.txt
```

## Menu Options

**1. Add new task**
   - Enter priority level (1-3, where 1 = high, 3 = low)
   - Enter task title (1-25 characters)
   - Enter deadline in format: `HH-MM-DD-MM-YYYY`
   - Confirm to add the task

**2. View next task**
   - Displays the most urgent task to complete

**3. Complete task**
   - Search by deadline or task title
   - Mark task as DONE

**4. Delete task**
   - Remove a task from the system
   - Search by deadline or title

**5. Search task**
   - Find task by deadline or task title

**6. Undo your operations**
   - Undo operations step-by-step

**7. View all tasks**
   - Browse all tasks by pages (20 tasks per page)

**8. Adjust task**
   - Change old task

**9. Show overdue or upcoming task**
   - View the most 20 overdue tasks or the most 20 upcoming tasks
   
**0. Exit program**


## Folder Structure

```
TaskManager/
├── app/
│   ├── main.cpp            
│   └── data.txt          
├── lib/
│   ├── AVL.hpp              
│   ├── BST.hpp               
│   ├── HashTable.hpp         
│   ├── LinkedList.hpp       
│   ├── PriorityQueue.hpp    
│   ├── Queue.hpp             
│   └── Algorithms.hpp       
├── src/
│   ├── TaskManager.hpp     
│   ├── UI.hpp              
│   ├── Task.hpp              
│   ├── Scheduler.hpp       
│   ├── Search.hpp          
│   ├── History.hpp           
│   ├── FileManager.hpp     
│   ├── DeadlineQueue.hpp    
│   └── functions.hpp       
├── Makefile                  
├── README.md               
└── demo.txt                  
```
