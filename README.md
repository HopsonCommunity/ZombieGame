# Community-Game
Made by my subscribers :) - Matthew Hopson

This project is a project maintained by Matt Hopson's subscriber community/server
and is an attempt at making a brand-spanking-new collaborative game together.

# How to join us

Just join our public discord, where all of the development happens.

`https://discord.gg/JKVBze6`

# Building and Contributing

If you want to know how to contribute to this project,
look at [`CONTRIBUTING.md`](CONTRIBUTING.md). The document will tell you how you can get the project
files with git, and how to contribute your code back into this
main repository.

Also take a look at the [`CODESTYLE.md`](CODESTYLE.md) file. It tells you how you should program
when you want your Pull Request mergerd into the project.

# Compiling the project

First, get the repsoitory downloaded to your computer. If you just want to look at
the code, clone the repository with

`git clone --recursive https://github.com/HopsonCommunity/ZombieGame`

## Preparation

#### Windows
Go to https://www.sfml-dev.org/download.php and click on SFML 2.x.x
There you can see a list of download buttons. Download the 32 Bit version of the
library your compiler needs.
**Note:** This README only covers the 2017 Version of Visual Studio, as it has an integrated
version of CMake. If you want to work with VS 2017 you will need to download the
VS 2015 libraries because they are compatible with VS 2017 and SFML doesnt
distribute VS 2017 libraries.

Now unzip the contents of the SFML-2.x.x folder into the deps/SFML folder.
It should look similar to this:
<img src="http://i.imgur.com/Q27AG5W.png" />

#### Linux
To download the latest SFML package for this project you need to execute following commands:
```
wget https://www.sfml-dev.org/files/SFML-2.4.2-linux-gcc-64-bit.tar.gz
tar -xvzf SFML-2.4.2-linux-gcc-64-bit.tar.gz
mv SFML-2.4.2/* repository-path/deps/SFML/ 
```

#### Mac is currently not supported as it is untested

## Compiling with Visual Studio
In Visual Studio, click on ``File->Open->Folder`` and select the root project folder.
Visual Studio should detect the CMakeLists.txt file. It prints the CMake log into
the console. It should look like this:
<img src="http://i.imgur.com/WPpcCj7.png" />
If it doesnt, you maybe have downloaded the wrong libraries or failed pasting them
into the right folder.
Next, click on the Dropdown arrow at the Launch-Button and select the game.
Now you can launch it.

## Compiling in CLion
Go to ``FILE->Import Project`` and select the root project folder.

Select ``Open Project`` and wait for CLion to prepare the IDE.

Click the green play button and in the executable config select the only available.
<img src="http://i.imgur.com/gwbZoA5.png" />

The IDE reads the CMakeLists.txt and compiles the program.

## Compiling without an IDE
#### Preparation Windows
Make sure you have MINGW with a c++ compiler, make installed in your path.
Install CMake from their official website and add it to the PATH.

**Note:** for the game to be correctly executed on Windows you will need to install OpenAL, check OpenAL at https://openal.org/downloads/ and download the latest installer.

#### Linux
Get a working C++ compiler, make and CMake from your distribution's package manager.

#### Mac is currently not supported as it is untested

#### Compiling
Go into the cloned repository and make a folder called `build`

`mkdir build`

Then, run CMake inside that build folder pointing the root folder.

`cd build`
`cmake ..`

CMake creates the Makefile in the build directory. Now you can just run

`make`

and your files will be compiled.

## Program crashes when launching?

Most likely it will happen because you wont have the res/ folder where the
execute relies. Just copy the folder to your build/ folder and you should be most
likely good to go.

If there are still error, go to our Discord and ask for help.

HAVE FUN CODING!
