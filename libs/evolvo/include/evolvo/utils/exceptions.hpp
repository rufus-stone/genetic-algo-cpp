#pragma once

#include <exception>
#include <string>


namespace ga::xcpt
{

// Base exception
class base : public std::exception
{
protected:
  std::string const err_msg;

public:
  explicit base(std::string const &msg) : err_msg(msg) {}

  [[nodiscard]] char const *what() const noexcept override
  {
    return err_msg.c_str();
  }
};


class invalid_parameter : public base
{
public:
  explicit invalid_parameter(std::string const &msg) : base(msg) {}
};

} // namespace ga::xcpt
