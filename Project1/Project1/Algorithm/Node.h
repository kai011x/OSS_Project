#pragma once

class Node : public BoxCollider
{
private:
	friend class AStar;

	enum State
	{
		NONE,OPEN,CLOSED,USING,OBSTACLE
	};

	struct Edge
	{
		int index;
		float cost;
	};

public:
	Node(Vector3 pos, int index);
	~Node();

	void Render();
	void AddEdge(Node* node);
	void SetState(State state) { this->state = state; }
	
	void Set_Obstacle() { this->state = Node::OBSTACLE; }
	float GetCost() { return f; }
	bool IsObstacle() { if (this->state == Node::OBSTACLE)return true; else return false; }

private:
	int index;
	int via = -1;

	float f, g, h;
	State state = NONE;
	vector<Edge*> edges;
};
