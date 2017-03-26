#pragma once

namespace GrovePi {

	///<summary>The pins available to use.</summary>
	enum class Pin : uint8_t {
		Analog_0 = 0,
		Analog_1 = 1,
		Analog_2 = 2,
		Digital_2 = 2,
		Digital_3 = 3,
		Digital_4 = 4,
		Digital_5 = 5,
		Digital_6 = 6,
		Digital_7 = 7,
		Digital_8 = 8,
	};

	///<summary>The pin modes.</summary>
	enum class PinMode : uint8_t {
		Input = 0,
		Output = 1,
	};

	///<summary>DHT sensor types.</summary>
	enum class DHT_Type : uint8_t {
		DHT11 = 0,
		DHT22 = 1,
		DHT21 = 2,
		AM2301 = 3,
	};
}
