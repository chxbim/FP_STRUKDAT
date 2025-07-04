# FP_STRUKDAT

--- Manajemen Transaksi Top-Up (AVL Tree & BST)

Program ini dibuat sebagai tugas akhir mata kuliah Struktur Data untuk mengelola data transaksi top-up berdasarkan waktu (`hh:mm`) dan nominal. Program ini mendemonstrasikan penggunaan dua jenis struktur data pohon biner:

- AVL Tree: Pohon pencarian biner yang selalu seimbang.
- Binary Search Tree (BST): Pohon pencarian biner biasa.

-- 📌 Studi Kasus

Studi kasus yang diangkat adalah pencatatan transaksi top-up yang terjadi sepanjang hari. Tiap transaksi dicatat berdasarkan waktu dan nilai top-up, lalu disimpan dan dikelola menggunakan AVL atau BST, tergantung pilihan user.


-- 📋 Fitur Program

 Tambah transaksi  
 Tampilkan semua transaksi secara terurut (in-order traversal)  
 Cari transaksi berdasarkan waktu  
 Hapus transaksi  
 Simpan data ke file `transaksi.txt`  
 Muat data dari file saat program dijalankan


-- 🧭 Struktur Data

- timestamp: dikonversi dari format `hh:mm` menjadi integer menit (`hh * 60 + mm`)
- quantity: jumlah top-up dalam satuan rupiah (int)
- Pohon menyimpan dan mengurutkan data berdasarkan timestamp


-- 🖥️ Tampilan Program (CLI)

Pilih tipe struktur data:

1. AVL Tree
2. Binary Search Tree (BST)
   Masukkan pilihan (1/2): 1

===== Program Recap Database Transaksi =====

1. Masukkan data transaksi
2. Tampilkan semua data transaksi
3. Hapus data transaksi
4. Cari data transaksi
5. Tutup program
   Pilih menu: 1
   Masukkan waktu transaksi (hh:mm) dan nominal: 09:45 15000


-- Contoh hasil tampilan data:


No | Waktu | Quantity

1  | 09:45 | 15000
2  | 13:20 | 25000
------------------


-- 💾 Format File `transaksi.txt`

Setiap baris terdiri dari `timestamp` (dalam menit) dan `quantity`, dipisahkan spasi. File ini akan dibuat secara otomatis jika belum ada.

Contoh isi file:

````
585 15000
800 25000

````

Artinya:
- 585 = 09:45 (karena 9*60 + 45)
- 800 = 13:20


-- ⚙️ Compile & Jalankan:

💻 Via Terminal (g++):

```bash
g++ -o transaksi main.cpp
./transaksi
````

📦 (Linux/WSL/VSCode Terminal)

```bash
g++ -std=c++11 -Wall -Wextra -o transaksi main.cpp
./transaksi
```


-- 🧑‍💻 Kontributor

- Christian Bimo Aryoputro (23081010223)
- Muhammad Abdul Aziz (230**010***)



-- 🪪 Lisensi

MIT License – bebas digunakan untuk pembelajaran dan pengembangan lebih lanjut.

```
MIT License

Copyright (c) 2025 Christian Bimo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files.
```


-- 📌 Catatan

- Program ini berbasis terminal (CLI) dan menyimpan data ke dalam file lokal.
- Pastikan file `transaksi.txt` berada di direktori yang sama dengan binary program (jika ada data yang ingin dimuat).
- Hindari memasukkan waktu yang sama dua kali karena key `timestamp` harus unik.


-- 📂 Rekomendasi Struktur Repo

```
├── README.md
├── main.cpp
├── transaksi.txt        # auto-generated
└── screenshots/         # opsional
```
