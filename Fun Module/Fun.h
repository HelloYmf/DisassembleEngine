#pragma once
#include <Windows.h>
#include <stdio.h>
#include <math.h>

#define		MAX_MNEMONIC_LEN		32
#define		MAX_OPERAND_LEN			64
#define		MAX_INSTRUCTION_LEN		128

/*
* Sib�ṹ
*/
typedef struct _SIB
{
	/*	Scale	*/
	CHAR* Scale = (CHAR*)malloc(sizeof(CHAR) * 2);

	/*	Index	*/
	CHAR* Index = (CHAR*)malloc(sizeof(CHAR) * 3);

	/*	Base	*/
	CHAR* Base = (CHAR*)malloc(sizeof(CHAR) * 3);
}SIB, *PSIB;

/*
* ModR/M�ṹ
*/
typedef struct _MODRM
{
	/*	Reg/OpCode���״���ʲô	*/
	BOOL IsReg = TRUE;
	/*	Mod	*/
	CHAR* Mod = (CHAR*)malloc(sizeof(CHAR) * 2);

	/*	Reg/OpCode	*/
	CHAR* Reg_OR_Op = (CHAR*)malloc(sizeof(CHAR) * 3);

	/*	R/M	*/
	CHAR* R_OR_M = (CHAR*)malloc(sizeof(CHAR) * 3);
} Mod_R_M, * PMod_R_M;

/*
* Ӳ����ָ�������ṹ
*/
typedef struct _INSTRUCTION
{
	/* prefixes */
	CHAR	RepeatPrefix;
	CHAR	SegmentPrefix;
	CHAR	OperandPrefix;
	CHAR	AddressPrefix;

	/* opcode���� */
	DWORD	OpcodeType;

	/* ModR/M */
	Mod_R_M modR_M;

	/* SIB */
	SIB	Sib;

	/* Displacement */
	DWORD	Displacement;

	/* Immediate */
	DWORD	Immediate;

	/* Linear address of this instruction */
	DWORD	LinearAddress;			/* �������Ϊָ��ĵ�ַ*/

	/*	������Ϣ	*/
	DWORD OpcodeOrder;			/*	��ǰָ��˳��	(1:�ڴ�Ѱַ��Դ)	*/		
	BOOL HaveModRM;				/*	�Ƿ�ӵ��ModR/M	*/
	BOOL HaveSib;				/*	�Ƿ�ӵ��Sib	*/
	BOOL HaveSignExtend;		/*	�Ƿ���Ҫ����λ��չ	*/

	/*
	* �ڴ�Ѱַ���
	*	1��ʾ16λ��2��ʾ32λ
	*		��ǰ׺67h��Ӱ��
	*			��Mod��ͬ�����̼����ֽ�
	*/
	DWORD dwMemoryFlag = 2;
	/*
	* ���ڴ�(�Ĵ���/������)Ѱַ���
	*	0��ʾ8λ��1��ʾ16λ��2��ʾ32λ
	*		��wλ��Ӱ��(8��32/16֮���л�)����ǰ׺66h��Ӱ��(16/32֮���л�)
	*			w==0ʱ��ǰ׺66��������(8λ)
	*/
	DWORD dwRegFlag = 1;
	/*
	* ���������
	*	0��ʾ8λ��1��ʾ32λ
	*/
	DWORD dwImeFlag = 0;

} INSTRUCTION, *PINSTRUCTION;

/*
* ���ָ�������ṹ
*/
typedef struct _ASMINSTRUCTION
{
	TCHAR prefix[MAX_OPERAND_LEN] = "";				//ǰ׺
	TCHAR mnemonic[MAX_MNEMONIC_LEN] = "";			//���Ƿ�
	TCHAR operandSrc[MAX_OPERAND_LEN] = "";			//������1
	TCHAR operandDes[MAX_OPERAND_LEN] = "";			//������2
	TCHAR operand3[MAX_OPERAND_LEN] = "";			//������3
} ASMINSTRUCTION, *PASMINSTRUCTION;

//�����
PBYTE Disassemble(PBYTE DesCode, PINSTRUCTION Instruction, PTCHAR InstructionStr);

//�ж�OpCode�����
VOID JudgeOpCodetype(PBYTE* CurrentCode, PINSTRUCTION Instruction);

/*
* ��ȡ1�ֽ����ݵģ������λ��ֵ����
*	����->���
*		ע��˳��
*/
VOID GetByteBit(BYTE Src, DWORD Len, DWORD Begin, BYTE* Res);

/*
* ����������->����
*/
DWORD BinArr2dw(BYTE* Res, DWORD Len);

//����ָ��ṹ
VOID ClearInstruction(PINSTRUCTION Instruction);

/*
* ����Reg/OpCode����(Reg)
*/
VOID AnalysisReg(PINSTRUCTION Instruction);

/*
* ����Reg/OpCode����(OpCode)
*/
VOID AnalysisOp(PINSTRUCTION Instruction, PBYTE* currentCode);

/*
* ����Mod+R/M
*/
VOID AnalysisModRM(PINSTRUCTION Instruction, PBYTE* currentCode);

/*
* ����Sib
*/
VOID AnalysisSib(PINSTRUCTION Instruction, PBYTE* currentCode, DWORD Mod, TCHAR* szContent);