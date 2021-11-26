#include <iostream>
#include <fstream>

#include "carcontroller.h"

using namespace std;

ofstream log;
bool needToClose = false;

void myButtonCallback(struct SteeringWheelButtons buttons){
    cout << "Louder  "<< buttons.Louder << "\n";
    cout << "Quieter "<< buttons.Quieter<< "\n";
    cout << "Up      "<< buttons.Up     << "\n";
    cout << "Down    "<< buttons.Down   << "\n";
    cout << "Mobile  "<< buttons.Mobile << "\n";
    cout << "Voice   "<< buttons.Voice  << "\n";
    cout << "Star    "<< buttons.Star   << "\n";
    cout << "Diamond "<< buttons.Diamond<< "\n";
    cout << "\n";
    if(buttons.Star)
        if (!log.is_open())
        {
            needToClose = false;
            log.open("/home/root/log.txt");
        }
        else
            cout << "Already running!\n";
    if(buttons.Diamond)
       needToClose = true;
}

void myPeriadicalCallback(CarController* c){
    for(int i=0 ;i < c->values.size() ; i++)
    {
        switch (c->values[i].type)
        {
        case CarEventType::WaterTemp:
        case CarEventType::Gear:
        case CarEventType::RPM:
        case CarEventType::Speed:
           if(log.is_open())
                log << c->values[i].convertCallback(c->values[i].data) <<";";
            break;
        }
    }
    if(log.is_open())
        log<<"\n";
    if(needToClose)
        log.close();
}

int main(void){
    cout << "Hello World!" << endl;
    CarController cc;
    cc.addButtonHandler(myButtonCallback);
    cc.addHandler(myPeriadicalCallback);
    cc.open("can0");
    cc.run();
    return 0;
}
