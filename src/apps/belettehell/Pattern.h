#ifndef Pattern_h__
#define Pattern_h__

namespace MA
{
class GraphicWrapper;
class Pattern
{
public:
	virtual void launchPattern(GraphicWrapper &gw)=0;
	enum ControllerType
	{
		FORMATION,
		CLOSE,
		AROUND,
	};
	virtual ~Pattern(){};
};
}
#endif