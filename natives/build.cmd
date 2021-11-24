@echo off

gcc -c -m64 -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" at_sudo200_JConsole_JConsole.c -o at_sudo200_JConsole_JConsole.o
gcc -shared -o jconsole.dll at_sudo200_JConsole_JConsole.o -Wl,--add-stdcall-alias
del at_sudo200_JConsole_JConsole.o
