#pragma once

#include <Windows.h>
#include <iostream>

#include <jni.h>

extern JavaVM* vm;
extern JNIEnv* env;

void client_main(HMODULE hModule);

class Player {
    Player();
    static void jump(JNIEnv* env);
private:
    jobject player;
};

void PlayerJump(JNIEnv* env);