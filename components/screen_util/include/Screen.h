#ifndef __SCREEN_H
#define __SCREEN_H

class CommonXY {
public:
    CommonXY(int x, int y) : x_(x), y_(y) {}
    CommonXY() : CommonXY(0, 0) {}
    CommonXY(const CommonXY &p) : CommonXY(p.x(), p.y()) {}
    int x() const { return x_; }
    int y() const { return y_; }
    void set_x(int v) { x_ = v; }
    void set_y(int v) { y_ = v; }

private:
    int x_;
    int y_;
};

typedef CommonXY Point;

template <typename ColorType>
class Screen {
public:
    Screen(int width, int height) : width_(width), height_(height) {}

    /// the basic drawing functions
    virtual void draw_point(const Point &p, ColorType color) {}

    /// the default `fill` is based on `draw_point`, which may be inefficient.
    /// Override this method when there are more efficient way.
    virtual void fill(const Point &p1, const Point &p2, ColorType color);
    virtual void clear(ColorType color);

    void draw_point_big(const Point &p, ColorType color);
    void draw_line(const Point &p1, const Point &p2, ColorType color);
    void draw_rectangle(const Point &p1, const Point &p2, ColorType color);

    /// helper for drawing circle
    void draw_point_x(const Point &p, int a, int b, ColorType color);
    void draw_circle(const Point &p, int r, ColorType color);

protected:
    int width_;
    int height_;
};

template <typename ColorType>
void Screen<ColorType>::fill(const Point &p1, const Point &p2, ColorType color) {
    for (int i = p1.x(); i < p2.x(); i++) {
        for (int j = p1.y(); j < p2.y(); j++) {
            draw_point(Point(i, j), color);
        }
    }
}

template <typename ColorType>
void Screen<ColorType>::clear(ColorType color) {
    fill(Point(0, 0), Point(width_, height_), color);
}

template <typename ColorType>
void Screen<ColorType>::draw_point_big(const Point &p, ColorType color) {
    fill(Point(p.x() - 1, p.y() - 1), Point(p.x() + 2, p.y() + 2), color);
}

template <typename T>
static inline T abs(T v) {
    return v < 0 ? -v : v;
}

template <typename T>
static inline T max(T a, T b) {
    return a > b ? a : b;
}

template <typename T>
static inline T unit_value(T v) {
    return v < 0 ? -1 : 1;
}

template <typename ColorType>
class LinePainter {
public:
    LinePainter(Screen<ColorType> &_screen, const Point &p1, const Point &p2, ColorType color1);
    void draw_line();

private:
    void draw_step();

private:
    Screen<ColorType> &screen;
    CommonXY cursor;
    CommonXY delta;
    CommonXY step;
    CommonXY acc;
    int distance;
    ColorType color;
};

template <typename ColorType>
LinePainter<ColorType>::LinePainter(Screen<ColorType> &_screen, const Point &p1, const Point &p2, ColorType color1)
        : screen(_screen), cursor(p1), delta(p2.x() - p1.x(), p2.y() - p1.y()), color(color1) {
    step.set_x(unit_value(delta.x()));
    step.set_y(unit_value(delta.y()));
    delta.set_x(abs(delta.x()));
    delta.set_y(abs(delta.y()));
    distance = max(delta.x(), delta.y());
}

template <typename ColorType>
void LinePainter<ColorType>::draw_step() {
    screen.draw_point(cursor, color);
    acc.set_x(acc.x() + delta.x());
    if (acc.x() >= distance) {
        acc.set_x(acc.x() - distance);
        cursor.set_x(cursor.x() + step.x());
    }
    acc.set_y(acc.y() + delta.y());
    if (acc.y() >= distance) {
        acc.set_y(acc.y() - distance);
        cursor.set_y(cursor.y() + step.y());
    }
}

template <typename ColorType>
void LinePainter<ColorType>::draw_line() {
    for (int i = 0; i <= distance; i++) {
        draw_step();
    }
}

template <typename ColorType>
void Screen<ColorType>::draw_line(const Point &p1, const Point &p2, ColorType color) {
    LinePainter<ColorType> p(*this, p1, p2, color);
    p.draw_line();
}

template <typename ColorType>
void Screen<ColorType>::draw_rectangle(const Point &p1, const Point &p2, ColorType color) {
    draw_line(p1, Point(p2.x(), p1.y()), color);
    draw_line(p2, Point(p1.x(), p2.y()), color);

    draw_line(Point(p1.x(), p2.y()), p1, color);
    draw_line(Point(p2.x(), p1.y()), p2, color);
}

template <typename ColorType>
void Screen<ColorType>::draw_point_x(const Point &p, int a, int b, ColorType color) {
    draw_point(Point(p.x() - a, p.y() + b), color);
    draw_point(Point(p.x() + a, p.y() - b), color);

    draw_point(Point(p.x() - a, p.y() - b), color);
    draw_point(Point(p.x() + a, p.y() + b), color);
}

template <typename ColorType>
void Screen<ColorType>::draw_circle(const Point &p, int r, ColorType color) {
    int px = r;
    int py = 0;
    int r_square = r * r;
    while (py <= px) {
        draw_point_x(p, py, px, color);
        draw_point_x(p, px, py, color);
        py++;
        if ((py * py + px * px) > r_square) {
            px--;
        }
    }
}

#endif
