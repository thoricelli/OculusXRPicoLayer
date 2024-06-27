# Add the NDK /bin/ to your PATH.
clang="${NDK_CLANG:-aarch64-linux-android30-clang++}"

mkdir -p out
$clang -fdeclspec -gdwarf -fPIC -shared -o out/libOculusXRPlugin.so libPxrPlatform.so libpxr_api.so OculusXRPlugin.cpp
$clang -fdeclspec -gdwarf -fPIC -shared -o out/libovrplatformloader.so libpxrplatformloader.so libpxr_api.so OvrPlatformLoader.cpp
$clang -fdeclspec -gdwarf -fPIC -shared -o out/libOVRPlugin.so libpxr_api.so libPxrPlatform.so OVRPlugin.cpp