// Report
//little endian
//gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
//Ubuntu 18.04

#include <stdio.h>
//functions prototype declearation
void checkShift();
void inplaceReverseArray();
void reverse_array(int a[], size_t cnt);
int gVar;
void inswap(int *x,int *y);

int main()
{
        int x1=23,y1=0xAA;

        //pinter test
        int B=-12345;
        int *p;
        int i;
        p=&B; //B的存储地址给p
        *p= 56789;
        char *pc;
        pc =(char*)&B;

        //check pointer addressed value
        printf("%d = %8.8x\n",p[0],p[0]);
        printf("%d = %x\n",(char)pc[0],pc[0]&0xFF);
        
        //check local address & endian
        for(i=0;i<sizeof(B);i++)
        {
               printf("localVar @ %p:%2.2x\n",pc+i,(unsigned char)*(pc+i));
        }
	
        //check global address & endian
        pc=(char *)&gVar;
        gVar=0x12345678;
        for(i=0;i<sizeof(gVar);i++)
        {
               printf("gVar @ %p:%2.2x\n",pc+i,(unsigned char)*(pc+i));
        }
		
	//check code address
        printf("main @ %p\n",main);

	//check lib code address
        printf("printf @ %p\n",printf);
      	
      	
      	//check inplace swap
        x1=0x23;
        y1=0xAA;
        printf("before swap: %x,%x\n",x1,y1);
        inpswap(&x1,&y1);
        printf("after swap: %x,%x\n",x1,y1);
        printf("%d,%d\n",x1,y1);

        //check Logical/arithmetic shift
      	checkShift();

     	//use inplace swap reverse array element
     	inplaceReverseArray();

}


//check shfit bits>=variable size
//learn shift 
void checkShift()
{
	unsigned uBig=0x00123456;
	int varBig=(0x00123456>>32);
        printf("varBig1 : %x\n",varBig);
	
	//signed shift constant  by compiler
	varBig=(0x87123456 >>32);
	//code4output varBig result
	printf("varBig2 : %x\n",varBig);
	
	varBig=(0x87123456 >>40);
	//code4output varBig result
        printf("varBig3 : %x\n",varBig);
	

	varBig=(0x87123456 <<32);
	//code4output varBig result
        printf("varBig4 : %x\n",varBig);

	varBig=(0x87123456 <<40);
	//cod4output varBig result
        printf("varBig5 : %x\n",varBig);
	
	varBig=(0x87123456);
	varBig <<=32;
	//code4output varBig result
        printf("varBig6 : %x\n",varBig);
	
        //varable shift by CPU
	varBig=(0x87123456);
	varBig <<=40;
	//code4output varBig result
        printf("varBig7 : %x\n",varBig);

	varBig=(0x87123456);
	varBig >>=32;
	//code4output varBig result
        printf("varBig8 : %x\n",varBig);
	

	varBig=(0x87123456);
	varBig >>=40;
	//code4output varBig result
        printf("varBig9 : %x\n",varBig);
	
	//unsigned shift by variable
        uBig=0x87654321;
	uBig <<=40;
	//code4output uBig result
        printf("uBig1 : %x\n",uBig);
	
        uBig=0x87654321;
	uBig <<=32;
	//code output uBig result
        printf("uBig2 : %x\n",uBig);

	//unsigned shift by variable
        uBig=0x87654321;
	uBig >>=40;
	//code4output uBig result
        printf("uBig3 : %08x\n",uBig);
	
        uBig=0x87654321;
	uBig >>=32;
	//code output uBig result
        printf("uBig4 : %x\n",uBig);


	unsigned int varBig2=(0x123456 << 40);//compiler =>0
         printf("varBig : %x\n",varBig2);

}

//you can not use other array as intermidiate buffer
//参考 中文ebook  p38练习题2.11，完善代码，找出BUG
//ref  Englisg Book p91 Practice Problem 2.11 complete the code & find bugs
void inplaceReverseArray()
{
        int table1[]={1,2,3,4,5};
        int table2[]={1,2,3,4};

        //output table1 contents
        printf("table1: ");
        for(int i=0;i<5;i++)
        {
                printf("%d ",table1[i]);
        }
        printf("\n");

        reverse_array(table1,sizeof(table1)/sizeof(int));

        //output reversed table1 contents
         printf("reverse table1: ");
        for(int i=0;i<5;i++)
        {
                printf("%d ",table1[i]);
        }
        printf("\n");


        //output table2 contents
        printf("table2: ");
        for(int i=0;i<4;i++)
        {
                printf("%d ",table2[i]);
        }
        printf("\n");

        reverse_array(table2,sizeof(table2)/sizeof(int));

        //output reversed table2 contents
         printf("reverse table2: ");
        for(int i=0;i<4;i++)
        {
                printf("%d ",table2[i]);
        }
        printf("\n");

}


//reverseArray without buffer
//
void reverse_array(int a[], size_t cnt)
{

        size_t first, last;
        for (first = 0, last = cnt-1; first < last; first++,last--)
        {
                inpswap(&a[first], &a[last]);
        }
}


//swap without buffer
void inpswap(int*x,int*y)
{
        *x=*x^*y;
        *y=*x^*y;
        *x=*x^*y;
}

