#ifndef IOUTPUTSINK_H
#define IOUTPUTSINK_H

class IOutputSink {
public:
    virtual ~IOutputSink() = default;

    virtual void send(double sample) = 0;
};

#endif 
