csscene
=======
A game engine at its infant state.

Linux
-----
Currently only work on 32 bit system.
### Building 
1. Go to the root folder csscene
2. run ./autogen.sh
3. run ./configure --build=i686-pc-linux-gnu "CFLAGS=-m32" "CXXFLAGS=-m32" "CXXFLAGS=-m32"  "LDFLAGS=-m32"

### Executing the viewer application
1 run ./viewer/linux/viewer from the root directory, you can provide scene with --scene option. scene files are available in the data folder.

Android
-------
Build the csscene library by going to the android/gles2 and android/gles1 folder. Use ndk-build command
Go to the viewer directory and build the shared library, use ndk-build command.
Open the viewer application in eclise and build the application.
You might want to link the jsrc folder to your application to complete the build. This can be done by going to the application properties->Java Build Path->Source tab->Link  source



