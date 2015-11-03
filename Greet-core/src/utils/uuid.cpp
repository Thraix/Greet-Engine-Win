#include "uuid.h"
namespace greet {namespace utils {

	UUID* UUID::s_instance;

	UUID::UUID()
	{
		srand(time(0));
		m_current = rand();
	}

	uint UUID::getUUID()
	{
		return m_current++;
	}


	void UUID::init()
	{
		s_instance = new UUID();
	}

	void UUID::cleanUp()
	{
		delete s_instance;
	}
}}