#pragma once
#include <exception>
#include <string>

class client_exception : public std::exception
{
public:
    explicit client_exception(const std::string& message);
    ~client_exception() noexcept override = default;
    const char* what() const noexcept override;

private:
    std::string m_message;
};
