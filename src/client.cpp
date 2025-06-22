#include <client.h>

Player::Player() {
    
}

void Player::jump(JNIEnv* env) {

}

void PlayerJump(JNIEnv* env) {
    jclass minecraftClass = env->FindClass("fud");
    jmethodID getMinecraft = env->GetStaticMethodID(minecraftClass, "R", "()Lfud;");
    jobject mc = env->CallStaticObjectMethod(minecraftClass, getMinecraft);

    jfieldID playerField = env->GetFieldID(minecraftClass, "t", "Lgwh;");
    jobject player = env->GetObjectField(mc, playerField);
    if (player == NULL) {
        std::cout << "Error: player is null musst schon ingame sein blud..." << std::endl;

        std::cout << "Versuche erneut in ";
        for (int x = 5; x > 0; x--) {
            Sleep(1000);
            std::cout << x;
        }
        std::cout << std::endl;
        return;
    }

    jclass player_class = env->GetObjectClass(player);
    jmethodID jumpMethod = env->GetMethodID(player_class, "s", "()V");
    env->CallVoidMethod(player, jumpMethod);
}

void client_main(HMODULE hModule) {
    while (true) {
        PlayerJump(env);
        Sleep(50);

        if (GetAsyncKeyState(VK_END)) {
            break;
        }
    }

    std::cout << "bye bye..." << std::endl;
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}