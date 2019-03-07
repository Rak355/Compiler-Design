# Project details:

**A simple compiler for C programming language, written in C itself.**

# Project Status:
1. A lexer has been created.
2. We are improving the lexer and correcting bugs.
3. Work on a parser is in progress.
4. The lexer could analyze its own code. See the log.txt file which was created when I ran the  program to analyze its own code in my system.

# Objectives:
1. Improve and debugg the lexer for efficient parsing.
2. Reach a parsing stage.

# Dependencies:
1. A Linux environment or a subsystem of Linux for other platforms.
2. gcc's C compiler.
3. make.

# How to build:
**Only a lexer has been implemented yet**

1. Clone this repository to your local branch.
2. Create or edit the "src_file.c" in the root folder/directory.
Write C codes on this file to test the Lexer.
3. Open a terminal in the root directory:
to build and run: $make run

## Notable bugs:
1. The lexer does identify token types. However their are bugs.
2. The lexer does not detects preprocessors directives.
3. Suffixes on literals are not supported yet.
4. The lexer does not distinguishes between the identifiers and the keywords.

**Please report any bugs by raising an issue on the repository.**
