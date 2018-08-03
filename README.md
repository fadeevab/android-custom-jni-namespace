# Demo of Android linker namespace design

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

Launch roadtosystem from your device's desktop. You should see "No exception: access granted" in a case of success.
