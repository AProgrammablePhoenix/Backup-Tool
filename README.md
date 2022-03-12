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
The compilation process is managed by CMake. In order to compile the project, just
run one of the build scripts located in the same directory as the CMakeLists.txt file
and they will create a build folder if necessary. All the build files will be stored
in this folder.