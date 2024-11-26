// fixed version of DFS.cpp
// Depth First Search (DFS) の実装例 (スタックを用いた実装)
// グラフ構造はDFS-GRAPTH.pngを参照

#include <iostream>
#include <stack>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

// 状態を表す型を定義
using State = char;

// グラフ構造を定義
unordered_map<State, vector<State>> graph = {
    {'A', {'B', 'C'}},
    {'B', {'D', 'E'}},
    {'C', {'F', 'G', 'H'}},
    {'D', {'I'}},
    {'F', {}},
    {'E', {}},
    {'G', {'J'}},
    {'H', {}},
    {'I', {}},
    {'J', {}}
};

// スタックの中身を表示する関数
void printStack(const stack<State>& s) {
    stack<State> temp = s; // コピーを作成 (元のスタックを壊さないため)
    vector<State> elements;
    while (!temp.empty()) {
        elements.push_back(temp.top());
        temp.pop();
    }
    reverse(elements.begin(), elements.end());
    cout << "[ ";
    for (State state : elements) {
        cout << state << " ";
    }
    cout << "]";
}

// クローズドリストの中身を表示する関数
void printClosedList(const unordered_set<State>& closedList) {
    cout << "[ ";
    for (State s : closedList) {
        cout << s << " ";
    }
    cout << "]";
}

void depthFirstSearch(State initialState) {
    stack<State> openList;           // オープンリスト (スタック)
    unordered_set<State> closedList; // クローズドリスト (探索済みの状態)

    // 初期状態をオープンリストに追加
    openList.push(initialState);

    // 探索を開始
    while (!openList.empty()) {
        cout << "\n=== 現在の状態 ===\n";
        cout << "オープンリスト: ";
        printStack(openList);
        cout << "\nクローズドリスト: ";
        printClosedList(closedList);
        cout << "\n";

        // オープンリストから先頭の要素を取り出す
        State s = openList.top();
        openList.pop();

        // 既に訪問済みならスキップ
        if (closedList.find(s) != closedList.end()) {
            continue;
        }

        // sをクローズドリストに追加 (探索済み)
        closedList.insert(s);

        // sから接続している状態をオープンリストに追加
        for (State nextState : graph[s]) {
            if (closedList.find(nextState) == closedList.end()) {
                openList.push(nextState);
            }
        }
    }

    cout << "\n探索完了。訪問済みノード: ";
    printClosedList(closedList);
    cout << endl;
}

int main() {
    State initialState = 'A'; // 初期状態
    depthFirstSearch(initialState);
    return 0;
}
