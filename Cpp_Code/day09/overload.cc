#include <iostream>
#include <unistd.h>
using std::cout;
using std::endl;

class Data {
  public:
    Data(int data)
        : _data(data) {}
    int &getData( ) {
        return _data;
    }

  private:
    int _data;
};


class middleLayer {

  public:
    middleLayer(Data *pdata)
        : _pdata(pdata) {}
    ~middleLayer( ) {
        if (_pdata) {
            delete _pdata;
            _pdata = nullptr;
        }
    }


    Data *operator->( ) {
        return _pdata;
    }

    Data &operator*( ) {

        return *_pdata;
    }


  private:
    Data *_pdata;
};

class thirdLayer {
  public:
    thirdLayer(middleLayer *ppdata)
        : _ppdata(ppdata) {}
    ~thirdLayer( ) {
        if (_ppdata) {
            // delete _ppdata;
            _ppdata = nullptr;
        }
    }

    middleLayer &operator->( ) {
        return *_ppdata;
    }

    Data &operator*( ) {
        return **_ppdata;
    }
    // middleLayer &operator*( ) {
    //    return *_ppdata;
    //}
    // Data *operator*( ) {
    //    return &(**_ppdata);
    //}

  private:
    middleLayer *_ppdata;
};

int main(void) {


    sleep(3);
    middleLayer ml(new Data(233));
    cout << ml->getData( ) << endl;
    cout << (*ml).getData( ) << endl;

    thirdLayer tl(new middleLayer(new Data(114514)));
    cout << tl->getData( ) << endl;
    (*tl).getData( ) = 1234;
    cout << (*tl).getData( ) << endl;

    return 0;
}
