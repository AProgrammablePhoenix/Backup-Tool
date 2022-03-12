cmake_minimum_required(VERSION 3.18)

project(BackupTool)

add_executable(BackupTool
    "src/backup_tool.cpp"
)

target_compile_features(BackupTool PUBLIC cxx_std_17)