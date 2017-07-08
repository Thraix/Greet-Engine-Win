#pragma once

namespace greet { namespace event{
	class Event
	{
	public:
		enum EventType {
			MOUSE_PRESSED,
			MOUSE_RELEASED,
			MOUSE_MOVED,
			MOUSE_SCROLLED,
			KEY_PRESSED,
			KEY_RELEASED,
			KEY_TYPED
		};

	private:
		EventType m_type;

	protected:
		Event(EventType type);
	public:
		inline const EventType& getType() const { return m_type; }

	};
}}