#include "stdafx.h"

#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <functional>
#include "Link.h"
#include "Node.h"
#include "BinarySearch.h"

static double GetChildNodeName(void *array, int64_t pos_U64);

Node::Node()
{

}

Node::Node(tNODENAME nodename)
{
	this->NodeName = nodename;
	this->Parent = nodename;
	this->SuperParent = nodename;
	this->Number_of_Child_U64 = 0;
}

void Node::AddChild(tNODENAME nodename, double value_D, eBOOLSORT needsort_B)
{
	Link newnode = Link(nodename, value_D);
	BinarySearch bs;
	if (needsort_B)
	{
		int64_t pos_I64 = bs.SmallNearestSearch(0, (int64_t)(this->Number_of_Child_U64) - 1, value_D, (void*)&this->Child[0], GetChildNodeName);
		this->InsertChild(newnode, pos_I64 + 1);
	}
	else
	{
		this->Child.push_back(newnode);
	}
	this->Number_of_Child_U64++;
}

void Node::InsertChild(Link link, uint64_t pos_U64)
{
	/*for (uint64_t i=this->Number_of_Child_U64;i>=pos_U64;i++)
		this->Child[i]=this->Child[i-1];

	this->Child[pos_U64]=link;*/
	auto it = this->Child.begin();
	this->Child.insert(it + pos_U64, link);

}

void Node::UpdateParent(tPARENT parent)
{
	this->Parent = parent;
}

tPARENT Node::GetSuperParent(Node *nodes)
{
	tNODENAME res = this->NodeName;

	//uint64_t *queue_PU64=(uint64_t*)calloc(1000,sizeof(uint64_t));
	//uint64_t cnt=0;

	while (nodes[res].Parent != res)
	{
		//queue_PU64[cnt++]=res;
		res = nodes[res].Parent;
	}

	//for (uint64_t i_U64=0;i_U64<cnt;i_U64++)
	//    nodes[queue_PU64[i_U64]].SuperParent=res;

	return res;
}

bool Node::IsChildNodeExist(tNODENAME nodename)
{
	BinarySearch bs;
	int64_t pos_I64 = bs.ExactlySearch(0, (int64_t)(this->Number_of_Child_U64) - 1, nodename, (void*)&this->Child[0], &GetChildNodeName /* TODO */);

	if (pos_I64 >= 0)
		return true;
	else
		return false;
}

double GetChildNodeName(void *array, int64_t pos_I64)
{
	return ((tLINK*)array)[pos_I64].NodeName;
}
