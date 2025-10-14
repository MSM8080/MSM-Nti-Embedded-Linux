#!/bin/bash

PYTHON_APP="/usr/bin/my_python_app.py"
CPP_APP="/usr/bin/my_cpp_app"
QT_APP="/usr/bin/appmsm_project"

while true; do
    echo ">>> Running Python app..."
    python3 "$PYTHON_APP"
    echo ">>> Python done. Running C++ app..."
    "$CPP_APP"
    echo ">>> C++ done. Running Qt app..."
    "$QT_APP" --platform wayland
    echo ">>> Qt app done. Looping again..."
done