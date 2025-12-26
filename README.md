🎵 MP3 Tag Reader & Editor (ID3v2) – C Programming
📌 Project Description

MP3 Tag Reader & Editor is a command-line based application written in C that allows users to read and edit ID3v2 metadata in MP3 files. The project provides functionality to view song details such as title, artist, album, year, composer, and genre, and also modify selected fields safely.

This project was developed as part of my learning journey at Emertxe Institute of Technology, focusing on file handling, binary data processing, and modular C programming.

📘 Project Overview

MP3 files store metadata using the ID3v2 tag format. This project parses those tags at the binary level and displays them in a readable format. For editing, it uses a temporary file mechanism to ensure data integrity before updating the original MP3 file.

⚙️ Key Features

✅ Reads ID3v2 tags from MP3 files

✅ Displays metadata in a clean, formatted output

✅ Edits specific tags (example: Year)

✅ Uses temporary file handling for safe updates

✅ Command-line based execution

✅ Modular code structure for maintainability

🧠 C Programming Concepts Used

File Handling (fopen, fread, fwrite, fseek, fclose)

Binary File Processing

ID3v2 Tag Structure Understanding

Structures and Pointers

Command Line Argument Handling

Modular Programming Architecture

Error Handling and Validation

🎯 Skills Strengthened

Low-level file system understanding

Binary data manipulation

Debugging and logical problem-solving

Real-world application of C programming

Media file format analysis

📂 Project Structure
MP3/
│── main.c
│── view.c
│── view.h
│── edit.c
│── edit.h
│── types.h
│── song.mp3
│── temp.mp3

▶️ How to Compile and Run
Compile
gcc *.c

View MP3 Tags
./a.out -v song.mp3

Edit MP3 Tag (Example: Update Year)
./a.out -e -y 2020 song.mp3

🛠 Tools & Environment

Language: C

Compiler: GCC

OS: Linux

Editor: VS Code

🔗 GitHub Profile

👉 https://github.com/allapureddyjayapalreddy-creator
