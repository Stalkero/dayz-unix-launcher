#pragma once

#include <exception>
#include <string>

class HtmlParserException : public std::exception
{
    public:
        explicit HtmlParserException(std::string const &error);

        char const *what() const noexcept override;

    private:
        std::string message;
};
