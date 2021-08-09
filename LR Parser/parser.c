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
	char *lexeme = malloc(sizeof(char) * 100); //문자열을 동적할당함
	int j = 1;
	int i;//토큰배열 인덱스

	printf("문자열을 입력하세요 : ");
	gets(lexeme); //문자열을 입력받음
	printf("-------------------------------------------------------------------\n");

	make_token(lexeme); //어휘 분석기

	for(i = 1; i <= index; i++)
	{
		T_arr.tocken_arr[i] = tocken[i];
	}
	T_arr.tocken_arr[index + 1] = '$';

	i = 0;

	for (j = 1; j<=index; j++ ) //토큰변환
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
	free(lexeme); // 문자열 메모리 해제
}

void make_token(char* lexeme)
{
	int i = 0; // 입력 문자열 배열 번호 변수

	printf("입력하신 문자열은 %s 입니다.\n", lexeme); //입력한 문자열 재확인

	while (lexeme[i] != '\0') // 입력의 끝까지 반복
	{
		if (lexeme[i] == '+') // +일 경우
		{
			tocken[++index] = PLUS;
		}//메세지출력
		else if (lexeme[i] == '*') // *일 경우
		{
			tocken[++index] = MULTY;
		} //메세지출력
		else if (lexeme[i] == '(') // (일 경우
		{
			tocken[++index] = OPEN;
		} //메세지출력
		else if (lexeme[i] == ')') // )일 경우
		{
			tocken[++index] = CLOSE;
		} //메세지출력
		else if ((('a' <= lexeme[i]) && (lexeme[i] <= 'z')) || ('A' <= lexeme[i]) && (lexeme[i] <= 'Z'))
			//알파벳일 경우
		{
			while ((('a' <= lexeme[i]) && (lexeme[i] <= 'z')) || ('A' <= lexeme[i]) && (lexeme[i] <= 'Z') || ('0' <= lexeme[i]) && (lexeme[i] <= '9'))
				//다음 문자도 알파벳과 숫자인지 검사
			{
				lexeme[i++];
			}
			{
				tocken[++index] = ID;
			} // 알파벳과 숫자 이외의 문자가 나오면 메세지출력
			i--; //백트랙킹 (예를들어 sum+일 경우 +를 읽고있을거기 때문에)
		}
		else if ('0' <= lexeme[i] && lexeme[i] <= '9')
			//숫자일 경우
		{
			while ('0' <= lexeme[i] && lexeme[i] <= '9')
				//다음 문자도 숫자인지 검사
			{
				lexeme[i++];
			}
			{
				tocken[++index] = NUM;
			} // 숫자 이외의 문자가 나오면 메세지출력
			i--; //백트랙킹 (예를들어 88-일 경우 -를 읽고있을거기 때문에)
		}
		else if (lexeme[i] == ' ')
		{
		}
		else // 위 경우에 전부 해당하지 않을때
		{
			printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
			exit(1);
		}

		i++; //다음 문자를 읽어옴
	}
}

int LR()
{
	char stack[929] = { 0, }; //스텍 배열, FAIL로 초기화
	int stack_num = 0; // 스텍 인덱스 변수
	int tocken_num = 1; // 토큰 인덱스 변수
	int arr_num = 0; //입력 인덱스 변수
	int i= 0;
	int tmp = 0; //이전 입력 인덱스 저장 변수 

	stack[0] = '0'; //스텍의 첫번째는 0으로 시작한다.

	printf("스택%30s%33s\n", "입력", "동작");
	printf("%c", stack[0]);
	printf("%25c", ' ');

	while (arr[i] != '\0')
	{
		printf("%c", arr[i]);
		i++;
	}
	while(1)
	{
		//상태 0 ///////////////////////////////////////////////
		if ((stack[stack_num-1] != '1') && (stack[stack_num] == '0'))
		{
			if (T_arr.tocken_arr[tocken_num] == OPEN) //상태 0이고 (이면
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
			else if (T_arr.tocken_arr[tocken_num] == ID) //상태 0이고 ID이면
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
			else if (T_arr.tocken_arr[tocken_num] == NUM) //상태 0이고 NUM이면
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
			else if (stack[stack_num + 1] == 'E') //상태 0이고 E이면
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
			else if (stack[stack_num + 1] == 'T') //상태 0이고 T이면
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
			else if (stack[stack_num + 1] == 'F') //상태 0이고 F이면
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
				printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		//상태 1 ///////////////////////////////////////////////
		else if ((stack[stack_num-1] != '1') && (stack[stack_num] == '1'))
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS) //상태 1이고 (이면
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
			else if (T_arr.tocken_arr[tocken_num] == '$') //상태 1이고 $이면
			{
				printf("%33s\n", "accept");
				printf("Accept!!!문법에 맞는 문자열입니다.\n");
				return 0;
			}
			else
			{
				printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 2//////////////////////////////////////////////
		else if ((stack[stack_num-1] != '1') && (stack[stack_num] == '2'))
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$') //상태 2이고 + 또는 ) 또는 $이면
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
			else if (T_arr.tocken_arr[tocken_num] == MULTY) //상태 2이고 *이면
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
				printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 3//////////////////////////////////////////////
		else if (stack[stack_num] == '3')
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MULTY || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$')//상태 3이고 + 또는 * 또는 ) 또는 $이면
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
				printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 4//////////////////////////////////////////////
		else if (stack[stack_num] == '4')
		{
			if (T_arr.tocken_arr[tocken_num] == ID)//상태 4이고 ID이면
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
			else if (T_arr.tocken_arr[tocken_num] == NUM)//상태 4이고 NUM이면
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
			else if (stack[stack_num + 1] == 'E')//상태 4이고 E이면
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
			else if (stack[stack_num + 1] == 'T')//상태 4이고 T이면
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
			else if (stack[stack_num + 1] == 'F')//상태 4이고 F이면
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
				printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 5//////////////////////////////////////////////
		else if (stack[stack_num] == '5')
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MULTY || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$')//상태 5이고 +또는 * 또는 ) 또는 $이면
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
				printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 6//////////////////////////////////////////////
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
				printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 7//////////////////////////////////////////////
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
				printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 8//////////////////////////////////////////////
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
				printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 9//////////////////////////////////////////////
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
				printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 10/////////////////////////////////////////////
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
				printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 11/////////////////////////////////////////////
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
				printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 12/////////////////////////////////////////////
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
				printf("\nParsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
	}
}