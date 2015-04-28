// ������Ӧ����
#include "stdafx.h"
#include "resource.h"
#include <stdlib.h>
#include <stdio.h> 
#include <cmath>
#include <shellapi.h> 

TCHAR str[256];     // �ݴ�
TCHAR str1[256];    // ��һ��������
TCHAR str2[256];    // �ڶ���������
double result=0;    // ����
int clear=0;        // ��յ�ǰ��ʾ����
int operation=0;    // ѡ���������㣨+��-��*��/��
int flag=0;         // ���������=���ű�־λ
int error=0;        // �����־���������Ϊ0��
int nobackspace=0;  // ��ֹ�˸���ʾ�ļ����������˸�

void InputOperand(HWND, int &, int &, int &, TCHAR *);    // ����������Ӻ���


void KeyPress(HWND hwnd, int id)
{
  switch(id)
  {
  /*******************************Number**********************************/
        case IDC_0:
		{
		    InputOperand(hwnd,error,clear,nobackspace,"0");
		}
		break;
			
		case IDC_1:
		{   
			InputOperand(hwnd,error,clear,nobackspace,"1");
		}
		break;

		case IDC_2:
		{
			InputOperand(hwnd,error,clear,nobackspace,"2");
      	}
		break;

		case IDC_3:
		{
			InputOperand(hwnd,error,clear,nobackspace,"3");
		}
		break;

		case IDC_4:
		{
			InputOperand(hwnd,error,clear,nobackspace,"4");
		}
		break;

		case IDC_5:
		{
			InputOperand(hwnd,error,clear,nobackspace,"5");
		}
		break;

		case IDC_6:
		{
			InputOperand(hwnd,error,clear,nobackspace,"6");
		}
		break;

		case IDC_7:
		{
			InputOperand(hwnd,error,clear,nobackspace,"7");
		}
		break;

		case IDC_8:
		{
			InputOperand(hwnd,error,clear,nobackspace,"8");
		}
		break;

		case IDC_9:
		{
			InputOperand(hwnd,error,clear,nobackspace,"9");
		}
		break;

		case IDC_POINT:
		{   
			if(1==error)
			{
		        return;
			}
	        if(1==clear)
			{
		        SetDlgItemText(hwnd,IDC_SHOW,TEXT("0"));
		        clear=0;
			}

            GetDlgItemText(hwnd,IDC_SHOW,str,sizeof(str));
            for (int i=0;str[i]!='\0';i++)  // һ��������ֻ������һ��С����
			{
				if('.'==str[i])
					return;
			}
		    strcpy(str,strcat(str,"."));
            SetDlgItemText(hwnd,IDC_SHOW,str);
		}
		break;
        
  /*******************************Operation**********************************/
		case IDC_ADD:
		{ 	
			if(1==error)
			{
		        return;
			}	
		
            GetDlgItemText(hwnd,IDC_SHOW,str1,sizeof(str1));
			operation=1;
			clear=1;
			flag=0;
		}
		break;

		case IDC_MINUS:
		{ 	
			if(1==error)
			{
		        return;
			}	

            GetDlgItemText(hwnd,IDC_SHOW,str1,sizeof(str1));
			operation=2;
			clear=1;
			flag=0;
		}
		break;

		case IDC_MULTIPLY:
		{ 	
			if(1==error)
			{
		        return;
			}	

            GetDlgItemText(hwnd,IDC_SHOW,str1,sizeof(str1));
			operation=3;
			clear=1;
			flag=0;
		}
		break;

		case IDC_DIVIDE:
		{ 	
			if(1==error)
			{
		        return;
			}	

            GetDlgItemText(hwnd,IDC_SHOW,str1,sizeof(str1));
			operation=4;
			clear=1;
			flag=0;
		}
		break;

		case IDC_INVERSE:
		{ 	
			if(1==error)
			{
		        return;
			}	
			
            GetDlgItemText(hwnd,IDC_SHOW,str,sizeof(str));
		    if (strcmp(str,TEXT("0"))==0)       // ��������Ϊ��
			{
			    SetDlgItemText(hwnd,IDC_SHOW,TEXT("cannot divide by zero"));  
				error=1;
				return;
			}
            result=1/atof(str);
			sprintf(str,"%g",result);
			SetDlgItemText(hwnd,IDC_SHOW,str);     
	        clear=1;
			nobackspace=1;
		}
		break;

		case IDC_PERCENTAGE:
		{  
			if(1==error)
			{
		        return;
			}	

            GetDlgItemText(hwnd,IDC_SHOW,str,sizeof(str));
			result=atof(str)*100;
			sprintf(str,"%g%%",result);    // ����ٷֱȷ��ű�����"%%"
			SetDlgItemText(hwnd,IDC_SHOW,str);     
	        clear=1;
			nobackspace=1;
		}
		break;

		case IDC_SQRT:
		{ 			
           	if(1==error)
			{
		        return;
			}	

			GetDlgItemText(hwnd,IDC_SHOW,str,sizeof(str));
		    result=sqrt(atof(str));
			sprintf(str,"%g",result);
			SetDlgItemText(hwnd,IDC_SHOW,str);     
	        clear=1;
			nobackspace=1;
		}
		break;

		case IDC_OPPOSITE:
		{ 			
           	if(1==error)
			{
		        return;
			}	

			GetDlgItemText(hwnd,IDC_SHOW,str,sizeof(str));
		    result=0-atof(str);
			sprintf(str,"%g",result);
			SetDlgItemText(hwnd,IDC_SHOW,str);     
	        clear=1;
			nobackspace=1;
		}
		break;

		case IDC_BACKSPACE:
        { 			
           	if(1==error||1==nobackspace)
			{
		        return;
			}	

			GetDlgItemText(hwnd,IDC_SHOW,str,sizeof(str));
		    str[strlen(str)-1]='\0';
			SetDlgItemText(hwnd,IDC_SHOW,str);  
			if(strcmp(str,TEXT("0"))!=1)
			{
                 SetDlgItemText(hwnd,IDC_SHOW,TEXT("0"));
			}
		}
		break;

		case IDC_CLEAR:
		{ 
			 SetDlgItemText(hwnd,IDC_SHOW,TEXT("0"));
			 result=clear=operation=flag=error=nobackspace=0;
			 strcpy(str,"0");
			 strcpy(str1,"0");
			 strcpy(str2,"0");
		}
		break;

		case IDC_EXIT:
		{ 
			 int ret = MessageBox(hwnd, TEXT("Exit the calculator?"), TEXT("Exit"), MB_OKCANCEL|MB_ICONQUESTION);
				 if(IDOK==ret)
				 {
                     EndDialog(hwnd, 0);
				 }
				 else
				 {
					 return;
				 }
		}
		break;

		case IDC_ABOUT:  // ��������
		{ 
			ShellExecute(hwnd, "open", "http://www.rupeng.com/forum/forum.php", NULL, NULL, SW_SHOWNORMAL);
		}
		break;

  /*******************************Result**********************************/
		case IDC_EQUAL:
		{
			if(1==error)
			{
		        return;
			}
			if(0==flag)
			{
                GetDlgItemText(hwnd,IDC_SHOW,str2,sizeof(str2));
			}

			switch(operation)
			{
			      
			       case 0:
				   {
					   return;
				   }
				   break;
			
			       case 1:
				   {
					   result=atof(str1)+atof(str2);
				   }
				   break;

				   case 2:
				   {
					   result=atof(str1)-atof(str2);
				   }
				   break;

				   case 3:
				   {
					   result=atof(str1)*atof(str2);
				   }
				   break;

				   case 4:
				   {
					   if (strcmp(str2,TEXT("0"))==0)    // ��������Ϊ��
					   {
						   SetDlgItemText(hwnd,IDC_SHOW,TEXT("cannot divide by zero"));  
						   error=1;
						   return;
					   }
                       result=atof(str1)/atof(str2);
				   }
				   break;
			}
            sprintf(str1,"%g",result);
			SetDlgItemText(hwnd,IDC_SHOW,str1);  
			clear=1;
			flag=1;
			nobackspace=1;
		}
		break;
	}
}


void InputOperand(HWND hwnd, int &error,int &clear, int &nobackspace, TCHAR *ID)
{
	if(1==error)
	{
		return;
	}

	if(1==clear)
	{
		SetDlgItemText(hwnd,IDC_SHOW,TEXT("0"));
		clear=0;
	}
	
	nobackspace=0;
	GetDlgItemText(hwnd,IDC_SHOW,str,sizeof(str));
	if(strcmp(str,TEXT("0"))!=0)           // ����ǰ��ʾ���ڴ���ֵΪ0�� ������������ִ��档����Ϊ�㣬��������������ڵ�ǰֵ�ĺ�ߡ�
	{                                      // ������ǰΪ0������6������ʾ6����ǰΪ889������6������ʾ8896��
	    strcpy(str,strcat(str,ID));
        SetDlgItemText(hwnd,IDC_SHOW,str);
	}
	else
	{
	    strcpy(str,TEXT(ID));
        SetDlgItemText(hwnd,IDC_SHOW,str);
	}
}