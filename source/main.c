/******************  STCBSP����Demo��STC_DemoV3 *************************** 
STCBSP�ṩ�ĵײ�֧�ֺ�Ӧ�ò㺯��֧������"STC-Bѧϰ��"����ͬʱ������
     	1���������ʾ
		2��LEDָʾ����ʾ
		3��ʵʱʱ��
		4���¶ȹ��ղ���
		5�����ֲ���
		6��FM������
		7��EXT��չ�ӿڣ����ӳӡ���������ࡢ��ת��������PWM���ƣ�4ѡ1������
		8���񶯴�����
		9������������
		10�������������
		11������1ͨ��
		12������2ͨ�ţ�485��EXT��չ�ӿڣ�2ѡ1��
		13������ң��
		14�������շ�ͨ��
		15������ʧ��NVM�洢��DS1302�ṩ31�ֽڣ�M24C02�ṩ256�ֽڣ�
����ʹ�÷�����μ���ģ��ͷ�ļ���

��STC_DemoV3ʾ������Դ������main.c��main.h��function.c��������ɣ������������£�		 
		1������Key2�л�"��ʾ"��"��������"ģʽ��ģʽֵ��LED����ʾ��������������ģʽ�У�
					 ģʽ1��ʵʱʱ�ӣ������գ�
					 ģʽ2��ʵʱʱ�ӣ�ʱ���룩
					 ģʽ3���¶ȡ����ղ���
					 ģʽ4�����ֲ���
					 ģʽ5��FM������
					 ģʽ6����������ࣨ��Ҫ��EXT�Ͻӳ��������ģ�飩
					 ģʽ7�����ӳ�    ����Ҫ��EXT�Ͻӵ��ӳ�ģ�飩
    2���������ʾ�������������ܣ�
		       ��ģʽ1�£��������ʾʵʱʱ��RTC   "����-����-����"���������� "��"�� ������˳�"����������"��"�ϡ��¡�����"����
		       ��ģʽ2�£��������ʾʵʱʱ��RTC   "ʱʱ-�ַ�-����"���������� "��"�� ������˳�"����ʱ����"��"�ϡ��¡�����"����
		       ��ģʽ3�£��������ʾ�¶ȡ�����ADֵ"������  ����", ���������޲���
					 ��ģʽ4�£��������ʾ      "������  ��������  ����"���������� "��"�� ��ͣ/���ţ�"�ϡ���"����������"����"����������
           ��ģʽ5�£��������ʾ      "����   ����Ƶ�ʣ�MHz��"���������� "��"�� ���浱ǰ����������NVM���´��ϵ�ʱ���øò���������
					                                                               "�ϡ���"����������"����"��������Ƶ��
					 ��ģʽ6�£��������ʾ       "       ����ֵ��cm��"  �����������޲��� 
           ��ģʽ7�£��������ʾ       "����ADCֵ����������"  �����������޲���  
     3������1������ʱ�����������ⷢ�� "��Һã�"������"STC-Bѧϰ��"�����ñ������ô������֣����ò�����1200bps���ı����շ�ʽ���ɿ������յ���"��Һã�"�ı�		
        ����3��̧��ʱ��������1���������� �����������ܲ��������ܲ���������������ѭ��ÿ�������ÿ���û�������ȶ�ʧ��	 
		 4���񶯴�����������������ֲ��ţ��������ֲ���"��ͣ/����"
		 5���������������дų��ӽ�ʱ����������������У�����������1350Hz����1��ʱ�䣩
		 6������1��������˫��ͨ�ţ�������1200bps��
		           ����յ�һ��"AA 55"��ͷ����С8�ֽ����ݰ����򽫵�7�ֽ�+1�����Բ�����2400bps�򴮿�2��485��EXT��ѡ��ת�������ݰ�
							 �������ӿ��յ����ݰ���������+����+�����룩�����򴮿�1ת��
		 7������2����ѡ��485��˫�򵥹�����EXT��TTL Uart��˫��˫��������λ�ã�����������2400bps
		           ����յ�һ��"AA 55"��ͷ����С8�ֽ����ݰ����򽫵�7�ֽ�+2���������Ir��ת�������ݰ���NEC_R05d����Э�飩
		 8�������շ��ӿڣ�
							 �������ӿ��յ����ݰ���������+����+�����룩���������������1000Hz��300mS�������򴮿�1ת����
               ������ݰ���ͷΪ"AA 55"��������3�ֽ�Ϊ F1�����������Ƶ�ʣ���4��5�ֽڣ�BCD�룬����Ƶ��ֵ��0.1MHz������������Ч��887��1080����
							                                                      ��������6�ֽ����ݣ�����������Ч��0��15��       ����7�ֽ�+4
							                              ��3�ֽ�Ϊ F2�������RTCʱ���루��4��5��6�ֽ����ݣ�BCD�룩����������Ч������7�ֽ�+4
																						��3�ֽ�Ϊ F3�������RTC�����գ���4��5��6�ֽ����ݣ�BCD�룩����������Ч������7�ֽ�+4
																				����ֵ����NVM��
																				������������1000Hz��600mS��
																				���򴮿�1ת����

��ƣ���ɣ��绰��18008400450��    2021��9��5��
***************************************************************************************************************************/

