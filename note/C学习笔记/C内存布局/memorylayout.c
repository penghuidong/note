
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <alloca.h>


//http://tech.ccidnet.com/art/302/20070108/995995_1.html
#define SHW_VAR_ADR(ID, I)                    \
printf("the %20s\t is at adr:%p\n", ID, &I); //��ӡ������ַ��


#define SHW_POT_ADR(ID, I)                    \
printf("the %20s\t is at adr:%p\n", ID, I);  //��ӡָ��ָ���ַ��


extern void afunc(void);

/*extern etext, edata, end;*/

/**
(1)ȫ�ֱ����;�̬�����Ĵ洢�Ƿ���һ��ģ�
��ʼ����ȫ�ֱ����;�̬������һ������RW data����
δ��ʼ����ȫ�ֱ�����δ��ʼ���ľ�̬���������ڵ���һ������BSS����
�����������ϵͳ�ͷ�
������(1).1   (1).2   (1).3����
**/
// (1).1  -- ֻҪ�Ǿ�̬��������ʹ�Ǿֲ��ģ�Ҳ���洢��ջ�У����Ǽ��洢�ھ�̬�����У����������Ƿ��ʼ�����ֱ�洢��BSS�κ�DATA��
static int /*bss_*/unini_glo_sta_var;                           //  ��̬δ��ʼ��ȫ�ֱ�������Ȼϵͳ��Ĭ�ϳ�ʼ��Ϊ0������Ȼ�����BSS��
static int /*data_*/ini_glo_sta_var = 10;                       //  ��̬��ʼ��ȫ�ֱ����������RW DATA��

// (1).2  --  ֻҪ��ȫ�ֱ��������洢�ھ�̬���򣬲��������Ƿ��ʼ�����ֱ�洢��BSS�κ�DATA��
int /*bss_*/unini_glo_var;                                      //  δ��ʼ��ȫ�����ݴ洢��BSS������
int /*data_*/ini_glo_var = 42;                                  //  ��ʼ��ȫ�����ݴ洢��RW DATA������

// (1).3  --  ȫ�ֳ������䱾����ȫ�ֱ��������洢�ھ�̬����, ͬ(1).2
const int unini_glo_cnt_var;                                        //  δ��ʼ��ȫ�ֳ���[����ȫ]�� �Զ���ʼ��Ϊ0�� ����Ȼ�����BSS��
const int ini_glo_cnt_var = 10;                                     //  ��ʼ��ȫ�ֳ������洢�ڳ�����
// ���ڳ���������Ҫע����������ڣ����ǲ��������������������洢�ڳ�����(RO data)��
// ������ֻ���ڴ洢��ʼ���õ�ȫ�ֳ����Լ��ַ�����������������ָ�룩
// �ֲ�������Ϊ�ֲ�����Ȼ�洢��ջ��
// ��Ϊ����������������һ��ģ�����Щ�η������У��ǲ����ڳ������ģ��������ʹ���κϳ�Ϊ��������
// ��������˵����ֻ�����������дȨ�ޣ����ֶ�дȨ�޵����ƿ����ڱ���׶��ɱ����������ƶ������ƣ�
// �������ϸ�ı�����������£����н׶εĴ���Ͳ����ڶԳ����Ķ�д��������˾�û��Ҫ�������ֲ�����Ҳ�洢�ڳ�����
// ������ɴ���ε�ӷ�ס�����

static int unini_glo_sta_cnt_var;
static int ini_glo_sta_cnt_var = 10;

