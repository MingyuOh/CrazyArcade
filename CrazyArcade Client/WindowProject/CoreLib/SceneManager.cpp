#include "SceneManager.h"

int g_iPlayerNumber = -1;
int g_iDropPlayerNumber = -1;

//--------------------------------------------------------------------------------------
// Update resources
//--------------------------------------------------------------------------------------
bool SceneManager::UpdateResources()
{
	return true;
}

//--------------------------------------------------------------------------------------
// Update render position
//--------------------------------------------------------------------------------------
void SceneManager::UpdateRenderPosition()
{
	// Set boundingbox
	RECT rtMapRenderBoundingBox;
	rtMapRenderBoundingBox.left = 0;
	rtMapRenderBoundingBox.top = 0;
	rtMapRenderBoundingBox.right = g_rtClient.right;
	rtMapRenderBoundingBox.bottom = g_rtClient.bottom;

	POINT_F position;
	position.fX = 0.0f;
	position.fY = 0.0f;

	SetRenderPosition(position);
}

//--------------------------------------------------------------------------------------
// Executes Init once when the scene is called
//--------------------------------------------------------------------------------------
bool SceneManager::ExecuteInit()
{
	if (m_bInit == false)
	{
		Init();
		m_bInit = true;
		return true;
	}

	return false;
}

HWND SceneManager::GetEditBox(T_STR szLargeCategory, T_STR szSmallCartegory)
{
	for (auto& editList : m_hEditList)
	{
		if (editList.first == szLargeCategory)
		{
			for (auto& edit : editList.second)
			{
				if (edit.first == szSmallCartegory)
				{
					return edit.second;
				}
			}
		}
	}
	return NULL;
}

//--------------------------------------------------------------------------------------
// Developer redefinition function
//--------------------------------------------------------------------------------------
bool SceneManager::Init()
{
	m_FadeInOut.SetOffScreenDC(GetOffScreenDC());
	m_FadeInOut.Create();
	return true;
}

bool SceneManager::Frame()
{
	return true;
}

bool SceneManager::Render()
{
	return true;
}

bool SceneManager::Release()
{
	Object::Release();

	m_FadeInOut.Release();

	for (auto& editBoxList : m_hEditList)
	{
		for (auto& editBox : editBoxList.second)
		{
			editBox.first = _T("");
		}
		editBoxList.second.clear();
	}
	m_hEditList.clear();
	m_hListBoxList.clear();
	m_hButtonList.clear();

	for (auto& buttonList : m_ButtonList)
	{
		for (auto& button : buttonList.second)
		{
			button.Release();
		}
	}
	m_ButtonList.clear();

	return true;
}

//--------------------------------------------------------------------------------------
// Network
//--------------------------------------------------------------------------------------
bool SceneManager::NetworkProcess()
{
	return true;
}

LRESULT SceneManager::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	}
	I_AsyncSelect.MsgProc(hWnd, msg, wParam, lParam);
	I_Input.MsgProc(hWnd, msg, wParam, lParam);
	return TRUE;
}

SceneManager::SceneManager()
{
	m_bIsLoad = false;
	m_bInit = false;
	m_bSceneChange = false;
}

SceneManager::~SceneManager()
{

}