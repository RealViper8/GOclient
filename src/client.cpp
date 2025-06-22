#include <client.h>

Player::Player(HMODULE hModule) {
    jclass minecraftClass = env->FindClass("fud");
    jmethodID getMinecraft = env->GetStaticMethodID(minecraftClass, "R", "()Lfud;");
    jobject mc = env->CallStaticObjectMethod(minecraftClass, getMinecraft);
    
    jfieldID playerField = env->GetFieldID(minecraftClass, "t", "Lgwh;");
    player = env->GetObjectField(mc, playerField);
    
    if (player == NULL) {
        while (player == NULL) {
            std::cout << "\nError: player is null musst schon ingame sein blud..." << std::endl;
            std::cout << "Versuche erneut in ";

            if (GetAsyncKeyState(VK_END)) {
                std::cout << "bye bye..." << std::endl;
                FreeConsole();
                FreeLibraryAndExitThread(hModule, 0);
            }

            for (int x = 5; x > 0; x--) {
                std::cout << " " << x << "..";
                Sleep(1000);
            }
    
            std::cout << "..." << std::endl;
            player = env->GetObjectField(mc, playerField);
        }
    }

    player_class = env->GetObjectClass(player);
}

void Player::jump(JNIEnv* env) {
    jmethodID jumpMethod = env->GetMethodID(player_class, "s", "()V");
    env->CallVoidMethod(player, jumpMethod);
}

void client_main(HMODULE hModule) {
    Player plr(hModule);
    while (true) {
        plr.jump(env);
        Sleep(50);

        if (GetAsyncKeyState(VK_END)) {
            break;
        }
    }

    std::cout << "bye bye..." << std::endl;
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}