//******* �û������1���û���������ļ� *************//
#include "main.H" //���롣��дӦ�ó���ʱ�������д main.h �� main.c�ļ�

//******* �û������2���û��Զ�������� *************//
#define A 0.1
#define B 0.25
#define C 0.6
#define D 1
unsigned int temp_mid = 30;
unsigned int temp_range = 10;
unsigned int rop_mid = 40;
unsigned int rop_range = 25;

//******* �û������3���û��Զ��庯������ *************//
unsigned char dist(unsigned int a, unsigned int b);
unsigned char gradingStd(unsigned int curr, unsigned int range);
void editRxdByTemp_Rop(unsigned int u, unsigned char idx);

//******* �û������4���û�����ȫ�ֱ������� *************//
struct_DS1302_RTC t = {0x30, 0, 9, 0x06, 9, 1, 0x21}; //������ ʵʱʱ�����ݽṹ���롢�֡�ʱ���ա��¡��ܡ��ꡣ��ֵ��2021��9��6�գ���һ��9��00��30
struct_SysPerF SysPer;								  //������ ϵͳ�������ݽṹ��ÿ����ѭ������4�ֽڡ�ÿ����ѯ��ʧ����1�ֽ�
struct_ADC ADCresult;								  //������ ��������������ADֵ
unsigned char Music_tone, Music_PM;					  //������ ���ֲ����������ڴգ�ÿ���ӽ�������

unsigned char rxd[8];					 //������ͨ�ţ�����1������2�����⹲�ã�������8�ֽ�
unsigned char rxdhead[2] = {0xaa, 0x55}; //������ͨ�ţ�����1������2�����հ�ͷƥ���ַ�2�ֽڣ���0xAA��0x55��

unsigned char funcmode; //������������ʾ����������ģʽ
enum funcname
{
	MainPage = 1, // main page
	RTC_YMD,	  //����������ģʽ������ʵʱʱ�ӣ�������
	RTC_HMS,	  //                    ʵʱʱ�ӣ�ʱ����
	Rt_Rop,		  //                    ������������
	Weight,

};					   //                    ���ӳ�
unsigned char tempadj; //�������������������ʱ��ʱ�ã�=1 �����ʱ��=2 ���»�� =3 ���� ����

// struct warningStatistics
// {
// 	unsigned char warningCnt;
// };

unsigned int temp, rop;
int valOfWeight, stdWeight;

//******* �û������5���û��Զ��庯��ԭ�� *************//
#include "function.c"

void myUart1Rxd_callback() //����������1�յ��Ϸ����ݰ��ص����������Ϸ����ݰ���AA��55��......����8�ֽڣ�
{
	if (GetUart2TxStatus() == enumUart2TxFree)
	{
		(*(rxd + 6)) += 1;			   //��7�ֽڼ�1
		Uart2Print(&rxd, sizeof(rxd)); //�����ݰ��Ӵ���2(485����EXT��չ�ӿ���)���ͳ�ȥ
	}
}

void myUart2Rxd_callback() //����������2�յ��Ϸ����ݰ��ص����������Ϸ����ݰ���AA��55��......����8�ֽڣ�
{
	if (GetIrStatus() == enumIrFree)
	{
		(*(rxd + 6)) += 2;			//��7�ֽڼ�2
		IrPrint(&rxd, sizeof(rxd)); //�����ݰ��Ӻ��ⷢ�ͳ�ȥ
	}
}

void myIrRxd_callback() //�����������յ����ݰ��ص����������к���ǰ��+����+������NEC_R05d���룩
{
	dealwithIrRxd();
}

void my1mS_callback() //������1mS�¼��ص�����
{
}

void my10mS_callback() //������10mS�¼��ص�����
{
}

void my100mS_callback() //������100mS�¼��ص�����
{
	temp = ADCresult.Rt;
	rop = ADCresult.Rop;
	rop = rop > 255 ? 255 : rop;
	dealwithDisp();
}

void my1S_callback() //������1S�¼��ص�����
{
	// SetBeep(1000,20);
	editRxdByTemp_Rop(temp / 15, 1);
	editRxdByTemp_Rop(rop, 2);
	Uart1Print(&rxd, sizeof(rxd));
}

void myADC_callback() //������ADC�¼��ص�����
{
}

void myKN_callback() //���������������¼��ص�����
{
	dealwithmyKN();
}

void mykey_callback() // ������Key1��Key2���¼��ص�����
{
	dealwithmykey();
}

void myhall_callback() //ʾ������hall�¼��ص���������������
{
	if (GetHallAct() == enumHallGetClose)
		SetBeep(1350, 100);
}

