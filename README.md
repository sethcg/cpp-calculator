``` bash
# BUILD APPLICATION
cmake -DCMAKE_BUILD_TYPE=Debug -S. -Bbuild
cmake --build build -j

# RUN APPLICATION
start ./build/Debug/main.exe
```