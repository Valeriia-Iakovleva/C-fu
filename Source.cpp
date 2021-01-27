// C++ review.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//
#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
using namespace std;//������ ��������� � �++ ����� ������������ ����, ��� �������� �������� ���������� ��� ������
                    // � ������� �����������(����������������) ��������� � ����� ����� 

//��������� �������, ���� ������ ��� ����� ��� ������, ��� �������, � ���� �� �� ������� ������� � ������ ����
void print_ma(int** arr, int n, int m);
int** get_matrix(int n, int m);
void print_ma(string** arr, int n, int m);

//����� ������ ���������, ������ ���� ��� �������, �� �� ����� ��������� �� ������ ���������� int, double, char, string
template <typename T>
class matrix {
    //�������� ������, �� ����� ������ ������ ���� ��� ���������� � ������
    //��� ����������, ������ ��� ���� ������� 
private:
    int N;//������ ������ ����� �� ������� ����� ������� � ��� ���� ���-�� ����� N
    int M; //��� - �� �������� N
    T** ma; // � ��� �� ������ ����������� ������������ ������(�� �����������)
public:
    //�����������
    matrix(int N = 0, int M = 0) {
        this->N = N;
        this->M = M;
        this->ma = new T * [N];
        for (int i = 0; i < N; i++)
        {
            ma[i] = new T[M];

        }
    }
    //� ��� ������������ �����������
    matrix(T** a, int N, int M) {
        this->N = N;
        this->M = M;
        this->ma = new T * [N];
        for (int i = 0; i < N; i++)
        {
            this->ma[i] = new T[M];
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                this->ma[i][j] = a[i][j];
            }
        }
    }
    //����������
    ~matrix() {
        if (this->ma[0] != nullptr) {
            for (int i = 0; i < N; i++)
            {
                delete[] ma[i];
            }
            delete[] ma;
        }
        else
            delete[] ma;
    }
    //������, ��� ��������� ������� � ����� ������ ������ ��� ������
    int GetM() {
        return M;
    }
    int GetN() {
        return N;
    }
    void print() {
        for (int i = 0; i < this->N; i++)
        {
            for (int j = 0; j < this->M; j++)
            {
                cout << this->ma[i][j] << " ";
            }
            cout << endl;
        }
    }
    //����� ������(�� ���� �������, �� ����������� ��� ����� ��� ��������� ������
    ;
    //���������� ���������(������ ������� ������������ �������� ������������ �������� ������)
    matrix& operator=(const matrix& b) {
        for (int i = 0; i < this->N; i++)
        {
            delete[] this->ma[i];
        }
        delete[] this->ma;
        this->M = b.M;
        this->N = b.N;
        this->ma = new int* [b.N];
        for (int i = 0; i < b.N; i++)
        {
            this->ma[i] = new int[b.M];
        }

        for (int i = 0; i < b.N; i++)
        {
            for (int j = 0; j < b.M; j++)
            {
                this->ma[i][j] = b.ma[i][j];
            }
        }


        return *this;
    }
    matrix operator+(const matrix& b) {

        int** arr = new int* [b.N];
        for (int i = 0; i < b.N; i++)
        {
            arr[i] = new int[b.M];
        }
        for (int i = 0; i < b.N; i++)
        {
            for (int j = 0; j < b.M; j++)
            {
                arr[i][j] = this->ma[i][j] + b.ma[i][j];
            }
        }
        return matrix(arr, b.N, b.M);

    }


};



int main()
{
    setlocale(LC_ALL, "rus");

    string filename;
    int N1, M1;
    int buff;

    cout << "������� ���� ��� ������ ������" << endl;    // Matrix.txt  ���
    cin >> filename;    // ��� getline(cin, filename);
    cout << endl;


    ifstream getmat; // �������� ����� ����� 
    getmat.open(filename);
    int** matrix1;
    //��������� ������� � �����
    if (getmat) { //�������� �� �� ��� ������ ���� � �������� ������ ��� ���(���� ��� �� ����� ������������� 0 � ��� false
        getmat >> N1;
        getmat >> M1;

        matrix1 = new int* [N1];
        for (int i = 0; i < N1; i++)
        {
            matrix1[i] = new int[M1];
        }
        for (int i = 0; i < N1; i++)
        {
            for (int j = 0; j < M1; j++)
            {
                getmat >> buff;
                matrix1[i][j] = buff;
            }
        }

    }
    else {
        printf("%s " "%d" " %s", "������! �� ������� ������� ���� ��� ��������� ������", 404, "XD");
        exit(1);
    }
    //������� ���������� ������ ������������ ���� ������ matrix
    matrix<int>A(matrix1, N1, M1);

    //����� ���������������� ������� � ������� 
    int N2, M2;
    cout << "������� ����������� ������� �" << endl;
    cin >> N2 >> M2;
    //���� ����� ���
    //ccin >> N2;
    //cin >> M2;
    //���������� ������ ��� ����� ostream 
    //cin ��� � ����� �����, �� ������ ��������� ����������� ������������������� ���� ����������� ����� ����������� ������, �� �������� ������� � ��


    //
    cout << "������� ������y �" << endl;
    int** matrix2 = get_matrix(N2, M2);
    matrix<int>B(matrix2, N2, M2);
    cout << "" << endl;
    string tuple;
    char oper = ' ';
    cin.ignore();//cin ��������� � ������ �����������, ������� �� ����������  getline(� ������� ����� ������ ������ � ��, �� ������� ���� ����������� �����
                 // ��������� ������� ��� ������� 
    getline(cin, tuple);
    //��� �� ������ � ��������� ��� ������ �������� ' ', �� ��������� � ������� ������� ������ ��� � �������� ������� ����� ��� ����������
    for (int i = 0; i < tuple.size(); i++) {
        if (tuple[i] == '+') {
            oper = '+';
            break;
        }
    }
    //���������� ��� ������ ������ 
    matrix<int>C;
    switch (oper)
    {
    case'+': {
        if (A.GetN() == B.GetN() && A.GetM() == B.GetM()) {
            C = A + B;
        }
        else
            cout << "������������ ����������" << endl;
    }
    case'*': {

    }
    }
    //����� ��������������� ��������� ������ � ������ 
    C.print();

    //������� ������ ������� �� ������������ ��� ������������ ��������
    for (int i = 0; i < N1; i++)
    {
        delete[] matrix1[i];
    }
    delete[]matrix1;

    for (int i = 0; i < N2; i++)
    {
        delete[] matrix2[i];
    }
    delete[]matrix2;

    return 0;
}

void print_ma(int** arr, int n, int m) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
void print_ma(string** arr, int n, int m) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
int** get_matrix(int n, int m) {
    int** arr = new int* [n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new int[m];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> arr[i][j];
        }
    }
    return arr;
}

//}

// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.


