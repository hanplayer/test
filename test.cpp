#include <iostream>
#include <string>
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
	
	for(int i = 0;i < second.len;i++)
	{
		char tmp[126];
		short len;
		BitMultiplyNum(first,second.value[i],tmp,len);
		
	}
	return 0;
}
//dec 十进制的进位
int Plus(char * first,char * second,short first_length,short second_length,short dec_first,short dec_second)
{
	
	return 0;
}

int main(void)
{
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
	return 0;

}






