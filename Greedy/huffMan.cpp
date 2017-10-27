#include<bits/stdc++.h>
using namespace std;

struct node{
    node *left, *right;
    int freq;
    char ch;
    node(){
        left = right = NULL;
        freq = ch = 0;
    }
};

struct CmpNodePtrs{
    bool operator()(const node* lhs, const node* rhs) const {
        return lhs->freq > rhs->freq;
    }
};

node* huffMan(string data) {
    int len = data.size();
    int cnt[256] = {0};
    for(int i = 0; i < len; i++) {
        ++cnt[data[i]];
    }
    priority_queue<node*,vector<node*>, CmpNodePtrs >Q;
    int n = 0;
    for(int i = 0; i < 256; i++) {
        if(cnt[i] > 0) {
            ++n;
            node *z = new node();
            z->freq = cnt[i];
            z->ch = i;
            Q.push(z);
        }
    }

    while(Q.size() > 1) {
        node *z = new node();
        node *x = Q.top();
        Q.pop();
        node *y = Q.top();
        Q.pop();
        z->left = x;
        z->right = y;
        z->freq = x->freq + y->freq;
        Q.push(z);
    }

    return Q.top();
}

void print_code(node *now, string code) {
    if(now->left == NULL && now->right == NULL) {
        printf("%c = %s\n", now->ch, code.c_str());
        return;
    }
    if(now->left != NULL) {
        print_code(now->left, code + "0");
    }
    if(now->right != NULL) {
        print_code(now->right, code + "1");
    }
}

int main() {
    node *head = huffMan("aaabbc");
    print_code(head, "");
}

