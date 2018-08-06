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

JNIEXPORT jint JNICALL Java_com_example_android_jniapi_RoadToSystem_linkSystemLib(
        JNIEnv *env, jobject obj) {
  const char *lib_path = getLibPath();

  struct android_namespace_t *ns = android_create_namespace(
      "trustme",
      lib_path,
      lib_path,
      ANDROID_NAMESPACE_TYPE_SHARED |
      ANDROID_NAMESPACE_TYPE_ISOLATED,
      "/system/:/data/:/vendor/",
      NULL);

  const android_dlextinfo dlextinfo = {
    .flags = ANDROID_DLEXT_USE_NAMESPACE,
    .library_namespace = ns,
  };

  // Access granted
  void *so = android_dlopen_ext("libwifi-system.so", RTLD_LOCAL | RTLD_NOW, &dlextinfo);

  // Comment out to check "access denied":
  //
  //   void *so = dlopen("libwifi-system.so", RTLD_LOCAL | RTLD_NOW);

  LOGV("Shared object handler: %p, errno: %d", so, errno);

  return (jint)so;
}
