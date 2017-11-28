#include "UUID.h"
namespace Greet {

	UUID* UUID::s_instance;

	UUID::UUID()
	{
		srand(time(0));
		m_current = rand();
	}

	uint UUID::GetUUID()
	{
		return m_current++;
	}


	void UUID::Init()
	{
		s_instance = new UUID();
	}

	void UUID::CleanUp()
	{
		delete s_instance;
	}
}