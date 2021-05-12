#include "Fun.h"

//前缀字串
const char* RepeatPrefixes[] = { "lock", "rep", "repe", "repz", "repne", "repnz" };
const char* SegmentRegisters[] = { "es", "cs", "ss", "ds", "fs", "gs" };
//32位寄存器字串
const char* Register32[] = { "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi" };
//16位寄存器字串
const char* Register16[] = { "ax", "cx", "dx", "bx", "sp", "bp", "si", "di" };
//8位寄存器字串
const char* Register8[] = { "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh" };
//16位寻址寄存器组合
const char* Address16[] = { "bx+si", "bx+di", "bp+si", "bp+di", "si", "di", "bp", "bx" };
//数据类型
const char* OperateType[] = { "byte", "word", "dword" };

/*
* 汇编指令通用结构
*/
ASMINSTRUCTION g_AsmInstruction;

PBYTE Disassemble(PBYTE DesCode, PINSTRUCTION Instruction, PTCHAR InstructionStr)
{
	//清理之前环境(硬编码结构+汇编结构)
	ClearInstruction(Instruction);

	//标记前缀是否找到重复，找到重复就会重新扫描
	int prefixFlag = 0;				

	/* 解析指令前缀 */
	PBYTE currentCode = DesCode;
	while (*currentCode == 0xF0 || *currentCode == 0xF2 || *currentCode == 0xF3 ||
		*currentCode == 0x2E || *currentCode == 0x36 || *currentCode == 0x3E ||
		*currentCode == 0x26 || *currentCode == 0x64 || *currentCode == 0x65 ||
		*currentCode == 0x66 || *currentCode == 0x67)
	{
		switch (*currentCode)
		{

		/* group1: lock and repeat prefixes */

		case 0xF0:
		{
			if (prefixFlag)
			{
				strcpy(InstructionStr, RepeatPrefixes[Instruction->RepeatPrefix]);
				currentCode++;
				return currentCode;
			}
			else
			{
				/* rescan */

				if (Instruction->RepeatPrefix >= 0)
				{
					currentCode = DesCode;
					prefixFlag = 1;
				}
				else
				{
					Instruction->RepeatPrefix = 0;
					strcat(g_AsmInstruction.prefix, "  ");
					strcat(g_AsmInstruction.prefix, RepeatPrefixes[Instruction->RepeatPrefix]);
					currentCode++;
				}
			}

			break;
		}
		case 0xF2:
		{
			if (prefixFlag)
			{
				strcpy(InstructionStr, RepeatPrefixes[Instruction->RepeatPrefix]);
				currentCode++;
				return currentCode;
			}
			else
			{
				/* rescan */
				
				if (Instruction->RepeatPrefix >= 0)
				{
					currentCode = DesCode;
					prefixFlag = 1;
				}
				else
				{
					Instruction->RepeatPrefix = 5;
					strcat(g_AsmInstruction.prefix, "  ");
					strcat(g_AsmInstruction.prefix, RepeatPrefixes[Instruction->RepeatPrefix]);
					currentCode++;
				}
			}

			break;
		}
		case 0xF3:
		{
			if (prefixFlag)
			{
				strcpy(InstructionStr, RepeatPrefixes[Instruction->RepeatPrefix]);
				currentCode++;
				return currentCode;
			}
			else
			{
				/* rescan */
				
				if (Instruction->RepeatPrefix >= 0)
				{
					currentCode = DesCode;
					prefixFlag = 1;
				}
				else
				{
					Instruction->RepeatPrefix = 1;
					strcat(g_AsmInstruction.prefix, "  ");
					strcat(g_AsmInstruction.prefix, RepeatPrefixes[Instruction->RepeatPrefix]);
					currentCode++;
				}
			}

			break;
		}

		/* group2: segment override prefixes */

		case 0x2E:
		{

			if (prefixFlag)
			{
				strcpy(InstructionStr, SegmentRegisters[Instruction->SegmentPrefix]);
				currentCode++;
				return currentCode;
			}
			else
			{
				/* rescan */
				
				if (Instruction->SegmentPrefix >= 0)
				{
					currentCode = DesCode;
					prefixFlag = 1;
				}
				else
				{
					Instruction->SegmentPrefix = 1;
					strcat(g_AsmInstruction.prefix, "  ");
					strcat(g_AsmInstruction.prefix, SegmentRegisters[Instruction->SegmentPrefix]);
					currentCode++;
				}
			}

			break;
		}
		case 0x36:
		{
			if (prefixFlag)
			{
				strcpy(InstructionStr, SegmentRegisters[Instruction->SegmentPrefix]);
				currentCode++;
				return currentCode;
			}
			else
			{
				/* rescan */

				if (Instruction->SegmentPrefix >= 0)
				{
					currentCode = DesCode;
					prefixFlag = 1;
				}
				else
				{
					Instruction->SegmentPrefix = 2;
					strcat(g_AsmInstruction.prefix, "  ");
					strcat(g_AsmInstruction.prefix, SegmentRegisters[Instruction->SegmentPrefix]);
					currentCode++;
				}
			}

			break;
		}
		case 0x3E:
		{
			if (prefixFlag)
			{
				strcpy(InstructionStr, SegmentRegisters[Instruction->SegmentPrefix]);
				currentCode++;
				return currentCode;
			}
			else
			{
				/* rescan */

				if (Instruction->SegmentPrefix >= 0)
				{
					currentCode = DesCode;
					prefixFlag = 1;
				}
				else
				{
					Instruction->SegmentPrefix = 3;
					strcat(g_AsmInstruction.prefix, "  ");
					strcat(g_AsmInstruction.prefix, SegmentRegisters[Instruction->SegmentPrefix]);
					currentCode++;
				}
			}

			break;
		}
		case 0x26:
		{
			if (prefixFlag)
			{
				strcpy(InstructionStr, SegmentRegisters[Instruction->SegmentPrefix]);
				currentCode++;
				return currentCode;
			}
			else
			{
				/* rescan */

				if (Instruction->SegmentPrefix >= 0)
				{
					currentCode = DesCode;
					prefixFlag = 1;
				}
				else
				{
					Instruction->SegmentPrefix = 0;
					strcat(g_AsmInstruction.prefix, "  ");
					strcat(g_AsmInstruction.prefix, SegmentRegisters[Instruction->SegmentPrefix]);
					currentCode++;
				}
			}

			break;
		}
		case 0x64:
		{
			if (prefixFlag)
			{
				strcpy(InstructionStr, SegmentRegisters[Instruction->SegmentPrefix]);
				currentCode++;
				return currentCode;
			}
			else
			{
				/* rescan */

				if (Instruction->SegmentPrefix >= 0)
				{
					currentCode = DesCode;
					prefixFlag = 1;
				}
				else
				{
					Instruction->SegmentPrefix = 4;
					strcat(g_AsmInstruction.prefix, "  ");
					strcat(g_AsmInstruction.prefix, SegmentRegisters[Instruction->SegmentPrefix]);
					currentCode++;
				}
			}

			break;
		}
		case 0x65:
		{
			if (prefixFlag)
			{
				strcpy(InstructionStr, SegmentRegisters[Instruction->SegmentPrefix]);
				currentCode++;
				return currentCode;
			}
			else
			{
				/* rescan */

				if (Instruction->SegmentPrefix >= 0)
				{
					currentCode = DesCode;
					prefixFlag = 1;
				}
				else
				{
					Instruction->SegmentPrefix = 5;
					strcat(g_AsmInstruction.prefix, "  ");
					strcat(g_AsmInstruction.prefix, SegmentRegisters[Instruction->SegmentPrefix]);
					currentCode++;
				}
			}

			break;
		}

		/* group3: Operand-size override prefixes */

		case 0x66:
		{
			if (prefixFlag)
			{
				//strcpy(InstructionStr, "prefix datasize:");
				currentCode++;
				return currentCode;
			}
			else
			{
				/* rescan */

				if (Instruction->OperandPrefix >= 0)
				{
					currentCode = DesCode;
					prefixFlag = 1;
				}
				else
				{
					Instruction->OperandPrefix = 0;
					//strcat(prefix, "  ");
					//strcat(prefix, "prefix datasize:");
					currentCode++;
				}
			}

			break;
		}

		/* group4: Address-size override prefixes */

		case 0x67:
		{
			if (prefixFlag)
			{
				//strcpy(InstructionStr, "prefix addrsize:");
				currentCode++;
				return currentCode;
			}
			else
			{
				/* rescan */

				if (Instruction->AddressPrefix >= 0)
				{
					currentCode = DesCode;
					prefixFlag = 1;
				}
				else
				{
					Instruction->AddressPrefix = 0;
					//strcat(prefix, "  ");
					//strcat(prefix, "prefix addrsize:");
					currentCode++;
				}
			}

			break;
		}
		
		}
	}	
	
	/*	解析OpCode	*/
	JudgeOpCodetype(&currentCode, Instruction);

	/*	解析ModR/M	*/
	if (Instruction->HaveModRM)
	{
		//为ModR/M赋值
		GetByteBit(*currentCode, 3, 0, (BYTE*)Instruction->modR_M.R_OR_M);
		GetByteBit(*currentCode, 3, 3, (BYTE*)Instruction->modR_M.Reg_OR_Op);
		GetByteBit(*currentCode, 2, 6, (BYTE*)Instruction->modR_M.Mod);
		/*	解析Reg/OpCode，得到寄存器	*/
		if (Instruction->modR_M.IsReg)
		{
			AnalysisReg(Instruction);
		}
		else	//代表OpCode或者是查扩展表
		{
			AnalysisOp(Instruction, &currentCode);
		}
		/*	解析Mod和R/M，得到寄存器或内存		*/
		AnalysisModRM(Instruction, &currentCode);
	}
	
	/* 把各个部分组合起来，用sprintf来组合， 判断各个部分是否为空，不为空就组合 */
	sprintf(InstructionStr, "%s%s%s%s%s%s%s%s%s",
		g_AsmInstruction.prefix, strlen(g_AsmInstruction.prefix) > 0 ? "\t" : "",
		g_AsmInstruction.mnemonic, "\t",
		g_AsmInstruction.operandDes,
		strlen(g_AsmInstruction.operandSrc) > 0 ? ", " : "", g_AsmInstruction.operandSrc,
		strlen(g_AsmInstruction.operand3) > 0 ? ", " : "", g_AsmInstruction.operand3);

	currentCode++;
	return currentCode;
}

