#pragma once
template <class F>
struct _rlamb {
    F f;
    template <class... Args>
    decltype(auto) operator()(Args&&... args) const { return f(*this, forward<Args>(args)...); }
};

template <class F>
_rlamb<decay_t<F>> rlamb(F&& f) { return { forward<F>(f) }; }
