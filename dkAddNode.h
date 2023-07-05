#pragma once
#include <maya/MPxNode.h>


class DKAddNode : public MPxNode
{
public:
	DKAddNode();
	virtual ~DKAddNode();
	static void* creator();
	static MStatus initialize();
	virtual MStatus compute(const MPlug& plug, MDataBlock& data);


public:
	static MTypeId id;
	static MObject input1;
	static MObject input2;
	static MObject output;
};
