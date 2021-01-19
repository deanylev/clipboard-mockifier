# Clipboard Mockifier

Mockify whatever is in your clipboard.

## Build Setup

1. Have Qt and qpm installed
2. Clone the repo
3. Run `git submodule update --init --recursive`
4. Run `qpm install`

In terms of Qt, you will likely want to [build it yourself statically](https://retifrav.github.io/blog/2018/02/17/build-qt-statically) and then install it, so that Clipboard Mockifier is statically linked against it. Otherwise, any user will need to install Qt themselves in order to run Clipboard Mockifier, which is obviously not ideal.

## Preparation
Run `VERSION=$version make configure` where "$version" is the version you want to appear on the settings screen. Run this every time you want to change the displayed version.

## Building
Run `make`.

## Running
Run `make run`, this will kill any currently running instances of Clipboard Mockifier.

## Building a macOS DMG
Run `VERSION=$version make installer` where "$version" is the version that you want to appear in the filename, e.g. "Clipboard.Mockifier.1.0.1.dmg". This should be the same one you used when running `make configure`.
