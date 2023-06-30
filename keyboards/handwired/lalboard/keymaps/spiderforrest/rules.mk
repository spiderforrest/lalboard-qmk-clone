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
SLEEP_LED_ENABLE  = no     # Breathing sleep LED during USB suspend

NO_USB_STARTUP_CHECK = yes # TODO(jesusfreke) implement support for split suspend

# my options

LTO_ENABLE = no						# optimize space
Link_Time_Optimization = no  		# more compile time, less keeb size. same as above?
#EXTRAFLAGS += -flto		 		  # direct arg for link time optimization
SPACE_CADET_ENABLE = no	 	 		 # disabling for space
GRAVE_ESC_ENABLE = no	 	 		 # disabling for space
MAGIC_ENABLE = no		 	 		 # disabling for space
CONSOLE_ENABLE = no      	 		 # Console for debug
SWAP_HANDS_ENABLE = no   	 		# Enable one-hand typing
RAW_ENABLE = no          	 		 # Send raw data back and forth
KEY_LOCK_ENABLE = no     	 		# key to supress next keyup
DYNAMIC_MACRO_ENABLE = no  	 		 # on the fly macros
#DEBOUNCE_TYPE = sym_defer_pk		  # not sure i wanna mess with debounce, now that I GOT LASERS ON MY FINGERS
COMBO_ENABLE = yes   		   		 # key combo features?
AUTO_SHIFT_ENABLE = no		   		 # holding a key emulates shift. pinkies love him.

# Project specific files
SRC = matrix.c

ifeq (left, ${SIDE})
    CFLAGS += -DMASTER_LEFT
else
    CFLAGS += -DMASTER_RIGHT
endif
