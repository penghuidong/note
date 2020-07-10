#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <alloca.h>

#define shw_var_addr(id, i) printf("the %20s\t is at addr: %p\n", id,&i);
#define shw_pot_addr(id, i) printf("the %20s\t is at addr: %p\n", id, i);

extern void afunc(void);

// ȫ�ֱ����;�̬�����Ǵ洢��һ���
// ��ʼ����ȫ�ֱ�������ʼ���ľ�̬������һ������ RW data
// δ��ʼ����ȫ�ֱ�����δ��ʼ���ľ�̬������ BSS
// �������ʱ��ϵͳ�ͷ�

/*  ֻҪ�Ǿ�̬��������ʹ�Ǿֲ��ģ�Ҳ���洢ֻ��ջ�У�
 *  ���Ǵ洢�ھ�̬�����У����������Ƿ��ʼ����
 *  �ֱ�洢��BSS�� �� data��
*/
// δ��ʼ����̬ȫ�ֱ�������Ȼϵͳ��Ĭ�ϳ�ʼ��Ϊ0������Ȼ�����BSS
static int unini_glo_sta_var;
// ��̬��ʼ��ȫ�ֱ����������RW data
static int ini_glo_sta_var = 10;

/* ֻҪ��ȫ�ֱ��������洢�ھ�̬���򣬲��������Ƿ��ʼ����
 * �ֱ�洢��BSS�κ�data��
 */
int unini_glo_var;    //δ��ʼ���� BSS������
int ini_glo_var = 42; //��ʼ����RW data������

/*ȫ�ֳ������䱾����ȫ�ֱ������洢�ھ�̬����ͬȫ�ֱ���*/
//δ��ʼ��ȫ�ֳ���[����ȫ]���Զ���ʼ��Ϊ0������BSS��
const int unini_glo_cnt_var;   
const int ini_glo_cnt_var = 10;  //�洢�ڳ�����RO data

/*	���ڳ��������ǲ���ȫ���洢�ڳ�����ro data��
 *	������ֻ�洢 ��ʼ����ȫ�ֳ��� �� �ַ�����������(����ָ��)��
 *	�ֲ�������Ϊ�ֲ����ݴ洢��ջ�С�
 *	��Ϊ����������������һ��ģ�����������ֻ�����������дȨ�ޣ�
 *	���ֶ�дȨ�޵����ƿ����ڱ���׶��ɱ����������ƶ������ƣ�
 *	�������ϸ�ı�����������£����н׶εĴ���Ͳ����ڶԳ����Ķ�д������
 *	��˾�û��Ҫ�������ֲ������洢�ڳ�������
 *	������ɴ���ε�ӷ��
*/

static const int unini_glo_sta_cnt_var;
static const int ini_glo_sta_cnt_var = 10;

