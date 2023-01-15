#include <SFML/Graphics.hpp>
#include <opencv2/opencv.hpp>

#include "commands/draw_text.hpp"
#include "image.hpp"
#include "tool/circle_maker.hpp"
#include "tool/rectangle_maker.hpp"
#include "tool/undo_maker.hpp"
#include "tool/line_maker.hpp"
#include "toolbar.hpp"
#include "tool/tool_tool.hpp"
#include "tool/thickness_changer.hpp"
#include "tool/color_changer.hpp"
#include "toolbar_resource_loader.hpp"
#include "tool/redo_maker.hpp"
#include "tool/text_maker.hpp"

//TODO add data validation
//TODO add network module
//TODO split into cpp and hpp

MouseEvent castToMouseEvent(int event){
    if(event == cv::MouseEventTypes::EVENT_MOUSEMOVE){
        return MouseEvent::MOVE;
    }else if(event == cv::MouseEventTypes::EVENT_LBUTTONUP){
        return MouseEvent::LUP;
    }else if(event == cv::MouseEventTypes::EVENT_RBUTTONUP){
        return MouseEvent::RUP;
    }else if(event == cv::MouseEventTypes::EVENT_LBUTTONDOWN){
        return MouseEvent::LDOWN;
    }else if(event == cv::MouseEventTypes::EVENT_RBUTTONDOWN){
        return MouseEvent::RDOWN;
    }else {
        return MouseEvent::ERROR;
    }
}

class ToolCallback{
    Whiteboard& board;
    Toolbar& tb;

    void process(int event, int x, int y, int flags){
        tb.getActiveTool().processMouseEvent(castToMouseEvent(event), x, y);
        if(tb.getActiveTool().getName().substr(0, 4) == "Draw") {
            auto& dwtool = dynamic_cast<DrawingTool &>(tb.getActiveTool());
            if (dwtool.ready()) {
                bool final = dwtool.final();
                board.add_and_redo(dwtool.getCommand());
                cv::imshow("Whiteboard", board.getBoard().getStorage());
                if(!final){
                    board.undo_and_remove();
                }
            }
        }else if(tb.getActiveTool().getName().substr(0, 7) == "Service"){
            auto& stool = dynamic_cast<ServiceTool &>(tb.getActiveTool());
            if (stool.ready()) {
                auto cmd = stool.getCommand();
                cmd->execute(board);
                cv::imshow("Whiteboard", board.getBoard().getStorage());
            }
        }
    }
public:
    ToolCallback(Whiteboard &board, Toolbar &tb) : board(board), tb(tb) {}

    static void callback(int event, int x, int y, int flags, void* userdata){
        ((ToolCallback*)userdata)->process(event, x, y, flags);
    }
};

class ToolbarCallback{
    Toolbar& tb;
    void process(int event, int x, int y, int flags){
        tb.processMouseEvent(castToMouseEvent(event), x, y);
        if(tb.getActiveTool().getName().substr(0, 4) == "Tool"){
            auto& ttool = dynamic_cast<ToolTool &>(tb.getActiveTool());
            ttool.processMouseEvent(castToMouseEvent(event), x, y);
            tb.for_each_drawing_tool(ttool.getCommand());
        }
    }
public:
    explicit ToolbarCallback(Toolbar &tb) : tb(tb) {}

    static void callback(int event, int x, int y, int flags, void* userdata){
        ((ToolbarCallback*)userdata)->process(event, x, y, flags);
    }
};

int main(int argc, char** argv)
{
    Whiteboard whiteboard{1000, 1000, {256, 256, 256}};

    cv::namedWindow("Whiteboard", cv::WINDOW_AUTOSIZE );
    cv::namedWindow("Tools", cv::WINDOW_AUTOSIZE );

    ToolbarResourceLoader loader{"../resources"};

    Toolbar tb{{std::pair{std::make_shared<Tool>("Empty"), loader.get("Empty")},
                      std::pair{std::make_shared<CircleMaker>(1, Color{0, 0 , 0}), loader.get(ToolName::DrawPrefix + ToolName::Circle)},
                      std::pair{std::make_shared<RectangleMaker>(1, Color{0, 0 , 0}), loader.get(ToolName::DrawPrefix + ToolName::Rectangle)},
                      std::pair{std::make_shared<LineMaker>(1, Color{0, 0 , 0}), loader.get(ToolName::DrawPrefix + ToolName::PolyLine)},
                      std::pair{std::make_shared<TextMaker>(1, Color{0, 0 , 0}), loader.get(ToolName::DrawPrefix + ToolName::Text)},
                      std::pair{std::make_shared<ThicknessChanger>(0, 100, 20), loader.get(ToolName::ToolPrefix + ToolName::Thickness)},
                      std::pair{std::make_shared<ColorChanger>(Rectangle{0, 100, 600, 700}), loader.get(ToolName::ToolPrefix + ToolName::Color)},
                      std::pair{std::make_shared<UndoMaker>(), loader.get(ToolName::ServicePrefix + ToolName::Undo)},
                      std::pair{std::make_shared<RedoMaker>(), loader.get(ToolName::ServicePrefix + ToolName::Redo)}}};

    ToolCallback tc{whiteboard, tb};
    cv::setMouseCallback("Whiteboard", ToolCallback::callback, &tc);

    ToolbarCallback tbc{tb};

    cv::setMouseCallback("Tools", ToolbarCallback::callback, &tbc);
    cv::imshow("Tools", tb.getImage().getStorage());

    cv::imshow("Whiteboard", whiteboard.getBoard().getStorage());

    while (true) {
        auto key = ASCIIKey(cv::waitKey(0));

        tb.getActiveTool().processKey(key);

        if(tb.getActiveTool().getName().substr(0, 4) == "Draw") {
            auto& dwtool = dynamic_cast<DrawingTool &>(tb.getActiveTool());
            if (dwtool.ready()) {
                bool final = dwtool.final();
                whiteboard.add_and_redo(dwtool.getCommand());
                cv::imshow("Whiteboard", whiteboard.getBoard().getStorage());
                if(!final){
                    whiteboard.undo_and_remove();
                }
            }
        }else if(tb.getActiveTool().getName().substr(0, 7) == "Service"){
            auto& stool = dynamic_cast<ServiceTool &>(tb.getActiveTool());
            if (stool.ready()) {
                auto cmd = stool.getCommand();
                cmd->execute(whiteboard);
                cv::imshow("Whiteboard", whiteboard.getBoard().getStorage());
            }
        }
    }

    return 0;
}