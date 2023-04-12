#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//霍尔最初方法--定义一个基准值key
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
		else//a[left]>a[mid]且a[right]>a[mid]
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
		else//a[left]<a[mid]且a[right]<a[mid]
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
//1.霍尔方法
void Quicksort1(int* a, int left, int right)//需要区间范围
{
	//递归结束条件
	if (left >= right)
		return;

	int keyi = left;
	int begin = left;
	int end = right;
	////随机选key
	//int randi = rand() % (right - left) + begin;
	//Swap(&a[keyi], &a[randi]);

	//三数取中，不是取数组中间的数，而是取三个数中中间的数--begin mid end
	int midi = Midi(a, begin, end);
	Swap(&a[keyi], &a[midi]);
	while (left < right)
	{
		//右找小
		while (left < right && a[right] >= a[keyi])
			right--;
		//左找大
		while (left < right && a[left] <= a[keyi])
			left++;
		//交换右边的小和左边的大
		Swap(&a[left], &a[right]);
	}
	//最后将key值与left和right相遇位置交换
	Swap(&a[keyi], &a[left]);
	keyi = left;
	//begin   keyi-1 key keyi+1   end
	Quicksort1(a, begin, keyi - 1);
	Quicksort1(a, keyi + 1, end);
}
//2.挖坑法
void Quicksort2(int* a, int left, int right)
{
	if (left >= right)
		return;
	//将key的值保留
	int key = a[left];
	int begin = left;
	int end = right;
	int hole = begin;
	//三数取中，不是取数组中间的数，而是取三个数中中间的数--begin mid end
	int midi = Midi(a, begin, end);
	Swap(&key, &a[midi]);
	while (left < right)
	{
		//右边找小
		while (left < right && a[right] >= key)
			--right;
		//找到之后将它甩到坑里，自己形成新的坑
		a[hole] = a[right];
		hole = right;
		while (left < right && a[left] <= key)
			++left;
		//找到之后将它甩到坑里，自己形成新的坑
		a[hole] = a[left];
		hole = left;
	}
	//最后left和right相遇，将key插入到坑里
	a[hole] = key;
	Quicksort2(a, begin, hole - 1);
	Quicksort2(a, hole + 1, end);

}
//3.前后指针方法
void Quicksort3(int* a, int left, int right)
{
	if (left >= right)
		return;
	//三数取中，不是取数组中间的数，而是取三个数中中间的数--begin mid end
	/*int midi = Midi(a, left, right);
	Swap(&a[left], &a[midi]);*/
	int keyi = left;
	int cur = left + 1;
	int prev = left;
	int begin = left;
	int end = right;
	//cur用来找小，当cur找到小时，prev++，prev的值与cur的值交换，cur继续往后走
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
//希尔排序--预排序--排序
void Shellsort(int* a, int n)
{
	int gap = n;
	while (gap)
	{
		gap /= 2;
		for (int j = 0; j < gap; j++)
		{
			//希尔排序的特点就是分成gap区间 假设gap为3的话，就分成3部分--假设红黄黑
			for (int i = j; i < n - gap; i += gap)
			{
				//先写一趟--也就是红色
				int end = i;
				int tmp = a[i + gap];
				while (end >= 0)
				{
					if (a[end] > tmp)
					{
						//往前移动gap位置，end每次移动gap
						a[end + gap] = a[end];
						end -= gap;
					}
					else
					{
						break;
					}
				}
				//tmp总归要插入到a[end+gap]位置上去的
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
	printf("霍尔-Quicksort:%d\n", end1 - begin1);
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
	printf("挖坑法-Quicksort:%d\n", end1 - begin1);
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
	printf("前后指针-Quicksort:%d\n", end1 - begin1);
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
	printf("希尔Shellsort:%d\n", end1 - begin1);
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