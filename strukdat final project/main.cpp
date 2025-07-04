#include <bits/stdc++.h>
using namespace std;

/*
 Christian Bimo Aryoputro (23081010223)
 Muhammad Abdul Aziz (230**010***)
 Studi Kasus Manajemen Transaksi Top-Up berdasarkan Waktu
 */

struct nodes {
    int timestamp;
    int quantity;
    nodes *left;
    nodes *right;
    int height;
};

int height(nodes *node) {
    return (node == nullptr) ? 0 : node->height;
}

nodes *createNode(int timestamp, int quantity) {
    nodes *node = new nodes();
    node->timestamp = timestamp;
    node->quantity = quantity;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

nodes *rotateKanan(nodes *K) {
    nodes *x = K->left;
    nodes *T2 = x->right;

    x->right = K;
    K->left = T2;

    K->height = max(height(K->left), height(K->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

nodes *rotateKiri(nodes *x) {
    nodes *K = x->right;
    nodes *T2 = K->left;

    K->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    K->height = max(height(K->left), height(K->right)) + 1;

    return K;
}

int getBalance(nodes *node) {
    return (node == nullptr) ? 0 : height(node->left) - height(node->right);
}

nodes *minValueNode(nodes *node) {
    nodes *current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

bool dataFound = false;

nodes *deleteNode(nodes *root, int timestamp) {
    if (root == nullptr) {
        return root;
    }

    if (timestamp < root->timestamp)
        root->left = deleteNode(root->left, timestamp);
    else if (timestamp > root->timestamp)
        root->right = deleteNode(root->right, timestamp);
    else {
        dataFound = true;
        if ((root->left == nullptr) || (root->right == nullptr)) {
            nodes *temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            nodes *temp = minValueNode(root->right);
            root->timestamp = temp->timestamp;
            root->quantity = temp->quantity;
            root->right = deleteNode(root->right, temp->timestamp);
        }
    }

    if (root == nullptr)
        return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateKanan(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateKiri(root->left);
        return rotateKanan(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateKiri(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateKanan(root->right);
        return rotateKiri(root);
    }

    return root;
}

void searchNode(nodes *root, int timestamp, bool &found){
    if(root == nullptr){
        return;
    }

    if(timestamp < root->timestamp){
        searchNode(root->left, timestamp, found);
    } else if (timestamp > root->timestamp){
        searchNode(root->right, timestamp, found);
    } else {
        found = true;
        int hours = root->timestamp / 60;
        int minutes = root->timestamp % 60;
        cout << "data ditemukan: ";
        cout << "waktu: " << setw(2) << setfill('0') << hours << ":"
        << setw(2) << setfill('0') << minutes << endl;
        cout << "nominal: " << root->quantity << endl;
    }
}

nodes *insertAVL(nodes *node, int timestamp, int quantity) {
    if (node == nullptr)
        return createNode(timestamp, quantity);

    if (timestamp < node->timestamp)
        node->left = insertAVL(node->left, timestamp, quantity);
    else if (timestamp > node->timestamp)
        node->right = insertAVL(node->right, timestamp, quantity);
    else {
        cout << "error! gunakan input waktu yang berbeda!" << endl;
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);

    if (balance > 1 && timestamp < node->left->timestamp)
        return rotateKanan(node);
    if (balance < -1 && timestamp > node->right->timestamp)
        return rotateKiri(node);
    if (balance > 1 && timestamp > node->left->timestamp) {
        node->left = rotateKiri(node->left);
        return rotateKanan(node);
    }
    if (balance < -1 && timestamp < node->right->timestamp) {
        node->right = rotateKanan(node->right);
        return rotateKiri(node);
    }
    return node;
}

nodes *insertBST(nodes *node, int timestamp, int quantity) {
    if (node == nullptr)
        return createNode(timestamp, quantity);

    if (timestamp < node->timestamp)
        node->left = insertBST(node->left, timestamp, quantity);
    else if (timestamp > node->timestamp)
        node->right = insertBST(node->right, timestamp, quantity);
    else {
        cout << "error! gunakan input waktu yang berbeda!" << endl;
        return node;
    }
    return node;
}

void inorderTraversal(nodes *root, int &counter) {
    if (root != nullptr) {
        inorderTraversal(root->left, counter);

        int hours = root->timestamp / 60;
        int minutes = root->timestamp % 60;

        // Tampilkan data dengan format tabel
        cout << setw(5) << counter++ << " | "; // Nomor urut
        cout << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0')
        << minutes << setfill(' ') << " | "; // Waktu
        cout << setw(5) << root->quantity << endl; // Quantity

        inorderTraversal(root->right, counter);
    }
}

bool parseTimestamp(const string &time, int &hours, int &minutes){
    regex pattern("^([0-1][0-9]|2[0-3]):[0-5][0-9]$");
    if (!regex_match(time, pattern)){
        cout << "format waktu salah! harap masukkan dalam format hh:mm (09:30, 12:05)" << endl;
        return false;
    }
    sscanf(time.c_str(), "%2d:%2d", &hours, &minutes);
    return true;
}

void saveFile(nodes *root, ofstream &file){
    if(root != nullptr){
        saveFile(root->left, file);
        file << root->timestamp << " " << root->quantity << endl;
        saveFile(root->right, file);
    }
}

void loadData(nodes *&root, bool isAVL){
    ifstream file("transaksi.txt");
    if (!file.is_open()){
        cout << "file tidak ditemukan! membuat file baru..." << endl;
        return;
    }
    int timestamp, quantity;
    while (file >> timestamp >> quantity){
        root = isAVL ? insertAVL(root, timestamp, quantity) : insertBST(root, timestamp, quantity);
    }
    file.close();
}

int main() {
    nodes *root = nullptr;
    bool isAVL = false;
    loadData(root, isAVL);

    cout << "Pilih tipe struktur data:" << endl;
    cout << "1. AVL Tree" << endl;
    cout << "2. Binary Search Tree (BST)" << endl;
    cout << "Masukkan pilihan (1/2): ";
    int choice;
    cin >> choice;
    if (choice == 1) isAVL = true;

    int menuChoice;
    do {
        cout << "\n===== Program Recap Database Transaksi =====" << endl;
        cout << "1. Masukkan data transaksi" << endl;
        cout << "2. Tampilkan semua data transaksi" << endl;
        cout << "3. Hapus data transaksi" << endl;
        cout << "4. Cari data transaksi" << endl;
        cout << "5. Tutup program" << endl;
        cout << "Pilih menu: ";
        cin >> menuChoice;

        switch (menuChoice) {
            case 1: {
                string time;
                int quantity;
                int hours, minutes;
                int timestamp;
                ofstream  file("transaksi.txt");
                saveFile(root, file);
                file.close();

                do {
                    cout << "Masukkan waktu transaksi (hh:mm) dan nominal: ";
                    cin >> time >> quantity;
                } while (!parseTimestamp(time, hours, minutes));

                timestamp = hours * 60 + minutes;
                root = isAVL ? insertAVL(root, timestamp, quantity) : insertBST(root, timestamp, quantity);
                break;
            }
            case 2: {
                cout << "-----------------------------" << endl;
                cout << setw(5) << "No" << " | "
                     << setw(5) << "Waktu" << " | "
                     << setw(5) << "Quantity" << endl;
                cout << "------------------------------" << endl;
                int counter = 1;
                inorderTraversal(root, counter);
                cout << "------------------------------" << endl;
                break;
            }

            case 3: {
                string time;
                int hours, minutes, timestamp;
                ofstream file("transaksi.txt");
                saveFile(root, file);
                file.close();

                cout << "Masukkan waktu transaksi (hh:mm) yang ingin dihapus: ";
                cin >> time;
                if (parseTimestamp(time, hours, minutes)) {
                    timestamp = hours * 60 + minutes;
                    dataFound = false;
                    root = deleteNode(root, timestamp);
                    if (dataFound)
                        cout << "Data berhasil dihapus." << endl;
                    else
                        cout << "Data tidak ditemukan." << endl;
                }
                break;
            }

            case 4: {
                string time;
                int hours, minutes, timestamp;
                cout << "Masukkan waktu transaksi (hh:mm) yang ingin dicari: ";
                cin >> time;
                if (parseTimestamp(time, hours, minutes)){
         timestamp = hours * 60 + minutes;
                    bool found = false;
                    searchNode(root, timestamp, found);
                    if (!found){
                        cout << "Data tidak ditemukan!" << endl;
                    }
                }
            }

            case 5:
                cout << "Menutup program..." << endl;
                break;

            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    } while (menuChoice != 5);

    return 0;
}