int main()
{
	char* p_alloca = NULL, * b_malloc = NULL, *nb_malloc = NULL;

	static int unini_sta_var;   // �ֲ�δ��ʼ����̬�������洢��BSS��
	static int ini_sta_var = 10;// ��̬��ʼ���ֲ��������洢��rw data

	// �ֲ�����������û�г�ʼ�����洢��ջ��
	int unini_var;
	int ini_var = 10;

	// �ֲ�����������û�г�ʼ�����洢��ջ��
	const int unini_cnt_var;   //δ��ʼ��������ȫ
	const int ini_cnt_var = 10;

	// ָ�볣���ͳ���ָ�룬�䱾�ʻ��Ǿֲ�����/�������洢��ջ��
	const int* p_cnt_var = &ini_cnt_var;            // ָ������ָ��
	int* const cnt_p_var = &ini_var;                // ָ�뱾���ǳ���
	const int* const cnt_p_cnt_var = &unini_cnt_var;// ָ������constָ��

	/*�ַ����������洢�ڳ�����*/
	char* str_cnt = "ABCDE";   // �ַ����������洢��ro data 
	char str_array[] = "ABCDE";// �ַ����飬�൱�ڳ�ʼ���ľֲ��������洢��ջ

	/*.bss δ��ʼ��ȫ�ֱ�����*/
	printf("--------------------------------------------------------\n");
	printf(".bss location:\n");
	shw_var_addr("unini_glo_sta_var", unini_glo_sta_var);
	shw_var_addr("unini_glo_sta_cnt_var", unini_glo_sta_cnt_var);
	shw_var_addr("unini_sta_var", unini_sta_var);
	shw_var_addr("unini_glo_cnt_var", unini_glo_cnt_var);
	shw_var_addr("unini_glo_var", unini_glo_var);
	printf("--------------------------------------------------------\n\n");
	
	/*.rw data �ɶ�д�ѳ�ʼ�����ݶ�*/
	printf("--------------------------------------------------------\n");
	printf("rw.data location:\n");
	shw_var_addr("ini_glo_sta_var", ini_glo_sta_var);
	shw_var_addr("ini_glo_var", ini_glo_var);
	shw_var_addr("ini_sta_var", ini_sta_var);
	printf("--------------------------------------------------------\n\n");

	/*.ro data ֻ�����ݶ�*/
	printf("--------------------------------------------------------\n");
	printf("ro.data location:\n");
	shw_var_addr("ini_glo_cnt_var", ini_glo_cnt_var);
	shw_var_addr("ini_glo_sta_cnt_var", ini_glo_sta_cnt_var);
	/*�ַ���ָ��ָ���������.ro data,ָ�뱾��洢��ջ��*/
	shw_pot_addr("str_cnt_point to RO data", str_cnt); 
	printf("--------------------------------------------------------\n\n");
	
	/*�����*/
	printf("--------------------------------------------------------\n");
	printf(".text location:\n");
	shw_var_addr("main", main);
	shw_var_addr("afunc", afunc);
	printf("--------------------------------------------------------\n\n");

	/*stack ��*/
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
	/*�ֲ�����������û�г�ʼ�����洢��ջ��*/
	shw_var_addr("unini_var", unini_var);
	shw_var_addr("ini_var", ini_var);
	
	/*�ֲ�����������û�г�ʼ�����洢��ջ��*/
	shw_var_addr("unini_cnt_var", unini_cnt_var);
	shw_var_addr("ini_cnt_var", ini_cnt_var);
	
	/*ָ�볣���ͳ���ָ�룬�䱾�ʻ��Ǿֲ�����/�������洢��ջ��*/
	shw_var_addr("p_cnt_var",p_cnt_var);   //ָ������ָ�룬�����Ǿֲ�����
	shw_var_addr("cnt_p_var", cnt_p_var);  //constָ�룬�����Ǿֲ�����
	shw_var_addr("cnt_p_cnt_var", cnt_p_cnt_var);//constָ��ָ�����������Ǿֲ�����

	//ָ��ro data���ַ�����ָ�룬�����Ǿֲ�����
	shw_var_addr("point str_cnt in stack", str_cnt);
	shw_pot_addr("str_array", str_array);//�ַ������飬�൱�ڳ�ʼ�������飬������ջ
	shw_var_addr("str_array", str_array);//ָ��ĵ�ַ�Ǳ���
	printf("--------------------------------------------------------\n\n");
	
	/*heap ��*/
	printf("--------------------------------------------------------\n");
	printf("heap location:\n");
	b_malloc = (char*)malloc(32*sizeof(char));
	nb_malloc = (char*)malloc(16*sizeof(char));
	printf("the heap start: %20p\n", b_malloc);
	printf("the heap end:   %20p\n", (nb_malloc+16 * sizeof(char)));
	printf("--------------------------------------------------------\n\n");
	
	/*stack ��*/ 
	printf("--------------------------------------------------------\n");
	printf("b and nb in stack\n");
	// ָ��ָ����ڴ���heap�У�ָ�뱾����ջ��
	shw_var_addr("b_malloc", b_malloc); 
	shw_var_addr("b_malloc", nb_malloc);

	free(b_malloc);
	b_malloc = NULL;
	free(nb_malloc);
	nb_malloc = NULL;   //����һ��ֵ��ѧϰ�ĵط����ͷ����ڴ����ָ��ΪNULL
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