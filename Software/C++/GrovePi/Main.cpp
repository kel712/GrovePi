#include <iostream>
#include "GrovePi.h"

int main()
{
	GrovePi::GrovePi grovePi;
	std::cout << "Firmware Version: " << grovePi.FirmwareVersion() << std::endl;
	float temerature, humidity;
	GrovePi::Pin dht = GrovePi::Pin::Digital_3;
	grovePi.DigitalHumidityTemperatureRead(dht, GrovePi::DHT_Type::DHT22, temerature, humidity);
	std::cout << "Temperature: " << temerature << ", Humidity: " << humidity << std::endl;

	GrovePi::Pin led = GrovePi::Pin::Digital_4;
	grovePi.ConfigurePinMode(led, GrovePi::PinMode::Output);
	grovePi.DigitalWrite(led, 1);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	grovePi.DigitalWrite(led, 0);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	grovePi.DigitalWrite(led, 1);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	grovePi.DigitalWrite(led, 0);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	return 0;
}