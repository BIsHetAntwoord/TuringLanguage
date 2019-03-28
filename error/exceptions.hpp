#ifndef EXCEPTIONS_HPP_INCLUDED
#define EXCEPTIONS_HPP_INCLUDED

#include <stdexcept>

class CompilerException : public std::runtime_error
{
    public:
        template <typename... Args>
        CompilerException(Args&&...);

        virtual ~CompilerException() = default;
};

class ParseException : public CompilerException
{
    public:
        template <typename... Args>
        ParseException(Args&&...);

        virtual ~ParseException() = default;
};

class SemanticException : public CompilerException
{
    public:
        template <typename... Args>
        SemanticException(Args&&...);

        virtual ~SemanticException() = default;
};

class TypeCheckException : public SemanticException
{
    public:
        template <typename... Args>
        TypeCheckException(Args&&...);

        virtual ~TypeCheckException() = default;
};

#include "error/exceptions.inl"

#endif // EXCEPTIONS_HPP_INCLUDED
