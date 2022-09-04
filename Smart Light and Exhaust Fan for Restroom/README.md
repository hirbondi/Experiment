##Projek "***Smart Light & Exhaust Fan for Restroom***" ini dibuat berkaitan dengan Skill Task Firmware Engineer V2.

Konsep dari projek ini adalah melakukan monitoring penggunaan lampu dan kipas pembuangan (exhaust fan) dari sebuah kamar mandi agar efisien. Konsep ini lebih cocok diterapkan di fasilitas publik dimana lampu dan kipas pembuangan kamar mandi selalu dinyalakan meskipun sedang tidak digunakan. Target dari projek ini ada dua, yaitu efisiensi penggunaan lampu dan mengurangi aroma tidak sedap dengan mengontrol kipas pembuangannya. Sehingga ketika terdapat aroma tidak sedap berlebih, kipas pembuangan masih akan beroperasi meskipun lampu sudah padam dan tidak ada aktivitas lagi di dalamnya. Hal tersebut bertujuan untuk meningkatkan kenyamanan pengguna berikutnya.

***

###Alat-alat yang digunakan diantaranya:
- 1 _Breadboard_
- 1 Arduino Uno _board_
- 1 _Passive_Infrared_sensor_ (PIR)
- 1 Gas sensor
- 1 Modul micro SD
- 1 LED putih  (sebagai representasi switch **lampu kamar mandi**)
- 1 LED orange (sebagai representasi switch **kipas pembuangan**)
- 2 Resistor 220 ohm
- 1 Resistor 10k ohm

###Variabel yang dimonitor:
- Radiasi _infrared_ (deteksi gerakan manusia).
- Senyawa gas/ udara di dalam kamar mandi.

