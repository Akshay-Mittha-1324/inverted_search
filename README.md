# Inverted Search Engine

![C](https://img.shields.io/badge/Language-C-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Architecture](https://img.shields.io/badge/Architecture-2D%20Linked%20List-orange.svg)

An industry-standard, highly efficient **Inverted Search Engine** written in C. This project is designed to index multiple text files, normalize the data, and store word occurrences in a custom **2D Linked List (Hash Table)** for `O(1)` average case search performance. It features a robust state machine, custom file serialization, and defensive programming techniques heavily utilized in Embedded Systems and systems programming.

## 🚀 Features
- **High-Performance Lookups:** Utilizes a custom 27-bucket Hash Table mapping English characters, numbers, and symbols to instantly locate data.
- **2D Linked List Architecture:** Implements a collision-resistant `main_node` (words) and `sub_node` (file frequency) tracking system.
- **Custom Serialization (Backup/Restore):** Saves the dynamic in-memory database to a custom-delimited text file, allowing instant state restoration without re-parsing files.
- **Data Normalization:** Converts strings to lowercase and dynamically hashes standalone special characters.
- **Defensive C Programming:** 
  - Prevents stack smashing and memory leaks via rigorous `malloc` and `free` management.
  - Guards against invalid file extensions, empty files, and duplicate file inputs.
  - Strict State Machine logic preventing DB corruption (e.g., stopping consecutive updates).
- **Interactive UI:** Professional CLI utilizing ANSI color codes and dynamically padded ASCII grids.

## 📂 Project Structure

```text
Inverted_Search/
├── include/
│   └── inverted_search.h   # Core data structures, macros, and function prototypes
├── src/
│   ├── validation.c        # File I/O validation and CLA parsing
│   ├── create_db.c         # Data normalization and Hash Table population
│   ├── main.c              # State machine and menu traffic control
│   ├── display_db.c        # ASCII grid rendering for the database
│   ├── search_db.c         # O(N) collision-traversal search logic
│   ├── save_db.c           # Memory-to-disk serialization
│   └── update_db.c         # Disk-to-memory deserialization and state updating
└── README.md
```

## 🛠️ Quick Start

### 1. Compile the Project
You can compile the project using `gcc`:
```bash
gcc src/*.c -o inverted_search
```

### 2. Run the Engine
Pass the text files you wish to index as command-line arguments:
```bash
./inverted_search file1.txt file2.txt
```

### 3. Usage Guide
Once launched, you will be presented with a menu. Follow the state machine workflow:
1. **Create Database:** Parses all valid files passed in the CLI and builds the Hash Table.
2. **Display Database:** Renders the current in-memory database as an ASCII table.
3. **Search Database:** Query a word to instantly see which files contain it and its frequency.
4. **Save Database:** Serializes the in-memory database into a `.txt` backup file.
5. **Update Database:** Restores the database from a backup file (Note: Cannot be run if a database is already created in memory).

## 👨‍💻 Author
**Akshay Mittha**
- Date: July 2026
