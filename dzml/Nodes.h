#pragma once
#include "dzml.h"
#include <memory>
#include <string>
#include <vector>

namespace dzml
{

	enum class NodeType
	{
		Let,
		LetRec,
		Integer,
		Float,
		Double,
		String,
		List,
		Array,
		Definition,
		Expression,
	};

	class Node final
	{
	public:
		NodeType Type;

		union {
			bool BoolValue;
			uc32 IntValue;
			float FloatValue;
			double DoubleValue;
		};

		std::unique_ptr<std::string> StringValue;
		std::vector<std::unique_ptr<Node>> NodesValue;
	};

	/*
	class Node
	{
	public:
		virtual ~Node() { }
	};

	template<class T>
	class _NumberNode : public Node
	{
	public:
		T data;

		_NumberNode(T data_) :
			data(data_)
		{ }
		virtual ~NumberNode() { }
	};

	typedef _NumberNode<uc32> IntegerNode;
	typedef _NumberNode<float> FloatNode;
	typedef _NumberNode<double> DoubleNode;
	*/

}