###Media simulasi:
- [Data Acquisition & Input Parameter Simulation](https://www.tinkercad.com/things/8VQjDwv1EwX?sharecode=6m6rZR8Xpvfb2RmDj3n5h9iKUaeYaXKtgQNOwsDkSSc)
- [Data Logging & Read SD Data Simulation](https://wokwi.com/projects/341793063678509650)
- [Youtube video demo](https://youtu.be/Ho3e2A5L66Y)
- [Github Documentation](https://github.com/hirbondi/Experiment/blob/main/Smart%20Light%20and%20Exhaust%20Fan%20for%20Restroom/API.yaml)

Simulasi projek ini dilakukan di dua web yang berbeda, yaitu _tinkercad.com_ dan _wokwi.com_ karena keterbatasan komponen yang tersedia dari masing-masing web. Untuk proses akuisisi data sensor dilakukan di _tinkercad.com_, sedangkan logging data ke micro SD dilakukan di _wokwi.com_.

***

###Secara umum cara kerja alat ini adalah sebagai berikut :
1. Default interval pembacaan nilai sensor adalah setiap satu detik.
2. Sensor PIR digunakan untuk mendeteksi keberadaan orang di dalam kamar mandi melalui gerakan di dalam range deteksi sensor.
3. Ketika sensor PIR mendeteksi gerakan, maka akan mentrigger LED putih dan LED orange untuk menyala.
4. Dalam 1-3 detik berikutnya ketika sensor tidak mendeteksi adanya gerakan, maka akan mentrigger sebuah timer (default 15 detik) yang akan melakukan hitung mundur untuk mematikan LED putih dan LED orange.
5. Jika dalam rentang waktu hitung mundur tersebut sensor PIR mendeteksi suatu gerakan, maka timer akan mereset ke hitungan awal lagi.
6. Sensor gas digunakan untuk memonitor dan mendeteksi bau tidak sedap yang nilainya melebihi batas tertentu (default 500 VADC). Nilai deteksi suatu senyawa gas umumnya dilakukan dalam satuan _parts_per_million_ (ppm), namun saat ini satuan tersebut diabaikan karena memerlukan proses kalibrasi lebih lanjut.
7. Kembali ke poin nomor 4, ketika  counter timer sudah habis maka LED putih akan padam. Sedangkan LED orange akan mengecek terlebih dahulu nilai dari pembacaan sensor gas. Apabila nilainya di bawah batas, maka LED orange juga akan padam. Namun apabila nilainya masih di atas batas, maka LED orange masih akan menyala hingga nilai pembacaan sensor gas tersebut turun di bawah batas.
8. Data logging dari pembacaan sensor dilakukan setiap detik ke sebuah micro SD melalui modul micro SD. File log dapat dibuka dan ditampilkan seluruh isinya ke serial monitor melalui command serial monitor.
9. Terdapat beberapa command yang bisa diinputkan ke dalam serial monitor Arduino IDE, baik di _tinkercad.com_ maupun di _wokwi.com_

***

###Interface command serial monitor pada ***tinkercad.com***:
- ***/help*** = untuk menampilkan informasi command apa saja yang tersedia di dalam serial monitor.
- ***/?***  = untuk menampilkan informasi command apa saja yang tersedia di dalam serial monitor.
- ***/stream 1*** = untuk menampilkan data-data _realtime_ Lamp status; Exhaust fan status; PIR sensor value; Gas sensor value; Lamp OFF Counter ke serial monitor.
- ***/stream 0*** = untuk menyembunyikan data-data _realtime_ dari serial monitor.
- ***/nilai1,nilai2,nilai3*** = untuk memasukkan input data integer. _nilai1_: batas nilai gas, _nilai2_: counter timer, _nilai3_: interval perulangan. Contoh : _/500,15,1_

###Interface command serial monitor pada ***wokwi.com***:
- ***/readSD*** = untuk membaca dan menampilkan seluruh data yang tersimpan di dalam file microSD ke serial monitor.

***

###Petunjuk pengoperasian simulasi ***tinkercad.com*** :
1. Buka link simulasi [Data Acquisition & Input Parameter Simulation](https://www.tinkercad.com/things/8VQjDwv1EwX?sharecode=6m6rZR8Xpvfb2RmDj3n5h9iKUaeYaXKtgQNOwsDkSSc).
2. Tekan "***Simulate***" button di sebelah kiri bawah.
3. Tekan "***Start Simulation***" di sebelah atas window simulasi.
4. Untuk menampilkan serial monitor, tekan "***Code***" button di sebelah atas window simulasi. Kemudian tekan "***Serial Monitor***" button di bawah listing program. Untuk menutup serial monitor, tekan "Code" button lagi.
5. Untuk memindahkan/ menggerakkan objek deteksi PIR, tekan dahulu sensor PIR (breadboard kiri) hingga muncul animasi bentuk bulat yang terhubung garis putus-putus. Objek bulat tersebut dapat digeser di dalam area deteksi maupun diluar area deteksi.
6. Untuk melakukan variasi besaran deteksi senyawa gas, tekan terlebih dahulu sensor gas (breadboard kanan) hingga muncul animasi berupa asap abu-abu. Objek asap tersebut dapat digeser mendekati maupun menjauhi sensor gas. Semakin dekat jaraknya maka nilai deteksi sensor gas akan semakin besar.

###Petunjuk pengoperasian simulasi ***wokwi.com*** :
1. Buka link simulasi [Data Logging & Read SD Data Simulation](https://wokwi.com/projects/341793063678509650)
2. Tekan button hijau bertanda play atau segitiga.
3. Di sebelah kanan akan otomatis muncul print writing... di serial monitor yang menandakan data logging ke micro SD.
4. Untuk membaca dan menampilkan seluruh data hasil logging, dapat langsung menuliskan command ***/readSD*** ke serial monitor.
5. Data yang terdapat di wokwi ini sebatas dummy karena tidak terkoneksi dengan data di tinkercad.com. Namun format data dan variable yang digunakan sudah disesuaikan dengan data yang terdapat di tinkercad.com

***

###Gambar schematic :

![Data Acquisition Schematic](https://github.com/hirbondi/Experiment/blob/main/Smart%20Light%20and%20Exhaust%20Fan%20for%20Restroom/Data%20Acquisition%20&%20Input%20Parameter%20Schematic.png?raw=true)

![Data Logger Schematic](https://github.com/hirbondi/Experiment/blob/main/Smart%20Light%20and%20Exhaust%20Fan%20for%20Restroom/Data%20Logging%20&%20Read%20SD%20Data%20Schematic.PNG?raw=true)