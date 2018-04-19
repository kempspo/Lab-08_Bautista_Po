Lab#7 - PThreads (Sin(x))
========================

1. Lab#7b_Bautista_Po_code.cpp

Description
-----------

1. This file is C++ code that, when compiled and executed, demonstrates the creation and concurrent execution of threads in C++ by taking in integer arguments from the command line and passing them to a thread's run function which will perform a specific operation on them depending on certain conditions. It also computes sin(x) using an arbitrary number of threads defined by N.


How to set up the program
-------------------------

If on Windows:
	1. Start up a Linux machine using a VM application. (ex. Oracle VM VirtualBox - download link can be found here: https://www.virtualbox.org/)

	2. Open a command line and navigate to the folder containing the files.

	3. If g++ compiler has not been installed on the Linux machine yet, type in the following into the terminal:
		sudo apt-get install g++

	4. To create an executable program, type into the command line: g++ -o -pthread <name of executable file> <name of program file>

If on Linux:
	1. If g++ compiler has not been installed on the Linux machine yet, type in the following into the terminal:
		sudo apt-get install g++

	2. To create an executable program, type into the command line: g++ -o -pthread <name of executable file> <name of program file>


How to use the program
----------------------
1. Open a command line and execute the program by navigating to the folder it is in and typing "./<name of executable file> <integer/s (separated by space if multiple)>"

2. The program will then create an array of threads, passing their index (int) in the array as the thread's argument

3. The thread will do the Sin(x) operation on x through using factorial and power.

4. The command line will output the following:

4.1 Confirmation messages that the threads performed the operations on the arguments

4.2 The threads and the resulting values


