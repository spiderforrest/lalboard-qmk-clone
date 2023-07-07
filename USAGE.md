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

## Notes
If your board was made after 5/31/2023(it probably was), add this to your `config.h`:
```c
// The column with the "down" keys on both the normal and thumb clusters
// is inverted.  This should be true on all units manufactured after 5/31/2023
#undef MATRIX_COL_PUSHED_STATES
#define MATRIX_COL_PUSHED_STATES { 0, 0, 1, 0, 0, 0 };
```
You can either write udev rules or just use `chmod 666` on `/dev/ttyACM0` each time you flash-I am lazy, so
[here](https://github.com/spiderforrest/fotdiles/blob/main/bin/sval) is the script I use, make sure to change the dirs.

Also, I personally hate the layout in the configs, so I wrote an alternative matrix, add to your `config.h`:
```c
#define VISUAL_LAYOUT( \
 l4w, l3w, l2w, l1w, r1e, r2e, r3e, r4e,    \
 l4e, l3e, l2e, l1e, r1w, r2w, r3w, r4w,    \
 l4n, l3n, l2n, l1n, r1n, r2n, r3n, r4n,    \
 l4s, l3s, l2s, l1s, r1s, r2s, r3s, r4s,    \
 l4d, l3d, l2d, l1d, r1d, r2d, r3d, r4d,    \
                                            \
 ltu,      ltuo,         rtuo,      rtu,    \
 lti, ltd, ltlo,         rtlo, rtd, rti,    \
      ltdd,                    rtdd         \
        ) \
{ \
    {rtlo,rtuo,rtd, rti, rtu, rtdd}, \
    {r1s, r1e, r1d, r1n, r1w, KC_NO}, \
    {r2s, r2e, r2d, r2n, r2w, KC_NO}, \
    {r3s, r3e, r3d, r3n, r3w, KC_NO}, \
    {r4s, r4e, r4d, r4n, r4w, KC_NO}, \
     \
    {ltlo,ltuo,ltd, lti, ltu, ltdd}, \
    {l1s, l1e, l1d, l1n, l1w, KC_NO}, \
    {l2s, l2e, l2d, l2n, l2w, KC_NO}, \
    {l3s, l3e, l3d, l3n, l3w, KC_NO}, \
    {l4s, l4e, l4d, l4n, l4w, KC_NO}, \
}
```

If you look in `./keyboards/handwired/lalboard/keymaps/spiderforrest/keymap.c` you can reference my layouts to see what that looks like.

If you run into hangups, you can ask me for help, I probably ran into every issue possible-you're probably in that one discord but:
JID/email: spider@spood.org
Telegram/Discord: @spiderforrest
Or open an issue here.
