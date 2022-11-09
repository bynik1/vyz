class Point
{
private:
    int id;
    int x;
    int y;
    int movemode;
    char* color;
    char trajectory;
    
public:

    void set_ball(int variant, int nomer);
    int get_id();
    int get_x();
    int get_y();
    char* get_color();
    void set_coords(int setx, int sety);

    void moving(int size);
    void set_movemode(int mode);
    void moving90lr(int size);
    void moving90ud(int size);
    void moving45(int size);
};
