/*编程实现链式存储栈的基本操作。将若干正整数，压入栈，然后演示出栈操作。  要求：
  1)定义链式存储栈的数据结构。如下：
    #define  MAXLEN 100
    typedef
	  struct st0201
	  { int data;                    //链栈的数据域
        struct st0201 *next;         //链栈的指针域         
    }LinkSTACK;

  2)自定义函数实现相应的功能：顺序栈的初始化、建立栈（输入若干正整数，压入栈，即进栈）、出栈、取栈顶元素、显示栈的元素；
  3)主函数中生成如下菜单：
    *******************************************************************
	*   1、建立链式栈             	      2、显示栈中所有元素         *
    *   3、元素进栈                       4、元素出栈                 *
	*   5、取出栈顶元素                   0、退出                     *	
	*******************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXLEN 100      //链式存储栈的最大容量
//定义链式存储栈的数据结构
 typedef
	  struct st0201
	  { int data;                    //链栈的数据域
        struct st0201 *next;         //链栈的指针域         
    }LinkSTACK;

LinkSTACK *top=NULL;                //不带头结点的单项链表，top指针为链栈的栈顶指针，开始为null
//定义函数InitList，实现链式栈（元素）的建立、节点数据的初始化操作
void Initstack()                  
{

	LinkSTACK *p=NULL;            //指向新节点的指针
	int k=0;   //k=0->MAXLEN-1
	srand((unsigned long)time(NULL));
	//成员数组各个元素值初始化为0；
	while( k<MAXLEN && ++k ) 
	{
		p=(LinkSTACK *)malloc(sizeof(LinkSTACK));
		p->next=NULL;
		p->data=rand()%100+1;   //使数组每个成员的每个元素值为0
		printf("%5d%c",p->data,k%10==0?'\n':32);
	    if(top==NULL) top=p;
		else
		{
			p->next=top;   top=p;
		}	
	}
	puts("\n");
}


//函数DisplayStack显示栈的所有元素值
void DisplayStack()  
{
	int x=0,k=0;
	LinkSTACK *p;            //指向栈顶元素（指针）	
	printf("栈中元素（从栈顶到栈底）序列（值）：\n"); 
	 //栈不为空时（p->top>=0），依次取出栈顶的每个元素值
	while(top!=NULL)          // 栈为空时（top==NULL）
	{	
		p=top;                //使得p指针指向栈顶元素（节点）位置（指针）   
		x=top->data;          //先取出栈顶元素值保存在临时变量x中				
		printf("%5d%c",x,++k%10==0?'\n':32);    //显示栈顶各个元素，每一行显示10各元素
		top=top->next;        //移动栈顶top“指针”（栈顶指针指向下一个节点）
		free(p);
	}
	puts("\n");               //输出换行字符
}

void main()
{
	int flag=1,x,s=0; 
	while(flag)
	{ 
		system("cls");  //清除屏幕信息
		//显示菜单项	
		printf("\t*******************************************************************\n");
		printf("\t* 1、建立顺序栈                       2、显示栈中所有元素         *\n");
		printf("\t* 3、元素进栈                         4、元素出栈                 *\n");
		printf("\t* 5、取出栈顶元素                     0、退出                     *\n");		
		printf("\t*******************************************************************\n");
		printf("\t输入数字[0、1、2、3、4、5]：");
		scanf(" %d",&x);
		//选择判断，执行
		if(x>=0 && x<=7)   //容错技术
			switch(x)
			{				
				case 1: Initstack() ;       //调用函数初始化顺序栈
					     system("pause");     //执行DOS的暂停命令，暂停程序的执行，并显示一个提示
					     break;
				case 2:                       //调用函数建立书序栈
				         DisplayStack();                     
					     system("pause");    //执行DOS的暂停命令，暂停程序的执行，并显示一个提示
					     break;			
				case 3:  //元素进栈操作演示
					  // printf("输入一个正整数：");  
					  // scanf(" %d",&x);  	
					  // PushtoStack(&t,x);   //新元素值进栈				
					   system("pause");   //执行DOS的暂停命令，暂停程序的执行，并显示一个提示
					   break;
				case 4:  //元素值出栈操作演示
				      	 //x=PopfromStack(&t);
                         //printf("当前出栈的元素（也是栈顶元素）值为：%d\n",x);  					     
						 system("pause");     //执行DOS的暂停命令，暂停程序的执行，并显示一个提示
					     break;    
				case 5:   //取当前栈顶的元素，栈顶元素（位置）不变化。
                         //x=GetStackTop(&t);
                         //printf("当前栈顶的元素值为：%d\n",x);  	
					     system("pause");     //执行DOS的暂停命令，暂停程序的执行，并显示一个提示
					     break;
				case 6:         //显示（输出）栈中所有元素
				    //DisplayStack(&t);                     
					//system("pause");    //执行DOS的暂停命令，暂停程序的执行，并显示一个提示
					break;
				
				case 0: 
					system("cls");  //清除屏幕信息
					flag=0;         //终止循环，退出系统
					system("pause"); 
			}
		else  continue;	                //分析该语句的作用		
		//getchar();   
	}   
}