#include <windows.h>

#include <iostream>

using namespace std;

class Light {
   public:
    void on() { cout << "Light is on" << endl; }
    void off() { cout << "Light is off" << endl; }
};

class GarageDoor {
   public:
    void up() { cout << "Garage Door is Open" << endl; }
    void down() { cout << "Garage Door is Closed" << endl; }
    void stop() { cout << "Garage Door is Stopped" << endl; }
    void lightOn() { cout << "Garage light is on" << endl; }
    void lightOff() { cout << "Garage light is off" << endl; }
};

class Command {
   public:
    virtual void execute(){};
    virtual void undo(){};
};

class LightOnCommand : public Command {
   private:
    Light* light;

   public:
    LightOnCommand(Light* light) { this->light = light; }
    void execute() { light->on(); }
    void undo() { light->off(); }
};

class LightOffCommand : public Command {
   private:
    Light* light;

   public:
    LightOffCommand(Light* light) { this->light = light; }
    void execute() { light->off(); }
    void undo() { light->on(); }
};

class GarageDoorUpCommand : public Command {
   private:
    GarageDoor* garageDoor;

   public:
    GarageDoorUpCommand(GarageDoor* garageDoor) { this->garageDoor = garageDoor; }
    void execute() { garageDoor->up(); }
    void undo() { garageDoor->down(); }
};

class GarageDoorDownCommand : public Command {
   private:
    GarageDoor* garageDoor;

   public:
    GarageDoorDownCommand(GarageDoor* garageDoor) { this->garageDoor = garageDoor; }
    void execute() { garageDoor->down(); }
    void undo() { garageDoor->up(); }
};

class NoCommand : public Command {
   public:
    void execute() {}
    void undo() {}
};

class RemoteControl {
   private:
    static const int maxCommandCount = 7;
    Command* onCommands[maxCommandCount];
    Command* offCommands[maxCommandCount];
    Command* undoCommand;

   public:
    RemoteControl() {
        Command* noCommand = new NoCommand();
        undoCommand = new NoCommand;

        for (int i = 0; i < 7; i++) {
            onCommands[i] = noCommand;
            offCommands[i] = noCommand;
        }
    }

    void setCommand(int slot, Command* onCommand, Command* offCommand) {
        onCommands[slot] = onCommand;
        offCommands[slot] = offCommand;
    }
    void onButtonWasPushed(int slot) {
        onCommands[slot]->execute();

        undoCommand = onCommands[slot];
    }

    void offButtonWasPushed(int slot) {
        offCommands[slot]->execute();

        undoCommand = offCommands[slot];
    }

    void undoButtonWasPushed(int slot) {
        undoCommand->undo();
    }
};

int main(int argc, char const* argv[]) {
    RemoteControl* remoteControl = new RemoteControl();
    // создание устройств
    Light* light = new Light();
    GarageDoor* garageDoor = new GarageDoor();
    // создание команд
    LightOnCommand* lightOn = new LightOnCommand(light);
    LightOffCommand* lightOff = new LightOffCommand(light);
    GarageDoorUpCommand* garageDoorUp = new GarageDoorUpCommand(garageDoor);
    GarageDoorDownCommand* garageDoorDown = new GarageDoorDownCommand(garageDoor);
    // связь команд с кнопками
    remoteControl->setCommand(0, lightOn, lightOff);
    remoteControl->setCommand(1, garageDoorUp, garageDoorDown);
    // нажатия кнопок
    remoteControl->onButtonWasPushed(0);
    remoteControl->offButtonWasPushed(0);
    remoteControl->undoButtonWasPushed(0);
    remoteControl->onButtonWasPushed(1);
    remoteControl->offButtonWasPushed(1);
    return 0;
}
