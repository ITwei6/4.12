#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//�����������--����һ����׼ֵkey
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
int Midi(int* a, int left, int right)
{
	int mid = (left + right) / 2;
	if (a[left] > a[mid])
	{
		if (a[mid] > a[right])
		{
			return mid;
		}
		else//a[left]>a[mid]��a[right]>a[mid]
		{
			if (a[left] > a[right])
			{
				return right;
			}
			else
			{
				return left;
			}
		}
	}
	else//a[left]<a[mid]
	{
		if (a[mid] < a[right])
		{
			return mid;
		}
		else//a[left]<a[mid]��a[right]<a[mid]
		{
			if (a[left] > a[right])
			{
				return left;
			}
			else
			{
				return right;
			}
		}
	}
}
//1.��������
void Quicksort1(int* a, int left, int right)//��Ҫ���䷶Χ
{
	//�ݹ��������
	if (left >= right)
		return;

	int keyi = left;
	int begin = left;
	int end = right;
	////���ѡkey
	//int randi = rand() % (right - left) + begin;
	//Swap(&a[keyi], &a[randi]);

	//����ȡ�У�����ȡ�����м����������ȡ���������м����--begin mid end
	int midi = Midi(a, begin, end);
	Swap(&a[keyi], &a[midi]);
	while (left < right)
	{
		//����С
		while (left < right && a[right] >= a[keyi])
			right--;
		//���Ҵ�
		while (left < right && a[left] <= a[keyi])
			left++;
		//�����ұߵ�С����ߵĴ�
		Swap(&a[left], &a[right]);
	}
	//���keyֵ��left��right����λ�ý���
	Swap(&a[keyi], &a[left]);
	keyi = left;
	//begin   keyi-1 key keyi+1   end
	Quicksort1(a, begin, keyi - 1);
	Quicksort1(a, keyi + 1, end);
}
//2.�ڿӷ�
void Quicksort2(int* a, int left, int right)
{
	if (left >= right)
		return;
	//��key��ֵ����
	int key = a[left];
	int begin = left;
	int end = right;
	int hole = begin;
	//����ȡ�У�����ȡ�����м����������ȡ���������м����--begin mid end
	int midi = Midi(a, begin, end);
	Swap(&key, &a[midi]);
	while (left < right)
	{
		//�ұ���С
		while (left < right && a[right] >= key)
			--right;
		//�ҵ�֮����˦������Լ��γ��µĿ�
		a[hole] = a[right];
		hole = right;
		while (left < right && a[left] <= key)
			++left;
		//�ҵ�֮����˦������Լ��γ��µĿ�
		a[hole] = a[left];
		hole = left;
	}
	//���left��right��������key���뵽����
	a[hole] = key;
	Quicksort2(a, begin, hole - 1);
	Quicksort2(a, hole + 1, end);

}
//3.ǰ��ָ�뷽��
void Quicksort3(int* a, int left, int right)
{
	if (left >= right)
		return;
	//����ȡ�У�����ȡ�����м����������ȡ���������м����--begin mid end
	/*int midi = Midi(a, left, right);
	Swap(&a[left], &a[midi]);*/
	int keyi = left;
	int cur = left + 1;
	int prev = left;
	int begin = left;
	int end = right;
	//cur������С����cur�ҵ�Сʱ��prev++��prev��ֵ��cur��ֵ������cur����������
	while (cur <= right)
	{
		if (a[cur] <= a[keyi] && a[++prev] != a[cur])
		{
			Swap(&a[cur], &a[prev]);
		}
		++cur;
	}
	Swap(&a[prev], &a[keyi]);
	keyi = prev;
	Quicksort3(a, begin, keyi - 1);
	Quicksort3(a, keyi + 1, end);
}
//ϣ������--Ԥ����--����
void Shellsort(int* a, int n)
{
	int gap = n;
	while (gap)
	{
		gap /= 2;
		for (int j = 0; j < gap; j++)
		{
			//ϣ��������ص���Ƿֳ�gap���� ����gapΪ3�Ļ����ͷֳ�3����--�����ƺ�
			for (int i = j; i < n - gap; i += gap)
			{
				//��дһ��--Ҳ���Ǻ�ɫ
				int end = i;
				int tmp = a[i + gap];
				while (end >= 0)
				{
					if (a[end] > tmp)
					{
						//��ǰ�ƶ�gapλ�ã�endÿ���ƶ�gap
						a[end + gap] = a[end];
						end -= gap;
					}
					else
					{
						break;
					}
				}
				//tmp�ܹ�Ҫ���뵽a[end+gap]λ����ȥ��
				a[end + gap] = tmp;
			}
		}
	}

}
void QuickTest1()
{
	srand(time(0));
	const int N = 1000000;
	int* a2 = (int*)malloc(sizeof(int) * N);
	for (int i = 0; i < N; ++i)
	{
		a2[i] = rand();
	}
	int begin1 = clock();
	Quicksort1(a2, 0, N - 1);
	int end1 = clock();
	printf("����-Quicksort:%d\n", end1 - begin1);
	free(a2);
}
void QuickTest2()
{
	srand(time(0));
	const int N = 1000000;
	int* a2 = (int*)malloc(sizeof(int) * N);
	for (int i = 0; i < N; ++i)
	{
		a2[i] = rand();
	}
	int begin1 = clock();
	Quicksort2(a2, 0, N - 1);
	int end1 = clock();
	printf("�ڿӷ�-Quicksort:%d\n", end1 - begin1);
	free(a2);
}
void QuickTest3()
{
	srand(time(0));
	const int N = 1000000;
	int* a2 = (int*)malloc(sizeof(int) * N);
	for (int i = 0; i < N; ++i)
	{
		a2[i] = rand();
	}
	int begin1 = clock();
	Quicksort3(a2, 0, N - 1);
	int end1 = clock();
	printf("ǰ��ָ��-Quicksort:%d\n", end1 - begin1);
	free(a2);
}
void ShellsortTest()
{
	srand(time(0));
	const int N = 1000000;
	int* a2 = (int*)malloc(sizeof(int) * N);
	for (int i = 0; i < N; ++i)
	{
		a2[i] = rand();
	}
	int begin1 = clock();
	Shellsort(a2, N);
	int end1 = clock();
	printf("ϣ��Shellsort:%d\n", end1 - begin1);
	free(a2);
}
int main()
{
	QuickTest1();
	QuickTest2();
	QuickTest3();
	ShellsortTest();
	return 0;

}