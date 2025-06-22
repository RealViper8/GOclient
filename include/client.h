#pragma once

#include <Windows.h>
#include <iostream>

#include <jni.h>

extern JavaVM* vm;
extern JNIEnv* env;

void client_main(HMODULE hModule);

class Player {
public:
    Player(HMODULE hModule);
    ~Player();
    void jump(JNIEnv* env);
private:
    jobject player;
    jclass player_class;
};