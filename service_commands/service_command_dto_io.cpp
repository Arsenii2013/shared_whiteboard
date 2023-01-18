#include "service_command_dto.hpp"

std::ostream& operator<<(std::ostream& stream,
                         const ServiceCommandDTO& dto){
    stream << dto.getName();
    return stream;
}

std::istream& operator>>(std::istream& stream,
                         ServiceCommandDTO& dto){
    std::string name;
    stream >> name;
    dto = ServiceCommandDTO{name};
    return stream;
}