
#ifndef MA_CLOSURE_H
#define MA_CLOSURE_H

namespace MA {

template<class T>
class Closure {
    virtual void call(T& param) = 0;
};

template<class T>
class FunctionClosure : public Closure<T> {
    typedef void(*FuncPtr)(T&);
    FunctionClosure(FuncPtr callback)
    : _function(callback) {}
 
    void call(T& params) {
        _function(params);
    }
    FuncPtr _function;
};

} // namespace

#endif
