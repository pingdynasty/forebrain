all: device/firmware.bin client/hidclient

tools/lpc-flash: tools/lpc-flash.c
	gcc $< -o $@

client/hidclient: force
	cd client; $(MAKE)

device/firmware.bin: tools/lpc-flash force
	cd device; $(MAKE) -f build/Makefile

upload: device/firmware.bin
	cp -i device/firmware.bin /Volumes/CRP\ DISABLD/

clean:
	cd device; $(MAKE) -f build/Makefile clean
	cd client; $(MAKE) clean
	rm -f tools/lpc-flash

force :
	true
