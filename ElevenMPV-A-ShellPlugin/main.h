#include <paf.h>

using namespace paf;

class ImposeThread : public paf::thread::Thread
{
public:

	using paf::thread::Thread::Thread;

	virtual SceVoid EntryFunction();

	SceBool done;
};

class RxThread : public paf::thread::Thread
{
public:

	using paf::thread::Thread::Thread;

	virtual SceVoid EntryFunction();
};

class PlayerButtonCB : public widget::Widget::EventCallback
{
public:

	enum ButtonHash
	{
		ButtonHash_Play = 0x56734CD1,
		ButtonHash_Rew = 0x9F6A44DA,
		ButtonHash_Ff = 0x6CA674D6
	};

	PlayerButtonCB()
	{
		eventHandler = PlayerButtonCBFun;
	};

	virtual ~PlayerButtonCB()
	{

	};

	static SceVoid PlayerButtonCBFun(SceInt32 eventId, widget::Widget *self, SceInt32 a3, ScePVoid pUserData);

};