// node.h
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <vector>

// Node class: Represents a draggable object that can be placed on a canvas
class Node : public Fl_Group {
public:
    // Constructor to initialize the node with position, size, and label
    Node(int X, int Y, int W, int H, const char* label = nullptr)
        : Fl_Group(X, Y, W, H, label), dragging(false) {
        box(FL_UP_BOX);           // Set the node's box style
        labelsize(12);            // Set the font size of the label
        align(FL_ALIGN_TOP);      // Align label to the top
        end();                    // End the group, which is necessary for Fl_Group
    }

    // Handle mouse events for dragging the node
    int handle(int event) override {
        static int offsetX, offsetY;  // Offsets to track mouse movement

        switch (event) {
        case FL_PUSH:  // Mouse button press
            if (Fl::event_button() == FL_LEFT_MOUSE) {  // If left mouse button pressed
                dragging = true;
                offsetX = Fl::event_x() - x();  // Calculate offset from node's top-left corner
                offsetY = Fl::event_y() - y();  // Calculate vertical offset
                return 1;  // Event handled
            }
            break;
        case FL_DRAG:  // Mouse drag event
            if (dragging) {
                position(Fl::event_x() - offsetX, Fl::event_y() - offsetY);  // Update node position
                parent()->redraw();  // Redraw the parent widget to update the display
                return 1;  // Event handled
            }
            break;
        case FL_RELEASE:  // Mouse button release
            dragging = false;  // Stop dragging
            return 1;  // Event handled
        }
        return Fl_Group::handle(event);  // Let the base class handle other events
    }

private:
    bool dragging;  // Flag to check if the node is being dragged
};

// Canvas class: Represents a drawing area where nodes and connections are displayed
class Canvas : public Fl_Widget {
public:
    std::vector<std::pair<Node*, Node*>> connections;  // List of connections between nodes

    // Constructor to initialize the canvas size and position
    Canvas(int X, int Y, int W, int H) : Fl_Widget(X, Y, W, H) {}

    // Draw the canvas, including nodes and connections
    void draw() override {
        fl_push_clip(x(), y(), w(), h());  // Set the clipping region for the canvas
        fl_color(FL_GRAY);                  // Set the canvas background color
        fl_rectf(x(), y(), w(), h());      // Draw a filled rectangle as the background

        fl_color(FL_BLACK);  // Set the line color for connections
        for (auto& conn : connections) {
            Node* a = conn.first;  // First node in the connection
            Node* b = conn.second; // Second node in the connection

            // Calculate the center position of the first node
            int ax = a->x() + a->w() / 2;
            int ay = a->y() + a->h() / 2;

            // Calculate the center position of the second node
            int bx = b->x() + b->w() / 2;
            int by = b->y() + b->h() / 2;

            // Draw a line connecting the two nodes
            fl_line(ax, ay, bx, by);
        }

        fl_pop_clip();  // Restore the original clipping region
    }

    // Add a connection between two nodes and redraw the canvas
    void add_connection(Node* from, Node* to) {
        connections.emplace_back(from, to);  // Store the connection
        redraw();  // Redraw the canvas to show the new connection
    }
};

