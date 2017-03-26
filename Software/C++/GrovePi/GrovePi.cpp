#include "GrovePi.h"
namespace GrovePi {

	GrovePi::GrovePi() {
		i2cFd = open(i2cDevice.c_str(), O_RDWR);
		if (i2cFd) {
			;// Throw error here
		}
		if (ioctl(i2cFd, I2C_SLAVE, i2cAddress) < 0) {
			;//throw error here
		}
	}

	GrovePi::~GrovePi() {
		close(i2cFd);
	}

	int GrovePi::DigitalRead(Pin pin)
	{
		std::vector<uint8_t> readBuffer = Query(Command::DigitalRead, (uint8_t)pin, UNUSED, UNUSED, ReadBytes::DigitalRead, ReadDelay::None);
		return readBuffer[0];
	}

	void GrovePi::DigitalWrite(Pin pin, uint8_t data) {
		Query(Command::DigitalWrite, (uint8_t)pin, data, UNUSED, ReadBytes::None, ReadDelay::None);
	}

	int GrovePi::AnalogRead(Pin pin)
	{
		std::vector<uint8_t> readBuffer = Query(Command::AnalogRead, (uint8_t)pin, UNUSED, UNUSED, ReadBytes::AnalogRead, ReadDelay::None);
		return ((readBuffer[1] * 256) + readBuffer[0]);
	}

	void GrovePi::AnalogWrite(Pin pin, uint8_t data) {
		Query(Command::DigitalWrite, (uint8_t)pin, data, UNUSED, ReadBytes::None, ReadDelay::None);
	}

	void GrovePi::ConfigurePinMode(Pin pin, PinMode mode) {
		Query(Command::PinMode, (uint8_t)pin, (uint8_t)mode, UNUSED, ReadBytes::None, ReadDelay::None);
	}

	std::string GrovePi::FirmwareVersion() {
		std::vector<uint8_t> localReadBuffer = Query(Command::FirmwareVersion, UNUSED, UNUSED, UNUSED, ReadBytes::FirmwareVersion, ReadDelay::Standard);
		std::string version = std::to_string(localReadBuffer[1]) + "." + std::to_string(localReadBuffer[2]) + "." + std::to_string(localReadBuffer[3]);
		return version;
	}

	void GrovePi::DigitalHumidityTemperatureRead(Pin pin, DHT_Type sensor, float & temperature, float & humidity) {
		std::vector<uint8_t> readBuffer = Query(Command::DHTRead, (uint8_t)pin, (uint8_t)DHT_Type::DHT22, UNUSED, ReadBytes::DHTRead, ReadDelay::DHTRead);
		union {
			uint8_t bytes[4];
			float f;
		}	
		temperatureUnion = { .bytes = { readBuffer[1], readBuffer[2], readBuffer[3], readBuffer[4] } },
		humidityUnion = { .bytes = { readBuffer[5], readBuffer[6], readBuffer[7], readBuffer[8] } };
		temperature = temperatureUnion.f;
		humidity = humidityUnion.f;
	}

	std::vector<uint8_t> GrovePi::Query(Command command, uint8_t byte1, uint8_t byte2, uint8_t byte3, ReadBytes readBytes, ReadDelay readDelay_ms) {
		const int writeSize = 4;
		uint8_t writeBuffer[writeSize] = { (uint8_t)command, byte1, byte2, byte3 };
		int writeResult = write(i2cFd, writeBuffer, writeSize);
		Delay_ms((unsigned int)readDelay_ms);
		std::vector<uint8_t> readBuffer((int)readBytes);
		if (readBytes != ReadBytes::None) {
			int readResults = read(i2cFd, &readBuffer[0], (int)readBytes);
		}
		return readBuffer;
	}

}
