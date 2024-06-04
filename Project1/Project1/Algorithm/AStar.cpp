#include "Framework.h"

AStar::AStar(UINT width, UINT height)
	: width(width), height(height)
{
	heap = new Heap();
}

AStar::~AStar()
{
	for (Node* node : nodes)
		delete node;

	delete heap;
}

void AStar::Update()
{
//	if (MOUSE_CLICK(0))
//	{
//		Ray ray = CAMERA->ScreenPointToRay(mousePos);
//
//		for (Node* node : nodes)
//		{
//			if (node->RayCollision(ray))
//			{
//				node->SetState(Node::OBSTACLE);
//				break;
//			}
//		}
//	}
}

void AStar::Render()
{
	for (Node* node : nodes)
	{
		node->Render();
	}
}

void AStar::CreateNode(Terrain* terrain)
{
	Float2 size = terrain->GetSize();
	
	interval.x = size.x / width;
	interval.y = size.y / height;

	for (UINT z = 0; z < height; z++)
	{
		for (UINT x = 0; x < width; x++)
		{
			Vector3 pos = { x * interval.x ,0.0f,z * interval.y };
			pos.y = terrain->GetHeight(pos);

			nodes.push_back(new Node(pos, nodes.size()));
		}
	}

	SetEdge();
}

void AStar::CreateMiddleNode(Quad* terrain)
{
	Float2 size = terrain->GetSize();

	interval.x = size.x / width;
	interval.y = size.y / height;

	for (UINT z = 0; z < height; z++)
	{
		for (UINT x = 0; x < width; x++)
		{
			Vector3 pos = {2.0f +  x * interval.x ,0.0f,2.0f + z * interval.y };
			pos.y = 0;

			nodes.push_back(new Node(pos, nodes.size()));
		}
	}

	SetEdge();
}


void AStar::SetEdge()
{
	for (UINT i = 0; i < nodes.size(); i++)
	{
		// �¿�
		if (i % width != width - 1)
		{
			nodes[i]->AddEdge(nodes[i + 1]);
			nodes[i + 1]->AddEdge(nodes[i]);
		}

		// ����
		if (i < nodes.size() - width)
		{
			nodes[i]->AddEdge(nodes[i  + width]);
			nodes[i  + width]->AddEdge(nodes[i]);
		}
		// ����
		if ((i % width != width - 1) && (i < nodes.size() - width))
		{
			nodes[i]->AddEdge(nodes[i + width + 1]);
			nodes[i + width + 1]->AddEdge(nodes[i]);
		}

		// �»��
		if ((i % width != 0) && (i < nodes.size() - width))
		{
			nodes[i]->AddEdge(nodes[i + width - 1]);
			nodes[i + width - 1]->AddEdge(nodes[i]);
		}
	}
}

int AStar::FindCloseNode(Vector3 pos)
{
	float minDist = FLT_MAX;
	int index = -1;

	for (UINT i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->state == Node::OBSTACLE)
			continue;

		float dist = Distance2D(pos, nodes[i]->Position());
		if (minDist > dist)
		{
			minDist = dist;
			index = i;
		}
	}

	return index;
}

void AStar::GetOriginPath(IN int start, IN int end, OUT vector<Vector3>& path)
{
	Reset();
	// 1. ���۳�� �ʱ�ȭ
	float G = 0.0f;
	float H = GetDiagonalManhattanDistance(start, end);

	nodes[start]->g = G;
	nodes[start]->h = H;
	nodes[start]->f = H + G;
	nodes[start]->via = start;
	nodes[start]->state = Node::OPEN;

	heap->Insert(nodes[start]);
//	openNodes.push_back(nodes[start]);

	while (nodes[end]->state != Node::CLOSED)
	{
		if (heap->Empty())// ������ ��ΰ� ����
			return;

		int selectIndex = GetMinNode();	// 2. ���µ� ��� �߿��� �ڽ�Ʈ ȿ���� ���� ���� ��� ã��
		Extend(selectIndex, end);	// 3. ã�� ����� ����� ��带 ���� ���� �߰��ϰ� ���� ����
		nodes[selectIndex]->SetState(Node::CLOSED);	// 4. Ȯ���� ���� ��� �ݱ�
	}
	// 5. ��Ʈ��ŷ ������
	int curIndex = end;
	while (curIndex != start)
	{
		nodes[curIndex]->state = Node::USING;
		path.push_back(nodes[curIndex]->Position());
		curIndex = nodes[curIndex]->via;
	}
}

