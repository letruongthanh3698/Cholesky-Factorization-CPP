#include "main.h"
#ifndef _LINK_H_
#define _LINK_H_
class Link
{
public:
	uint64_t NodeName;
	double Value;

public:
	Link(uint64_t nodename, double value);
	Link(uint64_t nodename);
	Link();
};
#endif