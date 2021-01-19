#include <vector>

template<typename T>
struct SegmentTree
{
    int N;
    std::vector<T> node;

    /*
    単位元と関数を必ず決めてください！
    ex) T = 0, func := max(a, b)
    */
    T element = 0;

    T func(int a, int b){
        //funcの内容は適宜変えてください
        return max(a, b);
    }


    SegmentTree(std::vector<T> A)
    {
        N = 1;
        while (N < (int)A.size()) N *= 2;
        node.resize(2 * N - 1, 0LL);
        for (int i = 0; i < (int)A.size(); i++)
            node[N - 1 + i] = A[i];
        //↓を適宜書き換えてね
        for (int i = N - 2; i >= 0; i--)
            node[i] = func(node[2* i + 1], node[2 * i + 2]);
    }

    /*元の配列Aでいうindexばんめの値をvalueに変更する*/
    void Update(int index, int value)
    {
        index += N - 1;
        node[index] = value;
        while (index > 0)
        {
            index = (index - 1) / 2;
            node[index] = func(node[2* index + 1], node[2 * index + 2]);
        }
    }

    /*もとの配列Aに対する要求区間[a, b)に対してのfunc*/
    int GetValue(int a, int b, int index = 0, int l = 0, int r = -1)
    {
        if (r < 0){
            r = N;
        }

        if (b <= l || r <= a){
            //INFにしたりする
            return element;
        }
        if (a <= l && r <= b){
            return node[index];
        }

        int left_value = GetValue(a, b, 2 * index + 1, l, (l + r) / 2);
        int right_value = GetValue(a, b, 2 * index + 2, (l + r) / 2, r);
        
        return func(left_value, right_value);
    }
};