VERSION ?= dev

.PHONY: all configure run installer clean

all:
	cd build && make

configure: clean
	cd build && qmake clipboard-mockifier.pro DEFINES+='VERSION=\\\"${VERSION}\\\"'

run: all
	killall "Clipboard Mockifier" || true
	./build/"Clipboard Mockifier.app"/Contents/MacOS/"Clipboard Mockifier"

installer: all
	npx appdmg build/appdmg.json build/"Clipboard.Mockifier.${VERSION}.dmg"

clean:
	git clean -xdf build
