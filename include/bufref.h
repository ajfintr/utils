#ifndef _BUFREF_H_
#define _BUFREF_UTILS_H_

#include <stdint.h>
#include <iostream>


struct bufref {
    bufref(): _buf(NULL), _len(0) {}
    bufref(const char* pointer,  uint16_t length): _buf(pointer), _len(length) {}
    bufref(const bufref& other): _buf(other._buf), _len(other._len) {}
    bufref& operator=( const bufref& other)
    {
      _buf = other._buf;
      _len = other._len;
      return *this;
    }
    size_t write(std::ostream& stream) {
     if(_len) {
       stream.write(_buf, _len);
       stream<<std::endl;
       stream.flush();
     }
     return _len;
  }
    void write() {
    }
    inline const uint16_t length() const { return _len; }
    inline const char* buffer() const { return _buf; }

    bool isTokenPresent() {return (_buf  == NULL)? false: true; }
    bool isEmptyValue() { return (_len == 0 && _buf != NULL)? true: false; }
    bool isValuePresent() { return _len? true: false;   }

    const char *_buf;
    uint16_t _len;
};

#endif _BUFREF_H_
