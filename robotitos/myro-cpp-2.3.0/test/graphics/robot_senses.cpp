#include<Myro.h>
#include<iostream>
#include<boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

static const int y_spacing = 20;
static const int title_left_x = 20;

static const int win_width = 300;

static const int padding_width = 10;

static const int title_right_x = 80;
static const int two_field_spacing = ( (win_width-padding_width) - title_right_x ) / 2;
static const int three_field_spacing = ( (win_width-padding_width) - title_right_x ) / 3;

static const void draw_label(int level, const char* text, GraphWin& win){
    Text t(Point(title_left_x, y_spacing*level), text);
    t.draw(win);
}

int main(){

    connect();

    GraphWin win("Senses", win_width, y_spacing*9);
    // Constantly poll the mouse position and draw a circle
    draw_label(1,"Line: ", win);
    Point line_1_l(title_right_x, y_spacing*1);
    Text line_val_left(line_1_l, "0.0");
    line_val_left.draw(win);
    Point line_2_l(title_right_x+two_field_spacing, y_spacing*1);
    Text line_val_right(line_2_l, "0.0");
    line_val_right.draw(win);

    draw_label(2,"Stall: ", win);
    Point stall_l(title_right_x, y_spacing*2);
    Text stall_val(stall_l, "0");
    stall_val.draw(win);

    draw_label(3,"Bright: ", win);
    Point bright_1_l(title_right_x,y_spacing*3);
    Text bright_val_left(bright_1_l, "0");
    bright_val_left.draw(win);
    Point bright_2_l(title_right_x+three_field_spacing,y_spacing*3);
    Text bright_val_center(bright_2_l, "0");
    bright_val_center.draw(win);
    Point bright_3_l(title_right_x+three_field_spacing*2,y_spacing*3);
    Text bright_val_right(bright_3_l, "0");
    bright_val_right.draw(win);

    draw_label(4,"Obstacle: ", win);
    Point obstacle_1_l(title_right_x, y_spacing*4);
    Text obstacle_val_left(obstacle_1_l, "0");
    obstacle_val_left.draw(win);
    Point obstacle_2_l(title_right_x+three_field_spacing, y_spacing*4);
    Text obstacle_val_center(obstacle_2_l, "0");
    obstacle_val_center.draw(win);
    Point obstacle_3_l(title_right_x+three_field_spacing*2, y_spacing*4);
    Text obstacle_val_right(obstacle_3_l, "0");
    obstacle_val_right.draw(win);

    draw_label(5,"IR: ", win);
    Point ir_1_l(title_right_x, y_spacing*5);
    Text ir_left(ir_1_l, "0");
    ir_left.draw(win);
    Point ir_2_l(title_right_x+two_field_spacing, y_spacing*5);
    Text ir_right(ir_2_l, "0");
    ir_right.draw(win);

    draw_label(6,"Light: ", win);
    Point light_1_l(title_right_x, y_spacing*6);
    Text light_left(light_1_l, "0");
    light_left.draw(win);
    Point light_2_l(title_right_x+three_field_spacing, y_spacing*6);
    Text light_center(light_2_l, "0");
    light_center.draw(win);
    Point light_3_l(title_right_x+three_field_spacing*2, y_spacing*6);
    Text light_right(light_3_l, "0");
    light_right.draw(win);

    draw_label(7,"Battery: ", win);
    Point battery_l(title_right_x, y_spacing*7);
    Text battery_val(battery_l, "0");
    battery_val.draw(win);

    Scribbler::AllData data;
    while ( ! win.isClosed() ){
        data = robot.getAll();

        line_val_left.setText(lexical_cast<std::string>(data.line[0]));
        line_val_right.setText(lexical_cast<std::string>(data.line[1]));

        stall_val.setText(lexical_cast<std::string>(data.stall));

        bright_val_left.setText(lexical_cast<std::string>(data.bright[0]));
        bright_val_center.setText(lexical_cast<std::string>(data.bright[1]));
        bright_val_right.setText(lexical_cast<std::string>(data.bright[2]));

        obstacle_val_left.setText(lexical_cast<std::string>(data.obstacle[0]));
        obstacle_val_center.setText(lexical_cast<std::string>(data.obstacle[1]));
        obstacle_val_right.setText(lexical_cast<std::string>(data.obstacle[2]));

        ir_left.setText(lexical_cast<std::string>(data.ir[0]));
        ir_right.setText(lexical_cast<std::string>(data.ir[1]));

        light_left.setText(lexical_cast<std::string>(data.light[0]));
        light_center.setText(lexical_cast<std::string>(data.light[1]));
        light_right.setText(lexical_cast<std::string>(data.light[2]));

        battery_val.setText(lexical_cast<std::string>(data.battery));
        win.update();
    }
    disconnect();
    return 0;
}
