#pragma once

namespace greet { namespace event{
	class Event
	{
	public:
		enum Type {
			MOUSE_PRESSED,
			MOUSE_RELEASED,
			MOUSE_MOVED
		};

	private:
		Type m_type;

	protected:
		Event(Type type);
	public:
		inline const Type& getType() const { return m_type; }

	};
}}