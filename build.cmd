if not exist build\ (mkdir build)
cd build
cmake ..
msbuild BackupTool.vcxproj /p:Configuration=Release