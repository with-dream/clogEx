ThreadContextMapFilter??

https://www.jianshu.com/p/c89a8b9f9859
https://blog.csdn.net/qq_29036453/article/details/120468341

1、主要数据结构:
Context

Configure

MessageFactory
    Message

LogEvent
    Message
    Marker ->parent
    Level

Appender
    LogEvent
    Filter[]
    Layout
    Lookup[]

Logger
    ->parent
    Appender[]

2、基本输出方式
控制台、文件、RollingFile

3、步骤
开始打印->封装Msg->封装LogEvent->Filter->Layout->Appender

4、filter

https://www.yisu.com/zixun/623271.html