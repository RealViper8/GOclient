#include <client.h>
#include <modules.h>

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

Player::~Player() {
    // env->DeleteLocalRef(player)
}

static WNDPROC window_proc;

LRESULT CALLBACK h_WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_KEYDOWN) {

    }

    if (uMsg == WM_KEYUP) {
        // key up
    }

    return CallWindowProc(window_proc, hWnd, uMsg, wParam, lParam);
}

void setup_wndproc() {

}

void client_main(HMODULE hModule) {
    Player plr(hModule);

    Fly* fly = new Fly {plr};
    // fly->enabled = true;
    while (true) {
        // plr.jump(env);
        call_event("Client-tick", "Y");
        
        if (GetAsyncKeyState(VK_END)) {
            break;
        }

        Sleep(10);
    }

    std::cout << "bye bye..." << std::endl;
    HWND window = FindWindowA(NULL, "Minecraft 1.21.6");
    SetWindowLongPtrA(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(window_proc));

    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}