#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <alloca.h>

#define shw_var_addr(id, i) printf("the %20s\t is at addr: %p\n", id,&i);
#define shw_pot_addr(id, i) printf("the %20s\t is at addr: %p\n", id, i);

extern void afunc(void);

// 全局变量和静态变量是存储在一块的
// 初始化的全局变量、初始化的静态变量在一块区域 RW data
// 未初始化的全局变量、未初始化的静态变量在 BSS
// 程序结束时由系统释放

/*  只要是静态变量，即使是局部的，也不存储只在栈中，
 *  而是存储在静态区域中，并依据其是否初始化，
 *  分别存储在BSS段 和 data段
*/
// 未初始化静态全局变量，虽然系统会默认初始化为0，但仍然存放在BSS
static int unini_glo_sta_var;
// 静态初始化全局变量，存放在RW data
static int ini_glo_sta_var = 10;

/* 只要是全局变量，即存储在静态区域，并依据其是否初始化，
 * 分别存储在BSS段和data段
 */
int unini_glo_var;    //未初始化， BSS数据区
int ini_glo_var = 42; //初始化，RW data数据区

/*全局常量，其本身是全局变量，存储在静态区域，同全局变量*/
//未初始化全局常量[不安全]，自动初始化为0，存在BSS中
const int unini_glo_cnt_var;   
const int ini_glo_cnt_var = 10;  //存储在常量区RO data

/*	对于常量，它们并不全部存储在常量区ro data，
 *	常量区只存储 初始化的全局常量 和 字符串变量本身(不是指针)，
 *	局部常量作为局部数据存储于栈中。
 *	因为常量区与代码段是在一起的，而常量本身只是限制了其读写权限，
 *	这种读写权限的限制可以在编译阶段由编译器进行制定和限制，
 *	这样在严格的编译器审查结果下，运行阶段的代码就不存在对常量的读写操作，
 *	因此就没必要将其他局部常量存储在常量区，
 *	否则将造成代码段的臃肿
*/

static const int unini_glo_sta_cnt_var;
static const int ini_glo_sta_cnt_var = 10;

int main()
{
	char* p_alloca = NULL, * b_malloc = NULL, *nb_malloc = NULL;

	static int unini_sta_var;   // 局部未初始化静态变量，存储在BSS段
	static int ini_sta_var = 10;// 静态初始化局部变量，存储在rw data

	// 局部变量不管有没有初始化都存储在栈中
	int unini_var;
	int ini_var = 10;

	// 局部常量不管有没有初始化都存储在栈中
	const int unini_cnt_var;   //未初始化，不安全
	const int ini_cnt_var = 10;

	// 指针常量和常量指针，其本质还是局部变量/常量，存储于栈中
	const int* p_cnt_var = &ini_cnt_var;            // 指向常量的指针
	int* const cnt_p_var = &ini_var;                // 指针本身是常量
	const int* const cnt_p_cnt_var = &unini_cnt_var;// 指向常量的const指针

	/*字符串常量，存储在常量区*/
	char* str_cnt = "ABCDE";   // 字符串字面量存储在ro data 
	char str_array[] = "ABCDE";// 字符数组，相当于初始化的局部变量，存储于栈

	/*.bss 未初始化全局变量区*/
	printf("--------------------------------------------------------\n");
	printf(".bss location:\n");
	shw_var_addr("unini_glo_sta_var", unini_glo_sta_var);
	shw_var_addr("unini_glo_sta_cnt_var", unini_glo_sta_cnt_var);
	shw_var_addr("unini_sta_var", unini_sta_var);
	shw_var_addr("unini_glo_cnt_var", unini_glo_cnt_var);
	shw_var_addr("unini_glo_var", unini_glo_var);
	printf("--------------------------------------------------------\n\n");
	
	/*.rw data 可读写已初始化数据段*/
	printf("--------------------------------------------------------\n");
	printf("rw.data location:\n");
	shw_var_addr("ini_glo_sta_var", ini_glo_sta_var);
	shw_var_addr("ini_glo_var", ini_glo_var);
	shw_var_addr("ini_sta_var", ini_sta_var);
	printf("--------------------------------------------------------\n\n");

	/*.ro data 只读数据段*/
	printf("--------------------------------------------------------\n");
	printf("ro.data location:\n");
	shw_var_addr("ini_glo_cnt_var", ini_glo_cnt_var);
	shw_var_addr("ini_glo_sta_cnt_var", ini_glo_sta_cnt_var);
	/*字符串指针指向的内容在.ro data,指针本身存储在栈中*/
	shw_pot_addr("str_cnt_point to RO data", str_cnt); 
	printf("--------------------------------------------------------\n\n");
	
	/*代码段*/
	printf("--------------------------------------------------------\n");
	printf(".text location:\n");
	shw_var_addr("main", main);
	shw_var_addr("afunc", afunc);
	printf("--------------------------------------------------------\n\n");

	/*stack 段*/
	printf("--------------------------------------------------------\n");
	printf("stack location:\n");
	afunc();
	printf("\n");

	p_alloca = (char*)alloca(32);
	if(p_alloca!=NULL)
	{
		shw_var_addr("start", p_alloca);
		shw_var_addr("end", p_alloca+31);
	}
	/*局部变量不管有没有初始化都存储在栈中*/
	shw_var_addr("unini_var", unini_var);
	shw_var_addr("ini_var", ini_var);
	
	/*局部常量不管有没有初始化都存储在栈中*/
	shw_var_addr("unini_cnt_var", unini_cnt_var);
	shw_var_addr("ini_cnt_var", ini_cnt_var);
	
	/*指针常量和常量指针，其本质还是局部变量/常量，存储在栈中*/
	shw_var_addr("p_cnt_var",p_cnt_var);   //指向常量的指针，本身是局部变量
	shw_var_addr("cnt_p_var", cnt_p_var);  //const指针，本身是局部常量
	shw_var_addr("cnt_p_cnt_var", cnt_p_cnt_var);//const指针指向常量，本身是局部常量

	//指向ro data中字符串的指针，本身是局部变量
	shw_var_addr("point str_cnt in stack", str_cnt);
	shw_pot_addr("str_array", str_array);//字符串数组，相当于初始化的数组，保存于栈
	shw_var_addr("str_array", str_array);//指针的地址是本身
	printf("--------------------------------------------------------\n\n");
	
	/*heap 段*/
	printf("--------------------------------------------------------\n");
	printf("heap location:\n");
	b_malloc = (char*)malloc(32*sizeof(char));
	nb_malloc = (char*)malloc(16*sizeof(char));
	printf("the heap start: %20p\n", b_malloc);
	printf("the heap end:   %20p\n", (nb_malloc+16 * sizeof(char)));
	printf("--------------------------------------------------------\n\n");
	
	/*stack 段*/ 
	printf("--------------------------------------------------------\n");
	printf("b and nb in stack\n");
	// 指针指向的内存在heap中，指针本身在栈中
	shw_var_addr("b_malloc", b_malloc); 
	shw_var_addr("b_malloc", nb_malloc);

	free(b_malloc);
	b_malloc = NULL;
	free(nb_malloc);
	nb_malloc = NULL;   //这是一个值得学习的地方：释放完内存后置指针为NULL
	printf("--------------------------------------------------------\n\n");
	
	return EXIT_SUCCESS;
}

void afunc(void)
{
	static int long level = 0;
	int stack_var;
	if(++level==5)
		return;
	shw_var_addr("stack_var", stack_var);
	afunc();
}