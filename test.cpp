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
int Switch(struct A &first,struct A &second);
int format(const char *p,short length,short dec_len,struct A &result);
int CompleteZero(struct A &first,struct A &second);
int NumPlusNum(struct A first,struct A second,struct A &result);

int BitMultiplyBit(char& first,char& second,char& bit,char& carry)
{
	char num;
	num = (first)*(second) + carry;
	bit = num%10;
	carry = num/10;
	return 0;
}
//len = 长度
int BitMultiplyNum(struct A &first,char &second,char *result,short &len)
{
	char carry = 0;
	char bit = 0;
	for(int i = 0;i < first.len;i++)
	{
		BitMultiplyBit( first.value[i],second,bit,carry );
		result[i] = bit;
	}
	if(carry!=0)
	{
		result[first.len] = carry;
		len = first.len + 1;
	}
	else
	{
		len = first.len;
	}
	return 0;
}

int NumMultiplyNum(struct A &first,struct A &second,struct A &result)
{
	struct A sum;
	memset(sum.value,0,126);
	sum.len = 0;
	sum.dec_len = 0;
#if 1
		printf("-----sum begin:----\n");
		for(short j = 0;j < 126 ;j++)
		{
			printf("%d ",sum.value[j]);
		}
		printf("\n");
		printf("sum.len = %d\n",sum.len);
		printf("sum.dec_len = %d\n",sum.dec_len);
#endif
	result.dec_len = first.dec_len + second.dec_len;
	for(int i = 0;i < second.len;i++)
	{
		struct A op;//操作数
		char tmp[126];
		short len;
		BitMultiplyNum(first,second.value[i],tmp,len);
#if 0
		printf("----tmp----\n");
		for(short j = 0;j < len ;j++)
		{
			printf("%d",tmp[j]);
		}
		printf("\n");
#endif
		format(tmp,len,i,op);
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
		Switch(sum,op);
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
		CompleteZero(sum,op);
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

		NumPlusNum(sum,op,result);
		sum = result;
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
//格式化函数
int format(const char *p,short length,short dec_len,struct A &result)
{
	result.len = length;
	memcpy(result.value,p,length);
	result.dec_len = dec_len;
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
int NumPlusNum(struct A first,struct A second,struct A &result)
{
	short len = first.len;
	char carry = 0;
	char bit = 0;
	short i;
	memset(result.value,0,126);
	for(i = 0;i < len; i++)
	{
		BitPlusBit(first.value[i],second.value[i],bit,carry);
		result.value[i] = bit;
	}
	if(carry != 0)
	{
		result.value[i] = carry;
		result.len = len + 1;
	}
	else
	{
		result.len = len;
	}
	result.dec_len = first.dec_len;
#if 1
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


//将dec_len小的放到前面
int Switch(struct A &first,struct A &second)
{
	struct A tmp;
	if(first.dec_len > second.dec_len)
	{
		tmp = second;
		second = first;
		first = tmp;
	}
	return 0;
}
//补全各位的0
int CompleteZero(struct A &first,struct A &second)
{
	short AppendLen = second.dec_len - first.dec_len;
	char sec_op[126];
	char fir_op[126];
	memset(fir_op,0,126);
	memset(sec_op,0,126);
	for(int i = 0; i < AppendLen;i++)
	{
		sec_op[i] = 0;
	}
	short first_len,second_len;
	second_len = AppendLen + second.len;
	first_len = first.len;
	short differ = first_len - second_len;

	for(int j = 0;j < second.len;j++)
	{
		sec_op[j+AppendLen] = second.value[j];
	}
	memcpy(fir_op,first.value,first.len);//????
#if 0
		printf("-----first----\n");
		for(short j = 0;j < 126;j++)
		{
			printf("%d ",first.value[j]);
		}
		printf("\n");
#endif
#if 0
		printf("-----fir_op----\n");
		for(short j = 0;j < 126;j++)
		{
			printf("%d ",fir_op[j]);
		}
		printf("\n");
#endif
	if( differ > 0 )
	{	
		for(int i = 0;i < differ ; i++  )
		{
			sec_op[i+AppendLen+second.len] = 0;
		}
	}
	else if( differ < 0 )
	{
		for( int i = 0 ;i < differ; i++ )
		{
			fir_op[i+first.len] = 0;
		}
	}
	memcpy(first.value,fir_op,126);
	memcpy(second.value,sec_op,126);
#if 1
		printf("-----one----\n");
		for(short j = 0;j < 126;j++)
		{
			printf("%d ",first.value[j]);
		}
		printf("\n");
		printf("first.len:%d\n",first.len);
		printf("first.dec_len:%d\n",first.dec_len);
		
#endif
#if 1
		printf("-----second----\n");
		for(short j = 0;j < 126;j++)
		{
			printf("%d ",second.value[j]);
		}
		
		printf("\n");
		printf("second.len:%d\n",second.len);
		printf("second.dec_len:%d\n",second.dec_len);
#endif
	if(differ < 0)
	{
		first.len = second_len;
		second.len = second_len;
	}
	else
	{
		first.len = first_len;
		second.len = first_len;
	}
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
	struct A a1,a2,result;
	a1.value[0] = 1;
	a1.value[1] = 0;
	a1.value[2] = 0;
	a1.value[3] = 0;
	a1.value[4] = 0;
	a1.value[5] = 8;
	a1.value[6] = 9;
	a1.value[7] = 9;
	a1.value[8] = 9;
	a1.value[9] = 9;

	a1.len = 10;
	a1.dec_len = 1;

	a2.value[0] = 1;
	a2.value[1] = 0;
	a2.value[2] = 0;
	a2.value[3] = 0;
	a2.value[4] = 0;
	a2.value[5] = 8;
	a2.value[6] = 9;
	a2.value[7] = 9;
	a2.value[8] = 9;
	a2.value[9] = 9;

	a2.len = 10;
	a2.dec_len = 1;
	NumMultiplyNum(a1,a2,result);
	printf("result.len:%d\n",result.len);
	printf("result:\n");
	for(int i = 0;i < result.len;i++)
	{	
		printf("%d ",result.value[i]);
	}
	printf("\n");
#endif

	return 0;

}






