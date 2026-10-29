#!/bin/bash

echo "Checking dependencies..."
./install_dependencies.sh
echo "Dependencies satisfied"

echo "Compiling the project..."
cd build
cmake ..
cmake --build .
cd ..

echo "Compilation finished"
echo "Running the application..."

if [ "$1" = "run" ]; then
    echo "Running the application..."
    ./build/monopoly_app
else
    echo "Compilation finished. (Skipping execution. Run './compile.sh run' to execute)."
fi