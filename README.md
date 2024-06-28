# OculusXRPicoLayer

An attempt to port Quest games over to PICO. <br>
<br>
This replaces the following libs:

- libOculusXRPlugin.so
- libovrplatformloader.so
- libOVRPlugin.so

And replaces them with a proxy, that relays functions/information over to the PICO libs.

Only a limited amount of Unity games are supported. <br>
Unreal games are **not** supported.

# Building

- Install the Android NDK <br>
  <b>Required version:</b> r21e (21.4.7075529).
  <br>https://developer.android.com/ndk/downloads <br>
  (I recommend you install it via Android Studio)

- Run either the `compile_windows.ps1` powershell script or the `compile_linux.bash` bash script. <br>
  Don't forget to add the toolchain /bin/ to your path! <br>
  (TODO is to make a Makefile...)

# Patching games

You will need the following

- An APK extractor <br>
  [apktool](https://apktool.org/docs/install)
- An APK signer <br>
  [uber-apk-signer](https://github.com/patrickfav/uber-apk-signer) or [PPTools](https://github.com/FallenAngel-PP/PP_Stuff_Tool_for_Windows)
- My patched libs <br>
  You can find prebuilt libs in [Actions](https://github.com/thoricelli/OculusXRPicoLayer/actions) > Build files.

You'll need the following files (both from my repo): <br>
(Oculus)

- libOculusXRPlugin.so
- libovrplatformloader.so
- libOVRPlugin.so

(Pico)

- libPxrPlatform.so
- libpxr_api.so
- libpxrplatformloader.so

(C++)

- libc++\_shared.so

Make sure you take the ones I committed to the repo, they have some patched strings/instructions to make them work.

1. Build or download the required libs.
2. Decompress the APK file with apktools.
3. Replace/add the library files into `/lib/arm64-v8a`
4. In `AndroidManifest.xml`, inside of `<application>...</application>` add:

```
<meta-data android:name="pvr.app.type" android:value="vr"/>
```

5. Then open `/assets/bin/Data/UnitySubsystems/OculusXRPlugin/UnitySubsystemsManifest.json`
6. Set the name to `"name": "PxrPlatform",`

# List of working games

|               Game               |         Works          |               Doesn't work               |
| :------------------------------: | :--------------------: | :--------------------------------------: |
| Keep Talking and Nobody Explodes |    Fully functional    |                    /                     |
|       Waltz of the Wizard        |         Sound          |                 No video                 |
|          Job Simulator           | Video <br> Controllers |   Audio glitches <br> Physics glitches   |
|       I Expect You To Die        |           /            | Won't work without custom implementation |

# Future

Currently only a limited amount of Unity games actually functionally work.
<br> Unreal games will not work without further reverse engineering efforts.

Figuring out why certain games don't work is going to require A LOT of reverse engineering. <br>
(Mostly just incompatible API calls with Oculus & PICO, different GUID's, etc, that can not simply just be solved by using a proxy)

Why certain games don't work:

- With some games, a proprietary method is used by Oculus, that requires me to RE the Oculus SDK in massive detail.
- A custom implementation of the: Unity API and the Unreal API will have to be done. <br>
  Which includes RE'ing the OpenXR API that is used on PICO systems. <br> (On the plus side, most parts are open source)
