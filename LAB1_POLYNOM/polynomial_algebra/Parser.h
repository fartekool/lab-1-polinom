#pragma once

#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <vector>

using namespace std;

class Token
{
public:

    // ���
    enum Type
    {
        OPERATOR,      // �������/�������� ��������
        L_PARANTHESIS, // ����������� ������
        R_PARANTHESIS, // ����������� ������
        INT_LITERAL,   // ����� �����
        FLOAT_LITERAL, // ����� � ��������� ������
        POLINOM_NAME,  // ��� ��������
        POLINOM,       // �������
        NONE_TYPE           // ������������� ��� 
    };

    // ���������������
    enum OperatorAssociativity
    {
        NONE,  // ����� - �� ��������
        RIGHT, // ������������������
        LEFT   // �����������������
    };

    Token(string token, Type type, OperatorAssociativity asc = OperatorAssociativity::NONE);

private:
    Type type;
    OperatorAssociativity opAsc;
    string str;

public:

    // ���������
    int getPrecendance() const;

    // �������
    const Type& getType() const;
    const OperatorAssociativity& getAsc() const;
    const string& getStr() const;

    // ������������ ������ ��� ������������ 
    bool operator==(const Token& other) const;

    bool operator!=(const Token& other) const;
};

class Parser {
private:
    enum State
    {
        S0, // ���������
        S1, // ����������� ������/���������
        S2, // ������ ������ ����� � �����
        S3, // ������ floating-point ����� � �����
        S4, // ������ ����� �������� � �����
        S5  // ����������� ����������� �����/����� �������� �� ������
    };
public:
    static vector<Token> Parse(const string& expr);
};
