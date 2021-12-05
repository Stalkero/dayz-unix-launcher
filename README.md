# DayZ Unix Launcher

DayZ Launcher for Linux
This is unofficial DayZ launcher for linux with mod support

## Table of contents

* [Installing](#installing)
    * [Building from source](#building-from-source)
* [Launch parameters](#launch-parameters)
* [Sceenshots](#screenshots)

## Installing

### Building from source

Requirements:
* GCC 8 or newer (Clang with C++17 support should work too)
* CMake 3.11
* Qt5 with SVG support, version 5.9 or later
* fmt (optional)

#### Debian based (Debian, Ubuntu)
    apt install cmake qt5-default libqt5widgets5 libqt5svg5 libqt5svg5-dev libfmt-dev libspdlog-dev

#### Arch based (Arch Linux, Manjaro)
    pacman -S cmake fmt nlohmann-json pugixml qt5-base qt5-svg spdlog

#### Fedora
    dnf install gcc gcc-c++ cmake qt5-qtbase qt5-qtsvg qt5-qtbase-devel qt5-qtsvg-devel spdlog-devel

#### Build process
    git clone https://github.com/stalkero/dayz-unix-launcher.git
    cd dayz-unix-launcher
    mkdir build
    cd build
    cmake ..
    make

After that you can launch with

    ./src/dayz-unix-launcher/dayz-unix-launcher

### Launch parameters

```shell
Usage: dayz-unix-launcher [options] 

Optional arguments:
-h --help          	show this help message and exit
-l --list-presets  	list available mod presets
-p --preset-to-run 	preset to run, launcher will start Arma with given mods and exit
--server-ip        	server ip to connect to, usable only with --preset-to-run
--server-port      	server port to connect to, usable only with --preset-to-run
--server-password  	server pasword to connect to, usable only with --preset-to-run
-v --verbose       	verbose mode which enables more logging
```

Example:
```shell
dayz-unix-launcher --preset-to-run testmod --server-ip 127.0.0.1 --server-port 1234 --server-password asdasd
```

