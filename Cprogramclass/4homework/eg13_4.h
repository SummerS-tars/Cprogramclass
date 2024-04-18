double power ( int m , int n )
{
    int i ;
    double y = 1.0 ;
    for ( i = 1 ; i <= n ; i ++ )
        y *= m ;
    
    return y ;
}