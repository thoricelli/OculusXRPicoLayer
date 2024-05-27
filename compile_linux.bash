# Add the NDK /bin/ to your PATH.
clang="aarch64-linux-android30-clang"

mkdir -p out
$clang -fdeclspec -gdwarf -fPIC -shared -o out/libOculusXRPlugin.so lib/libPxrPlatform.so lib/libpxr_api.so OculusXRPlugin.c
$clang -fdeclspec -gdwarf -fPIC -shared -o out/libovrplatformloader.so lib/libpxrplatformloader.so OvrPlatformLoader.c
$clang -fdeclspec -gdwarf -fPIC -shared -o out/libOVRPlugin.so lib/libpxr_api.so OVRPlugin.c