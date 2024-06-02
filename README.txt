Scratchpad Project

---------------------------

Teknologi yang dipakai: 
1. Visual Studio Code
2. C++
3. Raylib
4. Compiler g++
5. Compiler gcc
6. Compiler MinGW
7. C

Tautan / link ke public repository:  https://github.com/DarianHalim/ScratchPad-Project

---------------------------------------------

Apakah ini adalah proyek terbaik Anda?
Tidak, tetapi saya menginclude ini karena merupakan proyek diluar curriculum kuliah. Menunjukan awal-awal saya bisa mempelajari dan mendownload semua alat secara mandiri
tanpa resourced dari kampus

Tentang apakah proyek ini?
Pembuatan Software Scartchpad, semacam note taking app ringan. Untuk mengilustrasikan ide-ide, dan mendrafting. Bekerja untuk PC

Apa peran Anda di proyek ini?
Sole Developer, Designer. Semua saya kerjakan sendiri

Tantangan apa yang Anda hadapi selama
mengerjakan proyek ini? Bagaimana cara
Anda menghadapinya?

1. Membuat Raylib Bekerja
-> Raylib membutuhkan beberapa initial steps agar dapat bekerja. 

A. Membuat file include yang berisi raylib.h, dan lib file berisi lib.a, Dapatkan info tersebut dari video YouTube dan Dokumentasi

B. Diperlukan set-up basic format yang berisi libgcc_s_dw2-1.dll, dan lain-lain, Memilih salah satu basic format dari GitHub Raylib


2. Syntax Raylib
-> Raylib mempunyai beberapa Syntax unik -> Dipecahkan dengan membaca dokumentasi-dokumentasi Raylib 

3. Fungsi drawing memiliki timeout, hilang otomatis 
-> Terjadi sebab fungsi terletak dalam loop if mousekeydown. Harus dipisahkan agar tidak hilang atau ke reset saat mousekeyup dan bool isActive menjadi false;S

4. Fungsi drawing  di override fungsi pengapusan, jadi tidak bisa draw di tempat yang sudah dihapus
-> Diperlukan pembuatan fungsi menggunakan for. Untuk terus melakukan cek jika hasil eraser bertabrakan dengan draw. Element eraser akan dihapus dan digantikan dengan draw

5. Chalk tidak mengikuti saat full screen
-> Simple fix, mengganti colision border menjadi currentscreenheight dan width. Agar mengambil data window terbaru

6. Compiling static agar menjadi .exe universal
-> Menambahkan -static dan beberapa hal lain. Agar .exe dapaat diakses oleh pengguna yang tidak memiliki Raylib
