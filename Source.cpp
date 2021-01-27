// C++ review.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
using namespace std;//помиио библиотек в с++ важны пространства имен, они помагают избегать конфликтов при работе
                    // с большим количеством(пользовательских) библиотек в одном файле 

//обявления функций, тело тоесть код внизу под мейном, так принято, а ваще их по красоте выносят в другой файл
void print_ma(int** arr, int n, int m);
int** get_matrix(int n, int m);
void print_ma(string** arr, int n, int m);

//класс причем шаблонный, тоесть ваще это матрица, но мы может заполнить ее людыми значениями int, double, char, string
template <typename T>
class matrix {
    //сокрытые данные, их можно менять только если это обозначить в классе
    //это переменные, данные про машу матрицу 
private:
    int N;//тоесть всегда когда мы создаем обект матрицу у нее есть кол-во строк N
    int M; //кол - во столбцов N
    T** ma; // и под ее яцейки выделяеться динамическая память(из оперативной)
public:
    //конструктор
    matrix(int N = 0, int M = 0) {
        this->N = N;
        this->M = M;
        this->ma = new T * [N];
        for (int i = 0; i < N; i++)
        {
            ma[i] = new T[M];

        }
    }
    //а это перегруженый конструктор
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
    //диструктор
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
    //геттер, для получения скрытых в полях приват данных все класса
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
    //метод класса(по сути функция, но вызываеться как метод для элементов класса
    ;
    //перегрузка оператора(тоесть задание страндартной операции присваивания желаемых свойст)
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

    cout << "Укажите файл для чтения данный" << endl;    // Matrix.txt  мое
    cin >> filename;    // или getline(cin, filename);
    cout << endl;


    ifstream getmat; // файловый поток ввода 
    getmat.open(filename);
    int** matrix1;
    //получение матрици с файла
    if (getmat) { //проверка на то был найден файл с указаным именем или нет(если нет то поток обозначаеться 0 и тип false
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
        printf("%s " "%d" " %s", "Ошибка! Не удолось открыть файл для получения данных", 404, "XD");
        exit(1);
    }
    //создаем переменную нашего собственного типа данных matrix
    matrix<int>A(matrix1, N1, M1);

    //ввыод пользовательской матрици с консоли 
    int N2, M2;
    cout << "Введите размерность матрици В" << endl;
    cin >> N2 >> M2;
    //тоже самое что
    //ccin >> N2;
    //cin >> M2;
    //консольная строка это поток ostream 
    //cin это ж поток ввода, он просто считывает необходимую последовательнойсть байт обозначеную типом считываемых данных, не учитывая пробелы и тд


    //
    cout << "Введите матрицy В" << endl;
    int** matrix2 = get_matrix(N2, M2);
    matrix<int>B(matrix2, N2, M2);
    cout << "" << endl;
    string tuple;
    char oper = ' ';
    cin.ignore();//cin оставляет в потоке разделитель, который не игнорирует  getline(в гетлайн пожно ввести пробел и тд, мы удаляем этот разделитель иначе
                 // следующая функция его считает 
    getline(cin, tuple);
    //ход по строке и посколько это массив символов ' ', то обращаясь к каждому элменту строки как к эдеемнту масиива можно его сравнивать
    for (int i = 0; i < tuple.size(); i++) {
        if (tuple[i] == '+') {
            oper = '+';
            break;
        }
    }
    //переменная для записи ответа 
    matrix<int>C;
    switch (oper)
    {
    case'+': {
        if (A.GetN() == B.GetN() && A.GetM() == B.GetM()) {
            C = A + B;
        }
        else
            cout << "суммирование невозможно" << endl;
    }
    case'*': {

    }
    }
    //вызов собственноручно созданого метода у класса 
    C.print();

    //очистка памяти которую мы использовали для динамических массивов
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

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.


