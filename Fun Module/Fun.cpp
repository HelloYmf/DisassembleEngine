#include "Fun.h"

//ǰ׺�ִ�
const char* RepeatPrefixes[] = { "lock", "rep", "repe", "repz", "repne", "repnz" };
const char* SegmentRegisters[] = { "es", "cs", "ss", "ds", "fs", "gs" };
//32λ�Ĵ����ִ�
const char* Register32[] = { "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi" };
//16λ�Ĵ����ִ�
const char* Register16[] = { "ax", "cx", "dx", "bx", "sp", "bp", "si", "di" };
//8λ�Ĵ����ִ�
const char* Register8[] = { "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh" };
//16λѰַ�Ĵ������
const char* Address16[] = { "bx+si", "bx+di", "bp+si", "bp+di", "si", "di", "bp", "bx" };
//��������
const char* OperateType[] = { "byte", "word", "dword" };

/*
* ���ָ��ͨ�ýṹ
*/
ASMINSTRUCTION g_AsmInstruction;

PBYTE Disassemble(PBYTE DesCode, PINSTRUCTION Instruction, PTCHAR InstructionStr)
{
	//����֮ǰ����(Ӳ����ṹ+���ṹ)
	ClearInstruction(Instruction);

	//���ǰ׺�Ƿ��ҵ��ظ����ҵ��ظ��ͻ�����ɨ��
	int prefixFlag = 0;				

	/* ����ָ��ǰ׺ */
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
	
	/*	����OpCode	*/
	JudgeOpCodetype(&currentCode, Instruction);

	/*	����ModR/M	*/
	if (Instruction->HaveModRM)
	{
		//ΪModR/M��ֵ
		GetByteBit(*currentCode, 3, 0, (BYTE*)Instruction->modR_M.R_OR_M);
		GetByteBit(*currentCode, 3, 3, (BYTE*)Instruction->modR_M.Reg_OR_Op);
		GetByteBit(*currentCode, 2, 6, (BYTE*)Instruction->modR_M.Mod);
		/*	����Reg/OpCode���õ��Ĵ���	*/
		if (Instruction->modR_M.IsReg)
		{
			AnalysisReg(Instruction);
		}
		else	//����OpCode�����ǲ���չ��
		{
			AnalysisOp(Instruction, &currentCode);
		}
		/*	����Mod��R/M���õ��Ĵ������ڴ�		*/
		AnalysisModRM(Instruction, &currentCode);
	}
	
	/* �Ѹ������������������sprintf����ϣ� �жϸ��������Ƿ�Ϊ�գ���Ϊ�վ���� */
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
			//������
			if (BinArr2dw(szSecondOpCode, 4) >= 0x0 && BinArr2dw(szSecondOpCode, 4) <= 0x3)
			{
				/*	����ָ���ModR/M	*/
				Instruction->HaveModRM = TRUE;
				Instruction->modR_M.IsReg = FALSE;
				sprintf(g_AsmInstruction.mnemonic, "add  ");
				//˳��̶�����Դ������
				Instruction->OpcodeOrder = 0;

				//����wλ-����ģʽ
				BYTE Bit_w = 0;
				GetByteBit(**CurrentCode, 1, 0, &Bit_w);
				if (Bit_w)	//32λ����16λ
				{
					//�ж�ǰ׺66h
					if (Instruction->OperandPrefix >= 0)		//16λģʽ
					{
						Instruction->dwRegFlag = 1;
					}
					else										//32λģʽ
					{
						Instruction->dwRegFlag = 2;
					}
				}
				else		//8λģʽ
				{
					Instruction->dwRegFlag = 0;
				}

				//�ж�ǰ׺67h
				if (Instruction->AddressPrefix >= 0)		//16λģʽ
				{
					Instruction->dwMemoryFlag = 1;
				}
				else										//32λģʽ
				{
					Instruction->dwMemoryFlag = 2;
				}

				//����sλ
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

				/*	�ж����������	*/
				if (BinArr2dw(szSecondOpCode, 4) == 0x1)
					Instruction->dwImeFlag = 1;
				else
					Instruction->dwImeFlag = 0;
				
			}
			//�Ĵ���
			else if (BinArr2dw(szSecondOpCode, 4) >= 0x8 && BinArr2dw(szSecondOpCode, 4) <= 0xB)
			{
				/*	����ָ���ModR/M	*/
				Instruction->HaveModRM = TRUE;
				sprintf(g_AsmInstruction.mnemonic, "mov  ");
				//����dλ������˳��
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
				//����wλ-����ģʽ
				BYTE Bit_w = 0;
				GetByteBit(**CurrentCode, 1, 0, &Bit_w);
				if (Bit_w)	//32λ����16λ
				{
					//�ж�ǰ׺66h
					if (Instruction->OperandPrefix >= 0)		//16λģʽ
					{
						Instruction->dwRegFlag = 1;
					}
					else										//32λģʽ
					{
						Instruction->dwRegFlag = 2;
					}
				}
				else		//8λģʽ
				{
					Instruction->dwRegFlag = 0;
				}
				//�ж�ǰ׺67h
				if (Instruction->AddressPrefix >= 0)		//16λģʽ
				{
					Instruction->dwMemoryFlag = 1;
				}
				else										//32λģʽ
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
	//����Ӳ����ṹ
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
	//������ָ��ṹ
	memset(&g_AsmInstruction, 0, MAX_OPERAND_LEN + MAX_MNEMONIC_LEN + MAX_OPERAND_LEN + MAX_OPERAND_LEN + MAX_OPERAND_LEN);
}

VOID AnalysisReg(PINSTRUCTION Instruction)
{
	switch (Instruction->dwRegFlag)
	{
		/*	8λ	*/
		case 0:
		{
			if (Instruction->OpcodeOrder)
				sprintf(g_AsmInstruction.operandDes, Register8[BinArr2dw((BYTE*)Instruction->modR_M.Reg_OR_Op, 3)]);
			else
				sprintf(g_AsmInstruction.operandSrc, Register8[BinArr2dw((BYTE*)Instruction->modR_M.Reg_OR_Op, 3)]);
			break;
		}
		/*	16λ	*/
		case 1:
		{
			if (Instruction->OpcodeOrder)
				sprintf(g_AsmInstruction.operandDes, Register16[BinArr2dw((BYTE*)Instruction->modR_M.Reg_OR_Op, 3)]);
			else
				sprintf(g_AsmInstruction.operandSrc, Register16[BinArr2dw((BYTE*)Instruction->modR_M.Reg_OR_Op, 3)]);
			break;
		}
		/*	32λ	*/
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
		//ע�����λ��չ����
		TCHAR szOffset[20] = { 0 };
		if (Instruction->HaveSignExtend)
		{
			//�жϵ�ǰ�Ƿ�Ϊ����
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
		if (Instruction->dwRegFlag == 1)		//16λ
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
		else									//32λ
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
	* �����жϵ�ǰ����16λ����32λģʽ(�鲻ͬ�ı�)
	*	16λ�£����迼��SIB����
	*/
	switch (BinArr2dw((BYTE*)Instruction->modR_M.Mod, 2))
	{
		case 0x0:	/*	[Reg]	*/
		{
			//16λ
			if (Instruction->dwMemoryFlag == 1)		
			{
				//���������[disp16]
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
				//���������[]
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
			//32λ
			else									
			{
				//�ж�SIB�Ƿ����
				if (BinArr2dw((BYTE*)(Instruction->modR_M.R_OR_M), 3) == 4)
				{
					Instruction->HaveSib = TRUE;
					/*	����Sib	*/
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
					//���������[disp32]
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
			//16λ
			if (Instruction->dwMemoryFlag == 1)		
			{
				/*
				*	�ж����������ţ����Ϊ�����������䲹���������'-' 
				*		��λ0������
				*		��λ1������
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
			//32λ
			else									
			{
				//�ж�SIB�Ĵ���
				if (BinArr2dw((BYTE*)(Instruction->modR_M.R_OR_M), 3) == 4)
				{
					Instruction->HaveSib = TRUE;
					/*	����Sib	*/
					TCHAR szContent[256] = { 0 };
					AnalysisSib(Instruction, currentCode, 0x1, szContent);
					/*
					*	�ж����������ţ����Ϊ�����������䲹���������'-'
					*		��λ0������
					*		��λ1������
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
					*	�ж����������ţ����Ϊ�����������䲹���������'-'
					*		��λ0������
					*		��λ1������
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
		case 0x2:	/*	[Reg + disp16/disp32]	��ǰ׺67hӰ��	*/
		{
			//16λ
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
			//32λ
			else									
			{
				//�ж�SIB�Ĵ���
				if (BinArr2dw((BYTE*)(Instruction->modR_M.R_OR_M), 3) == 4)
				{
					Instruction->HaveSib = TRUE;
					/*	����Sib	*/
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
		case 0x3:	/*	�Ĵ���	*/
		{
			switch (Instruction->dwRegFlag)
			{
				//8λ
				case 0:
				{
					if(Instruction->OpcodeOrder == 1)
						sprintf(g_AsmInstruction.operandSrc, Register8[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
					else
						sprintf(g_AsmInstruction.operandDes, Register8[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
					break;
				}
				//16λ
				case 1:
				{
					if (Instruction->OpcodeOrder == 1)
						sprintf(g_AsmInstruction.operandSrc, Register16[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
					else
						sprintf(g_AsmInstruction.operandDes, Register16[BinArr2dw((BYTE*)Instruction->modR_M.R_OR_M, 3)]);
					break;
				}
				//32λ
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
	//ΪSib��ֵ
	GetByteBit(*(*currentCode+1), 3, 0, (BYTE*)Instruction->Sib.Base);
	GetByteBit(*(*currentCode+1), 3, 3, (BYTE*)Instruction->Sib.Index);
	GetByteBit(*(*currentCode+1), 2, 6, (BYTE*)Instruction->Sib.Scale);
	//Base��ȡ������ʱ����
	TCHAR szBase[20] = { 0 };
	TCHAR szScaledIndex[20] = { 0 };

//��ȡBaseָ��ļĴ���
	//���������BaseΪ101��[*]
	if (BinArr2dw((BYTE*)Instruction->Sib.Base, 3) == 0x5)
	{
		//�ж�ModR/M��Mod��ֵ
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
//��ȡScaledIndex������
	//���������IndexΪ100��2^n���ֲ����ڣ�ֻ��base + (disp8/32)
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
	
//���
	sprintf(szContent, "%s%s%s",
		szBase, strlen(szScaledIndex) > 0 ? "+" : "",
		szScaledIndex);
}