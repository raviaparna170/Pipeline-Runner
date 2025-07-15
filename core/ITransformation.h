#ifndef ITRANSFORMATION_H
#define ITRANSFORMATION_H
#include <optional>

class ITransformation {
public:
    virtual ~ITransformation() = default;

    virtual std::optional<double> process(double input) = 0;
};

#endif 
