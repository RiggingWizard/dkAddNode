#include "dkAddNode.h"

#include <maya/MFnNumericAttribute.h>
#include <maya/MFnPlugin.h>

MTypeId DKAddNode::id(0x80002);

MObject DKAddNode::input1;
MObject DKAddNode::input2;
MObject DKAddNode::output;

DKAddNode::DKAddNode() {}

DKAddNode::~DKAddNode() {}

void* DKAddNode::creator()
{
	return new DKAddNode();
}

MStatus DKAddNode::initialize()
{
	MFnNumericAttribute nAttr;
	input1 = nAttr.create("input1", "in1", MFnNumericData::kDouble, 0.0);
	nAttr.setWritable(true);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);

	input2 = nAttr.create("input2", "in2", MFnNumericData::kDouble, 0.0);
	nAttr.setWritable(true);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);

	output = nAttr.create("output", "out", MFnNumericData::kDouble, 0.0);
	nAttr.setWritable(false);
	nAttr.setStorable(false);

	addAttribute(input1);
	addAttribute(input2);
	addAttribute(output);

	attributeAffects(input1, output);
	attributeAffects(input2, output);

	return MS::kSuccess;
}

MStatus DKAddNode::compute(const MPlug& plug, MDataBlock& data)
{
	if (plug != output)
	{
		return MS::kUnknownParameter;
	}
	double input1_data = data.inputValue(input1).asDouble();
	double input2_data = data.inputValue(input2).asDouble();
	double output_value = input1_data + input2_data;
	data.outputValue(output).set(output_value);
	data.setClean(plug);
	return MS::kSuccess;
}

MStatus initializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj, "Dikshant Kumar", "1.0", "Any");
	status = plugin.registerNode("dkAddNode", DKAddNode::id, DKAddNode::creator, DKAddNode::initialize);
	return status;
}

MStatus uninitializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj);
	status = plugin.deregisterNode(DKAddNode::id);
	return status;
}







