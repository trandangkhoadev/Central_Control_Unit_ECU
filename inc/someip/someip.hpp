#ifndef __SOMEIP__
#define __SOMEIP__


class SomeIPMgr
{
private:
    SomeIPMgr() {};
    SomeIPMgr(const SomeIPMgr&) = delete; 
    SomeIPMgr& operator=(const SomeIPMgr&) = delete;
    SomeIPMgr& operator=(const SomeIPMgr&&) = delete;

public:
    static SomeIPMgr& getInstance();
};



#endif // __SOMEIP__