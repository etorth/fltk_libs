#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <cstdlib>

void button_callback(Fl_Widget* widget, void* data) {
    Fl_Box* box = (Fl_Box*)data;
    box->label("Button Clicked!");
    box->redraw();
}

int main(int argc, char** argv) {
    Fl_Window* window = new Fl_Window(400, 300, "FLTK Test");
    
    Fl_Box* box = new Fl_Box(50, 50, 300, 100, "FLTK 1.4.4 Static Library Test");
    box->box(FL_UP_BOX);
    box->labelsize(16);
    
    Fl_Button* button = new Fl_Button(150, 180, 100, 40, "Click Me");
    button->callback(button_callback, box);
    
    window->end();
    window->show(argc, argv);
    
    return Fl::run();
}