VOID JudgeOpCodetype(PBYTE* CurrentCode, PINSTRUCTION Instruction)
{
	BYTE* szFirstOpCode = (BYTE*)malloc(sizeof(BYTE) * 0x4);
	BYTE* szSecondOpCode = (BYTE*)malloc(sizeof(BYTE) * 0x4);

	GetByteBit(**CurrentCode, 4, 4, szFirstOpCode);
	GetByteBit(**CurrentCode, 4, 0, szSecondOpCode);

	switch(BinArr2dw(szFirstOpCode,4))
	{
		case 0x8:
		{
			//立即数
			if (BinArr2dw(szSecondOpCode, 4) >= 0x0 && BinArr2dw(szSecondOpCode, 4) <= 0x3)
			{
				/*	这组指令含有ModR/M	*/
				Instruction->HaveModRM = TRUE;
				Instruction->modR_M.IsReg = FALSE;
				sprintf(g_AsmInstruction.mnemonic, "add  ");
				//顺序固定，作源操作数
				Instruction->OpcodeOrder = 0;

				//解析w位-决定模式
				BYTE Bit_w = 0;
				GetByteBit(**CurrentCode, 1, 0, &Bit_w);
				if (Bit_w)	//32位或者16位
				{
					//判断前缀66h
					if (Instruction->OperandPrefix >= 0)		//16位模式
					{
						Instruction->dwRegFlag = 1;
					}
					else										//32位模式
					{
						Instruction->dwRegFlag = 2;
					}
				}
				else		//8位模式
				{
					Instruction->dwRegFlag = 0;
				}

				//判断前缀67h
				if (Instruction->AddressPrefix >= 0)		//16位模式
				{
					Instruction->dwMemoryFlag = 1;
				}
				else										//32位模式
				{
					Instruction->dwMemoryFlag = 2;
				}

				//解析s位
				BYTE Bit_s = 0;
				GetByteBit(**CurrentCode, 1, 1, &Bit_s);
				if (Bit_s)
				{
					Instruction->HaveSignExtend = TRUE;
				}
				else
				{
					Instruction->HaveSignExtend = FALSE;
				}

				/*	判断立即数宽度	*/
				if (BinArr2dw(szSecondOpCode, 4) == 0x1)
					Instruction->dwImeFlag = 1;
				else
					Instruction->dwImeFlag = 0;
				
			}
			//寄存器
			else if (BinArr2dw(szSecondOpCode, 4) >= 0x8 && BinArr2dw(szSecondOpCode, 4) <= 0xB)
			{
				/*	这组指令含有ModR/M	*/
				Instruction->HaveModRM = TRUE;
				sprintf(g_AsmInstruction.mnemonic, "mov  ");
				//解析d位，决定顺序
				BYTE Bit_d = 0;
				GetByteBit(**CurrentCode, 1, 1, &Bit_d);
				if (Bit_d)
				{
					Instruction->OpcodeOrder = 1;
				}
				else
				{
					Instruction->OpcodeOrder = 0;
				}
				//解析w位-决定模式
				BYTE Bit_w = 0;
				GetByteBit(**CurrentCode, 1, 0, &Bit_w);
				if (Bit_w)	//32位或者16位
				{
					//判断前缀66h
					if (Instruction->OperandPrefix >= 0)		//16位模式
					{
						Instruction->dwRegFlag = 1;
					}
					else										//32位模式
					{
						Instruction->dwRegFlag = 2;
					}
				}
				else		//8位模式
				{
					Instruction->dwRegFlag = 0;
				}
				//判断前缀67h
				if (Instruction->AddressPrefix >= 0)		//16位模式
				{
					Instruction->dwMemoryFlag = 1;
				}
				else										//32位模式
				{
					Instruction->dwMemoryFlag = 2;
				}

			}

			*CurrentCode += 1;
			break;
		}
		case 0x9:
		{
			sprintf(g_AsmInstruction.mnemonic, "nop");

			break;
		}
		default:
		{
			sprintf(g_AsmInstruction.mnemonic, "???");

			break;
		}
	}
	
}

