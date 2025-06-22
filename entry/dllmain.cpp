
#include <Windows.h>
#include <iostream>
#include <client.h>

#include <jni.h>
JavaVM* vm;
JNIEnv* env = NULL;

FILE* pFile = nullptr;

void init(HMODULE hModule) {
    AllocConsole();
    freopen_s(&pFile, "CONOUT$", "w", stdout);
    std::cout << "GO Client has been injected !" << std::endl;

    jsize vmCount;
    if (JNI_GetCreatedJavaVMs(&vm, 1, &vmCount) != JNI_OK || vmCount == 0) {
        std::cout << "JavaVM wurde nicht gefunden..." << std::endl;
        return;
    }

    jint res = vm->GetEnv((void**)&env, JNI_VERSION_1_8);
    if (res == JNI_EDETACHED) {
        res = vm->AttachCurrentThread((void**)&env, nullptr);
    }

    if (res != JNI_OK) {
        std::cout << "JNI injection ist fehlgeschlagen..." << std::endl;
        return;
    }

    if (env != nullptr) {
        std::cout << "JNI injection hat funktioniert !" << std::endl;
        client_main(hModule);
    }
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            CreateThread(0,0, (LPTHREAD_START_ROUTINE)init, hModule, 0, 0);
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }

    return TRUE;
}