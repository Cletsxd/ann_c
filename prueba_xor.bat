@echo off
title NeuralNet XOR
echo You will enter to the program Neural Net XOR
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
echo Compiling...
g++ -o prueba.exe error_code.c math_functions.c matrix.c neural_net.c main_xor.c
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
g++ -o prueba.exe error_code.c math_functions.c matrix.c neural_net.c main_xor.c
pause
goto Main

:E
cls
title Simbolo del sistema
echo Exit...