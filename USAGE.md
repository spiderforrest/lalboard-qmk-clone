# setting up the esp32 qmk build environment for the Svalboard

## esp-idf
The build requires installing the esp-idf tools, docs are
[here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html).

#### Note on os:
I use Linux. If you're on macos or windows, good luck, the guide linked above is probably fine.


### Dependencies
Ubuntu/Debian:
`sudo apt-get install git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0`

CentOS 7/8:
`sudo yum -y update && sudo yum install git wget flex bison gperf python3 cmake ninja-build ccache dfu-util libusbx`

Arch:
`sudo pacman -S --needed gcc git make flex bison gperf python cmake ninja ccache dfu-util libusb`

### Clone esp-idf
IDF has a [guide on versioning](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/versions.html).
We're using `release/v4.4`.
```bash
mkdir -p ~/esp-dir
cd ~/esp-dir
git clone --recursive -b release/v4.4 https://github.com/espressif/esp-idf.git
```


### Build esp-idf
Run their installer:
```bash
./install.sh all
```


### Set up build env
To build firmware for your keyboard, we need to be inside esp-idf's virtual environment-you can run the `export.sh` script,
but you can automate it later.

## esp-qmk-clone

### qmk_firmware
We'll be using a fork of [qmk_firmware](https://github.com/qmk/qmk_firmware), by JesusFreke and Claussen(morganvenable). Clone it down:
```bash
cd ~/esp-dir
git clone --recursive https://github.com/morganvenable/esp-qmk-clone
```

### Setup qmk
`qmk` needs to be setup/configured-it can do that itself with:
```bash
cd ~/esp-dir/esp-qmk-clone/components/qmk/qmk
./util/qmk_install.sh
```

Some distros may have errors about managed enviorments, edit `~/.espressif/python_venv/<venv name>/pyvenv.cfg` to change this to true:
```python
include-system-site-packages = true
```

### Configs
It's easier to copy your configs into qmk as `default` and flash that-it also makes sense if you're using your own fork
of esp-qmk-clone, and if so you can swap the directories:
```bash
cp -r ~/esp-dir/lalboard-qmk-clone/components/qmk/qmk/keyboards/handwired/lalboard/ ~/esp-dir/config
```
Then, do your configuring in `config/keymaps/default`.

If you don't like that, you can edit `~/esp-dir/esp-qmk-clone/CMakeLists.txt` to match your configs:
```
set(QMK_KEYBOARD handwired/lalboard)
set(QMK_LAYOUT default)
```

## Building qmk_firmware & flashing

I recommend making a script for it, like so:
```bash
touch ~/esp-dir/flash.sh
chmod +x ~/esp-dir/flash.sh
```

Then, paste this into the file:
```bash
#!/usr/bin/bash

# load esp-idf virtual env
source "$HOME/esp-dir/esp-idf/export.sh"
cd "$HOME/esp-dir/esp-qmk-clone/" || exit
# nuke and replace configs
rm -r ./components/qmk/qmk/keyboards/handwired/lalboard/
cp -r "$HOME/esp-dir/configs/" ./components/qmk/qmk/keyboards/handwired/lalboard/

echo "/// Press return to flash left hand... ///"
read
echo "/// Flashing left! ///"
SIDE=left idf.py -p /dev/ttyACM0 flash

echo "/// Press return to flash right hand... ///"
read
echo "/// Flashing right! ///"
SIDE=right idf.py -p /dev/ttyACM0 flash
```

Then, you can flash by running:
```bash
./flash.sh
```



