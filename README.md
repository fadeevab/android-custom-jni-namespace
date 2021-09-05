# Accessing System Private API Through the Android Linker Namespace

## Precondition

Install Android SDK.

## Build

For Android 11, you should find `getExportedNamespaceDiff` in `roadtosystem_jni.c` and adjust a hardcoded delta.

```bash
# Set up `local.properties`
echo "sdk.dir=/path/to/android-sdk-linux" > local.properties

./gradlew build
```

## Install

```bash
# Install on Android 8
./gradlew installArm8MinApi23Debug

# Install on Android 11
./gradlew installArm8MinApi30Debug

```

## Test

Launch "roadtosystem" from application list of your device. You should see
**Access granted** in a case of success.
