#pragma once
#include "CoreSTD.h"

class BoundingBox
{
private:
	RECT		m_rtBoundingBox;
public:
	//--------------------------------------------------------------------------------------
	// Set Function
	//--------------------------------------------------------------------------------------
	void		SetBoundingBoxInfo(RECT rtBoundingbox);
	//--------------------------------------------------------------------------------------
	// Get Function
	//--------------------------------------------------------------------------------------
	RECT		GetBoundingBoxInfo();
public:
	BoundingBox();
	virtual ~BoundingBox();
};

