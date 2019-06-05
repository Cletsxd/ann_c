#!/bin/bash

echo "You will enter to the program Neural Net XOR"
read -p "Presione una tecla para continuar . . ."

option=0

while [ $option -ne 4 ]; do
    clear
    echo "1. Compile and run"
    echo "2. Run"
    echo "3. Compile"
    echo "4. Exit"
    echo -n "Write and option: "
    read option

    if [ $option -eq 1 ]; then
        clear
        echo "Compiling..."
        g++ -o prueba.exe error_code.c math_functions.c matrix.c neural_net.c main_xor.c
        echo "Running..."
        ./prueba.exe
        read -p "Presione una tecla para continuar . . ."
    fi

    if [ $option -eq 2 ]; then
        clear
        echo "Running..."
        ./prueba.exe
        read -p "Presione una tecla para continuar . . ."
    fi

    if [ $option -eq 3 ]; then
        clear
        echo "Compiling..."
        g++ -o prueba.exe error_code.c math_functions.c matrix.c neural_net.c main_xor.c
        read -p "Presione una tecla para continuar . . ."
    fi

    if [ $option -eq 4 ]; then
        clear
        echo "Exit..."
    fi
done