VOID GetByteBit(BYTE Src, DWORD Len, DWORD Begin, BYTE* Res)
{
	for (DWORD i = Begin, j = 0; i < Begin + Len; i++, j++)
	{
		Res[j] = ((Src << (8 - i - 1)) &0x80) >> 0x7;
	}
}

DWORD BinArr2dw(BYTE* Res, DWORD Len)
{
	DWORD Ret = 0;
	for (DWORD i = 0; i < Len; i++)
	{
		DWORD Temp = Res[i] * pow(2, i);
		Ret += Temp;
	}
	return Ret;
}

VOID ClearInstruction(PINSTRUCTION Instruction)
{
	//清理硬编码结构
	Instruction->HaveSib = FALSE;
	Instruction->HaveModRM = FALSE;
	Instruction->OpcodeOrder = -1;
	Instruction->OpcodeType = -1;
	Instruction->RepeatPrefix = -1;
	Instruction->SegmentPrefix = -1;
	Instruction->OperandPrefix = -1;
	Instruction->AddressPrefix = -1;
	Instruction->dwMemoryFlag = -1;
	Instruction->dwRegFlag = -1;
	Instruction->dwRegFlag = -1;
	//清理汇编指令结构
	memset(&g_AsmInstruction, 0, MAX_OPERAND_LEN + MAX_MNEMONIC_LEN + MAX_OPERAND_LEN + MAX_OPERAND_LEN + MAX_OPERAND_LEN);
}

