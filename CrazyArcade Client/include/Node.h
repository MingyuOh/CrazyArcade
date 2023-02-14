#pragma once
#include "CoreSTD.h"
#include "Object.h"

class Node
{
private:
	DWORD				m_dwDepth;
	bool				m_bIsLeaf;
	RECT				m_rtCorner;
	POINT_F				m_vPos;
	int					m_iNodeIndex;
	TILETYPE			m_tileType;
	vector<Node*>		m_childList;
	vector<Object*>		m_objectList;
public:
	//--------------------------------------------------------------------------------------
	// Verify exsist object in node function
	//--------------------------------------------------------------------------------------
	bool				EnableExistObjectInNode(RECT rtObjectRect);
	bool				EnableExistObjectInNode(POINT_F vObjectPos);
	//--------------------------------------------------------------------------------------
	// Verify exsist object in node function
	//--------------------------------------------------------------------------------------
	bool				isExistObjectInNode(Object* pObject);
	//--------------------------------------------------------------------------------------
	// Add object in node function
	//--------------------------------------------------------------------------------------
	void				AddObjectInNode(Object* pObject);
	//--------------------------------------------------------------------------------------
	// Delete object in objectList
	//--------------------------------------------------------------------------------------
	void				DeleteObjectInNode(Object* pObject);
	//--------------------------------------------------------------------------------------
	// Set Function
	//--------------------------------------------------------------------------------------
	void				SetDepth(const DWORD dwDepth);
	void				SetIsLeaf(const bool bIsLeaf);
	void				SetCorner(const RECT corner);
	void				SetPos(const POINT_F vPos);
	void				SetChild(Node* child);
	void				SetChildList( vector<Node*> childList);
	void				SetObject(Object* object);
	void				SetObjectList(const vector<Object*> objectList);
	void				SetNodeIndex(int index);
	void				SetTileType(const TILETYPE tileType);
	//--------------------------------------------------------------------------------------
	// Get Function
	//--------------------------------------------------------------------------------------
	DWORD				GetDepth();
	bool				GetIsLeaf();
	RECT&				GetCorner();
	POINT_F				GetPos();
	Node*				GetChild(int index);
	vector<Node*>&		GetChildList();
	Object*				GetObject(int index);
	vector<Object*>&	GetObjectList();
	int					GetNodeIndex();
	TILETYPE			GetTileType();
public:
	Node();
	virtual ~Node();
};

