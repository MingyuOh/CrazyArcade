#include "Node.h"

//--------------------------------------------------------------------------------------
// Verify enable put an object in node function
//--------------------------------------------------------------------------------------
bool Node::EnableExistObjectInNode(RECT rtObjectRect)
{
	if (m_rtCorner.left <= rtObjectRect.left &&
		m_rtCorner.right >= rtObjectRect.right &&
		m_rtCorner.top <= rtObjectRect.top &&
		m_rtCorner.bottom >= rtObjectRect.bottom)
	{
		return true;
	}
	return false;
}

bool Node::EnableExistObjectInNode(POINT_F vObjectPos)
{
	if (static_cast<float>(m_rtCorner.left) <= vObjectPos.fX &&
		static_cast<float>(m_rtCorner.right) >= vObjectPos.fX &&
		static_cast<float>(m_rtCorner.top) <= vObjectPos.fY &&
		static_cast<float>(m_rtCorner.bottom) >= vObjectPos.fY)
	{
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------
// Verify exsist object in node function
//--------------------------------------------------------------------------------------
bool Node::isExistObjectInNode(Object* pObject)
{
	for (auto& obj : m_objectList)
	{
		if (obj == pObject)
		{
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------------------------------
// Add object in node function
//--------------------------------------------------------------------------------------
void Node::AddObjectInNode(Object* pObject)
{
	m_objectList.push_back(pObject);
}

//--------------------------------------------------------------------------------------
// Delete object in objectList
//--------------------------------------------------------------------------------------
void Node::DeleteObjectInNode(Object* pObject)
{
	m_objectList.erase(remove(m_objectList.begin(), m_objectList.end(), pObject), m_objectList.end());
}

//--------------------------------------------------------------------------------------
// Set Function
//--------------------------------------------------------------------------------------
void Node::SetDepth(const DWORD dwDepth)
{
	m_dwDepth = dwDepth;
}

void Node::SetIsLeaf(const bool bIsLeaf)
{
	m_bIsLeaf = bIsLeaf;
}

void Node::SetCorner(const RECT corner)
{
	m_rtCorner = corner;
}

void Node::SetPos(const POINT_F vPos)
{
	m_vPos = vPos;
}

void Node::SetChild(Node* child)
{
	m_childList.push_back(child);
}

void Node::SetChild(Node* child, int index)
{
	m_childList.at(index) = child;
}

void Node::SetChildList(const vector<Node*> childList)
{
	m_childList = childList;
}

void Node::SetParentNode(Node* pParent)
{
	m_pParentNode = pParent;
}

void Node::SetObject(Object* object)
{
	m_objectList.push_back(object);
}

void Node::SetObjectList(const vector<Object*> objectList)
{
	m_objectList = objectList;
}

void Node::SetNodeIndex(int index)
{
	m_iNodeIndex = index;
}
void Node::SetTileType(const eTileType tileType)
{
	m_tileType = tileType;
}

//--------------------------------------------------------------------------------------
// Get Function
//--------------------------------------------------------------------------------------
DWORD Node::GetDepth()
{
	return m_dwDepth;
}

bool Node::GetIsLeaf()
{
	return m_bIsLeaf;
}

RECT& Node::GetCorner()
{
	return m_rtCorner;
}

POINT_F Node::GetPos()
{
	return m_vPos;
}

Node* Node::GetChild(int index)
{
	return m_childList.at(index);
}

vector<Node*>& Node::GetChildList()
{
	return m_childList;
}

Node* Node::GetParentNode()
{
	return m_pParentNode;
}

Object* Node::GetObject(int index)
{
	return m_objectList.at(index);
}

vector<Object*>& Node::GetObjectList()
{
	return m_objectList;
}

int Node::GetNodeIndex()
{
	return m_iNodeIndex;
}

eTileType Node::GetTileType()
{
	return m_tileType;
}

Node::Node()
{
	m_dwDepth = 0;
	m_iNodeIndex = 0;
	m_bIsLeaf = false;
	m_rtCorner = { 0, };
	m_vPos = { 0,0 };
	m_tileType = eTileType::NONE;
	m_pParentNode = nullptr;
}

Node::~Node()
{
	m_childList.clear();
	m_objectList.clear();
}
