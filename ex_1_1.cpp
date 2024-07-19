#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Hàm xác định mức độ ưu tiên của toán tử
int Xacdinhmucdouutien(char c)
{
    if (c == '^')
        return 3; //'^' ưu tiên cao nhất
    else if (c == '*' || c == '/')
        return 2; //'*' và '/' ưu tiên cao hơn '+' và '-'
    else if (c == '+' || c == '-')
        return 1; //'+' và '-' ưu tiên thấp nhất
    else
        return -1; // Không phải toán tử
}

// Hàm chuyển đổi biểu thức trung tố sang hậu tố
string Infix2Postfix(string infix)
{
    stack<char> nganxep;
    string hauto = "";
    int length = infix.length(); // Độ dài của biểu thức trung tố

    for (int k = 0; k < length; ++k)
    {
        char temp = infix[k];

        if (isalnum(temp))
        {
            hauto += temp; // Nếu ký tự là toán hạng, thêm vào chuỗi biểu thức hậu tố
        }
        else if (temp == '(')
            nganxep.push(temp); // Nếu ký tự là dấu mở ngoặc, đẩy nó vào ngăn xếp
        else if (temp == ')')
        {
            // Nếu ký tự là dấu đóng ngoặc, lấy các toán tử từ ngăn xếp và thêm vào chuỗi biểu thức hậu tố cho đến khi gặp dấu mở ngoặc
            while (!nganxep.empty() && nganxep.top() != '(')
            {
                hauto += ' ';
                hauto += nganxep.top();
                nganxep.pop();
            }
            if (!nganxep.empty() && nganxep.top() == '(')
                nganxep.pop(); // Lấy dấu mở ngoặc ra khỏi ngăn xếp
        }
        else
        {
            // Nếu ký tự là toán tử, lấy các toán tử từ ngăn xếp và thêm vào chuỗi biểu thức hậu tố cho đến khi gặp toán tử có mức độ ưu tiên thấp hơn
     
                while (!nganxep.empty() && Xacdinhmucdouutien(nganxep.top()) >= Xacdinhmucdouutien(temp))
                {
                    hauto += ' ';
                    hauto += nganxep.top();
                    nganxep.pop();
                }
                hauto += ' ';
                nganxep.push(temp); // Đẩy toán tử hiện tại vào ngăn xếp
            
        }
    }

    // Lấy tất cả các toán tử
    while (!nganxep.empty())
    {
        hauto += ' ';
        hauto += nganxep.top();
        nganxep.pop();
    }
    return hauto;
}

int main()
{
    string s;
    getline(cin, s);          // Nhập biểu thức trung tố từ người dùng
    cout << Infix2Postfix(s); // Chuyển đổi biểu thức trung tố thành hậu tố và in kết quả
    return 0;
}