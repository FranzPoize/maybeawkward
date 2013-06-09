
#ifndef MA_CLOSURE_H
#define MA_CLOSURE_H

namespace MA {

template<class T>
struct Closure {
    virtual void call(T& param, float dt) = 0;
};

template<class T>
class FunctionClosure : public Closure<T> {
public:
    typedef void(*FuncPtr)(T&, float dt);
    FunctionClosure(FuncPtr callback)
    : _function(callback) {}

    void call(T& params, float dt) {
        _function(params, dt);
    }
private:
    FuncPtr _function;
};

template<class T>
FunctionClosure<T>*
closure( typename FunctionClosure<T>::FuncPtr f ) {
    return new FunctionClosure<T>(f);
}

} // namespace

#endif
