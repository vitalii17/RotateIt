# Rotate It!
The Qt-based Symbian application for rotation photo to any angle. Useful for correct the "littered horizon" directly on smartphone.

## Features
* Rotate photos and auto-cropping.
* Open images from file manager or gallery(in Extended version). 
* Multi-threading processing. You may edit next photo while saving previous.
* Settings for JPEG compression from 0% to 100%.
* Saves EXIF metadata. Uses Exiv2 library: https://github.com/Exiv2/.
* Supports Symbian Anna/Belle. Can be builded for lower Symbian version up to 9.4 with some limitations.

## Tools to build
* Qt Creator 2.4.1 or earlier.
* Latest Symbian toolchain.
* Qt 4.7.4.

To build "Extended" (unsigned) version create build configuration with additional argument "CONFIG+=extended_version" in QtCreator.

All tools available in the QtSDK 1.2.1. Link to download all developer resources: https://www.mediafire.com/folder/79jhy594xb3uk/Symbian_Development.

## Known issues
* Built-in QtSDK self-signed certificate dont have capabilities to fetch images from system Gallery. Use unsigned package instead.
* If you build with Qt 4.7.3 you should to add application icon manually because it works incorrect.
