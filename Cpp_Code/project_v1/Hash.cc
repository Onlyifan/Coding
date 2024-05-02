#include "Hash.h"
#include "unixHeader.h"

#include <iostream>
#include <openssl/sha.h>
using std::cout;
using std::endl;
using std::string;


std::string Hash::sha1( ) const {
    int fd = open(_filename.c_str( ), O_RDONLY);
    cout << "_filename:" << _filename << endl;
    if (fd < 0) {
        perror("open");
        return "";
    }
    char buff[1024] = { 0 };
    SHA_CTX ctx;
    SHA1_Init(&ctx);

    for (;;) {
        size_t ret = read(fd, buff, 1024);
        if (ret == 0) {
            break;
        }
        SHA1_Update(&ctx, buff, ret);
        bzero(buff, sizeof(buff));
    }
    unsigned char md[20] = { 0 };
    SHA1_Final(md, &ctx);
    char fragment[3] = { 0 };
    string result;
    for (auto &elem : md) {
        sprintf(fragment, "%02x", elem);
        result += fragment;
    }
    return result;
}
