#include <modules.h>
#include <thread>

Modules mods;
std::unordered_map<std::string, EventBinding> events;

bool wasPressed = false;

void Fly::init() {
    enabled = false;
    register_event(this, static_cast<void (Module::*)()>(&Fly::on_event), "Client-tick");
}

void Fly::toggle() {
    enabled = !enabled;
    if (enabled) {
        on_enable();
    } else {
        on_disable();
    }
}

void Fly::on_enable() {

}

void Fly::on_disable() {

}

void Fly::on_event() {
    if (enabled) {
        std::cout << "Fly module event call has ran" << std::endl;
        player.jump(env);
    }
}