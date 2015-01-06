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
vector<int> StringMatching::Simple(char *TEXT, char *MODEL)//朴素算法实现字符串匹配 
{
	int m;                                //定义模式串长度 
	int i, j = 0;
	int l;                                //定义匹配串长度 
	l = strlen(TEXT);
	m = strlen(MODEL);
	vector<int> answer;                   //建立容器 
	answer.clear();
	for (i = 0; i < l; i++)                      //循环匹配模式串与匹配串的首字符 
	{
		if (TEXT[i] == MODEL[j])
		{
			for (j = 0; j < m; i++, j++)          //若相同，则循环匹配下一字符  
			{
				if (TEXT[i] != MODEL[j] && j < m)//若未全部匹配，返回第二个字符再次循环 
				{
					i -= j;
					j = 0;
					break;
				}
				if (j == m - 1)                //若全部匹配，将当前位置压入容器，返回第二个字符再次循环 
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
int StringMatching::hash_s(char *a, int len)	//哈希函数，用来转化字符串为哈希值
{
	int i = 0; int result = 0;
	for (i = 0; i<len; i++)
		result = result*seed + (int)a[i];
	return result;
}
int StringMatching::simcom(char* par, char* sub, int sub_len)	//简单朴素字符串匹配，用于比较哈希值相等的子串和模式串
{
	int i = 0;
	for (i = 0; i<sub_len; i++)
		if (par[i] != sub[i]) break;	//字符逐一比较
	if (i != sub_len) return 0;
	else return 1;
}
vector<int> StringMatching::rabink(char *par, char *sub)		//Rabin-Karp函数
{
	int i = 0;
	int p_len = strlen(par); int sub_len = strlen(sub);	//计算字符串长度
	int sub_r = hash_s(sub, sub_len);			//计算模式串哈希值
	int par_r;
	vector<int> in;  in.clear();
	for (i = 0; i<p_len; i++)
	{
		par_r = hash_s(par + i, sub_len);		//循环计算子串哈希值
		if (par_r != sub_r) continue;		//判断哈希值是否相等
		else if (simcom(par + i, sub, sub_len) != 1) continue; //哈希值相等，判断朴素比较是否相等
		else { in.push_back(i); }		//将子串首字母下标添加入结果向量
	}
	return in;
}
void StringMatching::PrefixCompute(char *p, int *prefix)		//kmp算法前缀计算函数
{
	int plen = strlen(p);		//计算字符串长度
	int i = 0;
	prefix[i] = -1;		//初始化前缀列表首位
	int j = -1;
	while (i<plen - 1)		//循环处理整个模式串
	{
		if (j == -1 || p[i] == p[j])	//成功匹配
		{
			i++;	//继续计算下一字符
			j++;	//继续计算下一字符
			if (p[i] != p[j])	//下一字符未匹配
				prefix[i] = j;	//前缀设为j
			else
				prefix[i] = prefix[j];	//否则前缀设为j的前缀值
		}
		else
			j = prefix[j];	//若当前字符未匹配，从prefix[j]开始计算
	}
}
vector<int> StringMatching::kmp(char *s, char *p, clock_t &kmp)	//kmp算法实现字符串匹配
{
	vector<int> answer;		//记录找到的起始角标
	answer.clear();
	//int* prefix=new int[strlen(p)];
	PrefixCompute(p, prefix);	//计算前缀
	int i = 0, j = 0;
	int slen = (int)strlen(s);	//求原串长度
	int plen = (int)strlen(p);	//求模式串长度
	kmp = clock();
	while (i<slen&&j<plen)
	{
		if (j == -1 || *(s+i) == *(p+j))    //如果当前字符匹配，则判断下一字符
		{
			i++;
			j++;
			if (j == plen)		//模式串被原串的一个子串完全匹配
			{
				answer.push_back(i - plen);	//记录到结果vector中
				j = 0;	//下一次从模式串第一个字符开始匹配
			}
		}
		else
			j = *(prefix+j);	//未匹配则将模式串角标j，平移到prefix[j]进行匹配判断
		
	}
	return answer;
}
