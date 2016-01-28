#Console Version
Build_Dir = control_key
App_Name = controlkey
Src = $(wildcard src/*.cpp)
Include_Dir = deps/include
Lib_Dir = deps/lib/x64

Linux_Flags = -std=c++11 -lX11 -lXtst -lSDL2main -lSDL2

Windows_Flags = -static-libgcc -static-libstdc++ -Bstatic -lpthread -std=c++11 -lmingw32 -I$(Include_Dir) -L$(Lib_Dir) -lSDL2main -lSDL2

linux:
	g++ $(Src) -o $(Build_Dir)/$(App_Name) $(Linux_Flags)

linux-windows:
	x86_64-w64-mingw32-g++ $(Src) -o $(Build_Dir)/$(App_Name).exe $(Windows_Flags)
	
windows:
	g++ $(Src) -o $(Build_Dir)/$(App_Name).exe $(Windows_Flags)

clean:
	rm -f $(Build_Dir)/$(App_Name) $(Build_Dir)/$(App_Name).exe
		



