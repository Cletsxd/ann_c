@echo off
title NeuralNet Perceptron
echo You will enter to the program Neural Net Perceptron
pause

:Main
cls
echo 1. Compile and run
echo 2. Run
echo 3. Compile
echo 4. Exit

set /p option= Write and option: 

if %option%==1 goto Cr
if %option%==2 goto R
if %option%==3 goto C
if %option%==4 goto E

:Cr
cls
echo Compiling...
g++ -o prueba.exe c/error_code.c c/math_functions.c c/matrix.c c/neural_net.c perceptron.c
cls
echo Running...
prueba.exe
pause
goto Main

:R
cls
echo Running...
prueba.exe
pause
goto Main

:C
cls
echo Compiling...
g++ -o prueba.exe c/error_code.c c/math_functions.c c/matrix.c c/neural_net.c perceptron.c
pause
goto Main

:E
cls
title Simbolo del sistema
echo Exit...