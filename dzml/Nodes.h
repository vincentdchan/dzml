#pragma once
#include "dzml.h"

namespace dzml
{

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

}
