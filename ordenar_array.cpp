#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Dados {
    string nome;
    vector<string> datas;
};

int converter(string d) {
    int dia = stoi(d.substr(0, 2));
    int mes = stoi(d.substr(2, 2));
    int ano = stoi(d.substr(4, 2));
    
    if (ano > 26) {
        ano += 1900;
    } else {
        ano += 2000;
    }
    
    return (ano * 10000) + (mes * 100) + dia;
}

bool compData(string a, string b) {
    return converter(a) < converter(b);
}

bool compNome(Dados a, Dados b) {
    return a.nome < b.nome;
}

int main() {
    ifstream arq("arquivo.txt");
    vector<Dados> v;
    string s;

    while (getline(arq, s)) {
        if (s == "") continue;

        Dados aux;
        int i = 0;

        while (i < s.length() && (s[i] < '0' || s[i] > '9')) {
            aux.nome += s[i];
            i++;
        }

        while (i + 5 < s.length()) {
            aux.datas.push_back(s.substr(i, 6));
            i += 6;
        }

        v.push_back(aux);
    }
    arq.close();

    sort(v.begin(), v.end(), compNome);

    for (int i = 0; i < v.size(); i++) {
        sort(v[i].datas.begin(), v[i].datas.end(), compData);
    }

    for (int i = 0; i < v.size(); i++) {
        cout << v[i].nome << ": ";
        for (int j = 0; j < v[i].datas.size(); j++) {
            cout << v[i].datas[j];
            if (j < v[i].datas.size() - 1) cout << ", ";
        }
        cout << endl;
    }

    return 0;
}
