all: device/firmware.bin client/hidclient

tools/lpc-flash: tools/lpc-flash.c
	gcc $< -o $@

client/hidclient:
	cd client; make

device/firmware.bin: tools/lpc-flash
	cd device; make -f build/Makefile

upload: device/firmware.bin
	cp -i device/firmware.bin /Volumes/CRP\ DISABLD/

clean:
	cd device; make -f build/Makefile clean
	cd client; make clean
	rm -f tools/lpc-flash
