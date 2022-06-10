// 浠ｇ爜涓€瀹氳鏄? UTF-8(BOM)  

//qt鐗堟湰楂樹簬绛変簬qt5,VS鐗堟湰楂樹簬鎴栫瓑浜嶸S2010

#if _MSC_VER >= 1600  

#pragma execution_character_set("utf-8")  

#endif  

#include "search_words.h"
#define MAX_LINE 10240
#define IMGNUM 2000 //鍥剧墖鎵€鍦ㄦ枃浠跺す涓浘鐗囩殑鏈€澶ф暟閲?
char img_files[IMGNUM][1000];

int getFiles(char *path)
{
	int num_of_img = 0;
	long hFile = 0;
	//_finddata_t fileinfo;
	__finddata64_t   fileinfo;

	char p[700] = { 0 };
	strcpy(p, path);
	strcat(p, "\\*.txt");
	char * aaaa;

	//long  Handle = _findfirst(p, &fileinfo);
	__int64   Handle = _findfirst64(p, &fileinfo);
	if (Handle != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					continue;
			}
			else
			{
				//strcpy(img_files[num_of_img], path);
				//strcpy(img_files[num_of_img], "\\");
				//strcat(img_files[num_of_img], "\\");
				//strcat(img_files[num_of_img++], fileinfo.name);
				strcpy(img_files[num_of_img++], fileinfo.name);
			}

			aaaa= fileinfo.name ;
		//} while (_findnext(hFile, &fileinfo) == 0);
		} while (_findnext64(Handle, &fileinfo) == 0);
		_findclose(Handle);
	}
	return num_of_img;
}
char *search_words(char *aim_code)
{
	//	char aim_code[20];
	//scanf("%s", aim_code);

	char root[180];
	memset(root, 0x00, sizeof(root));


	char xxx[1];
	memset(xxx, 0x00, sizeof(xxx));

	strcpy(root, "DICT\\");
	//strcpy(root, "D:\\onedrive\\OneDrive - yyt6801\\QT_Projects\\QT_in_VS2015_Projects\\QtGuiApplication2\\x64\\Debug\\DICT\\");

	if (aim_code[0] >= 97 && aim_code[0] <= 122)
		xxx[0] = aim_code[0] - 32;

	root[strlen(root)] = xxx[0];
	strcat(root, "\\");

	//
	int num = getFiles(root);
	int i, j;
	if (1 == num)
	{
		strcat(root, img_files[0]);
	}
	else {
		for (i = 0; i < num; ++i)
		{
			//printf("%s\n", img_files[i]);
			for (j = 2; j < 20; j++)
			{
				if (img_files[i][j] == aim_code[1])
				{
					strcat(root, img_files[i]);
					printf("%s\n", root);
					break;
					break;
				}
			}
		}
	}

	/*root[41] = aim_code[0];
	strcat(root, "-");
	root[43] = aim_code[1];
	strcat(root, ".txt");*/
	//printf("%s\n", root);
	//system("pause");

	//return root;


	char buf[MAX_LINE]; /*缂撳啿鍖?*/
	memset(buf, 0x00, MAX_LINE);
	FILE *fp;           /*鏂囦欢鎸囬拡 */
	int len;            /*琛屽瓧绗︿釜鏁?*/
	int rownum = 0;
	if ((fp = fopen(root, "r")) == NULL)
	{
		printf("cannot read %s", root);
		return "cannot translate this words!";
	}
	while (fgets(buf, MAX_LINE, fp) != NULL)
	{
		len = strlen(buf);
		buf[len - 1] = '\0'; 

		rownum++;
		if (strcmp(buf, aim_code) == 0)
		{
			fgets(buf, MAX_LINE, fp);
			printf("%s %d \n", buf, rownum);
			//system("pause");

			return buf;
		}
	}
	return "no this words!";
	printf("cannot get password!\n");
}