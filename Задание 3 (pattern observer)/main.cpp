#include <iostream>
#include <list>
#include <string>

using namespace std;

class Subject;
class Observer;
class DisplayElement;
class ForecastDisplay;
class WeatherData;
class CurrentConditionsDisplay;

class Observer {
   public:
    virtual ~Observer() {}
    virtual void update(float temp, float humidity, float pressure) = 0;
};

class Subject {
   public:
    virtual void registerObserver(Observer* o) = 0;
    virtual void removeObserver(Observer* o) = 0;
    virtual void notifyObservers() = 0;
};

class DisplayElement {
   public:
    virtual void display() = 0;
};

class WeatherData : Subject {
   private:
    list<Observer*> observers;
    float temperature, humidity, pressure;

   public:
    ~WeatherData() {
        for (auto& element : observers) delete element;
    }
    void registerObserver(Observer* o) { observers.push_back(o); }
    void removeObserver(Observer* o) { observers.remove(o); }
    void notifyObservers() {
        for (auto& observer : observers) observer->update(temperature, humidity, pressure);
    }
    void measurementsChanged() { notifyObservers(); }
    void setMeasurements(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanged();
    }
};

class CurrentConditionsDisplay : Observer, DisplayElement {
   private:
    float temperature, humidity;
    WeatherData* weatherData;

   public:
    CurrentConditionsDisplay(WeatherData* weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }
    void update(float temperature, float humidity, float pressure) override {
        this->temperature = temperature;
        this->humidity = humidity;
        display();
    }
    void display() override {
        cout << "Current conditions: " << temperature << "F degrees and " << humidity << "% humidity" << endl;
    }
};

class ForecastDisplay : public Observer, DisplayElement {
   private:
    float currentPressure = 29.92;
    float lastPressure;
    WeatherData* weatherData;

   public:
    ForecastDisplay(WeatherData* weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }
    void update(float temp, float humidity, float pressure) override {
        lastPressure = currentPressure;
        currentPressure = pressure;
        display();
    }
    void display() override {
        cout << "Forecast: " << endl;
        if (currentPressure > lastPressure) {
            cout << "Improving weather on the way!" << endl;
        } else if (currentPressure == lastPressure) {
            cout << "More of the same" << endl;
        } else if (currentPressure < lastPressure) {
            cout << "watch out for cooler, rainy weather" << endl;
        }
    }
};

int main(int argc, char const* argv[]) {
    WeatherData* weatherData = new WeatherData;
    ForecastDisplay* fd = new ForecastDisplay(weatherData);
    CurrentConditionsDisplay* ccd = new CurrentConditionsDisplay(weatherData);

    weatherData->setMeasurements(80, 65, 30.4);
    weatherData->setMeasurements(82, 70, 29.2);
    weatherData->setMeasurements(78, 90, 29.2);
    weatherData->removeObserver(fd);
    weatherData->setMeasurements(62, 90, 28.1);

    delete ccd;
    return 0;
}
