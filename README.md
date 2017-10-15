# Community-Game
This game is the second series of the community games by Matthew Hopson's Discord Community.
This time around, we're replicating a Zombie game that we found online.

# How to join us

Just join our public discord, where all of the development happens. For project related talk just look under the "Community Project" category.

`https://discord.gg/feKbBwS`

# Building and Contributing

If you want to know how to contribute to this project,
look at [`CONTRIBUTING.md`](CONTRIBUTING.md). The document will tell you how you can get the project
files with git, and how to contribute your code back into this
main repository.

There is also an easier way using the renewed desktop app "Github for Desktop", but this is not yet documented by anyone. 
You can follow the command instructions in the GUI app, however, as the backend to the GUI app is the Git command line. Therefor,
the Github GUII app will have all the same features and buttons as Git (but git has them command-wise.)

Also take a look at the [`CODESTYLE.md`](CODESTYLE.md) file. 
This file makes it clear which coding-format is acceptable in this repository.
Pull Requests not conforming to the coding standard will be rejected. 
A rejected pull request can be re-opened when the code has been changed and is conforming.

# Compiling the project

First, download the repository to your local machine.

`git clone --recursive https://github.com/HopsonCommunity/ZombieGame`

## Preparation

#### Linux
As SFML will be built from sources, you will be required to have the SFML sources.
##### Debian-based(eg. Lubuntu, Xubuntu, Ubuntu, ...)
``sudo apt-get install -y libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew1.5-dev libjpeg8-dev libsndfile1-dev libopenal-dev libudev-dev libxcb-image0-dev libjpeg-dev libflac-dev``
The -y parameter works by automatically accepting the requests for approval.

##### Arch Linux-based(eg. Manjaro)
``sudo pacman -S libpthread-stubs libx11 libxrandr libjpeg libsndfile libudev0 libxcb mesa libxrandr freetype2 glew libjpeg6-turbo openal flac``


Other distributions will follow. The dependency names are listed here:
https://www.sfml-dev.org/tutorials/2.4/compile-with-cmake.php

## Compiling with Visual Studio
In Visual Studio, click on ``File->Open->Folder`` and select the root project folder.
Visual Studio should detect the CMakeLists.txt file. It prints the CMake log into
the console. It should look like this:
<img src="http://i.imgur.com/WPpcCj7.png" />
:::If there are any errors, please check that you have copied over the dependencies to the right folder.:::
Next, click on the Dropdown arrow at the Launch-Button and select the game.
The project will now be compiled and executed.

## Compiling in CLion
Go to ``FILE->Import Project`` and select the root project folder.

Select ``Open Project`` and wait for CLion to prepare the IDE.

Click the green play button and in the executable config select the only available.
<img src="http://i.imgur.com/gwbZoA5.png" />

The IDE reads the CMakeLists.txt and compiles the program.

## Compiling without an IDE
#### Preparation Windows
Make sure you have MINGW with a c++ compiler, make installed in your path.
Install CMake from the official website and add it to the PATH.

**Note:** For the game to be correctly executed on Windows you will need to install OpenAL, check OpenAL at https://openal.org/downloads/ and download the latest installer.

#### Linux
Install a C++ compiler, make and CMake using your distribution's package manager.

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

In most cases, crashes will be caused by the lack of the "res/" folder where the
executable files lie. Just copy the folder to your "build/" folder and this will
most likely get you up and running again.

If you're unable to resolve your errors, feel free to contact us on Discord!

### HAVE FUN CODING!
