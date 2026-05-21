# LAPORAN FINAL PROJECT STRUKTUR DATA

Perbandingan Waktu dan Memori Antara Struktur Data Hash Map dan B+ Tree

Kesimpulan yang dapat diambil berdasarkan hasil yang diperoleh dari program ini adalah sebagai berikut:

* HashMap menggunakan memori yang lebih banyak dibandingkan B+ Tree karena struktur internalnya yang menyisakan ruang untuk menghindari tabrakan data dan menjaga performa. 
* Kecepatan membaca dan memasukkan data dari file ke struktur data pada awalnya sedikit lebih cepat pada B+ Tree, namun seiring bertambahnya jumlah data, HashMap menjadi jauh lebih unggul dalam hal kecepatan. Hal ini dikarenakan B+ Tree akan mengandung overhead seperti untuk balancing dan hal hal lainnya yang pada jumlah data kecil masih belum terasa secara signifikan, namun semakin besarnya data maka overhead ini akan menjadi lebih besar. 
* Proses pencarian data (baik pada kasus terbaik maupun terburuk) serta proses penyisipan (insert) data jauh lebih cepat dilakukan menggunakan HashMap dibandingkan dengan B+ Tree. Hal ini dikarenakan B+ Tree harus melakukan traversal terlebih dahulu untuk menuju lokasi data, sedangkan hashmap hanya perlu mengubah input menjadi key yang akan memberitahu lokasi data-nya secara langsung. 

