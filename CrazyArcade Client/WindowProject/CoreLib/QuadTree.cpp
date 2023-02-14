#include "QuadTree.h"

//--------------------------------------------------------------------------------------
// Create Node
//--------------------------------------------------------------------------------------
Node* QuadTree::CreateNode(Node* pParent, RECT rect)
{
	Node* pNode = NULL;
	SAFE_NEW(pNode, Node);
	
	pNode->GetChildList().reserve(4);
	pNode->SetCorner(rect);
	pNode->SetPos(POINT_F(rect.left + (kObjectWidthSize * 0.5f), rect.top + (kObjectHeightSize * 0.5f)));

	if (pParent)
	{
		pNode->SetDepth(pParent->GetDepth() + 1);
		if (kQuadtreeMaxDepthLimit < pNode->GetDepth())
		{
			m_iMaxDepth = pNode->GetDepth();
		}
	}
	return pNode;
}

//--------------------------------------------------------------------------------------
// Delete Node
//--------------------------------------------------------------------------------------
bool QuadTree::DeleteNode(Node* pNode)
{
	assert(pNode);
	if (pNode->GetParentNode() != nullptr)
	{
		Node* pParent = pNode->GetParentNode();
		for (int index = 0; index < pParent->GetChildList().size(); index++)
		{
			if (pParent->GetChild(index) == pNode)
			{
				pParent->SetChild(nullptr, index);
			}
		}
	}
	SAFE_DEL(pNode);
	m_iNodeCount--;

	return true;
}

