all: device/firmware.bin client/hidclient

client/hidclient:
	cd client; make

device/firmware.bin:
	cd device; make -f build/Makefile

upload: device/firmware.bin
	cp -i device/firmware.bin /Volumes/CRP\ DISABLD/

clean:
	cd device; make -f build/Makefile clean
	cd client; make clean
