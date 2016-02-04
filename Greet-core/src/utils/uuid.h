#pragma once

#include <string>
#include <random>
#include <time.h>
#include <greet_types.h>
namespace greet { namespace utils {
	class UUID
	{
		private:
			UUID* INSTANCE;
		
		public:
			uint128 getUUID() const;
				
		private:
			UUID();
			unsigned long long randomLong() const;
			uint128 randomInt128() const;
		public:
			static void init();
			static void destroy();
			static const UUID& getInstance() const;	
	};
}}