int main(void)
{
    char *p_alloca = NULL, *b_malloc = NULL, *nb_malloc = NULL;

    // (1).4  �ֲ���̬��������Ȼ�Ǿ�̬������ͬ(1).1
    static int unini_sta_var;               //  �ֲ�δ��ʼ����̬�������洢��BSS��
    static int ini_sta_var = 10;            //  ��̬��ʼ���ֲ��������洢��DATA����

    // �ֲ��Ǿ�̬�����洢��ջ��
    // (2).1  --  �ֲ�����(���ܳ�ʼ��û��)�洢��ջ��
    int unini_var;                          //  �ֲ�δ��ʼ��������
    int ini_var = 10;                       //  �ֲ���ʼ������

    //  (2).2  --  �ֲ�����(���ܳ�ʼ��û��)�洢��ջ��, ͬ(2).1
    const int unini_cnt_var;            // δ����ʼ���ľֲ�����������ȫ���洢��ջ��
    const int ini_cnt_var = 10;         // �ֲ��������洢��ջ��

    //  (2).3  --  ָ�볣���ͳ���ָ�룬�䱾�ʻ��Ǿֲ��������߾ֲ��������洢��ջ�У�ͬ(2).1 (2).2
    const int *p_cnt_var =  &ini_cnt_var;   //  ָ������ָ��
    int * const cnt_p_var = &ini_var;       //  ָ�볣��
    const int * const cnt_p_cnt_var =  &unini_cnt_var;    // ָ�����ĳ�ָ��

    // (3)  �ַ����������洢�ڳ�����
    /*const */char* str_cnt = "ABCDE";      //  �ַ��������, �洢�ڳ�����, ����RO data��
                                            //  ������ȼ���const char* str1 = "ABCDE"
    char str_array[] = "ABCDE";             //  �ַ����飬 �൱�ڳ�ʼ���ľֲ��������洢��ջ��


/*    printf("Adr etext:%8x\t Adr edata %8x\t Adr end %8x\t\n", &etext, &edata, &end);*/

    // TEXT�� -- �����
    printf("------------------------------------------------------\n");
    printf(".Text Location:\n");
    SHW_VAR_ADR("main", main);              //�鿴�����main����λ��
    SHW_VAR_ADR("afunc", afunc);           //�鿴�����afunc����λ��
    printf("------------------------------------------------------\n\n");

    // BSS�� -- δ��ʼ��ȫ�ֱ�����
    printf("------------------------------------------------------\n");
    printf(".Bss Location:\n");
    SHW_VAR_ADR("unini_glo_sta_var", unini_glo_sta_var);                //  ȫ��δ��ʼ����̬����, ��BSS��
    SHW_VAR_ADR("unini_sta_var", unini_sta_var);                        //  δ��ʼ����̬��������BSS��
    SHW_VAR_ADR("unini_glo_cnt_var", unini_glo_cnt_var);                //  ȫ��δ��ʼ����������BSS��
    SHW_VAR_ADR("unini_glo_var", unini_glo_var);                        //  ȫ��δ��ʼ��������, BSS��
    SHW_VAR_ADR("unini_glo_sta_cnt_var", unini_glo_sta_cnt_var);        //  ȫ��δ��ʼ����̬��������BSS��
    printf("------------------------------------------------------\n\n");


    // RW DATA�� -- �ɶ�д�ѳ�ʼ�����ݶ�
    printf("------------------------------------------------------\n");
    printf(".Data Location:\n");
    SHW_VAR_ADR("ini_glo_sta_var", ini_glo_sta_var);                    //  ȫ�ֳ�ʼ����̬�����洢��RW data����
    SHW_VAR_ADR("ini_glo_var", ini_glo_var);                            //  ȫ�ֳ�ʼ�������洢��RW data

    SHW_VAR_ADR("ini_sta_var", ini_sta_var);                            //  �ֲ���ʼ����̬�����洢��RW data����

    SHW_VAR_ADR("ini_glo_sta_cnt_var", ini_glo_sta_cnt_var);            //  ȫ�־�̬�ѳ�ʼ���������洢��RW data����
    printf("------------------------------------------------------\n\n");

    // RO data  --  ֻ�����ݶ�
    printf("------------------------------------------------------\n\n");
    printf("RO data:\n");
    SHW_VAR_ADR("ini_glo_cnt_var", ini_glo_cnt_var);     // ��ʼ��ȫ�ֳ�����ͬ�ַ��������һ����λ���ı�������������
    SHW_POT_ADR("str_cnt point to RO data", str_cnt);    // �ַ�������������ڳ����������ı���
    SHW_VAR_ADR("point str_cnt in stack", str_cnt);      // ָ��str1������ջ��

    printf("------------------------------------------------------\n\n");

    // STACK -- ջ
    printf("------------------------------------------------------\n");
    printf("Stack Locations:\n");
    afunc();                                    // �ݹ����5��afunc����

    p_alloca = (char *)alloca(32);              // ��ջ�з���ռ�, ���������ͷ�
    if(p_alloca != NULL)
    {
        SHW_VAR_ADR("start", p_alloca);
        SHW_VAR_ADR("end",p_alloca + 31);
    }


    // �ֲ�����(���ܳ�ʼ��û��)�洢��ջ��
    SHW_VAR_ADR("unini_var", unini_var);
    SHW_VAR_ADR("ini_var", ini_var);

    // �ֲ�����(���ܳ�ʼ��û��)�洢��ջ��
    SHW_VAR_ADR("unini_cnt_var", unini_cnt_var);        // δ����ʼ���ľֲ�����������ȫ���洢��ջ��
    SHW_VAR_ADR("ini_cnt_var", ini_cnt_var);            // �ֲ��������洢��ջ��

    // ָ�볣���ͳ���ָ�룬�䱾�ʻ��Ǿֲ��������߳������洢��ջ��
    SHW_VAR_ADR("p_cnt_var", p_cnt_var);            // ��ָ������ָ�룬�䱾����ʵ��һ������ʼ���ģ��ֲ�����[ͬini_var], �洢��ջ��
    SHW_VAR_ADR("cnt_p_var", cnt_p_var);            // ��ָ�볣�����䱾����ʵ��һ����ʼ���ľֲ�����[ͬini_cnt_var]�� �洢��ջ��
    SHW_VAR_ADR("cnt_p_cnt_var", cnt_p_cnt_var);    // ��ָ������ָ�볣����Ϊһ����ʼ���ľֲ��������洢��ջ��

    SHW_POT_ADR("str_array", str_array);            // �ַ������飬�൱�ڳ�ʼ���ľֲ�������������ջ��
    SHW_VAR_ADR("str_array", str_array);            // ָ��str2������ջ�У����ַ���������ַ�������ĵ�ַ

    printf("------------------------------------------------------\n\n");


    printf("------------------------------------------------------\n");
    printf("Heap Locations:\n");
    b_malloc = (char *)malloc(32 * sizeof(char));   //�Ӷ��з���ռ�
    nb_malloc = (char *)malloc(16 * sizeof(char));  //�Ӷ��з���ռ�
    printf("the Heap start: %p\n", b_malloc);   //����ʼλ��
    printf("the Heap end:%p\n",(nb_malloc + 16 * sizeof(char)));//�ѽ���λ��

    // ָ��ָ��������ڶ��У�����ָ�뱾����ջ��
    printf("\nb and nb in Stack\n");
    SHW_VAR_ADR("b_malloc", b_malloc);       //��ʾջ������b��λ��
    SHW_VAR_ADR("b_malloc", nb_malloc);     //��ʾջ������nb��λ��
    free(b_malloc);               //�ͷ�����Ŀռ䣬�Ա����ڴ�й©
    b_malloc = NULL;
    free(nb_malloc);              //�ͷ�����Ŀռ䣬�Ա����ڴ�й©
    nb_malloc = NULL;
    printf("------------------------------------------------------\n\n");

    return EXIT_SUCCESS;
}

void afunc(void)
{
    static int long level = 0;          // ��̬���ݴ洢�����ݶ���
    int             stack_var;        // �ֲ��������洢��ջ��
    if(++level==5)                    // �˺����ݹ����5��
    {
        return;
    }
    printf("stack_var is at:%p\n",&stack_var);
    //      SHW_VAR_ADR("stack_var in stack section",stack_var);
    //      SHW_VAR_ADR("Level in data section",level);
    afunc();
}