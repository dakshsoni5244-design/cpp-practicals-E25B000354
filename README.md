# cpp-practicals-E25B000354

C++ Programming practical manual (RSSOFTTECS) - Daksh Soni, B.Tech AIDS, Roll No. E25B000354.

Each practical is in its own folder with a `main.cpp`. Compile and run any of them with:

```bash
g++ -std=c++17 -Wall -Wextra -o app pXX_name/main.cpp
./app
```

| No. | Folder | Topic |
|-----|--------|-------|
| 01 | `p01_fundamentals` | Data types, constants, operators, cin/cout |
| 02 | `p02_classes` | Classes and access specifiers (BankAccount) |
| 03 | `p03_rule_of_five` | Constructors and the Rule of Five (checked with Valgrind) |
| 04 | `p04_smart_pointers` | RAII, unique_ptr, shared_ptr |
| 05 | `p05_inheritance` | Person -> Student -> GraduateStudent |
| 06 | `p06_polymorphism` | Abstract Shape, virtual functions |
| 07 | `p07_overloading` | Function and operator overloading (ComplexNumber) |
| 08 | `p08_factory` | Factory design pattern (vehicles) |
| 09 | `p09_templates` | Generic Stack<T> with int, float, string |
| 10 | `p10_exceptions` | Custom exception classes (banking) |
| 11 | `p11_csv_fileio` | CSV records with fstream, seekg/seekp/tellg/tellp |
| 12 | `p12_library_project` | Mini project: Library Management System |

The full write-up with code, output and notes is in `docs/CPP_Practical_File_Daksh_Soni.docx`.

## Mini project: Library Management System

Features: add, list, search, issue and return books; data saved to / loaded from `data/books.csv`;
errors handled with a custom exception class.

```bash
cd p12_library_project
g++ -o library src/main.cpp
./library          # interactive menu
./library --demo   # scripted demo with normal and error cases
```

Classes: `Item` (abstract) -> `Book`, `Library` (vector of books), `LibraryError`.
The UML class diagram is in `docs/uml_class_diagram.png`.

Each practical folder has its own `README.md`, the source code and `output.txt` (program output). Practicals 1 and 12 also have `input_valid.txt`, `input_invalid.txt` and `output_invalid_input.txt`. Practicals 3 and 4 have `valgrind_output.txt`.
