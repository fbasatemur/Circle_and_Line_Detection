# Circle and Line Detection With Hough Transform

* GUI: Windows Form Application / C++

# Hedef:
Görüntü üzerinde Canny Edge Detection işlemi ile kenar tespitinin yapılması sonucunda, Hough Space algoritması kullanılarak image üzerinde line/circle tespiti.

# Steps:
1.	Intensity image üzerine 2.Mertebeden [3 * 3] Gaussian Filter kullanarak Smoothing uygula
2.	Smoothing uygulanmıs görüntüden Magnitude ve Direction bilgilerini bul
3.	Magnitude Image üzerinden histogram bilgilerini oluştur
4.	Histogram grafinini chart ile çiz
5.	Canny Edge Detection ile kenar tespiti:
    - 5.1	NonMaximalSuppression işlemi ile kenarlar inceltilir.
    - 5.2	HysteresisThreashold işlemine verilen 2 threshold değerine göre kenarlar belirlenir.
6.	CannyEdgeD sonucu kenar görüntüsünü (Magnitude Image) ekrana yansıt
7.	Çizilecek maksimum LINE/CIRCLE sayısını oku
8.	LINE Tespiti:
    - 8.1.	Kenar tespiti için houghSpace’e Hough Transform yap
    - 8.2.	İstenilen sayıda Hough Space’den maksimum kenarları bul.
    - 8.3.	Image üzerine maksimum kenarları işaretle
    - 8.4.	Sonucu ekrana yansıt
9.	CIRCLE Tespiti:
    - 9.1.	Circle yarıçapını textBox’tan oku
    - 9.2.	Circle tespiti için houghSpace’e Hough Transform yap
    - 9.3.	Hough Space’den Circle olma ihtimali en yüksek noktaları bul
    - 9.4.	Bulunan noktalara Circle çiz
    - 9.5.	Sonucu ekrana yansıt
10.	Hough Space’i ekrana yansıt
