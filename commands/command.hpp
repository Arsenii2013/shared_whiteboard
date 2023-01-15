#ifndef SHARED_WHITEBOARD_COMMAND_HPP
#define SHARED_WHITEBOARD_COMMAND_HPP
#include "../image.hpp"

//абстрактный класс представляющий команду к доске
class Command{
protected:
    std::string name;
public:

    Command() = default;

    explicit Command(std::string name) : name(std::move(name)) {}

    [[nodiscard]] const std::string & get_name() const{
        return name;
    }

    virtual void redo(Image &) {};
    virtual void undo(Image &) {};

    virtual ~Command() = default;
};

#endif //SHARED_WHITEBOARD_COMMAND_HPP
