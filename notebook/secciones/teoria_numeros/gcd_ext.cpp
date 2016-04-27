void gcd_ext(int a, int b, int&x, int& y, int& d) 
{
    if (b == 0) { x = 1; y = 0; d = a; return; }
    gcd_ext(b, a % b,x,y,d);
    int x1 = y;
    int y1 = x - (a / b) * y;
    x = x1;
    y = y1;
}
    