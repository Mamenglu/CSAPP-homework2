# homework2

> *p=a的意思：将a的值赋给p指针指向的地址的值,p=&a的意思是：将a的地址赋给指针p。

> gcc version: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
>
> Linux : Ubuntu 18.04

#### Part 1

首先判断是计算机是大端序还是小端序，

```c
  int B=-12345;
  int *p;
  int i;
  p=&B; //B的存储地址给p
  *p= 56789;
  char *pc;
  pc =(char*)&B;
```

p的存储地址为B的地址，并将p的地址赋值为56789，那么打印p[0]时结果为56789

```c
  //check pointer addressed value
  printf("%d = %8.8x\n",p[0],p[0]);
  printf("%d = %x\n",(char)pc[0],pc[0]&0xFF);

 //check local address & endian
 for(i=0;i<sizeof(B);i++)
 {
 	printf("localVar @ %p:%2.2x\n",pc+i,(unsigned char)*(pc+i));
 }
```

pc是一个字符串数组，存储的是B的地址，B的地址现在是56789，那么依次打印时即为从低地址向高地址打印，打印结果如下：

```c
56789 = 0000ddd5
-43 = d5
localVar @ 0x7ffc53c36240:d5
localVar @ 0x7ffc53c36241:dd
localVar @ 0x7ffc53c36242:00
localVar @ 0x7ffc53c36243:00
```

即低位存放在低地址，即为小端序。

打印gVar地址存放结果，如下：

```c
gVar @ 0x55b8edbe9014:78
gVar @ 0x55b8edbe9015:56
gVar @ 0x55b8edbe9016:34
gVar @ 0x55b8edbe9017:12
```

依旧是小端序。

#### Part 2

完善checkShift()函数输出结果的代码，得到如下结果：

```c
varBig1 : 0
varBig2 : 0
varBig3 : 0
varBig4 : 0
varBig5 : 0
varBig6 : 87123456
varBig7 : 12345600
varBig8 : 87123456
varBig9 : ff871234
uBig1 : 65432100
uBig2 : 87654321
uBig3 : 00876543
uBig4 : 87654321
varBig : 0
```

移位次数超过变量类型bit时，对常数，即前5个varBig，结果均为0，即确实移位的次数超过了变量类型的位，然后得到结果为0；对变量时，即varBig6789移位次数为n%最大bit，例如右移40位其实为右移8位，且为变量加括号时*varBig=(0x87123456)*为算数右移，uBig变量无括号为逻辑右移。

#### Part 3

修改inplaceReverseArray（）函数，由于该函数中调用 inpswap（）函数：

```c
void inpswap(int*x,int*y)
{
        *x=*x^*y;
        *y=*x^*y;
        *x=*x^*y;
}
```

阅读源代码，发现如下：

```c
for (first = 0, last = cnt-1; first < = last; first++,last--)
{
       inpswap(&a[first], &a[last]);
}
```

当有first=last时，inswap函数传入的两个参数相同，对table1来说传入table1[2]，然后对进行如下运算

```c
*table[2]=*table[2]^*table[2];//*table[2]=0
*table[2]=*table[2]^*table[2];//*table[2]=0
*table[2]=*table[2]^*table[2];//*table[2]=0
```

因此输出的结果中table[2]=0，讲终止条件改为first<last即可。