#include <jni.h>
#include <string>
#include <android/log.h>
#include <cstdlib>
#include <cstring>

#define LOG_TAG "AppIntegrityChecker"
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" {

JNIEXPORT jboolean JNICALL
Java_com_example_myapp_MainActivity_checkIntegrity(JNIEnv *env, jobject instance) {

    jclass clazz = env->GetObjectClass(instance);
    jmethodID methodId = env->GetMethodID(clazz, "getPackageName", "()Ljava/lang/String;");
    jstring jPackageName = (jstring) env->CallObjectMethod(instance, methodId);
    const char *packageName = env->GetStringUTFChars(jPackageName, NULL);

    // Expected hash of the app's signature
    const char *expectedHash = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";

    // Get the app's signature
    jclass contextClass = env->GetObjectClass(instance);
    jmethodID methodId_getPackageManager = env->GetMethodID(contextClass,
                                                             "getPackageManager",
                                                             "()Landroid/content/pm/PackageManager;");
    jobject packageManager = env->CallObjectMethod(instance, methodId_getPackageManager);

    jclass packageManagerClass = env->GetObjectClass(packageManager);
    jmethodID methodId_getPackageInfo = env->GetMethodID(packageManagerClass,
                                                         "getPackageInfo",
                                                         "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject packageInfo = env->CallObjectMethod(packageManager,
                                                methodId_getPackageInfo,
                                                jPackageName,
                                                env->GetStaticIntField(packageManagerClass,
                                                                       env->GetStaticFieldID(packageManagerClass,
                                                                                             "GET_SIGNATURES",
                                                                                             "I")));

    jclass packageInfoClass = env->GetObjectClass(packageInfo);
    jfieldID fieldId_signatures = env->GetFieldID(packageInfoClass,
                                                  "signatures",
                                                  "[Landroid/content/pm/Signature;");
    jobjectArray signatures = (jobjectArray) env->GetObjectField(packageInfo, fieldId_signatures);

    jobject signature = env->GetObjectArrayElement(signatures, 0);

    jclass signatureClass = env->GetObjectClass(signature);
    jmethodID methodId_toByteArray = env->GetMethodID(signatureClass,
                                                      "toByteArray",
                                                      "()[B");
    jbyteArray signatureBytes = (jbyteArray) env->CallObjectMethod(signature, methodId_toByteArray);
    jbyte *signatureBytesPtr = env->GetByteArrayElements(signatureBytes, NULL);
    int signatureBytesLength = env->GetArrayLength(signatureBytes);

    // Compute the SHA-256 hash of the signature
    unsigned char sha256[32];
    SHA256((unsigned char *) signatureBytesPtr, signatureBytesLength, sha256);

    // Compare the hash with the expected hash
    bool integrity = (std::memcmp(expectedHash, sha256, 32) == 0);

    // Release the resources
    env->ReleaseStringUTFChars(jPackageName, packageName);
    env->ReleaseByteArrayElements(signatureBytes, signatureBytesPtr, JNI_ABORT);

    return (jboolean) integrity;
}

}
