#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
using namespace std;

class StringMatching
{
private:
	const static int maxnum = 1e8;
	const int seed = 7;
	const int bigprime = 0xffffff;
	int prefix[maxnum];
public :
	vector<int> Simple(char *TEXT, char *MODEL);
	int hash_s(char *a, int len);
	int simcom(char* par, char* sub, int sub_len);
	vector<int> rabink(char *par, char *sub);
	void PrefixCompute(char *p, int *prefix);
	vector<int> kmp(char *s, char *p, clock_t &kmp);
};
vector<int> StringMatching::Simple(char *TEXT, char *MODEL)//�����㷨ʵ���ַ���ƥ�� 
{
	int m;                                //����ģʽ������ 
	int i, j = 0;
	int l;                                //����ƥ�䴮���� 
	l = strlen(TEXT);
	m = strlen(MODEL);
	vector<int> answer;                   //�������� 
	answer.clear();
	for (i = 0; i < l; i++)                      //ѭ��ƥ��ģʽ����ƥ�䴮�����ַ� 
	{
		if (TEXT[i] == MODEL[j])
		{
			for (j = 0; j < m; i++, j++)          //����ͬ����ѭ��ƥ����һ�ַ�  
			{
				if (TEXT[i] != MODEL[j] && j < m)//��δȫ��ƥ�䣬���صڶ����ַ��ٴ�ѭ�� 
				{
					i -= j;
					j = 0;
					break;
				}
				if (j == m - 1)                //��ȫ��ƥ�䣬����ǰλ��ѹ�����������صڶ����ַ��ٴ�ѭ�� 
				{
					answer.push_back(i - m + 1);
					i -= j;
					j = 0;
					break;
				}
			}
		}
	}
	return answer;
}
int StringMatching::hash_s(char *a, int len)	//��ϣ����������ת���ַ���Ϊ��ϣֵ
{
	int i = 0; int result = 0;
	for (i = 0; i<len; i++)
		result = result*seed + (int)a[i];
	return result;
}
int StringMatching::simcom(char* par, char* sub, int sub_len)	//�������ַ���ƥ�䣬���ڱȽϹ�ϣֵ��ȵ��Ӵ���ģʽ��
{
	int i = 0;
	for (i = 0; i<sub_len; i++)
		if (par[i] != sub[i]) break;	//�ַ���һ�Ƚ�
	if (i != sub_len) return 0;
	else return 1;
}
vector<int> StringMatching::rabink(char *par, char *sub)		//Rabin-Karp����
{
	int i = 0;
	int p_len = strlen(par); int sub_len = strlen(sub);	//�����ַ�������
	int sub_r = hash_s(sub, sub_len);			//����ģʽ����ϣֵ
	int par_r;
	vector<int> in;  in.clear();
	for (i = 0; i<p_len; i++)
	{
		par_r = hash_s(par + i, sub_len);		//ѭ�������Ӵ���ϣֵ
		if (par_r != sub_r) continue;		//�жϹ�ϣֵ�Ƿ����
		else if (simcom(par + i, sub, sub_len) != 1) continue; //��ϣֵ��ȣ��ж����رȽ��Ƿ����
		else { in.push_back(i); }		//���Ӵ�����ĸ�±������������
	}
	return in;
}
void StringMatching::PrefixCompute(char *p, int *prefix)		//kmp�㷨ǰ׺���㺯��
{
	int plen = strlen(p);		//�����ַ�������
	int i = 0;
	prefix[i] = -1;		//��ʼ��ǰ׺�б���λ
	int j = -1;
	while (i<plen - 1)		//ѭ����������ģʽ��
	{
		if (j == -1 || p[i] == p[j])	//�ɹ�ƥ��
		{
			i++;	//����������һ�ַ�
			j++;	//����������һ�ַ�
			if (p[i] != p[j])	//��һ�ַ�δƥ��
				prefix[i] = j;	//ǰ׺��Ϊj
			else
				prefix[i] = prefix[j];	//����ǰ׺��Ϊj��ǰ׺ֵ
		}
		else
			j = prefix[j];	//����ǰ�ַ�δƥ�䣬��prefix[j]��ʼ����
	}
}
vector<int> StringMatching::kmp(char *s, char *p, clock_t &kmp)	//kmp�㷨ʵ���ַ���ƥ��
{
	vector<int> answer;		//��¼�ҵ�����ʼ�Ǳ�
	answer.clear();
	//int* prefix=new int[strlen(p)];
	PrefixCompute(p, prefix);	//����ǰ׺
	int i = 0, j = 0;
	int slen = (int)strlen(s);	//��ԭ������
	int plen = (int)strlen(p);	//��ģʽ������
	kmp = clock();
	while (i<slen&&j<plen)
	{
		if (j == -1 || *(s+i) == *(p+j))    //�����ǰ�ַ�ƥ�䣬���ж���һ�ַ�
		{
			i++;
			j++;
			if (j == plen)		//ģʽ����ԭ����һ���Ӵ���ȫƥ��
			{
				answer.push_back(i - plen);	//��¼�����vector��
				j = 0;	//��һ�δ�ģʽ����һ���ַ���ʼƥ��
			}
		}
		else
			j = *(prefix+j);	//δƥ����ģʽ���Ǳ�j��ƽ�Ƶ�prefix[j]����ƥ���ж�
		
	}
	return answer;
}
