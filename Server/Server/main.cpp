#include <cstdio>
#include "ServerOP.h"
int main()
{
    //启动服务器
    ServerOP op("config.json");
    op.satrtServer();
    
    return 0;
}