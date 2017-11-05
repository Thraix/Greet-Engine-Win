#pragma once

#include <math/maths.h>
#include <internal/Greet_types.h>

namespace Greet {
	class KeyboardControl
	{
	public:
		
	private:
		vec2 velocity;
		float speed;
		bool yPos;
		bool yNeg;
		bool xPos;
		bool xNeg;
		uint yPosKey;
		uint yNegKey;
		uint xPosKey;
		uint xNegKey;

	public:
		KeyboardControl(uint xPosKey, uint xNegKey, uint yPosKey, uint yNegKey, float speed)
			:xPosKey(xPosKey), xNegKey(xNegKey),yPosKey(yPosKey),yNegKey(yNegKey), speed(speed)
		{
			yPos = false;
			yNeg = false;
			xPos = false;
			xNeg = false;
		}

		vec2 getVelocity()
		{
			velocity = vec2(0, 0);
			velocity.x += xPos ? speed : 0;
			velocity.x -= xNeg ? speed : 0;
			velocity.y += yPos ? speed : 0;
			velocity.y -= yNeg ? speed : 0;
			if(velocity.lengthSQ()!=0)
				velocity = velocity.normalize()*speed;
			return velocity;
		}

		void onInput(int key, bool pressed)
		{
			xPos = key == xPosKey ? pressed : xPos;
			xNeg = key == xNegKey ? pressed : xNeg;
			yPos = key == yPosKey ? pressed : yPos;
			yNeg = key == yNegKey ? pressed : yNeg;

		}
	};
}