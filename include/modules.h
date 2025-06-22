#pragma once

#include <client.h>
#include <vector>
#include <unordered_map>
#include <functional>

class Module {
    public:
    std::string name;
    
    int key_code;
    bool enabled;
    
    virtual void init() = 0;
    virtual void toggle() = 0;
    virtual void on_enable() = 0;
    virtual void on_disable() = 0;
    virtual void on_event() = 0;
    
    Module(Player player) : player(player) {

    }
    
    protected:
    Player player;
};

typedef void (Module::*EventHandler)();

struct EventBinding {
    Module* instance;
    EventHandler handler;
};

extern std::unordered_map<std::string, EventBinding> events;

extern bool wasPressed;

inline void call_event(const std::string& sig, std::string key_map) {
    SHORT keyState = GetAsyncKeyState(key_map[0]);
    bool isPressed = (keyState & 0x80000) != 0;

    auto it = events.find(sig);
    if (it != events.end()) {
        if (wasPressed && !isPressed) {
            it->second.instance->toggle();
        }

        EventBinding& binding = events[sig];
        (it->second.instance->*it->second.handler)();
        wasPressed = isPressed;
    }
}

inline void register_event(Module* obj, EventHandler handler, const std::string& name) {
    events.insert({name, EventBinding {obj, handler}});
}

typedef std::vector<Module*> Modules;

extern Modules mods;

class Fly : public Module {
public:
    void init();
    void toggle();
    void on_enable();
    void on_disable();
    void on_event();

    Fly(Player plr) : Module(plr) {
        init();
    }
};