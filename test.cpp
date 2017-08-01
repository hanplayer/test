#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;
struct A
{
	char value[126];
	unsigned short len;
	unsigned short dec_len;
	
};
int NumPlusNum(char *first,char *second,char *result,const short fir_len,const short& sec_len,short& result_len);


int BitMultiplyBit(const char& first,const char& second,char& bit,char& carry)
{
	char num;
	num = (first)*(second) + carry;
	bit = num%10;
	carry = num/10;
	return 0;
}
//len = 长度
int BitMultiplyNum(const char *first,char &second,char *result,const short &first_len,short &result_len)
{
	char carry = 0;
	char bit = 0;
	for(int i = 0;i < first_len;i++)
	{
		BitMultiplyBit( first[i],second,bit,carry );
		result[i] = bit;
	}
	if(carry!=0)
	{
		result[first_len] = carry;
		result_len = first_len + 1;
	}
	else
	{
		result_len = first_len;
	}
	return 0;
}
//num即为添加0的个数
int AppendZero(char *input,short len,short num)
{
	char tmp[126];
	memset(tmp,0,126);
	memcpy(tmp+num,input,len);
	memcpy(input,tmp,len+num);
	return 0;
}
int NumMultiplyNum(char *first,char *second,char *result,short first_len,short second_len,short &result_len)
{
	char sum[126];
	memset(sum,0,126);
	short sum_len = 1;
#if 0
		printf("-----sum begin:----\n");
		for(short j = 0;j < 126 ;j++)
		{
			printf("%d ",sum.value[j]);
		}
		printf("\n");
		printf("sum.len = %d\n",sum.len);
		printf("sum.dec_len = %d\n",sum.dec_len);
#endif
	for(int i = 0;i < second_len;i++)
	{
		struct A op;//操作数
		char tmp[126];
		short len;
		BitMultiplyNum(first,second[i],tmp,first_len,len);
#if 0
		printf("----tmp----\n");
		for(short j = 0;j < len ;j++)
		{
			printf("%d",tmp[j]);
		}
		printf("\n");
#endif
		AppendZero(tmp,len,i);
#if 0
		printf("-----op----\n");
		for(short j = 0;j < len ;j++)
		{
			printf("%d ",op.value[j]);
		}
		printf("\n");
		printf("op.len = %d\n",op.len);
		printf("op.dec_len = %d\n",op.dec_len);
#endif
#if 0
		printf("-----sum2:----\n");
		for(short j = 0;j < 126 ;j++)
		{
			printf("%d ",sum.value[j]);
		}
		printf("\n");
		printf("sum.len = %d\n",sum.len);
		printf("sum.dec_len = %d\n",sum.dec_len);
#endif
#if 0
		printf("-----sum3----\n");
		for(short j = 0;j < sum.len ;j++)
		{
			printf("%d ",sum.value[j]);
		}
		printf("\n");
		printf("sum.len = %d\n",sum.len);
		printf("sum.dec_len = %d\n",sum.dec_len);
#endif
#if 0
		printf("-----op----\n");
		for(short j = 0;j < op.len ;j++)
		{
			printf("%d ",op.value[j]);
		}
		printf("\n");
		printf("op.len = %d\n",op.len);
		printf("op.dec_len = %d\n",op.dec_len);
#endif
#if 0
		printf("-----sum----\n");
		for(short j = 0;j < sum.len ;j++)
		{
			printf("%d ",sum.value[j]);
		}
		printf("\n");
		printf("sum.len = %d\n",sum.len);
		printf("sum.dec_len = %d\n",sum.dec_len);
#endif		
		NumPlusNum(sum,tmp,result,sum_len,len+i,result_len);
		memcpy(sum,result,result_len);
		sum_len = result_len;
#if 0
		printf("---------\n");
		for(short j = 0;j < result.len ;j++)
		{
			printf("%d ",result.value[j]);
		}
		printf("\n");
		printf("result.len = %d\n",result.len);
		printf("result.dec_len = %d\n",result.dec_len);
#endif	
	}
	
	return 0;
}

