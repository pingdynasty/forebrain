LPCFLASH = ../tools/lpc-flash
LPCFIX = ../tools/lpcfix
DESTINATION = /Volumes/CRP\ DISABLD/firmware.bin

all: device/firmware.bin client/hidclient

$(LPCFLASH): $(LPCFLASH).c
	gcc $< -o $@

$(LPCFIX): $(LPCFIX).c
	gcc $< -o $@

client/hidclient: force
	cd client; $(MAKE)

device/firmware.bin: force
	cd device; $(MAKE) -f build/Makefile convert

upload: device/firmware.bin $(LPCFLASH)
	$(LPCFLASH) device/firmware.bin $(DESTINATION)

clean:
	cd device; $(MAKE) -f build/Makefile clean
	cd client; $(MAKE) clean

force :
	true
