#ifndef IDATASOURCE_H
#define IDATASOURCE_H

class IDataSource {
public:
    virtual double getNextSample() = 0;
    virtual ~IDataSource() = default;
};

#endif 
