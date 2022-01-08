#include "sobj.h"

class Q_DECL_EXPORT MyObject : public Object {
public:
	static const MetaObject staticMetaObject;
	MyObject();
public:
	int signalFunction(int hello);
};

const MetaObject MyObject::staticMetaObject {
	4321,
	'a'
};


MyObject::MyObject()
{
	connect(this, &MyObject::signalFunction);
}

int MyObject::signalFunction(int hello)
{
	hello++;
	return 0;
}

int main()
{
	MyObject o;
	return 0;
}
