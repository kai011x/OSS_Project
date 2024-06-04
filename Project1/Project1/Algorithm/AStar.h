#pragma once

class AStar
{
public:
	AStar(UINT width = 20, UINT height = 20);
	~AStar();

	void Update();
	void Render();

	void CreateNode(class Terrain* terrain);
	void CreateMiddleNode(class Quad* terrain);

	int FindCloseNode(Vector3 pos);
	
	void GetPath(IN int start, IN int end, OUT vector<Vector3>& path);
	bool CollisionObstacle(Ray ray, float distance);

	void SetObstalceNode();
	void AddObstacle(Collider* collider) { obstacles.push_back(collider); }


	vector<Collider*>& Get_Obstacles() { return obstacles; }
	vector<Node*>& Get_Nodes() { return nodes; }
private:
	void Reset();
	float GetManhattanDistance(int start, int end);
	float GetDiagonalManhattanDistance(int start, int end);

	int GetMinNode();
	void Extend(int select, int end);
	void SetEdge();

	void GetOriginPath(IN int start, IN int end, OUT vector<Vector3>& path);
	void MakeDirectPath(IN Vector3 start, IN Vector3 end, OUT vector<Vector3>& path);


private:
	// node °¹¼ö
	UINT width, height;
	
	vector<Node*> nodes;
//	vector<Node*> openNodes;
	Heap* heap;

	// node ¹Ý°æ
	Float2 interval;

	vector<Collider*> obstacles;

};

