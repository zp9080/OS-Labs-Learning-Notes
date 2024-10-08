###############################################################
# Configuration file for Bochs
###############################################################

# how much memory the emulated machine will have
megs: 256

# filename of ROM images
romimage: file=/usr/local/share/bochs/BIOS-bochs-latest
vgaromimage: file=/usr/share/vgabios/vgabios.bin

# what disk images will be used
floppya: 1_44=freedos.img, status=inserted
floppyb: 1_44=pm.img, status=inserted

# choose the boot disk.
boot: a 

magic_break: enabled=1
# where do we send log messages?
#log: bochsout.txt

# disable the mouse
# mouse: enabled=0

# enable key mapping, using US layout as default.
# keyboard_mapping: enabled=1, map=/usr/share/bochs/keymaps/x11-pc-us.map
