g++ -c -o Claw.o Claw.cpp -I"../Dependencies/freeglut/include"
g++ -o Claw.exe Claw.o -L"../Dependencies/freeglut/lib/x64" -lfreeglut -lopengl32 -lglu32
Claw.exe