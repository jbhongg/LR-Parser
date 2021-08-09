#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define PLUS 1
#define MULTY 2
#define OPEN 3
#define CLOSE 4
#define ID 5
#define NUM 6

int tocken[100] = { ' ', };
int index = 0;
char arr[100] = { ' ', };
void make_token(char* lexeme);
int LR();

typedef struct Tocken_arr {
	int tocken_arr[1000];
}Tocken_arr;

Tocken_arr T_arr;

int main()
{
	char *lexeme = malloc(sizeof(char) * 100); //���ڿ��� �����Ҵ���
	int j = 1;
	int i;//��ū�迭 �ε���

	printf("���ڿ��� �Է��ϼ��� : ");
	gets(lexeme); //���ڿ��� �Է¹���
	printf("-------------------------------------------------------------------\n");

	make_token(lexeme); //���� �м���

	for(i = 1; i <= index; i++)
	{
		T_arr.tocken_arr[i] = tocken[i];
	}
	T_arr.tocken_arr[index + 1] = '$';

	i = 0;

	for (j = 1; j<=index; j++ ) //��ū��ȯ
	{
		if (T_arr.tocken_arr[j] == 1)
			arr[i++] = '+';
		else if (T_arr.tocken_arr[j] == 2)
			arr[i++] = '*';
		else if (T_arr.tocken_arr[j] == 3)
			arr[i++] = '(';
		else if (T_arr.tocken_arr[j] == 4)
			arr[i++] = ')';
		else if (T_arr.tocken_arr[j] == 5)
		{
			arr[i++] = 'i';
			arr[i++] = 'd';
		}
		else if (T_arr.tocken_arr[j] == 6)
		{
			arr[i++] = 'n';
			arr[i++] = 'u';
			arr[i++] = 'm';
		}		
	}
	arr[i] = '$';
	LR();
	printf("\n");
	free(lexeme); // ���ڿ� �޸� ����
}

void make_token(char* lexeme)
{
	int i = 0; // �Է� ���ڿ� �迭 ��ȣ ����

	printf("�Է��Ͻ� ���ڿ��� %s �Դϴ�.\n", lexeme); //�Է��� ���ڿ� ��Ȯ��

	while (lexeme[i] != '\0') // �Է��� ������ �ݺ�
	{
		if (lexeme[i] == '+') // +�� ���
		{
			tocken[++index] = PLUS;
		}//�޼������
		else if (lexeme[i] == '*') // *�� ���
		{
			tocken[++index] = MULTY;
		} //�޼������
		else if (lexeme[i] == '(') // (�� ���
		{
			tocken[++index] = OPEN;
		} //�޼������
		else if (lexeme[i] == ')') // )�� ���
		{
			tocken[++index] = CLOSE;
		} //�޼������
		else if ((('a' <= lexeme[i]) && (lexeme[i] <= 'z')) || ('A' <= lexeme[i]) && (lexeme[i] <= 'Z'))
			//���ĺ��� ���
		{
			while ((('a' <= lexeme[i]) && (lexeme[i] <= 'z')) || ('A' <= lexeme[i]) && (lexeme[i] <= 'Z') || ('0' <= lexeme[i]) && (lexeme[i] <= '9'))
				//���� ���ڵ� ���ĺ��� �������� �˻�
			{
				lexeme[i++];
			}
			{
				tocken[++index] = ID;
			} // ���ĺ��� ���� �̿��� ���ڰ� ������ �޼������
			i--; //��Ʈ��ŷ (������� sum+�� ��� +�� �а������ű� ������)
		}
		else if ('0' <= lexeme[i] && lexeme[i] <= '9')
			//������ ���
		{
			while ('0' <= lexeme[i] && lexeme[i] <= '9')
				//���� ���ڵ� �������� �˻�
			{
				lexeme[i++];
			}
			{
				tocken[++index] = NUM;
			} // ���� �̿��� ���ڰ� ������ �޼������
			i--; //��Ʈ��ŷ (������� 88-�� ��� -�� �а������ű� ������)
		}
		else if (lexeme[i] == ' ')
		{
		}
		else // �� ��쿡 ���� �ش����� ������
		{
			printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
			exit(1);
		}

		i++; //���� ���ڸ� �о��
	}
}