VOID AnalysisReg(PINSTRUCTION Instruction)
{
	switch (Instruction->dwRegFlag)
	{
		/*	8位	*/
		case 0:
		{
			if (Instruction->OpcodeOrder)
				sprintf(g_AsmInstruction.operandDes, Register8[BinArr2dw((BYTE*)Instruction->modR_M.Reg_OR_Op, 3)]);
			else
				sprintf(g_AsmInstruction.operandSrc, Register8[BinArr2dw((BYTE*)Instruction->modR_M.Reg_OR_Op, 3)]);
			break;
		}
		/*	16位	*/
		case 1:
		{
			if (Instruction->OpcodeOrder)
				sprintf(g_AsmInstruction.operandDes, Register16[BinArr2dw((BYTE*)Instruction->modR_M.Reg_OR_Op, 3)]);
			else
				sprintf(g_AsmInstruction.operandSrc, Register16[BinArr2dw((BYTE*)Instruction->modR_M.Reg_OR_Op, 3)]);
			break;
		}
		/*	32位	*/
		case 2:
		{
			if (Instruction->OpcodeOrder)
				sprintf(g_AsmInstruction.operandDes, Register32[BinArr2dw((BYTE*)Instruction->modR_M.Reg_OR_Op, 3)]);
			else
				sprintf(g_AsmInstruction.operandSrc, Register32[BinArr2dw((BYTE*)Instruction->modR_M.Reg_OR_Op, 3)]);
			break;
		}
	}
}

VOID AnalysisOp(PINSTRUCTION Instruction, PBYTE* currentCode)
{
	switch (Instruction->dwImeFlag)
	{
	case 0:
	{
		//注意符号位扩展问题
		TCHAR szOffset[20] = { 0 };
		if (Instruction->HaveSignExtend)
		{
			//判断当前是否为负数
			BYTE Highest_Bit;
			GetByteBit(*(*currentCode + 1), 1, 7, &Highest_Bit);
			TCHAR szOffset[20] = { 0 };
			if (Highest_Bit == 1)
			{
				BYTE Temp = 0xFF - *(*currentCode + 1) + 0x1;
				sprintf(szOffset, "%x", Temp);
				strcat(g_AsmInstruction.operandSrc, ", -0x");
				strcat(g_AsmInstruction.operandSrc, szOffset);
			}
		}
		else
		{
			sprintf(szOffset, "%x", *(*currentCode + 1));
			strcat(g_AsmInstruction.operandSrc, ", 0x");
			strcat(g_AsmInstruction.operandSrc, szOffset);
		}

		*currentCode += 1;
		break;
	}
	case 1:
	{
		if (Instruction->dwRegFlag == 1)		//16位
		{
			TCHAR szOffset[20] = { 0 };
			TCHAR szTemp[20] = { 0 };
			sprintf(szTemp, "%x", *(*currentCode + 2));
			strcat(szOffset, szTemp);
			sprintf(szTemp, "%x", *(*currentCode + 1));
			strcat(szOffset, szTemp);

			strcat(g_AsmInstruction.operandSrc, ", 0x");
			strcat(g_AsmInstruction.operandSrc, szOffset);

			*currentCode += 2;
		}
		else									//32位
		{
			TCHAR szOffset[20] = { 0 };
			TCHAR szTemp[20] = { 0 };
			sprintf(szTemp, "%x", *(*currentCode + 4));
			strcat(szOffset, szTemp);
			sprintf(szTemp, "%x", *(*currentCode + 3));
			strcat(szOffset, szTemp);
			sprintf(szTemp, "%x", *(*currentCode + 2));
			strcat(szOffset, szTemp);
			sprintf(szTemp, "%x", *(*currentCode + 1));
			strcat(szOffset, szTemp);

			strcat(g_AsmInstruction.operandSrc, ", 0x");
			strcat(g_AsmInstruction.operandSrc, szOffset);
			*currentCode += 4;
		}

		break;
	}
	}
}

