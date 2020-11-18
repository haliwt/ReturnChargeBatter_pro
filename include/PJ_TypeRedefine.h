/*
Copyright 2010  BUT
---------- file information -----------------------------------------------
file name: PJ_TypeRedefine.h
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/
#ifndef  PJ_TypeRedefine_h
#define  PJ_TypeRedefine_h
#define  codec51


//for c51--------------------------------------------------------------
#ifdef  codec51
typedef    unsigned  char     INT8U;         // �޷���8λ���ͱ���
//  0~255
typedef    signed    char     INT8S;         // �з���8λ���ͱ���
//  -128~+127
typedef    unsigned  int      INT16U;        // �޷���16λ���ͱ���
//  0~65535
typedef    signed    int      INT16S;        // �з���16λ���ͱ���
//  -32768~+32767
typedef    unsigned  long     INT32U;        // �޷���32λ���ͱ���
//  0~4294967295
typedef    signed    long     INT32S;        // �з���32λ���ͱ���
//  -2147483648~+2147483647
typedef    float              FP32;          // �����ȸ�������32λ���ȣ�
//  +/-1.175494E-38~+/-3.402823E+38
#define    INT1U              bit

//for c51 spec memory type used

#define    indata             data
#define    inindata           idata
#define    outdata            xdata
#endif
//for c51--------------------------------------------------------------



//for HT --------------------------------------------------------------
#ifdef  codeHT
typedef              char     INT8S;         // �з���8λ���ͱ���
//  -128~+127
typedef    unsigned  char     INT8U;         // �޷���8λ���ͱ���
//  0~255
/*
 typedef              int      INT8S;         // �з���8λ���ͱ���
                                              //  -128~+127
 typedef    unsigned           INT8U;         // �޷���8λ���ͱ���
                                              //  0~255
 typedef    short     int      INT8S;         // �з���8λ���ͱ���
                                              //  -128~+127
 typedef    unsigned short int INT8U;         // �޷���8λ���ͱ���
                                              //  0~255
*/
typedef              long     INT16S;        // �з���16λ���ͱ���
//  -32768~+32767
typedef    unsigned  long     INT16U;        // �޷���16λ���ͱ���
//  0~65535
#define    INT1U              bit;

#endif
//for HT --------------------------------------------------------------


//for gcc
//for ads
//STM8










#endif //PJ_TypeRedefine_h
/*
---------- modify information ---------------------------------------------
version  : v0
modify   : 0000
begin    : 20080403
finish   : 20080403
define   :
---------------------------------------------------------------------------
*/