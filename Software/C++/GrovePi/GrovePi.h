#pragma once
#include <string>
#include <chrono>
#include <thread>
#include <cstdint>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "GrovePiPins.h"

namespace GrovePi {
	class GrovePi {
	public:
		GrovePi();
		~GrovePi();

		///<summary>Read the value from a digital pin, either HIGH or LOW.</summary>
		///<param name='pin'>The pin to read from.</param>
		///<return>The logic state of the pin.</return>
		int DigitalRead(Pin pin);
		///<summary>Write a HIGH or LOW to a digital pin</summary>
		///<param name='pin'>The pin to write to.</param>
		///<param name='data'>The logic value to set the pin.</param>
		void DigitalWrite(Pin pin, uint8_t data);
		///<summary>Read the value from an analog pin</summary>
		///<param name='pin'>The pin to read from.</param>
		///<return>The value of the pin.</return>
		int AnalogRead(Pin pin);
		///<summary>Writes an analog value (PWM wave) to a pin</summary>
		///<param name='pin'>The pin to write to.</param>
		///<param name='data'>The value to set the pin.</param>
		void AnalogWrite(Pin pin, uint8_t data);
		///<summary>Configure a pin to behave either as input or output</summary>
		///<param name='pin'>The pin to configure.</param>
		///<param name='mode'>The mode of the pin.</param>
		void ConfigurePinMode(Pin pin, PinMode mode);
		///<summary>Get the firmware version of the software running on the GrovePi</summary>
		///<return>The firmware version of the GrovePi</return>
		std::string FirmwareVersion();
		///<summary>Read the temperature and humidity from a DHT sensor</summary>
		///<param name='pin'>The pin to write to.</param>
		///<param name='sensor'>The type of DHT sensor.</param>
		///<param name='temperature'>Returns the current temperature of the sensor.</param>
		///<param name='humidity'>Returns the current humidity of the sensor.</param>
		void DigitalHumidityTemperatureRead(Pin pin, DHT_Type sensor, float & temperature, float & humidity);

	private:
		///<sumary>Command number.</sumary>
		enum class Command : uint8_t {
			DigitalRead = 1,
			DigitalWrite = 2,
			AnalogRead = 3,
			AnalogWrite = 4,
			PinMode = 5,
			FirmwareVersion = 8,
			DHTRead = 40,
		};

		///<sumary>Number of bytes written by the firmware (based on v1.2.7).</sumary>
		enum class ReadBytes : int {
			None = 0,
			DigitalRead = 1,
			AnalogRead = 3,
			FirmwareVersion = 4,
			DHTRead = 9,
			Max = 32,
		};

		///<sumary>Amount of thime to wait (in ms) before reading data after write.</sumary>
		enum class ReadDelay : unsigned int {
			None = 0,
			Standard = 100,
			DHTRead = 600,
		};

		///<sumary>Unused defintion for when write does not need all 4 bytes.</sumary>
		const uint8_t UNUSED = 0;

		///<sumary>Write a command then read the response.</sumary>
		std::vector<uint8_t> Query(Command command, uint8_t byte1, uint8_t byte2, uint8_t byte3, ReadBytes readBytes, ReadDelay readDelay_ms);

		///<summary>Go to sleep (wait) for a period of time<summary>
		inline void Delay_ms(unsigned int milliseconds) {
			std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
		};

		int i2cFd;
		int i2cAddress = 0x04;
		std::string i2cDevice = "/dev/i2c-1";

	};
}

