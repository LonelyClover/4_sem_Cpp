//  FINISHED  //

#include <iostream>
#include <cmath>

class Rect
{
  private:
    int x, y;
    unsigned int wd, hd;

  public:
    Rect()
    {
      x = 0;
      y = 0;
      wd = 1;
      hd = 1;
    }

    Rect(int x_, int y_, unsigned int wd_, unsigned int hd_)
    {
      x = x_;
      y = y_;
      wd = wd_;
      hd = hd_;
    }

    Rect(unsigned int a)
    {
      x = 0;
      y = 0;
      wd = a;
      hd = a;
    }

    void print_corner()
    {
      std::cout << '(' << x << ',' << y << ')' << std::endl;
    }

    void print_sz()
    {
      std::cout << "wd=" << wd << " hd=" << hd << std::endl;
    }

    int area()
    {
      return wd * hd;
    }

    int perimeter()
    {
      return 2 * (wd + hd);
    }

    bool intersect(Rect r)
    {
      double this_center_x = x + wd / 2.0;
      double this_center_y = y + hd / 2.0;
      
      double r_center_x = r.x + r.wd / 2.0;
      double r_center_y = r.y + r.hd / 2.0;

      return abs(this_center_x - r_center_x) <= wd / 2.0 + r.wd / 2.0 && abs(this_center_y - r_center_y) <= hd / 2.0 + r.hd / 2.0;
    }
};

/*
using namespace std;

int main()
{
     Rect r1(-2, -3, 4, 5);
     Rect r2;
     Rect r3(7);
     r1.print_corner();
     r1.print_sz();

     int a2 = r2.area();
     int p2 = r2.perimeter();
        cout << a2 << " " << p2 << endl;

     if (r1.intersect(r3))
        cout << "YES";
     else
        cout << "NO";

     return 0;
}
*/