unsigned char dist(unsigned int a, unsigned int b)
{
	// unsigned int max = a > b ? a : b, min = a < b ? a : b;
	return (a > b ? a : b) - (a < b ? a : b);
}

// unsigned char gradingStd(unsigned int curr, unsigned int range)
// {
// 	if (curr <= range * A)			return 10;
// 	else if (curr <= range * B)		return 11;
// 	else if (curr <= range * C)		return 12;
// 	else							return 13;
// }

void editRxdByTemp_Rop(unsigned int u, unsigned char idx)
{
	unsigned char table[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
	if (u > 255)		return ;
	rxd[2 * idx] = (u / 16 % 16 > 9) ? table[(u / 16 % 16) - 10] : u / 16 % 16;
	rxd[2 * idx + 1] = u % 16 > 9 ? table[(u % 16) - 10] : u % 16;
}


//******* main()���� *************//
void main() //������ main() ��ʼ         //���б��룡����
{

	//******* �û������6���û�main()�����ڲ��ֲ��������� *************//

	//******* �û������7���û�main()��������ʼ������� *************//
	//1,������Ҫ�õ�ģ��(�ɸ�ģ���ṩ���غ���)
	Key_Init();			//��������Ҫ�õ���ģ�鼰�亯������������������ʼ��������׼������������Ӧ����̨����
	HallInit();			//����
	VibInit();			//����
	DisplayerInit();	//����
	// BeepInit();			//����
	AdcInit(ADCexpEXT); //������ADCģ���ʼ�����в�����ѡ����չ�ӿ�EXT��P1.0��P1.1�Ƿ�Ҳ��ADC����
	DS1302Init(t);		//������DS1302��ʼ��

	IrInit(NEC_R05d); //����������ӿ�����
					  /******* ���¿�4ѡ1������EXT�ӿ� ********/
					  //    EXTInit(enumEXTWeight);                          //������EXT��ʼ���ɵ��ӳӹ���
					  // 	  EXTInit(enumEXTPWM);                             //������EXT��ʼ������·PWM����
					  // 	  EXTInit(enumEXTDecode);                          //������EXT��ʼ��������ʽ���������빦�ܣ��磺��ת��������
					  // 	  EXTInit(enumEXTUltraSonic);                      //������EXT��ʼ���ɳ�������๦��
	Uart1Init(4800);  //����������1��ʼ�����в���������Uart1ͨ�Ų�����
	/******* ���¿�2ѡ1�����ش���2 ********/
	Uart2Init(2400, Uart2Usedfor485); //����������2��ʼ����485�ӿڣ�RS485��ҵ�ֳ����ߣ���˫����
									  // 	  Uart2Init(2400,Uart2UsedforEXT);               //����������2��ʼ����EXT�ӿڣ�TTL Uart����ͨ�ſڣ�

	//2,�����¼��ص�����(��sys�ṩ���ú���SetEventCallBack())
	SetEventCallBack(enumEventKey, mykey_callback);			  //����
	SetEventCallBack(enumEventSys1mS, my1mS_callback);		  //����
	SetEventCallBack(enumEventSys10mS, my10mS_callback);	  //����
	SetEventCallBack(enumEventSys100mS, my100mS_callback);	  //����
	SetEventCallBack(enumEventSys1S, my1S_callback);		  //����
	SetEventCallBack(enumEventHall, myhall_callback);		  //����
	SetEventCallBack(enumEventNav, myKN_callback);			  //���������õ��������ص�����
	SetEventCallBack(enumEventXADC, myADC_callback);		  //��չ�ӿ����µ�ADֵ�¼�

	//3,�û�����״̬��ʼ��
	SetDisplayerArea(0, 7);									  //����
	SetUart1Rxd(&rxd, sizeof(rxd), rxdhead, sizeof(rxdhead)); //���ô��ڽ��շ�ʽ�����ݰ��������������ݰ�������rxd�У����ݰ���Сrxd��С�����ݰ�ͷ��Ҫ��rxdheadƥ�䣬ƥ������rxdhead��С
	SetUart2Rxd(&rxd, sizeof(rxd), rxdhead, sizeof(rxdhead));
	SetIrRxd(&rxd); //����

	//4,�û����������ʼ��

	funcmode = M24C02_Read(0x00);
	LedPrint(funcmode);

	/*****************  MySTC_OS ��ʼ������ؿ�ʼ  ********************************/
	MySTC_Init(); // MySTC_OS ��ʼ��         //���б��룡����
	while (1)	  // ϵͳ��ѭ��              //���б��룡����
	{
		MySTC_OS(); // MySTC_OS ����           //���б��룡����
					/*****************  MySTC_OS ��ʼ������ؽ���  ********************************/

		//******* �û������8���û�main()��������ѭ������ *************//

	} //��ѭ��while(1)����         //���б��룡����
} //������ main() ����         //���б��룡����