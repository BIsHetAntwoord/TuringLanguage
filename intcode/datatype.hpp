#ifndef INTCODE_DATATYPE_HPP_INCLUDED
#define INTCODE_DATATYPE_HPP_INCLUDED

#include <memory>
#include <iosfwd>

enum class BaseType
{
    VOID,
    BOOL,
    U32,
    POINTER,
    REFERENCE
};

class DataType
{
    private:
        BaseType type;
        std::unique_ptr<DataType> subtype;

        friend std::ostream& operator<<(std::ostream&, const DataType&);
    public:
        DataType(BaseType);
        DataType(BaseType, DataType*);

        inline BaseType getBaseType() const
        {
            return this->type;
        }

        inline const DataType* getSubType() const
        {
            return this->subtype.get();
        }
        inline DataType* getSubType()
        {
            return this->subtype.get();
        }

        bool equals(const DataType&) const;
        DataType* copy() const;
        size_t size() const;

        bool isPointer() const;
        bool isArithmetic() const;
};

bool operator==(const DataType&, const DataType&);
bool operator!=(const DataType&, const DataType&);

std::ostream& operator<<(std::ostream&, const DataType&);

#endif // INTCODE_DATATYPE_HPP_INCLUDED
