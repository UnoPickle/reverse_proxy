#pragma once
#include <exception>
#include <string>

class server_exception : public std::exception
{
public:
    explicit server_exception(const std::string& message);
    ~server_exception() noexcept override = default;

    const char* what() const noexcept override;

private:
    std::string m_message;
};
