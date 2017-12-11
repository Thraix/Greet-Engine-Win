#include "UUID.h"
namespace Greet {

	UUID UUID::s_instance;

	UUID::UUID()
	{
		srand(time(0));
		m_current = GetRandomNumber();
	}

	uint UUID::GetUUID()
	{
		uint uuid = m_current;

		m_current = GenNewUUID();
		return uuid;
	}

	uint UUID::GetRandomNumber()
	{
		return (rand() + 1) * (rand() + 1);
	}

	uint UUID::GenNewUUID()
	{
		uint i = 1000;
		uint number;
		while (i--)
		{
			number = GetRandomNumber();
			if (number != 0 && m_usedUUID.count(number) > 0)
			{
				m_usedUUID.insert(number);
				return number;
			}
		}
		return 0;
	}
}