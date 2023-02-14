#pragma once
#include "Bitmap.h"

class BitmapManager
{
public:
	int m_iCount;
	map<int, Bitmap*> m_List;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	static BitmapManager& GetInstance();

	// ���� �� �ε�
	int			Load(T_STR pszFileName);

	// �ߺ� �˻�
	int			CheckOverlap(T_STR pszFileName);
	Bitmap*		GetPtr(int iIndex);
private:
	BitmapManager();
	virtual ~BitmapManager();
};
#define I_BitmapManager BitmapManager::GetInstance()