# ELVIS

* Программа запрашивает путь к файлам, которые необходимо распарсить.
* Примером служат файлы ab.txt и hd.txt, находящиеся в корневой папке.
* Файлы запрашиваются до тех пор, пока не придет пустая строка.
* В запросе разделители необходимо так же вводить через Enter.
* Примером могут служить "!?."
* 
* Количество потоков зависит от количества обрабатываемых файлов.
* Каждый поток работает с отдельным файлом.
* Для удобства в выходной файл и консоль записываются 
* подстрока, файл, откуда она взята и номер подстроки.
* 
* Результат записывается в выходной файл out.txt, находящийся в корневой папке.