//dec 十进制的进位 位和位相加
int BitPlusBit(char& first,char& second,char& bit,char& carry)
{
	char num = first + second + carry;
	bit = num%10;
	carry = num/10;
	return 0;
}
int NumPlusNum(char *first,char *second,char *result,const short fir_len,const short& sec_len,short& result_len)
{
	short len;
	len = (fir_len>=sec_len)?fir_len:sec_len;
	char carry = 0;
	char bit = 0;
	short i;
	memset(result,0,126);
	for(i = 0;i < len; i++)
	{
		BitPlusBit(first[i],second[i],bit,carry);
		result[i] = bit;
	}
	if(carry != 0)
	{
		result[i] = carry;
		result_len = len + 1;
	}
	else
	{
		result_len = len;
	}
#if 0
		printf("----result----\n");
		for(short j = 0;j < 126;j++)
		{
			printf("%d ",result.value[j]);
		}
		printf("\n");
		printf("result.len:%d\n",result.len);
		printf("result.dec_len:%d\n",result.dec_len);
		
#endif

	return 0;
}

int main(void)
{
#if 0	
	char tmp = '9';
	char result[126];
	short len;
	struct A a;
	sprintf(a.value,"%s","54321");
	a.len = 5;
	BitMultiplyNum(a,tmp,result,len);
	cout<<"Length:"<<len<<endl;
	for(int i = 0; i < len;i++)
	{
		printf("%d",result[i]);
	}
#endif	
#if 0
	struct A a1,a2;
	a1.value[0] = 5;
	a1.value[1] = 4;
	a1.value[2] = 3;
	a1.value[3] = 2;
	a1.value[4] = 1;

	a1.len = 5;
	a1.dec_len = 1;

	a2.value[0] = 2;
	a2.value[1] = 3;
	
	a2.len = 2;
	a2.dec_len = 2;
	
	Switch(a1,a2);
	CompleteZero(a1,a2);
	for(int i = 0;i < a1.len;i++)
	{
		printf("%d",a1.value[i]);
	}
	printf("\n");
	printf("a1.len:%d\n",a1.len);
	printf("a1.dec_len:%d\n",a1.dec_len);
	for(int i = 0;i < a2.len;i++)
	{
		printf("%d",a2.value[i]);
	}
	printf("\n");
	printf("a2.len:%d\n",a2.len);
	printf("a2.dec_len:%d\n",a2.dec_len);
#endif
#if 0
	struct A a1,a2,result;
	a1.value[0] = 5;
	a1.value[1] = 2;
	a1.value[2] = 9;
	a1.value[3] = 0;
	a1.len = 4;
	a1.dec_len = 0;

	a2.value[0] = 0;
	a2.value[1] = 2;
	a2.value[2] = 9;
	a2.value[3] = 9;
	a2.len = 4;
	a2.dec_len = 1;

	NumPlusNum(a1,a2,result);
	cout<<"result.len:"<<result.len<<endl;
	for(int i = 0;i < 5;i++)
	{
		printf("result:");
		
		printf("%d\n",result.value[i]);
	}
	printf("\n");
#endif
#if 1
	char a1[126],a2[126],result[126];
	a1[0] = 1;
	a1[1] = 9;
	a1[2] = 0;
	a1[3] = 0;
	a1[4] = 0;
	a1[5] = 8;
	a1[6] = 9;
	a1[7] = 9;
	a1[8] = 9;
	a1[9] = 9;

	short a1_len = 10;

	a2[0] = 9;
	a2[1] = 9;
	a2[2] = 9;
	a2[3] = 9;
	a2[4] = 9;
	a2[5] = 9;
	a2[6] = 9;
	a2[7] = 9;
	a2[8] = 9;
	a2[9] = 9;

	short a2_len = 10;
	short result_len = 0;
        NumMultiplyNum(a1,a2,result,a1_len,a2_len,result_len);

	printf("result.len:%d\n",result_len);
	printf("result:\n");
	for(int i = 0;i < result_len;i++)
	{	
		printf("%d ",result[i]);
	}
	printf("\n");
#endif

	return 0;

}






