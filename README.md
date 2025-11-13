# Log File Analyzer
This project is a high-efficiency Log File Analyzer and Classifier written entirely in C. It processes a master log file, extracts the log type (INFO, WARNING, ERROR), and directs each line to its corresponding output file.

The primary focus of this project was optimizing I/O performance and demonstrating robust low-level memory and file management skills.

# Key Technical Concepts
**Optimal File I/O Management (Performance):**
- Resolved severe performance bottlenecks by implementing an **"Open Once, Close Once"** strategy for file handling.
- Eliminated I/O Overhead: Successfully avoided thousands of expensive system calls (fopen/fclose) that are common in inefficient code.
- Resource Efficiency: Managed four simultaneous FILE* streams (log_file, info_file, warning_file, error_file) from a central point (main).

**Robust Pointer and Memory Management:**
- Pass by Reference: Correct use of pointers (* and &) to pass data to functions and safely return values (LogType, file_size) to the main execution scope.
- File Position Indicator: Explicitly managed the file position indicator using `rewind()` after the initial file-counting pass to prepare the file for sequential parsing.

**Data Parsing and Control:**
- Used sscanf with advanced formatting (%*d %s) to efficiently parse structured data from each line.
- Utilized typedef enum and the switch statement for clear, type-safe classification logic.
