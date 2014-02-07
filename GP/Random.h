#pragma once

// Forward declaration of sf::Time
namespace sf {
	class Time;
}

namespace Random {
	unsigned int getSeed();
	void setSeed(unsigned int seed);
	void setRandomSeed();

	int between(int min, int max);
	float betweenf(float min, float max);
	sf::Time betweenTime(sf::Time min, sf::Time max);
}