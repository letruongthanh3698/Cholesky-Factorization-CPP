#include "stdafx.h"

#include <cstdint>
#include "Link.h"
Link::Link(uint64_t nodename, double value)
{
	NodeName = nodename;
	Value = value;
}

Link::Link(uint64_t nodename)
{
	NodeName = nodename;
	Value = 0;
}

Link::Link()
{
	NodeName = 0;
	Value = 0;
}