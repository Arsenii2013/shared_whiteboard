#ifndef SHARED_WHITEBOARD_SERVICE_COMMAND_DTO_HPP
#define SHARED_WHITEBOARD_SERVICE_COMMAND_DTO_HPP
#include <string>

class ServiceCommandDTO final{
    std::string name;

public:
    ServiceCommandDTO() = default;

    explicit ServiceCommandDTO(std::string name) : name(std::move(name)) {}

    [[nodiscard]] const std::string &getName() const {
        return name;
    }

};

std::ostream& operator<<(std::ostream& stream,
                         const ServiceCommandDTO& dto);

std::istream& operator>>(std::istream& stream,
                         ServiceCommandDTO& dto);
#endif //SHARED_WHITEBOARD_SERVICE_COMMAND_DTO_HPP
