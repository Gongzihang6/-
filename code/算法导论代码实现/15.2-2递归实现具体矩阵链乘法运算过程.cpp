#include <iostream>  
#include <vector>  
using namespace std;

// �������ṹ��  
struct Matrix {
    int rows, cols;
    vector<vector<int>> data;
    // �����캯������ʼ��Ϊȫ0����
    Matrix(int r, int c) : rows(r), cols(c), data(r, vector<int>(c, 0)) {}
};

// ����˷�����  
Matrix Multiply(const Matrix& A, const Matrix& B) {
    if (A.cols != B.rows) {
        throw runtime_error("���ɽ��о���˷�");
    }

    Matrix result(A.rows, B.cols);
    for (int i = 0; i < A.rows; ++i) {
        for (int j = 0; j < B.cols; ++j) {
            for (int k = 0; k < A.cols; ++k) {
                result.data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }
    return result;
}

// �������˷��ݹ�ʵ��  
Matrix MATRIX_CHAIN_MULTIPLY(vector<Matrix>&A, vector<vector<int>>&s, int i, int j) {
    if (i == j) {
        return A[i - 1];  // ע���±��0��ʼ  
    }
    else {
        int k = s[i][j];
        Matrix left = MATRIX_CHAIN_MULTIPLY(A, s, i, k);
        Matrix right = MATRIX_CHAIN_MULTIPLY(A, s, k + 1, j);
        return Multiply(left, right);
    }
}

// 15.2-1�еľ������˷����Ž��㷨�������������ŷ���s
vector<vector<int>> MatrixChainOrder(const vector<int>& p) {
    int n = p.size() - 1;  // ��������

    // ������̬�滮����
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    // �������ȴ�2��ʼ�����n
    for (int l = 2; l <= n; l++) {
        // �������п��ܵ��������
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;  // �����յ�
            m[i][j] = INT_MAX;  // ��ʼ��Ϊ���ֵ

            // �������п��ܵķָ��k
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;     // ������С����
                    s[i][j] = k;     // ��¼���ŷָ��
                }
            }
        }
    }
    return s;
}



int main() {
    // ʾ����A1(5*10)��A2(10*3)��A3(3*12)��A4(12*5)��A5(5*50)��A6(50*6)  
    // ����ֻ��������״��û�о�����ֵ��������ֵĬ�ϳ�ʼ��ȫ��Ϊ0
    vector<Matrix> matrices = {
        Matrix(5, 10),   // A1  
        Matrix(10, 3),   // A2  
        Matrix(3, 12),   // A3  
        Matrix(12, 5),   // A4  
        Matrix(5, 50),   // A5  
        Matrix(50, 6)    // A6  
    };
    vector<int> p = { matrices[0].rows, matrices[1].rows, matrices[2].rows, matrices[3].rows, matrices[4].rows, matrices[5].rows, matrices[0].cols };
    // Ԥ�ȼ�������ŷָ���  
    vector<vector<int>> s = MatrixChainOrder(p);

    // �������ս��  
    Matrix result = MATRIX_CHAIN_MULTIPLY(matrices, s, 1, 6);

    // ������ά��  
    cout << "���ս������ά��: " << result.rows << " x " << result.cols << endl;

    return 0;
}