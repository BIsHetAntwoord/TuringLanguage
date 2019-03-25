#ifndef INTCODE_DATATYPE_HPP_INCLUDED
#define INTCODE_DATATYPE_HPP_INCLUDED

#include <memory>

enum class BaseType
{
    BOOL,
    U8,
    POINTER,
    REFERENCE
};

class DataType
{
    private:
        BaseType type;
        std::unique_ptr<DataType> subtype;
    public:
        DataType(BaseType);
        DataType(BaseType, DataType*);
};

#endif // INTCODE_DATATYPE_HPP_INCLUDED
