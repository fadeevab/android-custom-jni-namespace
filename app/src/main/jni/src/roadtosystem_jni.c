#include "roadtosystem_jni.h"

// http://androidxref.com/8.0.0_r4/xref/system/core/libnativeloader/include/nativeloader/dlext_namespaces.h
#include "dlext_namespaces.h"

#include <android/log.h>
#include <dlfcn.h>
#include <errno.h>

#define APPNAME "roadtosystem"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, __VA_ARGS__);

static const char *getLibPath(void) {
#ifndef __aarch64__
  return "/system/lib/";
#else
  return "/system/lib64/";
#endif
}

static const int getExportedNamespaceDiff(void) {
  // Hardcoded delta is different on different mobile phone models.
#ifndef __aarch64__
  return 0x4a430;
#else
  return 0x650e0;
#endif
}

static struct android_namespace_t *getAndroidNamespace() {
  struct android_namespace_t *ns = NULL;

#ifdef ANDROID11
  // It's a trick to find a private symbol android_get_exported_namespace.
  // `android_get_exported_namespace` is in libc.so, and its address can be found by
  // getting any public symbol (e.g. android_get_device_api_level) + some delta.

  struct android_namespace_t* (*android_get_exported_namespace)(const char*) =
      dlsym(RTLD_DEFAULT, "android_get_device_api_level");
  if (!android_get_exported_namespace) {
    LOGV("failed to get android_get_device_api_level\n");
    return NULL;
  }

  android_get_exported_namespace += getExportedNamespaceDiff();

  ns = android_get_exported_namespace("vndk");
#else
  const char *lib_path = getLibPath();

  ns = android_create_namespace(
    "trustme",
    lib_path,
    lib_path,
    ANDROID_NAMESPACE_TYPE_SHARED |
    ANDROID_NAMESPACE_TYPE_ISOLATED,
    "/system/:/data/:/vendor/",
    NULL);
#endif

  return ns;
}

JNIEXPORT jint JNICALL Java_com_example_android_jniapi_RoadToSystem_linkSystemLib(
  JNIEnv *env, jobject obj) {
  struct android_namespace_t *ns = getAndroidNamespace();

  if (!ns) {
    LOGV("failed to get namespace\n");
    return (jint)NULL;
  }

  const android_dlextinfo dlextinfo = {
      .flags = ANDROID_DLEXT_USE_NAMESPACE,
      .library_namespace = ns,
  };

  // Access granted
  void *so = android_dlopen_ext("libwifi-system-iface.so", RTLD_LOCAL | RTLD_NOW, &dlextinfo);

  // Comment out to check "access denied":
  //
  //   void *so = dlopen("libwifi-system.so", RTLD_LOCAL | RTLD_NOW);

  LOGV("Shared object handler: %p, errno: %d", so, errno);

  return (jint)so;
}
