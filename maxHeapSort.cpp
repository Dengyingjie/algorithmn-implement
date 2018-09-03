#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<limits>
using namespace std;

/*
堆排序和优先队列的实现
注：函数大多用引用，因此会破坏原来的数据。因为堆的查找效率为O(N)，效率低，因此尽量避免遍历以及数组移动。
*/
//#define INT_MIN //定义负无穷

//堆调整，调整的时间复杂度为O(logn)，即由树高决定
void maxHeapifyByRecur(vector<int>& a,int n, int i)
{
	int largest=i;
	int l = 2 * i+1;
	int r = l + 1;
	if (l < n && a[l] > a[i])
		largest = l;
	else
		largest = i;
	if (r < n && a[r] > a[largest])
		largest = r;
	if (largest != i)
	{
		swap(a[i], a[largest]);
		maxHeapifyByRecur(a, n,largest);//可以用循环去除递归。while(i<a.size()){...i=l;l=2*i;...}
	}
}
//建堆,线性时间O(n)
void maxHeapBuild(vector<int>& a)
{
	if (a.size() < 1)return;
	for (int i = a.size() / 2-1; i >= 0; i--)
	{
		maxHeapifyByRecur(a, a.size(),i);
	}
}
void maxHeapSort(vector<int>& a)
{
	maxHeapBuild(a);
	int size = a.size();
	for (int i = a.size() - 1; i >= 0; i--)
	{
		swap(a[0], a[i]);
		size--;
		maxHeapifyByRecur(a, size, 0);
	}
}
//优先队列抽取最大值
int maxHeapExtractMax(vector<int>& a)
{
	if (a.size() < 1) { cout << "heap is null"; return 0; }
	int max = a[0];
	a[0] = a[a.size() - 1];
	maxHeapifyByRecur(a, a.size() - 1, 0);
	return max;
}
//优先队列更新关键字的值
void maxHeapUpdateKey(vector<int> a, int index,int data)
{
	if (data < a[index])
	{
		a[index] = data;
		int j = index ;
		while (2 * j + 1 < a.size() && a[2 * j + 1] > a[j])
		{
			swap(a[j], a[2 * j + 1]);
			j = 2 * j + 1;
		}
	}
	else
	{
		a[index] = data;
		int j = index;
		while (j/2-1 >=0 && a[j/2-1] > a[j])
		{
			swap(a[j], a[j / 2 - 1]);
			j = j / 2 - 1;
		}
	}
}
//插入，先扩展容量，设新节点为负无穷，然后调整。
void maxHeapInsert(vector<int>& a, int key)
{
	a.resize(a.size() + 1, INT_MIN);
	maxHeapUpdateKey(a, a.size()-1, key);
}

int main()
{
	default_random_engine e;
	uniform_int_distribution<unsigned> u(0, 9);
	vector<int> a;
	for (int i = 0; i < 10; i++)
	{
		a.push_back(u(e));
		cout << a[i] << ',';
	}
	cout << endl;
	maxHeapSort(a);
	for (auto v : a)cout << v << ",";
	system("pause");
	return 0;
}