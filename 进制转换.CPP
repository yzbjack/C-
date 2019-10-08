/*编程实现链式栈的基本操作。问题：将大于156的正整数转化成二、八、十六进制数压入栈中，然后显示出该正整数转化之后对应的进制数
  编程要求：
  1)定义栈的链式存储之数据结构。如下：    
    typedef
	  struct tmp{ unsigned int data;    //数据                     
             struct tmp *next;
    }LinkSTACK;
    并定义指针变量：*head=NULL,*p=NULL;
  2)自定义函数（原形：void initStack(unsigned int,unsigned int r),
  实现：链栈的初始化、将任意正整数转化为八进制进栈（建立栈）（链式存储）  
  3)自定义函数（原形：void outStack(unsigned int r),输出栈元素，实现输出正整数的八进制数。
    格式(156)=>* * * * * * * *    
  4)自定义函数（原形：int getvalue(int *p),实现输入任一正整数，小于156时重新输入。
    整正书通过指针“返回”，进制数[2、8、16]通过函数本身返回
*/

#include <stdio.h>
#include <stdlib.h>


//定义顺序栈的数据结构
typedef
	  struct tmp{
	         unsigned int data;                     
             struct tmp *next;
    }LinkSTACK;
 LinkSTACK *head=NULL,*p=NULL;

 //输入正整数（不得小于156）
 //输入转化成的进制数[2、8、16]
 //不满足要求，重新输入
 unsigned int getvalue(int *p)
 {
	 int r;
	 do{ printf("先输入正整数[>156],再输入转化成的进制数[2、8、16]:"); 
	 scanf(" %d %d",p,&r);   //p=>&x
	 }while(*p<156 &&  !(r==2 || r==8 || r==16) );
	 return r;     //返回进制数的数值2或8或16三个值其中之一
 }

 void outStack(int x,int r)
 {
      p=head;   //p指向头节点
	  printf("%d=>",x);
	 while(p)
	 {
		 //if(r==16)   //转化成16进制数时，结果值按字符方式输出
			  printf("%-3c%c",p->data,p->next==NULL?'\n':32);
		 //else       //转化成16进制数时，结果值按字符方式输出
		 //	  printf("%-3d%c",p->data,p->next==NULL?'\n':32);
		
        p=p->next;  		
	 }
    system("pause");
 }
 void initStack(int x,int r)
 {	 	 
	 while(x)
	 {
		 //1)建立新节点，并初始化成员
		p=(LinkSTACK *)malloc(sizeof(LinkSTACK));
		p->data=x%r;   //进栈		
		//if(r==16)
		//{
			if(x%r<10)	p->data=x%r+'0';   //进栈		
			else   p->data=x%r+'A'-10;     //进栈		
			//printf("%5d",p->data);
		//}		
        p->next=NULL;  
		//2)向前插入节点到链中：		
			if(head==NULL)  //(1)为空链表时；
			{	head=p; 	}		
			else            //(2)链表不为空
			{
	            p->next=head;   //向前插入新节点
				head=p;          //head指针指向新节点
			}
        x=x/r;    //转化为r进制的数，r的值只能是2、8、16其中之一;
	 }
	 puts("\n");
 }

void main()
{
   int x=0,r;
   r=getvalue(&x); 
   printf("x=%d  r=%d\n",x,r);
   initStack(x,r);
   outStack(x,r);
}