int LR()
{
	char stack[929] = { 0, }; //���� �迭, FAIL�� �ʱ�ȭ
	int stack_num = 0; // ���� �ε��� ����
	int tocken_num = 1; // ��ū �ε��� ����
	int arr_num = 0; //�Է� �ε��� ����
	int i= 0;
	int tmp = 0; //���� �Է� �ε��� ���� ���� 

	stack[0] = '0'; //������ ù��°�� 0���� �����Ѵ�.

	printf("����%30s%33s\n", "�Է�", "����");
	printf("%c", stack[0]);
	printf("%25c", ' ');

	while (arr[i] != '\0')
	{
		printf("%c", arr[i]);
		i++;
	}
	while(1)
	{
		//���� 0 ///////////////////////////////////////////////
		if ((stack[stack_num-1] != '1') && (stack[stack_num] == '0'))
		{
			if (T_arr.tocken_arr[tocken_num] == OPEN) //���� 0�̰� (�̸�
			{
				stack[++stack_num] = '(';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '4';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 4");
				for (i = 0; i <= stack_num; i++)
					printf("%c" , stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else if (T_arr.tocken_arr[tocken_num] == ID) //���� 0�̰� ID�̸�
			{
				stack[++stack_num] = 'i';
				arr[arr_num++] = ' ';
				stack[++stack_num] = 'd';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '5';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 5");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%-24c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else if (T_arr.tocken_arr[tocken_num] == NUM) //���� 0�̰� NUM�̸�
			{
				stack[++stack_num] = 'n';
				arr[arr_num++] = ' ';
				stack[++stack_num] = 'u';
				arr[arr_num++] = ' ';
				stack[++stack_num] = 'm';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '6';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 6");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else if (stack[stack_num + 1] == 'E') //���� 0�̰� E�̸�
			{
				++stack_num;
				stack[++stack_num] = '1';
				tmp = arr_num;
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else if (stack[stack_num + 1] == 'T') //���� 0�̰� T�̸�
			{
				++stack_num;
				stack[++stack_num] = '2';
				tmp = arr_num;
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else if (stack[stack_num + 1] == 'F') //���� 0�̰� F�̸�
			{
				++stack_num;
				stack[++stack_num] = '3';
				tmp = arr_num;
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else
			{
				printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		//���� 1 ///////////////////////////////////////////////
		else if ((stack[stack_num-1] != '1') && (stack[stack_num] == '1'))
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS) //���� 1�̰� (�̸�
			{
				stack[++stack_num] = '+';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '7';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 7");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else if (T_arr.tocken_arr[tocken_num] == '$') //���� 1�̰� $�̸�
			{
				printf("%33s\n", "accept");
				printf("Accept!!!������ �´� ���ڿ��Դϴ�.\n");
				return 0;
			}
			else
			{
				printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 2//////////////////////////////////////////////
		else if ((stack[stack_num-1] != '1') && (stack[stack_num] == '2'))
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$') //���� 2�̰� + �Ǵ� ) �Ǵ� $�̸�
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'T')
					{
						stack[i] = 'E';
						for (int j = i + 1; j <= stack_num; j++)
						{
							stack[j] = ' ';
						}
					}
				}
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'E')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("%33s\n", "reduce 2(E->T)");
			}
			else if (T_arr.tocken_arr[tocken_num] == MULTY) //���� 2�̰� *�̸�
			{
				stack[++stack_num] = '*';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '8';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 8");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%24c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else
			{
				printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 3//////////////////////////////////////////////
		else if (stack[stack_num] == '3')
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MULTY || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$')//���� 3�̰� + �Ǵ� * �Ǵ� ) �Ǵ� $�̸�
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'F')
					{
						stack[i] = 'T';
						for (int j = i + 1; j <= stack_num; j++)
						{
							stack[j] = ' ';
						}
					}
				}
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'T')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("%33s\n", "reduce 4(T->F)");
			}
			else
			{
				printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 4//////////////////////////////////////////////
		else if (stack[stack_num] == '4')
		{
			if (T_arr.tocken_arr[tocken_num] == ID)//���� 4�̰� ID�̸�
			{
				stack[++stack_num] = 'i';
				arr[arr_num++] = ' ';
				stack[++stack_num] = 'd';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '5';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 5");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else if (T_arr.tocken_arr[tocken_num] == NUM)//���� 4�̰� NUM�̸�
			{
				stack[++stack_num] = 'n';
				arr[arr_num++] = ' ';
				stack[++stack_num] = 'u';
				arr[arr_num++] = ' ';
				stack[++stack_num] = 'm';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '6';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 6");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else if (stack[stack_num + 1] == 'E')//���� 4�̰� E�̸�
			{
				++stack_num;
				stack[++stack_num] = '9';
				tmp = arr_num;
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else if (stack[stack_num + 1] == 'T')//���� 4�̰� T�̸�
			{
				++stack_num;
				stack[++stack_num] = '2';
				tmp = arr_num;
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else if (stack[stack_num + 1] == 'F')//���� 4�̰� F�̸�
			{
				++stack_num;
				stack[++stack_num] = '3';
				tmp = arr_num;
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else
			{
				printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 5//////////////////////////////////////////////
		else if (stack[stack_num] == '5')
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MULTY || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$')//���� 5�̰� +�Ǵ� * �Ǵ� ) �Ǵ� $�̸�
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'i')
					{
						stack[i] = 'F';
						for (int j = i + 1; j <= stack_num; j++)
						{
							stack[j] = ' ';
						}
					}
				}
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'F')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("%33s\n", "reduce 6(F->id)");
			}
			else
			{
				printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 6//////////////////////////////////////////////
		else if (stack[stack_num] == '6')
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MULTY || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$')
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'n')
					{
						stack[i] = 'F';
						for (int j = i + 1; j <= stack_num; j++)
						{
							stack[j] = ' ';
						}
					}
				}
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'F')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("%33s\n", "reduce 7(F->num)");
			}
			else
			{
				printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 7//////////////////////////////////////////////
		else if (stack[stack_num] == '7')
		{
			if (T_arr.tocken_arr[tocken_num] == OPEN)
			{
				stack[++stack_num] = '(';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '4';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 4");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}

			else if (T_arr.tocken_arr[tocken_num] == ID)
			{
				stack[++stack_num] = 'i';
				arr[arr_num++] = ' ';
				stack[++stack_num] = 'd';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '5';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 5");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}

			else if (T_arr.tocken_arr[tocken_num] == NUM)
			{
				stack[++stack_num] = 'n';
				arr[arr_num++] = ' ';
				stack[++stack_num] = 'u';
				arr[arr_num++] = ' ';
				stack[++stack_num] = 'm';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '6';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 6");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}
			else if (stack[stack_num + 1] == 'T')
			{
				++stack_num;
				stack[++stack_num] = '1';
				stack[++stack_num] = '0';
				tmp = arr_num;
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}

			else if (stack[stack_num + 1] == 'F')
			{
				++stack_num;
				stack[++stack_num] = '3';
				tmp = arr_num;
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}

			else
			{
				printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 8//////////////////////////////////////////////
		else if (stack[stack_num] == '8')
		{
			if (T_arr.tocken_arr[tocken_num] == OPEN)
			{
				stack[++stack_num] = '(';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '4';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 4");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}

			else if (T_arr.tocken_arr[tocken_num] == ID)
			{
				stack[++stack_num] = 'i';
				arr[arr_num++] = ' ';
				stack[++stack_num] = 'd';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '5';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 5");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}

			else if (T_arr.tocken_arr[tocken_num] == NUM)
			{
				stack[++stack_num] = 'n';
				arr[arr_num++] = ' ';
				stack[++stack_num] = 'u';
				arr[arr_num++] = ' ';
				stack[++stack_num] = 'm';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '6';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 6");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%23c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}

			else if (stack[stack_num + 1] == 'F')
			{
				++stack_num;
				stack[++stack_num] = '1';
				stack[++stack_num] = '1';
				tmp = arr_num;
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%24c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}

			else
			{
				printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 9//////////////////////////////////////////////
		else if (stack[stack_num] == '9')
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS)
			{
				stack[++stack_num] = '+';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '7';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 7");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
			}

			else if (T_arr.tocken_arr[tocken_num] == CLOSE)
			{
				stack[++stack_num] = ')';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '1';
				stack[++stack_num] = '2';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 12");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}

			else
			{
				printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 10/////////////////////////////////////////////
		else if ((stack[stack_num-1] == '1') && (stack[stack_num] == '0'))
		{
			if (T_arr.tocken_arr[tocken_num] == MULTY)
			{
				stack[++stack_num] = '*';
				arr[arr_num++] = ' ';
				stack[++stack_num] = '8';
				tocken_num++;
				tmp = arr_num;
				printf("%33s\n", "Shift 8");
				for (i = 0; i <= stack_num; i++)
					printf("%c", stack[i]);
				printf("%25c", ' ');
				while (arr[arr_num] != '\0')
				{
					printf("%c", arr[arr_num]);
					arr_num++;
				}
				arr_num = tmp;
			}

			else if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$')
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'E')
					{
						for (int j = i + 1; j <= stack_num; j++)
						{
							if (stack[j] == '+')
							{
								for (int k = j + 1; k <= stack_num; k++)
								{
									if (stack[k] == 'T')
									{
										for (int m = i + 1; m <= stack_num; m++)
										{
											stack[m] = ' ';
										}
									}
								}
							}
						}
					}
				}

				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'E')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("%33s\n", "reduce 1(E->E+T)");
			}

			else
			{
				printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 11/////////////////////////////////////////////
		else if ((stack[stack_num-1] == '1') && (stack[stack_num] == '1'))
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MULTY || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$')
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'T')
					{
						for (int j = i + 1; j <= stack_num; j++)
						{
							if (stack[j] == '*')
							{
								for (int k = j + 1; k <= stack_num; k++)
								{
									if (stack[k] == 'F')
									{
										for (int m = i + 1; m <= stack_num; m++)
										{
											stack[m] = ' ';
										}
									}
								}
							}
						}
					}
				}

				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'T')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("%33s\n", "reduce 3(T->T*F)");
			}

			else
			{
				printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 12/////////////////////////////////////////////
		else if ((stack[stack_num-1] == '1') && (stack[stack_num] == '2'))
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MULTY || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$')
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == '(')
					{
						for (int j = i + 1; j <= stack_num; j++)
						{
							if (stack[j] == 'E')
							{
								for (int k = j + 1; k <= stack_num; k++)
								{
									if (stack[k] == ')')
									{
										stack[i] = 'F';
										for (int m = i + 1; m <= stack_num; m++)
										{
											stack[m] = ' ';
										}
									}
								}
							}
						}
					}
				}

				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'F')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("%33s\n", "reduce 5(F->(E))");
			}
			else
			{
				printf("\nParsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
	}
}