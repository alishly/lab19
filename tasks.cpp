#include "tasks.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

struct Node {//дерево хаффмана 
char ch;
int f; 
Node* l = nullptr, * r = nullptr; 
};

struct Cmp {//если частота а больше б 
 bool operator()(Node* a, Node* b) { return a->f > b->f; }
};

void getCodes(Node* n, string s, map<char, string>& codes) {//получение кодов Хаффмана
    if (!n) return;
    if (!n->l && !n->r) { codes[n->ch] = s; return; }
    getCodes(n->l, s + "0", codes);
    getCodes(n->r, s + "1", codes);
}

void Task1() {
    string msg = "0100111010010";
    cout << "Исходное сообщение: " << msg << endl;
    int m = msg.length(), r = 1;
    while ((1 << r) < m + r + 1) r++;
    cout << "Биты данных m = " << m << ", контрольные r = " << r << endl;
    int n = m + r;
    vector<int> res(n + 1, 0);
    int k = 0;
    for (int i = 1; i <= n; i++) {//расстановка значений 
        if ((i & (i - 1)) == 0) continue;//попуск степеней 2 
        res[i] = msg[k++] - '0';
    }
    //вычисление контольных бит через иксор 
    for (int i = 1; i <= n; i <<= 1) {
        int p = 0;
        for (int j = i; j <= n; j++) if (j & i) p ^= res[j];
        res[i] = p;
        cout << "P" << i << "=" << p << " ";
    }
    cout << "\nИтоговый код: ";
    for (int i = 1; i <= n; i++) cout << res[i];
    cout << endl;
}

void Task2() {
    string text = "КРИЧАЛ АРХИП, АРХИП ОХРИП";
    cout << "Текст: " << text << endl;
    map<char, int> freq; //символ частота 
    for (char c : text) freq[c]++;
    cout << "Частоты: ";
    for (auto& p : freq) cout << p.first << "=" << p.second << " ";
    cout << endl;
    priority_queue<Node*, vector<Node*>, Cmp> pq;
    for (auto& p : freq) pq.push(new Node{ p.first, p.second });
    while (pq.size() > 1) {// Построение дерева Хаффмана обьеденить два узла с нам частотой и извлечь  и меньшей частотой
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();
        pq.push(new Node{ 0, a->f + b->f, a, b });
    }
    Node* root = pq.top();//корень дерева хаффмана 
    map<char, string> codes;
    getCodes(root, "", codes);
    int huffSize = 0;
    cout << "Коды Хаффмана:\n";
    for (auto& p : freq) {
        cout << "  '" << p.first << "' -> " << codes[p.first] << endl;
        huffSize += p.second * codes[p.first].length();
    }
    cout << "Равномерный размер: " << text.length() * 8 << " бит\n";
    cout << "Размер Хаффмана: " << huffSize << " бит\n";
}

void Task3() {
    string s; int k;
    cout << "Текст: "; getline(cin, s);
    cout << "Сдвиг: "; cin >> k; cin.ignore();
    string res = s;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c >= 'A' && c <= 'Z') res[i] = 'A' + (c - 'A' + k + 26) % 26;
        else if (c >= 'a' && c <= 'z') res[i] = 'a' + (c - 'a' + k + 26) % 26;
        else if (c >= 'А' && c <= 'Я') res[i] = 'А' + (c - 'А' + k + 33) % 33;
        else if (c >= 'а' && c <= 'я') res[i] = 'а' + (c - 'а' + k + 33) % 33;
        else res[i] = c;
    }
    cout << "Результат: " << res << endl;
}