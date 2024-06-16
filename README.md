# TrongB0XX

TrongB0XX is a ([fork of a fork](https://github.com/avahe-kellenberger/HayBox)) of the [HayBox](https://github.com/JonnyHaystack/HayBox) firmware. 
- "HayBox is a modular, cross-platform firmware for digital or mixed analog/digital controllers, primarily targeted at [B0XX](https://b0xx.com)-style controllers."


This fork contains custom modes & code for other Nintendo switch games.
- Mario Kart 8
- Taiko No Tatsujin

## Table of Contents
* [Installation](#installation)
  * [Pre-built binaries](#pre-built-binaries)
  * [Building from source](#building-from-source)
* [Usage](#usage)
  * [Default button holds](#default-button-holds)
* [Customisation](#customisation)
  * [Console/gamemode selection bindings](#consolegamemode-selection-bindings)
  * [Creating custom input modes](#creating-custom-input-modes)
  * [Mod X lightshield and R shield tilt](#mod-x-lightshield-and-r-shield-tilt)
  * [Mode-specific optional features](#mode-specific-optional-features)
    * [Melee modes](#melee-modes)
    * [Project M/Project+ mode](#project-mproject-mode)
  * [Input sources](#input-sources)
  * [Using the Pico's second core](#using-the-picos-second-core)
* [License](#license)

## Features

Features include:
- Cross platform support:
  - RP2040 (e.g. Raspberry Pi Pico)
  - 16MHz AVR MCUs (e.g. ATMega32U4 which several Arduinos are based on)
- Supports many existing controllers/PCBs, e.g. B0XX, LBX, Smash Box, Crane's
  GCCPCB/Model S
- Supports a variety of communication backends which can be used either separately or in conjunction with each other:
  - XInput
  - DInput
  - GameCube console
  - Nintendo 64 console
  - Nintendo Switch console
  - B0XX input viewer
- Supports a variety of "input sources" which can be used in conjunction to create mixed input controllers:
  - Buttons/switches wired directly to GPIO pins
  - Switch matrix (as typically found in keyboards)
  - Wii Nunchuk
  - GameCube controller
- Melee mode up to date with B0XX V3 specifications
- Existing modes for popular games (e.g. Melee, Project M, Ultimate, Rivals of Aether, traditional fighting games)
- Easy to create new controller modes (or keyboard modes) for different games
- USB keyboard game modes for games that lack gamepad support
- Fully customisable SOCD cleaning, allowing you to configure SOCD button pairs (e.g. left/right, up/down) for each controller/keyboard mode, and also easily change the SOCD resolution method for each SOCD pair
- Switch modes on the fly without unplugging your controller
- Automatically detects whether plugged into console or USB
- Game modes and communication backends are independent entities, meaning you can use any game mode with any supported console without extra work
- Easily switch between different GameCube/N64 polling rates in order to have optimal latency on console, overclocked adapter, etc. (not necessary for Pico/RP2040)

## Installation

If you want to simply use a pre-built firmware with default pin mappings and configuration, refer to the [pre-built binaries](#pre-built-binaries) section. If you want to make any changes to the code, refer to the [building from source](#building-from-source) section.

### Pre-built binaries

1. Browse the [existing configs](config/) to determine which config is appropriate for your hardware
2. Download the corresponding artifact from either the [latest HayBox release](https://github.com/JonnyHaystack/HayBox/releases), or from a [workflow run](https://github.com/JonnyHaystack/HayBox/actions) if you want the latest development version (unstable).
3. Flash the firmware to your microcontroller in the usual way
   - If you are using a Pico/RP2040 build (`.uf2` file), simply put it into bootsel mode while plugging it into your PC, and drag and drop the `.uf2` file onto the RPI-RP2 drive that comes up
   - If you are using Arduino/AVR build (`.hex` file), you can use a program like [QMK Toolbox](https://github.com/qmk/qmk_toolbox) to flash the `.hex` file to it

### Building from source

There are currently three main ways to build HayBox:
- Locally using PlatformIO IDE for VSCode or PlatformIO CLI
- In the cloud using GitHub Codespaces
- In the cloud using GitHub Actions

Both GitHub Actions and GitHub Codespaces require you to create a GitHub account, but do not require you to install any dependencies on your local machine.

#### Building locally

The following dependencies are required when building locally:
- [Git](https://git-scm.com/downloads) - required only if you are using a Pico
- [PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode)

After installing all of the requirements, download and extract the
[latest HayBox release](https://github.com/JonnyHaystack/HayBox/releases),
or clone the repository if you have git installed (which makes it easier for you
to pull updates).

After that:
1. Open Visual Studio Code
2. Click File -> **Open Folder** and choose the HayBox folder (the one containing platformio.ini, not the folder above that)
3. Choose the appropriate build environment for your controller's PCB by
  clicking the environment selection button near the bottom left of the window
  
  ![image](https://user-images.githubusercontent.com/1266473/187039372-485c5f0d-60b3-4534-befb-e713f138a7c8.png)
  ![image](https://user-images.githubusercontent.com/1266473/187039585-cea18994-fd12-45fb-b43f-427eb7affb81.png)
  
4. If your controller has a different pinout than any of the existing configs, you may edit the button mappings and other pins at the top of the config (`config/<environment>/config.cpp`). Any buttons that your controller doesn't have can simply be deleted from the list.
5. If you see a message in the bottom bar saying "Rebuilding IntelliSense Index" or "Loading Project Tasks", wait for it to disappear. For Pico especially it may take quite a while the first time because it has to download 2-3GB of dependencies.
6. Click **Build** (in the bottom left) and make sure everything compiles without
  errors
7. This next step differs depending on the microcontroller used in your controller.
    - **For Pico-based controllers**: hold the bootsel button while plugging it in (or your Start button if you already have HayBox installed) and then drag and drop the file `HayBox/.pio/build/<environment>/firmware.uf2` onto the RPI-RP2 drive that comes up.
    - **For Arduino-based controllers**: Plug in your controller via USB and click **Upload** (next to the Build button)

## Usage

### Default button holds

#### Pico bootsel mode

To reboot Pico-based controllers into bootsel mode, hold Start on plugin.

#### Brook board passthrough mode

To switch to Brook board mode on GCCPCB2, GCCMX, B0XX R2, or LBX, hold B on
plugin.

#### Communication backends (console selection)

Communication backends are selected slightly differently depending on the type
of microcontroller used in the controller.

On Pico/RP2040, USB vs GameCube vs Nintendo 64 is detected automatically. If
not plugged into a console, the default is **XInput**, which should work
plug-and-play with most PC games.
Other backends are selected by holding one of the following buttons on plugin:
- X - Nintendo Switch USB mode (also sets initial game mode to Ultimate mode)
- Z - DInput mode (only recommended for games which don't support XInput)

On Arduino/AVR, the **DInput** backend is selected if a USB connection is detected.
Otherwise, it defaults to GameCube backend, unless another backend is manually
selected by holding one of the following buttons on plugin:
- A - GameCube backend with polling rate fix disabled (used for GCC adapters)
- C-Left - Nintendo 64 backend (60Hz polling rate)

#### Game mode selection

Unlike other similar firmwares, HayBox by default allows you to switch
modes on the fly without unplugging your controller. This is mainly useful on
PC, as opposed to console where you usually have to restart the console to
switch game anyway. It also serves the purpose of reducing the number of buttons
you have to hold with one hand while plugging in.

The default controller mode button combinations are:
- Mod X + Start + L - Melee mode (default)
- Mod X + Start + Left - Project M/Project+ mode
- Mod X + Start + Down - Ultimate mode (default on Nintendo Switch)
- Mod X + Start + Right - FGC mode (Hitbox style fighting game layout)
- Mod X + Start + B - Rivals of Aether mode
- Mod Y + Start + Down - Mario Kart 8 Deluxe mode

Default keyboard mode button combinations (only available when using DInput backend, **not** with XInput):
- Mod Y + Start + L - Default keyboard mode

### Dolphin setup

HayBox needs a different Dolphin controller profile than the official B0XX firmware, as it
uses different DInput mappings that make more sense for use across multiple games. These
can be found in the `dolphin` folder in the HayBox repo. The profile files are named to
indicate what communication backend and operating system they are for:
- For Windows:
  - HayBox_XInput.ini - For Pico/RP2040-based controllers (e.g. B0XX R4)
  - HayBox_DInput.ini - For Arduino/AVR-based controllers (e.g. B0XX R1-3, LBX)
- For Linux:
  - HayBox_XInput_Linux.ini - For Pico/RP2040-based controllers (e.g. B0XX R4)
  - HayBox_DInput_Linux.ini - For Arduino/AVR-based controllers (e.g. B0XX R1-3, LBX)
- For macOS (unsupported*):
  - HayBox_DInput_macOS.ini

To install the profile:
1. Copy the appropriate .ini file from the `dolphin` folder within HayBox to the folder `<YourDolphinInstallation>\User\Config\Profiles\GCPad\` (create it if it does not exist)
- For Slippi this should be
  - On Windows: `%appdata%\Slippi Launcher\netplay\User\Config\Profiles\GCPad\`
  - On Linux: `~/.config/SlippiOnline/Config/Profiles/GCPad/`
  - On Mac: `Cmd + Shift + G` and enter the path `/Users/<USER>/Library/Application Support/Slippi Launcher/netplay/Slippi Dolphin.app/Contents/Resources/Sys/Config/Profiles/GCPad`
- For vanilla Dolphin: 
  - On Windows: `%userprofile%\Documents\Dolphin Emulator\Config\Profiles\GCPad\`
  - On Linux: `~/.config/dolphin-emu/Profiles/GCPad/`
2. Plug in your controller, and configure a "Standard Controller" in Dolphin
3. Click **Refresh** next to the Device dropdown
4. Select the HayBox profile from the profile dropdown, and click **Load** (NOT Save)
5. Make sure the correct device is selected in the device dropdown
6. Click **Close**

\* macOS only supports DInput (and not very well), so if using a Pico/RP2040-based controller you will have to force DInput mode by holding Z on plugin, and even then it may not work. I can't really do anything about Apple's poor controller support (which they seem to break with every other update) and I don't own any Apple devices, so this will also be considered unsupported usage of HayBox.

### Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available,
see the [tags on this repository](https://github.com/JonnyHaystack/HayBox/tags).

## Built With

* [https://github.com/MHeironimus/ArduinoJoystickLibrary]() - Used for DInput support for AVR
* [https://github.com/NicoHood/Nintendo]() - Used for GameCube and Nintendo 64 support for AVR
* [https://github.com/JonnyHaystack/ArduinoKeyboard]() - Used for keyboard modes on AVR
* [https://github.com/JonnyHaystack/arduino-nunchuk]() - Used for Nunchuk support
* [https://github.com/JonnyHaystack/joybus-pio]() - Used for GameCube and Nintendo 64 support for RP2040
* [https://github.com/earlephilhower/arduino-pico]() - Used for Arduino framework/PlatformIO support for Pico

## Contributors

* **Jonathan Haylett** - *Creator* - [@JonnyHaystack](https://github.com/JonnyHaystack)
* **Crane** - *Creator of the DIYB0XX firmware, which served as a great reference/starting point* - [@Crane1195](https://github.com/Crane1195)

See also the list of [contributors](https://github.com/JonnyHaystack/HayBox/contributors) who participated in this project.

### Acknowledgments

* The B0XX team, for designing and creating an incredible controller
* [@Crane1195](https://github.com/Crane1195) - for his DIYB0XX and GCCPCB projects, and for hours of answering my questions when I was first writing this
* [@MHeironimus](https://github.com/MHeironimus) - for the Arduino Joystick library
* [@NicoHood](https://github.com/NicoHood) - for the Nintendo library
* [@GabrielBianconi](https://github.com/GabrielBianconi) - for the Arduino Nunchuk library
* [@earlephilhower](https://github.com/earlephilhower) - for the arduino-pico core
* [@maxgerhardt](https://github.com/maxgerhardt) - for adding PlatformIO support for arduino-pico
* The Arduino project and the Raspberry Pi Foundation - for all their open-source hardware and software

## License

This project is licensed under the GNU GPL Version 3 - see the [LICENSE](LICENSE) file for details
