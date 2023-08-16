# MIDI Pedalboard over Arduino

> ⚠️ Attention : If you are building your own pedalboard using this repository and planning to change elements
> disposition, you will have to edit the PC software located in the `desktop` folder and rebuild yourself (The build
> steps
> are explained in the [Build PC software](#build-pc-software) section).

This repository contains all the instructions to build my MIDI pedalboard created over Arduino cards. There is no
guaranty the code will work for you. Feel free to open an issue if there is a need.
I assume you are on Windows or macOS (not tested for the Arduino part). Linux is not explained here because I don't
intend to support it. This repository is for Windows in the fist place.
I also assume you are not a developer, and you are not familiar with C++ building tools. This is why the guide is
detailed like this.

## Repository structure

The repository is divided in 2 parts :

- The `arduino` folder contains all the code that will be uploaded to the Arduino card
- The `desktop` folder contains all the code for the PC software needed to use the board. (If you built an identical
  version to mine, you can download the prebuilt software in
  the [Release](https://github.com/CommandMaker/arduino-midi-pedalboard/releases) section)

All the build steps are described below.

## Requirements

All the components was bought on AliExpress (The total cost ~15€ at the time I write this)

- [Arduino card (unofficial, nano model)](https://aliexpress.com/item/1005005757251645.html)
- [x10 3PDT foot switch](https://fr.aliexpress.com/item/32897629489.html)
- [Some LEDs for button state (red for me)](https://fr.aliexpress.com/item/1005001382143715.html)
- [A stereo jack to plug an expression pedal (not tested yet, be careful : it
  **must** be stereo)](https://www.thomann.de/fr/goeldo_j0019_stereoklinkenbuchse.htm)
- Some time and patience
- Qt SDK or CMake & MinGW (for Windows) if using the prebuilt software (installation process is
  described [below](#install-development-tools))

## Soldering components

Not written yet. Come back later !

## Install development tools

- ### Qt SDK (Windows)

> ⚠️ If you already have Qt installed, you can skip this part

Go to the [Qt download page](https://www.qt.io/download-qt-installer-oss) and select your platform. Run the installer,
log in you to your account, select an installation folder and select, inside the Qt components list
the `MinGW xx.xx.x 64-bits` under `Qt > Qt 6.x` (the latest Qt 6 version available)
Select also the same `MinGW` inside `Qt > Developer and Designer Tools`. You can disable all other options
except `CMake` if you are just planning to build this software.
Make sure you have the `Qt Serial Port` selected under `Qt > Qt 6.x > Additional Libraries`
Launch the installation (it can take several minutes depending on your network speed).

Add these folders to your path : 
- `<Qt install path>/Tools/CMake_64/bin`
- `<Qt install path>/Tools/mingw<version>_64/bin`
- `<Qt install path>/Tools/mingw<version>_64/lib`
- `<Qt install path>/<Qt version (6.5.2 for example)>/mingw_64/bin`

I don't know if it's required on macOS but for Windows, you need to do it.

On macOS, you will have to install `make` if you don't have it installed on your PC.

- ### Arduino SDK (Windows & macOS)

To install the Arduino SDK go to the [Arduino downloads page](https://www.arduino.cc/en/software) and install the
**Legacy IDE (1.8.x)**. If you install the new IDE (2.x) CMake will not be able to find the Arduino SDK.

## Uploading program to the Arduino

For this part, you will need CMake, a C++ compiler such as `g++` and a build system like `Ninja` or `MinGW make` (This
is the one I will use)
To install them, refer you to the [Install development tools](#install-development-tools) section if you don't have them
installed.

Change the `set(${PROJECT_NAME}_BOARD uno)` to your arduino board model & the `set(${PROJECT_NAME}_PORT COM3)` to your Arduino port

When you have the tools, open a terminal (`Win+R > cmd` on Windows & `Terminal` app on macOS) and run the following commands
```bash
cd <Where you have downloaded the repo>
cd arduino
mkdir build # Create the build folder
cd build
cmake .. -G "MinGW Makefiles" # On Windows to generate CMake build files using make
cmake .. -G "Unix Makefiles" # Same but on macOS
mingw32-make upload-arduino # replace mingw32-make with make on macOS
```

## Build PC software
For this part, you will need the Qt SDK (refer you to [Install development tools](#install-development-tools) if you don't have it).

Open a terminal and run these commands (They are likely the same as the Arduino's one, so refer to the section to know their usage)
```bash
cd <Where you have downloaded the repo>
cd desktop
mkdir build
cmake .. -G "MinGW Makefiles -DCMAKE_BUILD_TYPE=Release" # Windows
cmake .. -G "Unix Makefiles -DCMAKE_BUILD_TYPE=Release" # macOS
mingw32-make upload-arduino # replace mingw32-make with make on macOS
```
You will find the software compiled in the `build/bin` folder. Copy the entire directory to another place to save it.

You can delete the repo after uploading to arduino & building the software