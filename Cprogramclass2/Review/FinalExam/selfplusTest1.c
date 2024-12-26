#include <stdio.h>

void func( int a, int b , int c )
{
    printf("a = %d, b = %d, c = %d\n", a, b, c);
}

int main()
{
    int a = 1 ;
    func( a++ , a++ , a++ ) ;
    a = 1;
    func( a++ , a++ , ++a ) ;
    a = 1;
    func( a++ , ++a , a++ ) ;
    a = 1;
    func( ++a , a++ , a++ ) ;
    a = 1;
    func( ++a , ++a , ++a ) ;
    a = 1;
    func( a++ , a , ++a ) ;
    a = 1;
    func( a , ++a , ++a ) ;
    a = 1;
    func( ++a , a++ , a ) ;
    return 0;

    /**
     * 总结：
     * 函数调用中实参出现自增运算符
     * 理解点：
     * 1. 函数调用实参进入顺序为从右到左
     * 2. a++ 会不管如何先传入a运算到此时的值，再自增
     * 3. ++a 会进行自增，但会返回计算完所有实参时的a的值
     * 4. a 也是传入最后计算完所有实参后的a的值
     * 
     * 理解不了也没关系
     * 计算规律：
     * 1. 从右到左计算
     * 2. 碰到a 先不传入，a值不变，继续往左计算
     * 3. 碰到a++ 先传入a的值，再a自增，继续往左计算
     * 4. 碰到++a 先不传入，a自增，继续往左计算
     * 5. 计算完所有实参表达式后，再将最后的a的值代替之前所有的++a 和a 的实参传入
     * 
     * 最后，我的评价是没事不要乱写这种东西
     */
}