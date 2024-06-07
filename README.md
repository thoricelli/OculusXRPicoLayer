# OculusXRPicoLayer
A WIP to port Quest games over to PICO. <br>
<br>
This replaces the following libs:
- libOculusXRPlugin.so
- libovrplatformloader.so
- libOVRPlugin.so

And replaces them with a proxy, that relays functions/information over to the PICO libs. <br>
Currently not yet finished. <br>

Feel free to contribute with a PR!

# Building
- Install the Android NDK: https://developer.android.com/ndk/downloads <br>
(I recommend you install it via Android Studio)
- Run either the `compile_windows.ps1` powershell script or the `compile_linux.bash` bash script. <br>
Don't forget to add the toolchain /bin/ to your path! <br>
(TODO is to make a Makefile...)

# List of working games
| Game | Works    | Doesn't work    |
| :---:   | :---: | :---: |
| Keep Talking and Nobody Explodes | Fully functional | / |
| Waltz of the Wizard | Sound | No video |

(All OpenVR games should work, however non-OpenVR games are not yet implemented)

More games are to be tested soon.

# APKs
If anyone has the APK for VRChat on their Quest, if you could please provide me with one, that would be appreciated!
