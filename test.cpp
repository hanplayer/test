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


int BitMultiplyBit(char& first,char& second,char& bit,char& carry)
{
	char num;
	num = (first - '0')*(second - '0') + carry;
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

int NumMultiplyNum(struct A &first,struct A &second,struct A result)
{
	struct A sum;
	memset(sum.value,0,126);
	sum.len = 0;
	sum.dec_len = 0;
	for(int i = 0;i < second.len;i++)
	{
		struct A op;//操作数
		char tmp[126];
		short len;
		BitMultiplyNum(first,second.value[i],tmp,len);
		format(tmp,len,i,op);
		Switch(sum,op);
		CompleteZero(sum,op);
		
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
/*

*/
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
	memcpy(fir_op,first.value,first.len);
	
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
	/*
	char tmp = '0';
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
	*/
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
	return 0;

}






