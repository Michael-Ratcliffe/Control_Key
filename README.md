#(Control)ler to (key)board
USB controller to keyboard and mouse emulator 

#About
Control_Key is a cross-platform application that is available in both console and GUI versions.
This program will work with any controller that exist in the config/gamecontrollerdb.txt database file. I will periodically update it to match the one from this site: https://raw.githubusercontent.com/gabomdq/SDL_GameControllerDB/master/gamecontrollerdb.txt
There is one controller that I added that is not on this site which is the “Cideko Air Keyboard Conqueror”. However, only for Windows and Linux (sorry I do not have a Mac).
This program has been tested on Ubuntu 14.04, Ubuntu 15.10, Windows 8.1, and Windows 10.

The "builds" directory contains the prebuilt application for Windows and Linux

#Dependencies
SDL2

QT5

libx11 (Linux)

libxtst  (Linux)


#RoadMap

Mac support

Nicer looking GUI

#Building

Note: The built executable will be in the control_key folder. This is the application directory, and after compiling it can be placed anywhere on your computer.

Console: In the root directory, run “make linux” or “make windows” in a terminal. There is also "make linux-windows" which will make the Windows executable from Linux.
Then cd to the control_key directory and launch the program with the path of the config file as an argument. 
Example, ./controlkey config/minecraft.conf
Please note that using the console version requires you to make config files manually.

GUI: In the Qt folder open the ControlKey-GUI.pro file with Qt Creator. Then compile using release mode. On Windows do not "build and run" just "build" and then run deploy.bat in the root directory. This will copy the required libs from the deps folder into the control_key folder

#Disclaimer: Read The Full GPL v3 License For More Information

"THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
ALL NECESSARY SERVICING, REPAIR OR CORRECTION."