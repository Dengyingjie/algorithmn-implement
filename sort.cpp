#include <iostream>
#include<random>
#include<memory>
using namespace std;

/**
* 插入排序之直接插入法：
* 将待排序表看作左右两部分，其中左边为有序区，右边为无序区，整个排序过程就是将右边无序区中的元素逐个插入到左边的有序区中。
* 分析：平均情况O(n2)，最坏情况O(n2),最好情况O(n)，空间复杂度O(1),稳定。
*/
template <typename T>
void InsertSort(T A[], int n)
{
	for (int i = 1; i < n; i++)
	{
		T temp = A[i];
		int j = i - 1;
		while (temp < A[j] && j >= 0)
		{
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = temp;
	}
}
/**
* 插入排序之希尔排序：
* 将待排序列划分为若干组，在每组内进行直接插入排序，使得整个序列基本有序，然后再对整个序列进行直接插入排序。
* 分组方法：对给定的一个步长d(d>0),将下标相差为d的元素分在一组。d的取值依次为:d1=n/2,d2=d1/2,……，dk=1
* 分析：时间复杂度：平均情况 O(n*Log2(n)) 最坏情况 O(n^2) 最好情况 O(n) 空间复杂度：O(1)	稳定性：不稳定
*/
template <typename T>
void ShellSort(T A[], int n)
{
	int d = n / 2; //步长初始为n/2
	while (d != 0)
	{
		for (int i = d; i < n; i++)
		{
			T x = A[i];
			int j = i - d;
			while (j >= 0 && x < A[j])
			{
				A[j + d] = A[j];
				j = j - d;
			}
			A[j + d] = x;
		}
		d = d / 2; //步长变为原来的1/2
	}
}
/**
* 冒泡排序：平均和最坏都是O(n2)，最好是O(n)
* 从一端开始，逐个比较相邻的两个元素，发现倒叙即交换。每一次都会有最小或最大值归位。
*/
template <typename T>
void BubbleSort(T *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				T temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}
/**
* 快速排序：平均和最好情况复杂度都是O(nlogn),最坏n2（退化成冒泡排序）
* 1．先从数列中取出一个数作为基准数。
* 2．分区过程，将比这个数大的数全放到右边，小于或等于它的数全放到左边。
* (并不是以这个数为分界线，因为两边满足的数不一定相同。)
* 3．再对左右区间重复第二步，直到各区间只有一个数。
*/
//定轴法
template <typename T>
void QuickSort1(int begin, int end, T a[])
{
	int b = begin;
	int e = end;
	T temp = a[(begin + end) / 2];
	while (begin < end)
	{
		while (a[begin] < temp && begin <= e)
			begin++;
		while (a[end] > temp && b<= end)
			end--;
		if (begin <= end)
			std::swap(a[begin++], a[end--]);
	}
	if (begin < e)
		QuickSort1(begin, e, a);
	if (end > b)
		QuickSort1(b, end, a);
}
//挖坑法
template <typename T>
void QuickSort2(int begin, int end, T a[])
{
	if (begin < end)
	{
		int b = begin;
		int e = end;
		int pivot = a[b];
		while (b < e)
		{
			while (b < e && a[e] >= pivot)
				e--;
			if (b < e)
				a[b++] = a[e];
			while (b < e && a[b] <= pivot)
				b++;
			if (b < e)
				a[e--] = a[b];
		}
		a[b] = pivot;
		QuickSort2(begin, b - 1, a);
		QuickSort2(b + 1, end, a);
	}
}
//随机数优化版本
template<typename T>
void RandomQuickSort(int begin, int end, T a[])
{
	int b = begin;int e = end;
	uniform_int_distribution<int> u(b, e);
	default_random_engine r;
	T pivot = a[u(r)];
	while (b<e)
	{
		while (a[b]<=pivot&&b<end)b++;
		while (a[e]>pivot&&e>begin)e--;
		if (b <= e)swap(a[b++], a[e--]);//此处没有=号会产生栈溢出，因为当b=e且不满足前面两个while时，b和e不自增，永远循环下去。
	}
	if (begin < e)
	{
		RandomQuickSort(begin, e,a);		
	}
	if(end>b)RandomQuickSort(b , end,a);
}
//快排结合插入排序优化
//针对相同元素的优化（划分成三部分，相同的在中间）

/**
* 直接选择排序：
* 在待排序的序列中找出最小或最大元素放在序列的最前或最后。
*/
template<typename T>
void SelectSort(T a[], int n)
{
	for (int i = 0; i<n; i++)
	{
		int min = i;
		for (int j = i + 1; j<n; j++)
		{
			if (a[min]>a[j])swap(a[min], a[j]);
		}
	}
}
/**
* 树形选择排序：
* 是一种按照锦标赛的思想进行选择排序的方法。
* 首先对n个记录进行两两比较，然后优胜者之间再进行两两比较，如此重复，直至选出最小关键字的记录为止。
* 这个过程可以用一棵有n个叶子结点的完全二叉树表示。根节点中的关键字即为叶子结点中的最小关键字。
* 在输出最小关键字之后，欲选出次小关键字，仅需将叶子结点中的最小关键字改为“最大值”，如∞，然后从该叶子结点开始，
* 和其兄弟的关键字进行比较，修改从叶子结点到根的路径上各结点的关键字，最后根结点的关键字即为次小关键字。
*/
//平均时间复杂度都是O(nlogn),最坏O(nlogn),最好O(nlogn)，空间复杂度O(1)
template<typename T>
void TreeSelectionSort(T data[], int n)
{
	T MinValue = -100000000;  //用该数表示负无穷
	int baseSize;             //刚好能存储n个数的最小的2的幂，等于满二叉树最下一层的叶子树
	int treeSize;             //整个二叉树的节点数
	int i;
	T max;
	int maxIndex;

	baseSize = 1;
	while (baseSize < n)
	{
		baseSize *= 2;
	}
	//用最下一层的叶子树计算总节点数
	treeSize = baseSize * 2 - 1;

	//创建数组存放二叉树，数据从下标1开始存放
	T* tree = new T[treeSize + 1]();

	//将数据放入最下一层中
	for (i = 0; i < n; i++)
	{
		tree[treeSize - i] = data[i];
	}
	//将二叉树的其他节点初始化为负无穷，如果每轮是求一个最小值则应初始化为正无穷
	for (; i < baseSize; i++)
	{
		tree[treeSize - i] = MinValue;
	}
	// 构造一棵树，根节点是最大值
	for (i = treeSize; i > 1; i -= 2)
	{
		tree[i / 2] = (tree[i] > tree[i - 1] ? tree[i] : tree[i - 1]);
	}
	n -= 1;    //未排序的数量-1
	while (n >= 0)
	{
		max = tree[1];             //取出最大值
		data[n--] = max;          //将当前找到的最大值放到数组的最后面
								  //在二叉树的最下面一层找到当前最大值的位置
		maxIndex = treeSize;
		while (tree[maxIndex] != max)
		{
			maxIndex--;
		}
		tree[maxIndex] = MinValue;  //将树中底层的现最大值替换为负无穷

									//从被替换的位置向上计算，修改从叶子结点到根的路径上各结点的值
		while (maxIndex > 1)
		{
			if (maxIndex % 2 == 0)
			{
				tree[maxIndex / 2] = (tree[maxIndex] > tree[maxIndex + 1] ? tree[maxIndex] : tree[maxIndex + 1]);
			}
			else
			{
				tree[maxIndex / 2] = (tree[maxIndex] > tree[maxIndex - 1] ? tree[maxIndex] : tree[maxIndex - 1]);
			}
			maxIndex /= 2;
		}
	}
	delete[] tree;
}
/**
* 堆排序：如何由无序序列建成一个堆。如何在输出对顶元素后，调整剩余元素成为一个新的堆。
* 可以使用函数指针来判断大顶堆还是小顶堆，进行切换升序还是降序。此处略。
* 时间复杂度都是O(nlogn)，空间O(1)
*/
template<typename T>
void sift(T a[], int i, int n)//a[i]是有孩子的节点，默认左右孩子树都满足堆。
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l<n&&a[l]>a[largest])largest = l;
	if (r<n&&a[r]>a[largest])largest = r;
	if (largest != i)
	{
		swap(a[i], a[largest]);
		sift(a, largest, n);
	}
}
template<typename T>
void maxHeapBuild(T a[], int n)//自底向上建堆
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		sift(a, i, n);
	}
}
template<typename T>
void maxHeapSort(T a[], int n)
{
	maxHeapBuild(a, n);
	for (int i = n - 1; i>0; i--)
	{
		swap(a[i], a[0]);
		sift(a, 0, i);
	}
}
/**
* 归并排序：
* 将两个或两个以上的有序表合并成一个新的有序表。
* 时间复杂度都是O(nlogn)，空间复杂度是O(n)。
*/
template<typename T>
void Merge(T a[], int p, int q, int r)
{
	if (r>p)
	{
		int i = p, j = q + 1;
		int b[r - p + 1];
		int k = 0;
		while (i <= q&&j <= r)
		{
			if (a[i]<a[j])b[k++] = a[i++];
			else b[k++] = a[j++];
		}
		while (i <= q)b[k++] = a[i++];
		while (j <= r)b[k++] = a[j++];
		int m = 0;
		for (int h = p; h <= r; h++)
		{
			a[h] = b[m++];
		}
	}

}
template<typename T>
void MergeSort(T a[], int p, int r)
{
	if (p<r)
	{
		int q = (p + r) / 2;
		MergeSort(a, p, q);
		MergeSort(a, q + 1, r);
		Merge(a, p, q, r);
	}
}
/**
*计数排序：
*/
void CountingSort(int * a, int n)
{
	unique_ptr<int[]> b(new int[n]);
	int k = 0;
	for (int i = 0; i < n; i++)k = a[i] <= k ? k : a[i];
	unique_ptr<int[]> c(new int[k+1]);
	for (int i = 0; i < k+1; i++)c[i] = 0;
	for (int j = 0; j < n; j++)c[a[j]]++;//相应的下标自增。
	for (int i = 1; i < k + 1; i++)c[i] += c[i - 1];//每个数获得小于等于它的数目。	
	//for (int i = 0; i < n; i++)//这种写法导致不稳定，相同的元素排序前后位置相反。
	//{
	//	c[a[i]]--;//先减的话，才能保证从b的下标从0开始。
	//	b[c[a[i]]] = a[i];
	//	c[a[i]]--;//
	//}
	for (int i = n - 1; i >= 0; i--)
	{
		c[a[i]]--;
		b[c[a[i]]] = a[i];		
	}
	for (int i = 0; i < n; i++)a[i] = b[i];
}
/**
* 基数排序:基于计数排序
*/
void CountingSortbyRadix(int a[], int n,int divide)
{
	unique_ptr<int[]> output(new int[n]);
	int b[10]{0};//存储出现次数
	for (int i = 0; i < n; i++)b[a[i]/divide % 10]++;
	for (int i = 1; i < 10; i++)b[i] += b[i - 1];
	for (int i = n - 1; i >= 0;i--)
	{
		b[a[i]/divide % 10]--;
		output[b[a[i]/divide%10]] = a[i];
	}
	for (int i = 0; i < n; i++)a[i] = output[i];
}
void RadixSort(int a[], int n)
{
	int max=-11111111111; 
	for (int i = 0; i < n; i++)max = max>a[i] ? max : a[i];
	for (int i = 1; max / i>0; i *= 10)
	{
		CountingSortbyRadix(a, n,i);
	}
}
/**
*桶排序：桶内可以用数组排序，桶间可以用链表。
*/
int main()
{
	int a[]{ 3, 6, 1, 3, 4, 9, 2 };
	//CountingSort(a,7);
	RandomQuickSort(0, 6, a);
	//RadixSort(a, 7);
	system("pause");
	for (int e : a)
		cout << e << ",";

	system("pause");
	return 0;
}