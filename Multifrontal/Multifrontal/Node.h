#include "main.h"
#include "Link.h"

#include <cstdbool>
#include <vector>

#ifndef _NODE_H_
#define _NODE_H_

typedef enum {
	NONEEDSORT = false,
	NEEDSORT = true
}eBOOLSORT;

typedef uint64_t tNODENAME;
typedef uint64_t tPARENT;
typedef Link tLINK;

using namespace std;

class Node
{
public:
	tNODENAME NodeName;
	tPARENT Parent;
	tPARENT SuperParent;
	vector<tLINK> Child;
	uint64_t Number_of_Child_U64;

public:
	Node();
	Node(tNODENAME nodename);
	void AddChild(tNODENAME nodename, double value_D, eBOOLSORT needsort_B);
	void UpdateParent(tPARENT parent);
	tPARENT GetSuperParent(Node *nodes);
	bool IsChildNodeExist(tNODENAME nodename);

private:
	void InsertChild(tLINK link, uint64_t pos_U64);
	//tNODENAME GetChildNodeName(int64_t pos_U64);
};
#endif