# Practical 12: Library Management System

Console project: add, list, search, issue and return books. Data is saved in data/books.csv. Classes: Item (abstract), Book, Library, LibraryError.

## Files
- `src/main.cpp`
- `data/books.csv`
- `input_invalid.txt`
- `input_valid.txt`
- `output.txt`
- `output_demo.txt`
- `output_invalid_input.txt`

Menu run with valid input and with invalid input, plus a scripted demo.

## Compile and run
```bash
g++ -o library src/main.cpp
./library < input_valid.txt     # menu with input file
./library --demo               # scripted demo
```

## Output
See `output.txt` and `output_invalid_input.txt`.
