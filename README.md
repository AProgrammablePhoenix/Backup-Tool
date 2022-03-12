# Backup-Tool

## General
As its name already shows it, Backup-Tool is a mere tool helping you
to make backups of your data. It is compatible with any OS supporting
at least C++17 even though a C version of it is planned to be released
soon.

This backup tool is useful when it comes to save huge files since
it will copy them concurrently in order to speed up the process. It is 
designed to be fast and flexible. Its only limitation being the hardware itself.

## How to use it
Telling the program which files to backup is a piece of cake: just list
all of the files you need to backup in a file called backup_list.txt.
The last entry being the output path where the tool will copy every
file/directory listed above it.

The config file supports both relative and absolute path.

## Installation
At this moment, you will need to compile everything manually with a
compiler C++ compiler of your choice. However, a CMake file is going to be added soon in order to simplify the compilation process, no matter
what your platform is.