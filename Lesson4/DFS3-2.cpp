// fixed version of DFS.cpp
// Depth First Search (DFS) の実装例 (スタックを用いた実装)
// グラフ構造はDFS-GRAPH.pngを参照

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
    {'S', {'A', 'B'}},
    {'A', {'C', 'D'}},
    {'B', {'C'}},
    {'C', {'D'}},
    {'D', {}},
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
        vector<State> nextStates = graph[s];
        sort(nextStates.begin(), nextStates.end(), greater<State>()); // アルファベットの逆順にソート
        for (State nextState : nextStates) {
            if (closedList.find(nextState) == closedList.end()) {
                // 未訪問の状態をオープンリストに追加
                // ネクストステートがオープンリストにすでにあるものは追加しない
                bool isExist = false;
                stack<State> temp = openList;
                while (!temp.empty()) {
                    if (temp.top() == nextState) {
                        isExist = true;
                        break;
                    }
                    temp.pop();
                }
                if (!isExist) {
                    openList.push(nextState);
                }
            }
        }
    }

    cout << "\n探索完了。訪問済みノード: ";
    printClosedList(closedList);
    cout << endl;
}

int main() {
    State initialState = 'S'; // 初期状態
    depthFirstSearch(initialState);
    return 0;
}
