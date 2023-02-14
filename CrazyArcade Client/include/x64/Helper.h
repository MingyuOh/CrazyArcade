#pragma once

template<class T>
class Singleton
{
public:
	static T& GetInstance()
	{
		static T thisSigletonInstance;
		return thisSigletonInstance;
	}
};

static bool RectInequality(RECT rt1, RECT rt2)
{
	if (rt1.left == rt2.left 
		&& rt1.top == rt2.top 
		&& rt1.right == rt2.right 
		&& rt1.bottom == rt2.bottom)
	{
		return true;
	}
	return false;
}