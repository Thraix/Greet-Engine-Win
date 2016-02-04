#include "uuid.h"

namespace greet { namespace utils {

	UUID* UUID::INSTANCE;

	UUID::UUID()
	{
		srand(time(0);
	}

	uint128 UUID::randomLong() const
	{
		return (unsigned long long )rand() << (sizeof(int) * 8) | rand();
	}

	uint128 UUID::randomInt128() const 
	{
		return (uint128) randomLong() << (sizeof(long long) * 8) | randomLong();
	}
	
	uint128 UUID::getUUID() const 
	{
		return randomInt128();
	}	

	void UUID::init()
	{
		INSTANCE = new UUID();
	}

	const UUID& getInstance() const
	{
		return *INSTANCE;
	}

	void UUID::destroy()
	{
		delete INSTANCE;
	}	
}}
