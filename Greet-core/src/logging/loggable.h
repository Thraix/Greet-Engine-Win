#pragma once
#include <string>
namespace greet { namespace logging {
	class Loggable
	{
	public:
		Loggable(){}
		virtual ~Loggable(){}
		virtual std::string toString() const {return "Loggable";}
	};
}}
