#pragma once
#include <Windows.h>
#include <stdio.h>
#include <math.h>

#define		MAX_MNEMONIC_LEN		32
#define		MAX_OPERAND_LEN			64
#define		MAX_INSTRUCTION_LEN		128

/*
* Sib结构
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
* ModR/M结构
*/
typedef struct _MODRM
{
	/*	Reg/OpCode到底代表什么	*/
	BOOL IsReg = TRUE;
	/*	Mod	*/
	CHAR* Mod = (CHAR*)malloc(sizeof(CHAR) * 2);

	/*	Reg/OpCode	*/
	CHAR* Reg_OR_Op = (CHAR*)malloc(sizeof(CHAR) * 3);

	/*	R/M	*/
	CHAR* R_OR_M = (CHAR*)malloc(sizeof(CHAR) * 3);
} Mod_R_M, * PMod_R_M;

/*
* 硬编码指令完整结构
*/
typedef struct _INSTRUCTION
{
	/* prefixes */
	CHAR	RepeatPrefix;
	CHAR	SegmentPrefix;
	CHAR	OperandPrefix;
	CHAR	AddressPrefix;

	/* opcode类型 */
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
	DWORD	LinearAddress;			/* 这个部分为指令的地址*/

	/*	辅助信息	*/
	DWORD OpcodeOrder;			/*	当前指令顺序	(1:内存寻址在源)	*/		
	BOOL HaveModRM;				/*	是否拥有ModR/M	*/
	BOOL HaveSib;				/*	是否拥有Sib	*/
	BOOL HaveSignExtend;		/*	是否需要符号位拓展	*/

	/*
	* 内存寻址宽度
	*	1表示16位，2表示32位
	*		受前缀67h的影响
	*			与Mod共同决定吞几个字节
	*/
	DWORD dwMemoryFlag = 2;
	/*
	* 非内存(寄存器/立即数)寻址宽度
	*	0表示8位，1表示16位，2表示32位
	*		受w位的影响(8和32/16之间切换)，受前缀66h的影响(16/32之间切换)
	*			w==0时，前缀66不起作用(8位)
	*/
	DWORD dwRegFlag = 1;
	/*
	* 立即数宽度
	*	0表示8位，1表示32位
	*/
	DWORD dwImeFlag = 0;

} INSTRUCTION, *PINSTRUCTION;

/*
* 汇编指令完整结构
*/
typedef struct _ASMINSTRUCTION
{
	TCHAR prefix[MAX_OPERAND_LEN] = "";				//前缀
	TCHAR mnemonic[MAX_MNEMONIC_LEN] = "";			//助记符
	TCHAR operandSrc[MAX_OPERAND_LEN] = "";			//操作数1
	TCHAR operandDes[MAX_OPERAND_LEN] = "";			//操作数2
	TCHAR operand3[MAX_OPERAND_LEN] = "";			//操作数3
} ASMINSTRUCTION, *PASMINSTRUCTION;

//反汇编
PBYTE Disassemble(PBYTE DesCode, PINSTRUCTION Instruction, PTCHAR InstructionStr);

//判断OpCode的类别
VOID JudgeOpCodetype(PBYTE* CurrentCode, PINSTRUCTION Instruction);

/*
* 获取1字节数据的，任意个位的值返回
*	从右->左查
*		注意顺序
*/
VOID GetByteBit(BYTE Src, DWORD Len, DWORD Begin, BYTE* Res);

/*
* 二进制数组->整数
*/
DWORD BinArr2dw(BYTE* Res, DWORD Len);

//清理指令结构
VOID ClearInstruction(PINSTRUCTION Instruction);

/*
* 解析Reg/OpCode部分(Reg)
*/
VOID AnalysisReg(PINSTRUCTION Instruction);

/*
* 解析Reg/OpCode部分(OpCode)
*/
VOID AnalysisOp(PINSTRUCTION Instruction, PBYTE* currentCode);

/*
* 解析Mod+R/M
*/
VOID AnalysisModRM(PINSTRUCTION Instruction, PBYTE* currentCode);

/*
* 解析Sib
*/
VOID AnalysisSib(PINSTRUCTION Instruction, PBYTE* currentCode, DWORD Mod, TCHAR* szContent);