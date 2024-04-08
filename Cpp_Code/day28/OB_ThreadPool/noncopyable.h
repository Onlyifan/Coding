#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_


class Noncopyable {
  protected:
    Noncopyable( ) = default;
    ~Noncopyable( ) = default;
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable &operator=(const Noncopyable &) = delete;
};


#endif // _NONCOPYABLE_H_