//--------------------------------------------------------------------------------------
// Build
//--------------------------------------------------------------------------------------
bool QuadTree::Build(LONG lWidth, LONG lHeight)
{
	m_lHeight = lHeight;
	m_lWidth = lWidth;

	RECT rect;
	rect.left = kMapMinWidthSize;
	rect.right = lWidth + rect.left;
	rect.top = kMapMinHeightSize;
	rect.bottom = lHeight + rect.top;
	
	m_pRootNode = CreateNode(nullptr, rect);
	m_pRootNode->SetNodeIndex(m_iNodeCount++);

	if (BuildTree(m_pRootNode))
	{
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------
// Create QuadTree
//--------------------------------------------------------------------------------------
bool QuadTree::BuildTree(Node* pNode)
{
	if (SubDivide(pNode) == true)
	{
		for (int iNode = 0; iNode < pNode->GetChildList().size(); iNode++)
		{
			pNode->GetChild(iNode)->SetParentNode(pNode);
			BuildTree(pNode->GetChildList().at(iNode));
		}
	}
	return true;
}

//--------------------------------------------------------------------------------------
// Divide space
//--------------------------------------------------------------------------------------
bool QuadTree::SubDivide(Node* pNode)
{
	// 4등분 할 수 없으면 더이상 분할하지 않는다.
	if (pNode == NULL)
	{
		return false;
	}
	RECT rect;

	// 최대 깊이 한도 초과시 강제 리프노드 지정
	if (kQuadtreeMaxDepthLimit <= pNode->GetDepth())
	{
		pNode->SetIsLeaf(true);
		return false;
	}

	// 현재 노드의 실제 크기를 계산
	LONG lWidthSplit = (pNode->GetCorner().right - pNode->GetCorner().left) / 2;
	LONG lHeightSplit = (pNode->GetCorner().bottom - pNode->GetCorner().top) / 2;

	// 자식 노드가 지정된 분할크기보다 작다면 더이상 분할하지 않는다.
	if (fabs(lWidthSplit) < kQuadtreeMinDivideSize || fabs(lHeightSplit) < kQuadtreeMinDivideSize)
	{
		pNode->SetIsLeaf(true);
		return false;
	}

	// 왼쪽 상단 노드 ( 1번 노드 )
	rect = pNode->GetCorner();
	rect.right = rect.left + lWidthSplit;
	rect.bottom = rect.bottom - lHeightSplit;
	pNode->SetChild(CreateNode(pNode, rect));
	pNode->SetNodeIndex(m_iNodeCount++);

	// 오른쪽 상단 노드 ( 2번 노드 )
	rect = pNode->GetCorner();
	rect.left = rect.left + lWidthSplit;
	rect.bottom = rect.bottom - lHeightSplit;
	pNode->SetChild(CreateNode(pNode, rect));
	pNode->SetNodeIndex(m_iNodeCount++);

	// 왼쪽 하단 노드 ( 3번 노드 )
	rect = pNode->GetCorner();
	rect.right = rect.left + lWidthSplit;
	rect.top = rect.bottom - lHeightSplit;
	pNode->SetChild(CreateNode(pNode, rect));
	pNode->SetNodeIndex(m_iNodeCount++);

	// 오른쪽 하단 노드 ( 4번 노드 )
	rect = pNode->GetCorner();
	rect.left = rect.left + lWidthSplit;
	rect.top = rect.bottom - lHeightSplit;
	pNode->SetChild(CreateNode(pNode, rect));
	pNode->SetNodeIndex(m_iNodeCount++);

	return true;
}

//--------------------------------------------------------------------------------------
// Find node
//--------------------------------------------------------------------------------------
Node* QuadTree::FindNodeInQuadTree(RECT rt)
{
	assert(m_pRootNode);

	Node* pNode = m_pRootNode;
	while (pNode != nullptr && pNode->GetIsLeaf() == false)
	{
		for (int index = 0; index < kQuadTreeSize; index++)
		{
			if (pNode->GetChild(index) != nullptr
				&& pNode->GetChild(index)->EnableExistObjectInNode(rt) == true)
			{
				m_QuadTreeQueue.push(pNode->GetChild(index));
				break;
			}
		}
		if (m_QuadTreeQueue.empty() == true)
		{
			break;
		}
		pNode = m_QuadTreeQueue.front();
		m_QuadTreeQueue.pop();
	}

	if (pNode == m_pRootNode)
	{
		pNode = nullptr;
	}

	return pNode;
}

//--------------------------------------------------------------------------------------
// Find node
//--------------------------------------------------------------------------------------
Node* QuadTree::FindNodeInQuadTree(POINT_F vPos)
{
	assert(m_pRootNode);

	Node* pNode = m_pRootNode;
	while (pNode != nullptr && pNode->GetIsLeaf() == false)
	{
		for (int index = 0; index < kQuadTreeSize; index++)
		{
			if (pNode->GetChild(index) != nullptr
				&& pNode->GetChild(index)->EnableExistObjectInNode(vPos) == true)
			{
				m_QuadTreeQueue.push(pNode->GetChild(index));
				break;
			}
		}
		if (m_QuadTreeQueue.empty() == true)
		{
			break;
		}
		pNode = m_QuadTreeQueue.front();
		m_QuadTreeQueue.pop();
	}

	if (pNode == m_pRootNode)
	{
		pNode = nullptr;
	}

	return pNode;
}

//--------------------------------------------------------------------------------------
// Add object in quadtree
//--------------------------------------------------------------------------------------
bool QuadTree::AddInQuadTree(Node* pNode, Object* pObject)
{
	if (pNode != nullptr)
	{
		pNode->AddObjectInNode(pObject);
		return true;
	}

	return false;
}

//--------------------------------------------------------------------------------------
// Delete an object from the list of objects in a node
//--------------------------------------------------------------------------------------
bool QuadTree::DeleteObject(Node* pNode, Object* pObject)
{
	if (pNode->isExistObjectInNode(pObject) == true)
	{
		pNode->DeleteObjectInNode(pObject);
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------
// Set tile information in the map in the quadtree
//--------------------------------------------------------------------------------------
bool QuadTree::SetMapTilesInfoToQuadtree(vector<Tile*> tileList, map<int, Item*> itemMap)
{
	for (int index = 0; index < kMapPixelCount; index++)
	{
		RECT rect = tileList.at(index)->GetBoundingBox().GetBoundingBoxInfo();
		Node* pNode = FindNodeInQuadTree(rect);
		if (pNode != nullptr)
		{
			eTileType tileType = tileList.at(index)->GetTileType();
			pNode->SetTileType(tileType);
			if (tileType != eTileType::NONE && tileType != eTileType::EMPTY)
			{
				if (tileList.at(index)->GetExistenceItem() == true)
				{
					if (itemMap[index] != nullptr)
					{
						pNode->AddObjectInNode((Object*)itemMap[index]);
					}
				}
				pNode->AddObjectInNode((Object*)tileList.at(index));
			}
			m_rtLeafNodePoint.push_back(pNode->GetCorner());
		}
	}
	return true;
}

//--------------------------------------------------------------------------------------
// Transform the quad tree to match the tile characteristics of the map
//--------------------------------------------------------------------------------------
bool QuadTree::ConvertQuadtreeToMapTileInfo()
{
	for (int index = 0; index < m_rtLeafNodePoint.size(); index++)
	{
		RECT rect = m_rtLeafNodePoint.at(index);
		Node* pNode = FindNodeInQuadTree(rect);
		if (pNode != nullptr)
		{
			eTileType tileType = pNode->GetTileType();
			if (tileType == eTileType::NONE)
			{
				m_rtLeafNodePoint.erase(m_rtLeafNodePoint.begin() + (index--));
				DeleteNode(pNode);
			}
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Update
//--------------------------------------------------------------------------------------
Node* QuadTree::UpdateQuadTree(Object* pObject, POINT_F vPrevPos)
{
	assert(pObject);

	Node* pNode = FindNodeInQuadTree(vPrevPos);
	if (pNode != nullptr)
	{
		DeleteObject(pNode, pObject);
		pNode = FindNodeInQuadTree(pObject->GetPosition());
		if (pNode != nullptr)
		{
			AddInQuadTree(pNode, pObject);
			return pNode;
		}
		return pNode;
	}
	return pNode;
}

Node* QuadTree::UpdateQuadTree(Object* pObject, RECT rtCurrent, RECT rtNext)
{
	assert(pObject);

	Node* pNode = FindNodeInQuadTree(rtCurrent);
	if (pNode != nullptr)
	{
		DeleteObject(pNode, pObject);
		pNode = FindNodeInQuadTree(rtNext);
		if (pNode != nullptr)
		{
			AddInQuadTree(pNode, pObject);
			return pNode;
		}
		return pNode;
	}
	return pNode;
}

//--------------------------------------------------------------------------------------
// Release
//--------------------------------------------------------------------------------------
bool QuadTree::Release()
{
	//SAFE_DEL();

	return true;
}

//--------------------------------------------------------------------------------------
// Get Function
//--------------------------------------------------------------------------------------
Node* QuadTree::GetRootNode()
{
	return m_pRootNode;
}

vector<RECT> QuadTree::GetLeafNodePosition()
{
	return m_rtLeafNodePoint;
}

QuadTree::QuadTree()
{
	m_lWidth = 0;
	m_lHeight = 0;
	m_iMaxDepth = 0;
	m_pRootNode = nullptr;
	m_iNodeCount = 0;
}


QuadTree::~QuadTree()
{
	Release();
}
