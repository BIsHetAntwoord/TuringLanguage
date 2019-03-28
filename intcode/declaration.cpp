#include "intcode/declaration.hpp"
#include "intcode/datatype.hpp"
#include "intcode/intinstr.hpp"

Declaration::Declaration(const std::string& name, DataType* type, IntInstr* content) : name(name), type(type), content(content) {}
