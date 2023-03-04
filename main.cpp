#include <iostream>
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual void handleEvent(float temperature, float humidity, float pressure) = 0;
};

class Client : public Observer {
    int id;
public:
    Client(int id) : id(id) {}
    void handleEvent(float temperature, float humidity, float pressure) override {
        std::cout << "Client (with id " << id << ") information:\nTemperature: " << temperature
                  << "\nHumidity: " << humidity
                  << "\nPressure: " << pressure
                  << "\n";
    }
};

class Subject {
public:
    virtual void addObserver(Observer *observer) = 0;
    virtual void removeObserver(Observer *observer) = 0;
    virtual void notifyObservers() = 0;
};

class WeatherStation : public Subject {
    std::vector<Observer *> observers; // observers

    float temperature = 0.0f;
    float humidity = 0.0f;
    float pressure = 0.0f;

public:
    void addObserver(Observer *observer) override {
        observers.push_back(observer);
    }
    void removeObserver(Observer *observer) override {
        auto iterator = std::find(observers.begin(), observers.end(), observer);

        if (iterator != observers.end()) {
            observers.erase(iterator);
        }
    }
    void notifyObservers() override {
        for (Observer *observer : observers) {
            observer->handleEvent(temperature, humidity, pressure);
        }
    }
    void setState(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        std::cout << std::endl;
        notifyObservers();
    }

};

int main() {
    WeatherStation weatherStation;
    Client Client1(1), Client2(2), Client3(3);

    float temperature = 18.427834, humidity = 55.143425, pressure = 740.424;

    weatherStation.addObserver(&Client1);
    weatherStation.addObserver(&Client2);
    weatherStation.addObserver(&Client3);

    weatherStation.setState(temperature, humidity, pressure);

    weatherStation.removeObserver(&Client2);

    temperature = 23.52542, humidity = 59.235423, pressure = 741.524;

    weatherStation.setState(temperature, humidity, pressure);

    return 0;
}
