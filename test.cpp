#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;
class Addition
{
public:
    int BitPlusBit(char& first,char& second,char& bit,char& carry);
    int NumPlusNum(char *first,char *second,char *result,const short fir_len,const short& sec_len,short& result_len);
    int AppendZero(char *input,short len,short num);
};

class Multiplication
{
public:
    int BitMultiplyBit(const char& first,const char& second,char& bit,char& carry);
    int BitMultiplyNum(const char *first,char &second,char *result,const short &first_len,short &result_len);
    int NumMultiplyNum(char *first,char *second,char *result,short first_len,short second_len,short &result_len);
private:
    Addition adder;

};
class Analysis
{
public:
    int GetPointPos(char* value,short &pos);
    int GetPowerDec(short dec,short power,short &result);//幂运算之后的小数位置
};
class Formater
{
public:
    int DelHeadZero(char *opra);
    int Coverse(char *opra,short len);
    int Format(char *input,short len,short dec,char *output);
};
int Analysis::GetPointPos(char* value,short &pos)
{
    for(short i = 0 ;i < 6;i++ )
    {
        if(value[i]=='.')
        {
            pos = i;
            return 0;
        } 
    }
}

int Analysis::GetPowerDec(short dec,short power,short &result)
{
    result = dec*power;
    return 0;
}

int Formater::Coverse(char *opra,short len)
{
    char tmp[126];
    short j = 0;
    for(short i = len;i > 0;i-- )
    {
        tmp[j] = opra[i];
        j++;
    }
    memcpy(opra,tmp,len);
    return 0;
}
//添加小数点
int Formater::AddPoint(char *opra,short len,short point_pos)
{
    char tmp[126];
    memset(tmp,0,126);
    opra[point_pos] = 10;
    for(short i = 0;;i++)
    {
        
    }
    return 0;
}
//dec 小数点的位数
int Formater::Format(char *input,short len,short dec,char *output)
{ 
    return 0;
}


//删除尾部的0
int Formater::DelEndZero(char *opra,short len)
{
    for(short i = len;i > 0;i--)
    {
        if(opra[i-1] != 0)
        {
            len = i;
            return 0;
        }
    }
}

int Multiplication::BitMultiplyBit(const char& first,const char& second,char& bit,char& carry)
{
    char num;
    num = (first)*(second) + carry;
    bit = num%10;
    carry = num/10;
    return 0;
}
//len = 长度
int Multiplication::BitMultiplyNum(const char *first,char &second,char *result,const short &first_len,short &result_len)
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
int Addition::AppendZero(char *input,short len,short num)
{
    char tmp[126];
    memset(tmp,0,126);
    memcpy(tmp+num,input,len);
    memcpy(input,tmp,len+num);
    return 0;
}
int Multiplication::NumMultiplyNum(char *first,char *second,char *result,short first_len,short second_len,short &result_len)
{
    char sum[126];
    memset(sum,0,126);
    short sum_len = 1;

    for(int i = 0;i < second_len;i++)
    {
        char tmp[126];
        short len;
        BitMultiplyNum(first,second[i],tmp,first_len,len);
        adder.AppendZero(tmp,len,i);  
        adder.NumPlusNum(sum,tmp,result,sum_len,len+i,result_len);
        memcpy(sum,result,result_len);
        sum_len = result_len;
    }
    return 0;
}
/*
int Multiplication::DeleteZero(char *result,short &result_len)
{
    for(short i = result_len;i > 0;i-- )
    {
        if(result[result_len - 1] != 0)
	{
	    result_len = i;
            return 0;
	}
    }
}
*/

//dec 十进制的进位 位和位相加
int Addition::BitPlusBit(char& first,char& second,char& bit,char& carry)
{
    char num = first + second + carry;
    bit = num%10;
    carry = num/10;
    return 0;
}
int Addition::NumPlusNum(char *first,char *second,char *result,const short fir_len,const short& sec_len,short& result_len)
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

    return 0;
}

int main(void)
{
#if 1
    Multiplication multitor;
    char a1[126],a2[126],result[126];
    a1[0] = 1;
    a1[1] = 2;
    a1[2] = 3;
    a1[3] = 4;
    a1[4] = 0;

    short a1_len = 5;

    a2[0] = 1;
    a2[1] = 2;
    a2[2] = 3;
    a2[3] = 4;
    a2[4] = 0;

    short a2_len = 5;
    short result_len = 0;
    for(int t = 0;t < 19;t++)
    {
        multitor.NumMultiplyNum(a1,a2,result,a1_len,a2_len,result_len);
	memcpy(a2,result,result_len);
	a2_len = result_len;
    }
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




