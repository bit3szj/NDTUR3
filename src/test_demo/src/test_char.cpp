#include<iostream>
#include<cstring>
int main()
{
    char test_char[1024] = "woshiwangdalu";
    char buff[20] = {0};
    memcpy(&buff, test_char+2, 1);
    std::cout << buff <<std::endl;

}