int main()
{
    void * p = 0;
    void*& rp = p;
    int*& p2 = *static_cast<int**>( &rp );
}