void AStar::GetPath(IN int start, IN int end, OUT vector<Vector3>& path)
{
	Reset();
	//1. ���۳�� �ʱ�ȭ
	float G = 0.0f;
	float H = GetDiagonalManhattanDistance(start, end);

	nodes[start]->g = G;
	nodes[start]->h = H;
	nodes[start]->f = G + H;
	nodes[start]->via = start;
	nodes[start]->state = Node::OPEN;

	//openNodes.push_back(nodes[start]);
	heap->Insert(nodes[start]);

	while (nodes[end]->state != Node::CLOSED)
	{
		if (heap->Empty())//������ ��ΰ� ����
			return;

		int selectIndex = GetMinNode();//2. ���³�� �߿��� ȿ���� ���� ���� ��� ã��
		Extend(selectIndex, end);//3. ã�� ����� ����� ��带 ���³��� �߰��ϰ� ���� ����
		nodes[selectIndex]->SetState(Node::CLOSED);//4. Ȯ���� ���� ��� �ݱ�
	}

	//5. BackTracking
	int curIndex = end;
	while (curIndex != start)
	{
		nodes[curIndex]->state = Node::USING;
		path.push_back(nodes[curIndex]->Position());
		curIndex = nodes[curIndex]->via;
	}
}
void AStar::MakeDirectPath(IN Vector3 start, IN Vector3 end, OUT vector<Vector3>& path)
{
	int cutNodeNum = 0;

	Ray ray;
	ray.position = start;
	
	for (UINT i = 0; i < path.size(); i++)
	{
		ray.direction = path[i] - ray.position;
		float distance = ray.direction.length();
		ray.direction = ray.direction.Normalize();

		if (!CollisionObstacle(ray,distance))
		{
			cutNodeNum = path.size() - i - 1;
			break;
		}
	}

	for (int i = 0; i < cutNodeNum; i++)
		path.pop_back();

	cutNodeNum = 0;
	ray.position = end;

	for (UINT i = 0; i < path.size(); i++)
	{
		ray.direction = path[path.size() - i - 1] - ray.position;
		float distance = ray.direction.length();
		ray.direction = ray.direction.Normalize();

		if (!CollisionObstacle(ray, distance))
		{
			cutNodeNum = path.size() - i - 1;
			break;
		}
	}

	for (int i = 0; i < cutNodeNum; i++)
		path.erase(path.begin());

}

void AStar::Reset()
{
	for (Node* node : nodes)
	{
		if (node->state != Node::OBSTACLE)
			node->state = Node::NONE;
	}

	heap->Clear();
//	openNodes.clear();
}

float AStar::GetManhattanDistance(int start, int end)
{
	Vector3 startPos = nodes[start]->Position();
	Vector3 endPos = nodes[end]->Position();

	Vector3 temp = startPos - endPos;

	return abs(temp.x) + abs(temp.z);
}

float AStar::GetDiagonalManhattanDistance(int start, int end)
{
	// GetPath �� Extand���� �̰ɷ� �ٲ������
	Vector3 startPos = nodes[start]->Position();
	Vector3 endPos = nodes[end]->Position();

	Vector3 temp = startPos - endPos;

	float x = abs(temp.x);
	float z = abs(temp.z);

	float minSize = min(x, z);
	float maxSize = max(x, z);

	return (maxSize - minSize) + sqrt(2)* minSize;
}

int AStar::GetMinNode()
{
	/*
	float minCost = FLT_MAX;
	int index = -1;

	for (UINT i = 0; i < nodes.size(); i++)
	{
		if (minCost > openNodes[i]->GetCost())
		{
			minCost = openNodes[i]->GetCost();
			index = i;
		}
	}
	int nodeIndex = openNodes[index]->index;

	openNodes.erase(openNodes.begin() + index);

	return nodeIndex;

	*/

	return heap->DeleteRoot()->index;
}
void AStar::Extend(int select, int end)
{
	vector<Node::Edge*> edges = nodes[select]->edges;

	for (Node::Edge* edge : edges)
	{
		int index = edge->index;
		if (nodes[index]->state == Node::CLOSED)
			continue;
		if (nodes[index]->state == Node::OBSTACLE)
			continue;

		// ������������ ����������� ȿ��
		float G = nodes[select]->g + edge->cost;
		// ���ݺ��� ���������� ���� ȿ��
		float H = GetDiagonalManhattanDistance(index, end);
		float F = G + H;

		if (nodes[index]->state == Node::OPEN)
		{
			if (F < nodes[index]->GetCost())
			{
				nodes[index]->g = G;
				nodes[index]->f = F;
				nodes[index]->via = select;

			}
		}
		else if(nodes[index]->state == Node::NONE)
		{
			nodes[index]->g = G;
			nodes[index]->h = H;
			nodes[index]->f = F;
			nodes[index]->via = select;
			nodes[index]->state = Node::OPEN;

			heap->Insert(nodes[index]);
//			openNodes.push_back(nodes[index]);
		}
	}
}

void AStar::SetObstalceNode()
{
	for (Collider* obstacle : obstacles)
	{
		for (Node* node : nodes)
		{
			if (obstacle->Collision(node))
			{
				node->state = Node::OBSTACLE;
			}
		}
	}
}

bool AStar::CollisionObstacle(Ray ray, float distance)
{
	for (Collider* obstacle : obstacles)
	{
		Contact contact;

		if (obstacle->RayCollision(ray, &contact))
		{
			if (contact.distance < distance)
				return true;
		}
	}

	return false;
}
