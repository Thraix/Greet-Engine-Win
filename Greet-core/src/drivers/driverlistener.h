#pragma once


namespace greet { namespace drivers {

	class DriverListener
	{
	public:
		virtual void onFinished() = 0;
	};

}}