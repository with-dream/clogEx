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