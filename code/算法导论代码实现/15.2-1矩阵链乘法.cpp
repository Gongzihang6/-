
#include <iostream>
#include <vector>
#include <climits>
#include <format>
#include <iomanip>

using namespace std;

// ������������ӡ�������ŷ���
void PrintOptimalParens(const vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    }
    else {
        cout << "(";
        PrintOptimalParens(s, i, s[i][j]);
        PrintOptimalParens(s, s[i][j] + 1, j);
        cout << ")";
    }
}

// �������˷����Ž��㷨
void MatrixChainOrder(const vector<int>& p) {
    int n = p.size() - 1;  // ��������

    // ������̬�滮����
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    // �������ȴ�2��ʼ�����n
    for (int l = 2; l <= n; l++) {
        cout << "����������Ϊ��" << l << "ʱ��" << endl;

        // �������п��ܵ��������
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;  // �����յ�
            m[i][j] = INT_MAX;  // ��ʼ��Ϊ���ֵ

            cout << format("m[{},{}]:", i, j) << endl;

            // �������п��ܵķָ��k
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                // ��ϸ���ÿһ���������
                cout << format("  kȡ{}ʱ:", k) << endl;
                cout << format("    q = m[{},{}] + m[{},{}] + p[{}]p[{}]p[{}]",
                    i, k, k + 1, j, i - 1, k, j) << endl;
                cout << format("    q = {} + {} + {} = {}",
                    m[i][k], m[k + 1][j], p[i - 1] * p[k] * p[j], q) << endl;

                if (q < m[i][j]) {
                    m[i][j] = q;     // ������С����
                    s[i][j] = k;     // ��¼���ŷָ��

                    cout << format("    ����: m[{},{}] = {}", i, j, q) << endl;
                }
            }
            cout << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    // ��ӡ��С����
    cout << "��С�����˷�����: " << m[1][n] << endl;

    // ��ӡ�������ŷ���
    cout << "�������ŷ���: ";
    PrintOptimalParens(s, 1, n);
    cout << endl;
}

int main() {
    // �����ľ���ά�����У�5, 10, 3, 12, 5, 50, 6
    vector<int> p = { 5, 10, 3, 12, 5, 50, 6 };

    MatrixChainOrder(p);

    return 0;
}