VOID AnalysisModRM(PINSTRUCTION Instruction, PBYTE* currentCode)
{
	/*
	* 首先判断当前处于16位还是32位模式(查不同的表)
	*	16位下，无需考虑SIB问题
	*/
	switch (BinArr2dw((BYTE*)Instruction->modR_M.Mod, 2))
	{
		case 0x0:	/*	[Reg]	*/
		{
			//16位
			if (Instruction->dwMemoryFlag == 1)		
			{
				//特殊情况，[disp16]
				if (BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3) == 0x6)		
				{
					TCHAR szOffset[20] = { 0 };
					TCHAR szTemp[20] = { 0 };
					sprintf(szTemp, "%x", *(*currentCode + 2));
					strcat(szOffset, szTemp);
					sprintf(szTemp, "%x", *(*currentCode + 1));
					strcat(szOffset, szTemp);
					if (Instruction->OpcodeOrder == 0)
					{
						sprintf(g_AsmInstruction.operandDes, "%s  ptr  [%s]", OperateType[Instruction->dwRegFlag], szOffset);
					}
					else if (Instruction->OpcodeOrder == 1)
					{
						sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [%s]", OperateType[Instruction->dwRegFlag], szOffset);
					}
					*currentCode += 2;
				}
				//正常情况，[]
				else
				{
					if (Instruction->OpcodeOrder == 0)
					{
						sprintf(g_AsmInstruction.operandDes, "%s  ptr  [%s]", OperateType[Instruction->dwRegFlag], Address16[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
					}
					else if (Instruction->OpcodeOrder == 1)
					{
						sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [%s]", OperateType[Instruction->dwRegFlag], Address16[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
					}
				}
			}
			//32位
			else									
			{
				//判断SIB是否存在
				if (BinArr2dw((BYTE*)(Instruction->modR_M.R_OR_M), 3) == 4)
				{
					Instruction->HaveSib = TRUE;
					/*	解析Sib	*/
					TCHAR szContent[256] = { 0 };
					AnalysisSib(Instruction, currentCode, 0, szContent);

					if (Instruction->OpcodeOrder == 0)
					{
						sprintf(g_AsmInstruction.operandDes, "%s  ptr  [%s]", OperateType[Instruction->dwRegFlag], szContent);
					}
					else if (Instruction->OpcodeOrder == 1)
					{
						sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [%s]", OperateType[Instruction->dwRegFlag], szContent);
					}

					*currentCode += 1;
				}
				else
				{
					//特殊情况，[disp32]
					if (BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3) == 0x5)
					{
						TCHAR szOffset[20] = { 0 };
						TCHAR szTemp[20] = { 0 };
						sprintf(szTemp, "%x", *(*currentCode + 4));
						strcat(szOffset, szTemp);
						sprintf(szTemp, "%x", *(*currentCode + 3));
						strcat(szOffset, szTemp);
						sprintf(szTemp, "%x", *(*currentCode + 2));
						strcat(szOffset, szTemp);
						sprintf(szTemp, "%x", *(*currentCode + 1));
						strcat(szOffset, szTemp);
						if (Instruction->OpcodeOrder == 0)
						{
							sprintf(g_AsmInstruction.operandDes, "%s  ptr  [0x%s]", OperateType[Instruction->dwRegFlag], szOffset);
						}
						else if (Instruction->OpcodeOrder == 1)
						{
							sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [0x%s]", OperateType[Instruction->dwRegFlag], szOffset);
						}
						*currentCode += 4;
					}
					else
					{
						if (Instruction->OpcodeOrder == 0)
						{
							sprintf(g_AsmInstruction.operandDes, "%s  ptr  [%s]", OperateType[Instruction->dwRegFlag], Register32[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
						}
						else if (Instruction->OpcodeOrder == 1)
						{
							sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [%s]", OperateType[Instruction->dwRegFlag], Register32[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
						}
					}
				}
			}
			break;
		}
		case 0x1:	/*	[Reg + disp8]	*/
		{
			//16位
			if (Instruction->dwMemoryFlag == 1)		
			{
				/*
				*	判断立即数符号，如果为负数，则求其补码再添符号'-' 
				*		高位0：正数
				*		高位1：负数
				*/
				BYTE Highest_Bit;
				GetByteBit(*(*currentCode + 1), 1, 7, &Highest_Bit);
				TCHAR szOffset[20] = { 0 };
				if (Instruction->OpcodeOrder == 0)
				{
					if (Highest_Bit == 1)
					{
						BYTE Temp = 0xFF - *(*currentCode + 1) + 0x1;
						sprintf(szOffset, "%x", Temp);
						sprintf(g_AsmInstruction.operandDes, "%s  ptr  [%s - 0x%s]", OperateType[Instruction->dwRegFlag], Address16[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)], szOffset);
					}
					else
					{
						sprintf(szOffset, "%x", *(*currentCode + 1));
						sprintf(g_AsmInstruction.operandDes, "%s  ptr  [%s + 0x%s]", OperateType[Instruction->dwRegFlag], Address16[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)], szOffset);
					}
				}
				else if (Instruction->OpcodeOrder == 1)
				{
					if (Highest_Bit == 1)
					{
						BYTE Temp = 0xFF - *(*currentCode + 1) + 0x1;
						sprintf(szOffset, "%x", Temp);
						sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [%s - 0x%s]", OperateType[Instruction->dwRegFlag], Address16[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)], szOffset);
					}
					else
					{
						sprintf(szOffset, "%x", *(*currentCode + 1));
						sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [%s + 0x%s]", OperateType[Instruction->dwRegFlag], Address16[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)], szOffset);
					}
				}
				*currentCode += 1;
			}
			//32位
			else									
			{
				//判断SIB的存在
				if (BinArr2dw((BYTE*)(Instruction->modR_M.R_OR_M), 3) == 4)
				{
					Instruction->HaveSib = TRUE;
					/*	解析Sib	*/
					TCHAR szContent[256] = { 0 };
					AnalysisSib(Instruction, currentCode, 0x1, szContent);
					/*
					*	判断立即数符号，如果为负数，则求其补码再添符号'-'
					*		高位0：正数
					*		高位1：负数
					*/
					BYTE Highest_Bit;
					GetByteBit(*(*currentCode + 2), 1, 7, &Highest_Bit);
					TCHAR szOffset[20] = { 0 };
					if (Instruction->OpcodeOrder == 0)
					{
						if (Highest_Bit == 1)
						{
							BYTE Temp = 0xFF - *(*currentCode + 2) + 0x1;
							sprintf(szOffset, "%x", Temp);
							sprintf(g_AsmInstruction.operandDes, "%s  ptr  [%s - 0x%s]", OperateType[Instruction->dwRegFlag], szContent, szOffset);
						}
						else
						{
							sprintf(szOffset, "%x", *(*currentCode + 2));
							sprintf(g_AsmInstruction.operandDes, "%s  ptr  [%s + 0x%s]", OperateType[Instruction->dwRegFlag], szContent, szOffset);
						}

					}
					else if (Instruction->OpcodeOrder == 1)
					{
						if (Highest_Bit == 1)
						{
							BYTE Temp = 0xFF - *(*currentCode + 1) + 0x1;
							sprintf(szOffset, "%x", Temp);
							sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [%s - 0x%s]", OperateType[Instruction->dwRegFlag], szContent, szOffset);
						}
						else
						{
							sprintf(szOffset, "%x", *(*currentCode + 1));
							sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [%s + 0x%s]", OperateType[Instruction->dwRegFlag], szContent, szOffset);
						}
					}
					*currentCode += 2;
				}
				else
				{
					/*
					*	判断立即数符号，如果为负数，则求其补码再添符号'-'
					*		高位0：正数
					*		高位1：负数
					*/
					BYTE Highest_Bit;
					GetByteBit(*(*currentCode + 1), 1, 7, &Highest_Bit);
					TCHAR szOffset[20] = { 0 };
					if (Instruction->OpcodeOrder == 0)
					{
						if (Highest_Bit == 1)
						{
							BYTE Temp = 0xFF - *(*currentCode + 1) + 0x1;
							sprintf(szOffset, "%x", Temp);
							sprintf(g_AsmInstruction.operandDes, "%s  ptr  [%s - 0x%s]", OperateType[Instruction->dwRegFlag], Register32[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)], szOffset);
						}
						else
						{
							sprintf(szOffset, "%x", *(*currentCode + 1));
							sprintf(g_AsmInstruction.operandDes, "%s  ptr  [%s + 0x%s]", OperateType[Instruction->dwRegFlag], Register32[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)], szOffset);
						}

					}
					else if (Instruction->OpcodeOrder == 1)
					{
						if (Highest_Bit == 1)
						{
							BYTE Temp = 0xFF - *(*currentCode + 1) + 0x1;
							sprintf(szOffset, "%x", Temp);
							sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [%s - 0x%s]", OperateType[Instruction->dwRegFlag], Register32[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)], szOffset);
						}
						else
						{
							sprintf(szOffset, "%x", *(*currentCode + 1));
							sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [%s + 0x%s]", OperateType[Instruction->dwRegFlag], Register32[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)], szOffset);
						}
					}
					*currentCode += 1;
				}
			}
			break;
		}
		case 0x2:	/*	[Reg + disp16/disp32]	受前缀67h影响	*/
		{
			//16位
			if (Instruction->dwMemoryFlag == 1)		
			{
				TCHAR szOffset[20] = { 0 };
				TCHAR szTemp[20] = { 0 };
				sprintf(szTemp, "%x", *(*currentCode + 2));
				strcat(szOffset, szTemp);
				sprintf(szTemp, "%x", *(*currentCode + 1));
				strcat(szOffset, szTemp);
				if (Instruction->OpcodeOrder == 0)
				{
					sprintf(g_AsmInstruction.operandDes, "%s  ptr  [%s + 0x%s]", OperateType[Instruction->dwRegFlag], Address16[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)], szOffset);
				}
				else if (Instruction->OpcodeOrder == 1)
				{
					sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [%s + 0x%s]", OperateType[Instruction->dwRegFlag], Address16[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)], szOffset);
				}

				*currentCode += 2;
			}
			//32位
			else									
			{
				//判断SIB的存在
				if (BinArr2dw((BYTE*)(Instruction->modR_M.R_OR_M), 3) == 4)
				{
					Instruction->HaveSib = TRUE;
					/*	解析Sib	*/
					TCHAR szContent[256] = { 0 };
					AnalysisSib(Instruction, currentCode, 0x2, szContent);
					TCHAR szOffset[20] = { 0 };
					TCHAR szTemp[20] = { 0 };
					sprintf(szTemp, "%x", *(*currentCode + 5));
					strcat(szOffset, szTemp);
					sprintf(szTemp, "%x", *(*currentCode + 4));
					strcat(szOffset, szTemp);
					sprintf(szTemp, "%x", *(*currentCode + 3));
					strcat(szOffset, szTemp);
					sprintf(szTemp, "%x", *(*currentCode + 2));
					strcat(szOffset, szTemp);
					if (Instruction->OpcodeOrder == 0)
					{
						sprintf(g_AsmInstruction.operandDes, "%s  ptr  [%s + 0x%s]", OperateType[Instruction->dwRegFlag], szContent, szOffset);
					}
					else if (Instruction->OpcodeOrder == 1)
					{
						sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [%s + 0x%s]", OperateType[Instruction->dwRegFlag], szContent, szOffset);
					}

					*currentCode += 5;
				}
				else
				{
					TCHAR szOffset[20] = { 0 };
					TCHAR szTemp[20] = { 0 };
					sprintf(szTemp, "%x", *(*currentCode + 4));
					strcat(szOffset, szTemp);
					sprintf(szTemp, "%x", *(*currentCode + 3));
					strcat(szOffset, szTemp);
					sprintf(szTemp, "%x", *(*currentCode + 2));
					strcat(szOffset, szTemp);
					sprintf(szTemp, "%x", *(*currentCode + 1));
					strcat(szOffset, szTemp);
					if (Instruction->OpcodeOrder == 0)
					{
						sprintf(g_AsmInstruction.operandDes, "%s  ptr  [%s + 0x%s]", OperateType[Instruction->dwRegFlag], Register32[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)], szOffset);
					}
					else if (Instruction->OpcodeOrder == 1)
					{
						sprintf(g_AsmInstruction.operandSrc, "%s  ptr  [%s + 0x%s]", OperateType[Instruction->dwRegFlag], Register32[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)], szOffset);
					}

					*currentCode += 4;
				}
			}
			break;
		}
		case 0x3:	/*	寄存器	*/
		{
			switch (Instruction->dwRegFlag)
			{
				//8位
				case 0:
				{
					if(Instruction->OpcodeOrder == 1)
						sprintf(g_AsmInstruction.operandSrc, Register8[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
					else
						sprintf(g_AsmInstruction.operandDes, Register8[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
					break;
				}
				//16位
				case 1:
				{
					if (Instruction->OpcodeOrder == 1)
						sprintf(g_AsmInstruction.operandSrc, Register16[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
					else
						sprintf(g_AsmInstruction.operandDes, Register16[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
					break;
				}
				//32位
				case 2:
				{
					if (Instruction->OpcodeOrder == 1)
						sprintf(g_AsmInstruction.operandSrc, Register32[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
					else
						sprintf(g_AsmInstruction.operandDes, Register32[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
					break;
				}
			}
		}
		break;
	}
}

VOID AnalysisSib(PINSTRUCTION Instruction, PBYTE* currentCode, DWORD Mod, TCHAR* szContent)
{
	//为Sib赋值
	GetByteBit(*(*currentCode+1), 3, 0, (BYTE*)Instruction->Sib.Base);
	GetByteBit(*(*currentCode+1), 3, 3, (BYTE*)Instruction->Sib.Index);
	GetByteBit(*(*currentCode+1), 2, 6, (BYTE*)Instruction->Sib.Scale);
	//Base获取到的临时内容
	TCHAR szBase[20] = { 0 };
	TCHAR szScaledIndex[20] = { 0 };

//获取Base指向的寄存器
	//特殊情况：Base为101，[*]
	if (BinArr2dw((BYTE*)Instruction->Sib.Base, 3) == 0x5)
	{
		//判断ModR/M里Mod的值
		switch (Mod)
		{
			case 0:
			{
				TCHAR szOffset[20] = { 0 };
				TCHAR szTemp[20] = { 0 };
				sprintf(szTemp, "%x", *(*currentCode + 5));
				strcat(szOffset, szTemp);
				sprintf(szTemp, "%x", *(*currentCode + 4));
				strcat(szOffset, szTemp);
				sprintf(szTemp, "%x", *(*currentCode + 3));
				strcat(szOffset, szTemp);
				sprintf(szTemp, "%x", *(*currentCode + 2));
				strcat(szOffset, szTemp);

				strcat(szBase, "0x");
				strcat(szBase, szOffset);

				*currentCode += 0x4;
				break;
			}
			case 1:
			{
				sprintf(szBase, "ebp");

				TCHAR szOffset[20] = { 0 };
				sprintf(szOffset, "%x", *(*currentCode + 2));

				strcat(szBase, " + 0x");
				strcat(szBase, szOffset);

				*currentCode += 0x1;
				break;
			}
			case 2:
			{
				sprintf(szBase, "ebp");
				TCHAR szOffset[20] = { 0 };
				TCHAR szTemp[20] = { 0 };
				sprintf(szTemp, "%x", *(*currentCode + 5));
				strcat(szOffset, szTemp);
				sprintf(szTemp, "%x", *(*currentCode + 4));
				strcat(szOffset, szTemp);
				sprintf(szTemp, "%x", *(*currentCode + 3));
				strcat(szOffset, szTemp);
				sprintf(szTemp, "%x", *(*currentCode + 2));
				strcat(szOffset, szTemp);

				strcat(szBase, " + 0x");
				strcat(szBase, szOffset);

				*currentCode += 0x4;
				break;
			}
		}
	}
	else
	{
		sprintf(szBase, Register32[BinArr2dw((BYTE*)Instruction->Sib.Base, 3)]);
	}
//获取ScaledIndex的内容
	//特殊情况：Index为100，2^n部分不存在，只有base + (disp8/32)
	if (BinArr2dw((BYTE*)Instruction->Sib.Index, 3) != 0x4)
	{
		switch (BinArr2dw((BYTE*)Instruction->Sib.Scale, 2))
		{
			case 0x0:
			{
				sprintf(szScaledIndex, "%s", Register32[BinArr2dw((BYTE*)Instruction->Sib.Index, 3)]);

				break;
			}
			case 0x1:
			{
				sprintf(szScaledIndex, "%s*2", Register32[BinArr2dw((BYTE*)Instruction->Sib.Index, 3)]);

				break;
			}
			case 0x2:
			{
				sprintf(szScaledIndex, "%s*4", Register32[BinArr2dw((BYTE*)Instruction->Sib.Index, 3)]);

				break;
			}
			case 0x3:
			{
				sprintf(szScaledIndex, "%s*8", Register32[BinArr2dw((BYTE*)Instruction->Sib.Index, 3)]);

				break;
			}
		}
	}
	
//组合
	sprintf(szContent, "%s%s%s",
		szBase, strlen(szScaledIndex) > 0 ? "+" : "",
		szScaledIndex);
}