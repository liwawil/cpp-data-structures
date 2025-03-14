# cpp-data-structures

Welcome to the `cpp-data-structures` repository! This C++ collection blends educational value with practical, product-focused applications, featuring projects that demonstrate array and linked list concepts. As an aspiring entrepreneur in game development, I’ve designed these projects to build my skills and create tools with real-world utility.

## Projects

### Arrays

#### 1. Enhanced Personal Budget Manager (Intermediate)
- **File**: `budget-manager.cpp`
- **Description**: An upgraded budgeting tool supporting multiple users, budget limits with alerts, and persistent data storage. It offers a menu-driven interface for managing expenses across different users.
- **Purpose**: Provides a robust financial management system with multi-user capabilities.
- **Data Structure Used and Why**: 
  - **Structs with Vectors (Dynamic Arrays)**: Vectors simplify dynamic memory management over raw arrays, offering flexibility for multiple users and their expenses. Contiguous storage ensures efficient access, suitable for frequent updates and retrievals.
- **Learning Objectives**:
  - Structs with arrays (via vector).
  - Simplified dynamic memory management.
  - Multi-user data management.
  - Advanced file I/O.
  - Practical feature design (e.g., budget alerts).
- **Market Appeal**: Ideal for intermediate learners or small households/businesses seeking a comprehensive budget solution.

#### 2. Dynamic Inventory Management System (Advanced)
- **File**: `inventory-manager.cpp`
- **Description**: A sophisticated system for managing inventory across multiple warehouses, featuring product tracking, analytics (total value, low stock), and fast search/sort capabilities.
- **Purpose**: Offers a scalable inventory solution for business applications.
- **Data Structure Used and Why**: 
  - **Multi-dimensional Raw Arrays and Pointers**: Raw arrays provide fine-grained control over memory, critical for managing large, multi-warehouse datasets. Multi-dimensional arrays organize products by warehouse efficiently, and pointers enable dynamic resizing without vector overhead, optimizing performance for analytics.
- **Learning Objectives**:
  - Multi-dimensional arrays.
  - Manual dynamic resizing.
  - Array of pointers.
  - Quicksort and binary search algorithms.
  - Complex data persistence.
- **Market Appeal**: Valuable for advanced developers or small businesses/warehouses needing efficient inventory management.

### Linked Lists

#### 1. Task Manager (Beginner)
- **File**: `task-manager.cpp`
- **Description**: A simple console-based tool for managing tasks, like a to-do list. Users can add tasks, mark them as completed, view the list, and save/load to `tasks.txt`.
- **Purpose**: Demonstrates basic linked list operations in a practical productivity tool.
- **Data Structure Used and Why**: 
  - **Singly Linked List**: Chosen for its simplicity and dynamic growth, allowing tasks to be added or removed without resizing constraints. Sequential access fits the linear nature of a to-do list, avoiding array shifting overhead.
- **Learning Objectives**:
  - Basic singly linked list operations (insertion, deletion, traversal).
  - Memory management with `new` and `delete`.
  - File I/O for data persistence.
  - User interface design with a menu-driven approach.
- **Market Appeal**: Useful for personal productivity or small teams needing a lightweight task organizer.

#### 2. Game Event Scheduler (Intermediate)
- **File**: `game-event-scheduler.cpp`
- **Description**: A tool for game developers to manage time-based events (e.g., "Spawn enemy at 10s") using a sorted singly linked list. Features include adding/removing events, listing events up to a time, advancing game time, and saving/loading to `events.txt`.
- **Purpose**: Provides a reusable component for game prototyping, simulating event sequences.
- **Data Structure Used and Why**: 
  - **Sorted Singly Linked List**: Ideal for maintaining chronological order of events with efficient insertion (O(n) to find position, O(1) to insert). Dynamic size accommodates unpredictable event counts, and sequential traversal aligns with game timeline simulation.
- **Learning Objectives**:
  - Managing a sorted linked list by time stamp.
  - Dynamic insertion and deletion with sorting.
  - Simulation of time progression for game loops.
  - File I/O for game data persistence.
  - Product design for game development workflows.
- **Market Appeal**: Practical for indie game developers needing event scheduling in prototypes or full games.

#### 3. Behavioral State Machine for Game Characters (Advanced)
- **File**: `behavioral-state-machine.cpp`
- **Description**: A system for managing character behaviors (e.g., "Idle", "Attack") using a doubly linked list for states and nested singly linked lists for transitions. Users can add states, define transitions, simulate behavior, track history, and save/load to `states.txt`.
- **Purpose**: Offers a reusable AI framework for game characters, simulating dynamic behaviors.
- **Data Structure Used and Why**: 
  - **Doubly Linked List for States**: Enables bidirectional navigation, useful for state history or debugging, with O(1) insertion/deletion at known positions. 
  - **Nested Singly Linked Lists for Transitions**: Each state’s transitions are dynamic and variable-length, perfectly suited for singly linked lists, avoiding array resizing and simplifying memory management within states.
- **Learning Objectives**:
  - Doubly linked list operations for state navigation.
  - Nested singly linked lists for transition management.
  - State history tracking with a linked list.
  - File I/O for complex data structures.
  - Game logic simulation with condition-based transitions.
- **Market Appeal**: Valuable for indie studios or educators needing a demo-ready AI tool for games.

## Getting Started
To run any project:
1. Clone this repository: `git clone <repo-url>`
2. Navigate to the project folder: `cd cpp-data-structures/arrays`
3. Compile with a C++ compiler: `g++ <filename>.cpp -o <filename>`
4. Run the executable: `./<filename>`

Each project includes a console-based interface with menu options for interaction.

## Learning Journey
These projects reflect my progression in mastering data structures for game development and beyond:
- **Arrays**: 
  - Beginner: Focused on foundational array skills with the Personal Budget Tracker.
  - Intermediate: Advanced to multi-user systems and dynamic arrays with the Enhanced Personal Budget Tracker.
  - Advanced: Explored complex array techniques and algorithms with the Dynamic Inventory Management System.
- **Linked Lists**: 
  - Beginner: Mastered basic linked list operations with the Task Manager.
  - Intermediate: Progressed to sorted linked lists and game logic with the Game Event Scheduler.
  - Advanced: Tackled doubly linked lists, nested structures, and AI simulation with the Behavioral State Machine.

This dual approach ensures both practical utility and deep learning, preparing me for entrepreneurial ventures in game development and other domains.

## Future Plans
- Enhance array projects with features like graphical UI or database integration.
- Expand linked list projects with game engine compatibility (e.g., Unity export) or additional AI features.
- Build a small game prototype combining these components.
- Share with the community for feedback and collaboration.

## Contact
Feel free to reach out or contribute! Check my progress or suggest ideas as I continue this journey.