windows-compile:
	g++ -c main.cpp Game.h Game.cpp -I../Dependencies/SFML-Win/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/include
	
windows-build: 
	g++ main.cpp Game.h Game.cpp -mwindows -o ../bin/win/app.exe -I../Dependencies/SFML-Win/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/include -L../Dependencies/SFML-Win/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/lib -lsfml-graphics -lsfml-window -lsfml-system

win-debug: 
	g++ main.cpp Game.h Game.cpp -g -o ../bin/win/app-d.exe -I../Dependencies/SFML-Win/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/include -L../Dependencies/SFML-Win/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/lib -lsfml-graphics -lsfml-window -lsfml-system
	
linux-compile: 
	g++ -c main.cpp Game.h Game.cpp -I../Dependencies/SFML-Linux/include

linux-build:
	g++ main.cpp Game.h Game.cpp -o ../bin/linux/app -I../Dependencies/SFML-Linux/include -L../Dependencies/SFML-Linux/lib -lsfml-graphics -lsfml-window -lsfml-system
	
linux-clean:
	rm *.o *.h.gch

windows-clean:
	del *.o *.h.gch