# MCU name
MCU = esp32s2

# Build Options
BOOTMAGIC_ENABLE  = no     # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE   = yes    # Mouse keys(+4700)
EXTRAKEY_ENABLE   = yes    # Audio control and System control(+450)
CONSOLE_ENABLE    = yes    # Console for debug(+400)
COMMAND_ENABLE    = yes    # Commands for debug and configuration
COMBO_ENABLE      = no     # Key combo feature
LEADER_ENABLE     = no     # Enable the Leader Key feature
NKRO_ENABLE       = yes    # USB Nkey Rollover
BACKLIGHT_ENABLE  = no     # Enable keyboard backlight functionality on B7 by default
MIDI_ENABLE       = no     # MIDI controls
UNICODE_ENABLE    = no     # Unicode
BLUETOOTH_ENABLE  = no     # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE      = no     # Audio output on port C6
CUSTOM_MATRIX     = yes    # Some pins have inverted logic
SPLIT_KEYBOARD    = no     # yes, but we don't use any of qmk's logic for this
SLEEP_LED_ENABLE = no      # Breathing sleep LED during USB suspend

NO_USB_STARTUP_CHECK = yes # TODO(jesusfreke) implement support for split suspend

# Project specific files
SRC = matrix.c

ifeq (left, ${SIDE})
    CFLAGS += -DMASTER_LEFT
else
    CFLAGS += -DMASTER_RIGHT
endif
