#include <iostream>
#include <stack>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

// 状態を表す型を定義
using State = char;

// グラフ構造を定義
std::unordered_map<State, std::vector<State>> graph = {
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
void printStack(const std::stack<State>& stack) {
    std::stack<State> temp = stack; // コピーを作成 (元のスタックを壊さないため)
    std::vector<State> elements;
    while (!temp.empty()) {
        elements.push_back(temp.top());
        temp.pop();
    }
    std::reverse(elements.begin(), elements.end());
    std::cout << "[ ";
    for (State s : elements) {
        std::cout << s << " ";
    }
    std::cout << "]";
}

// クローズドリストの中身を表示する関数
void printClosedList(const std::unordered_set<State>& closedList) {
    std::cout << "[ ";
    for (State s : closedList) {
        std::cout << s << " ";
    }
    std::cout << "]";
}

void depthFirstSearch(State initialState) {
    std::stack<State> openList;           // オープンリスト (スタック)
    std::unordered_set<State> closedList; // クローズドリスト (探索済みの状態)

    // 初期状態をオープンリストに追加
    openList.push(initialState);

    // 探索を開始
    while (!openList.empty()) {
        std::cout << "\n=== 現在の状態 ===\n";
        std::cout << "オープンリスト: ";
        printStack(openList);
        std::cout << "\nクローズドリスト: ";
        printClosedList(closedList);
        std::cout << "\n";

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

    std::cout << "\n探索完了。訪問済みノード: ";
    printClosedList(closedList);
    std::cout << std::endl;
}

int main() {
    State initialState = 'A'; // 初期状態
    depthFirstSearch(initialState);
    return 0;
}
