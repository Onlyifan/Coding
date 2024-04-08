#ifndef _NONCOPYABLE_HH_
#define _NONCOPYABLE_HH_


class Noncopyable {
  protected:
    Noncopyable( ) = default;
    ~Noncopyable( ) = default;
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable &operator=(const Noncopyable &) = delete;
};


#endif // _NONCOPYABLE_HH_
