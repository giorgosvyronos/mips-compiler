int g(int x, int y,int z)
{   
    x = x + 1;
    return x+y+z;
}

int f()
{
    int x=16;
    return g(10,3,x);
}
