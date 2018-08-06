# Accessubg System Private API Through the Android Linker Namespace

## Build

```bash
# Set up `local.properties`
echo "sdk.dir=/path/to/android-sdk-linux" > local.properties
echo "ndk.dir=/path/to/android-ndk-r17b" >> local.properties

./gradlew build
```

## Install

```bash
./gradlew installArm8Debug
```

## Test

Launch "roadtosystem" from application list of your device. You should see
**Access granted** in a case of success.
