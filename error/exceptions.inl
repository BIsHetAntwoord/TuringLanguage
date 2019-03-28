#include <sstream>
#include <utility>

template <typename... Args>
std::string make_msg(Args&&... args)
{
    std::stringstream ss;
    ((ss << args), ...);
    return ss.str();
}

template <typename... Args>
CompilerException::CompilerException(Args&&... args) : std::runtime_error(make_msg(std::forward<Args>(args)...)) {}

template <typename... Args>
ParseException::ParseException(Args&&... args) : CompilerException(std::forward<Args>(args)...) {}

template <typename... Args>
SemanticException::SemanticException(Args&&... args) : CompilerException(std::forward<Args>(args)...) {}

template <typename... Args>
TypeCheckException::TypeCheckException(Args&&... args) : SemanticException(std::forward<Args>(args)...) {}
