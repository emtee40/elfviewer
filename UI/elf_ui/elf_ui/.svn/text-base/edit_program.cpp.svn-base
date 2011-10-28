#include "stdafx.h"
#include "edit_program.h"
#include "resource.h"
#include <stdio.h>

int Init_Env(OPTION_ENV *o_env)
{
	FILE *env_file;
	char line_buf[MAX_PATH] = {0,};
	char temp_str[MAX_PATH] = "$Edit Program = notepad";
	char edit_cmd[MAX_PATH] = {0,};
	int fret;
#ifdef ELF_DEBUG
	char env_path[MAX_PATH] = "D:\\Projects\\Personal_Projects\\ELF\\UI\\elf_ui\\Debug\\elf_viewer.env";
#else
	char env_path[MAX_PATH] = "elf_viewer.env";
#endif	//ELF_DEBUG

	env_file = fopen(env_path, "r+t");
	if(env_file == NULL){
		env_file = fopen(env_path, "w+t");
		if(env_file != NULL){
			strcpy(o_env->edit_cmd, "notepad");				//copy edit_program var of env file to global var.
			fret = fwrite(temp_str, sizeof(char) * strlen(temp_str), 1, env_file);
			fclose(env_file);
			return TRUE;
		}
		DWORD error_flag = GetLastError();

		return FALSE;
	}

	fgets(line_buf, MAX_PATH, env_file);
	if(strstr(line_buf, "$Edit Program") != NULL){
		strcpy(o_env->edit_cmd, strchr(line_buf, '=') + 2);
	}
	fclose(env_file);
	return TRUE;
}

void Save_Env(HWND hDlg, OPTION_ENV *o_env)
{
	FILE *env_file;
	char path_str[MAX_PATH];
	char temp_str[MAX_PATH];
	int fret;
#ifdef ELF_DEBUG
	char env_path[MAX_PATH] = "D:\\Projects\\Personal_Projects\\ELF\\UI\\elf_ui\\Debug\\elf_viewer.env";
#else
	char env_path[MAX_PATH] = "elf_viewer.env";
#endif	//ELF_DEBUG

	env_file = fopen(env_path, "r+t");
	if(env_file != NULL){		
		HWND folder_path = GetDlgItem(hDlg, IDC_EDIT_PROGRAM_PATH);
		GetWindowText(folder_path, path_str, MAX_PATH);
		strcpy(o_env->edit_cmd, path_str);				//copy edit_program var of env file to global var.

		sprintf(temp_str,"$Edit Program = %s", path_str);
		fret = fwrite(temp_str, sizeof(char) * strlen(temp_str), 1, env_file);
		fclose(env_file);
	}
}

/*****************************************************************************/
//Description:
// This function represent the contained data of a section.
//Parameter:
// - hDlg: parent window.
// - data: the contained data of a section.
// - data_size: size of the data of a section
/*****************************************************************************/
void Binary_View(HWND hDlg, char *data, unsigned int data_size)
{
	char bbuff[10] = {0,};
	char bstr[100] = {0,};
	char cbuff[10] = {0,};
	char cstr[100] = {0,};
	char bdata = 0;
	unsigned int line_n;

	HWND bView = GetDlgItem(hDlg, IDC_BINARY_VIEW);

	for(unsigned int ndata = 0; ndata < data_size; ndata++){
		bdata = *(data + ndata);
		sprintf(bbuff,"%02x  ", (unsigned char)bdata);
		sprintf(cbuff,"%c ", bdata);
		_strupr(bbuff);
		
		if(ndata == 0){
			strcpy(bstr,bbuff);
			strcpy(cstr,cbuff);
		}
		else{
			strcat(bstr,bbuff);
			strcat(cstr,cbuff);
		}

		line_n = (ndata+1) % 16;

		if((line_n == 0) && (ndata != 0)){
			strcat(bstr, "\t");
			strcat(bstr, cstr);
			Disp_Data(bView, bstr);	
			memset(bstr, 0, sizeof(char) * 100);
			memset(cstr, 0, sizeof(char) * 100);
		}
		memset(bbuff, 0, sizeof(char) * 10);
		memset(cbuff, 0, sizeof(char) * 10);
	}	
}

void Disp_Data(HWND hDlg, char *str)
{
	char temp_str[MAX_PATH];

	strcpy(temp_str, str);
	strcat(temp_str, "\r\n");
	SendMessage(hDlg, EM_REPLACESEL, (WPARAM)TRUE, (LPARAM)temp_str);
	UpdateWindow(hDlg);
}