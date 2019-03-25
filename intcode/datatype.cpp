#include "intcode/datatype.hpp"

#include <iostream>

const char* BASETYPE_NAMES[] = {
    "void",
    "bool",
    "u32",
    "*",
    "&"
};

DataType::DataType(BaseType base) : type(base) {}
DataType::DataType(BaseType base, DataType* subtype) : type(base), subtype(subtype) {}

bool DataType::equals(const DataType& o) const
{
    if(this->subtype != nullptr && o.subtype != nullptr && !this->subtype->equals(*o.subtype))
        return false;
    else if(this->subtype != nullptr || o.subtype != nullptr)
        return false;
    else
        return this->type == o.type;
}

bool operator==(const DataType& lop, const DataType& rop)
{
    return lop.equals(rop);
}

bool operator!=(const DataType& lop, const DataType& rop)
{
    return !(lop == rop);
}

std::ostream& operator<<(std::ostream& os, const DataType& type)
{
    if(type.subtype != nullptr)
        os << *type.subtype;
    os << BASETYPE_NAMES[static_cast<size_t>(type.type)];
    return os;
}
