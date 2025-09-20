import random
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time
def draw_bars(values, color_indexes=None):
    #Burada kolonları çizdiriyorum. 'color_indexes' içine hangi indeksleri koyarsak,
    #o kolonlar kırmızıya boyanıyor. Geri kalanlar mavi olacak.
    if color_indexes is None:
        color_indexes = []
    # Önce herkes mavi oluyo
    colors = ['blue'] * len(values)
    # color_indexes listesindekileri kırmızı yapıyorum
    for i in color_indexes:
        if 0 <= i < len(values):
            colors[i] = 'red'
    plt.bar(range(len(values)), values, color=colors)
def bubble_sort(data):
    #Bubble Sort: Yan yana duran elemanları karşılaştırıp büyük olanı sağa taşıyorum.
    #Her değişim (swap) sonrası listeyi dönüyorum ki animasyonda görelim.
    arr = data.copy()
    n = len(arr)
    for i in range(n):                                                  #
        for j in range(n - i - 1):                                      #
            if arr[j] > arr[j + 1]:                                     #
                arr[j], arr[j + 1] = arr[j + 1], arr[j]                 #
                yield arr, (j, j + 1)
def selection_sort(data):
    #Selection Sort: Her seferinde en küçük elemanı bulup başa alıyorum.
    #Swap işlemini yaptığımda da 'yield' ediyorum ki görselde değişimi izleyelim.
    arr = data.copy()
    n = len(arr)
    for i in range(n):
        min_index = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]
        yield arr, (i, min_index)
def insertion_sort(data):
    #Insertion Sort: Dizideki her elemanı, kendisinden önceki elemanlarla karşılaştırarak
    #doğru yerine yerleştiriyorum. Her yerleştirme veya kaydırma aşamasında listeyi dönüyorum.
    arr = data.copy()
    for i in range(1, len(arr)):
        key = arr[i] #key şuan sıralanan eleman
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
            yield arr, (j + 1, j + 2) #diyerek hangi indekslerin kırmızı olacağını da belirtiyoruz.
        arr[j + 1] = key
        yield arr, (j + 1, i) #diyerek hangi indekslerin kırmızı olacağını da belirtiyoruz.
def merge_sort(data, start=0, end=None):
    #Merge Sort: Listeyi bölerek (divide) sıralıyorum, ardından parçaları birleştirerek (merge)
    #sıralı hale getiriyorum. Her parçanın birleştirilmesinde güncel listeyi dönüyorum.
    if end is None:
        arr = data.copy()
        end = len(arr) - 1
    else:
        arr = data
    if start < end:
        mid = (start + end) // 2
        yield from merge_sort(arr, start, mid)
        yield from merge_sort(arr, mid + 1, end)
        yield from merge(arr, start, mid, end)
    yield arr, None
def merge(arr, start, mid, end):
    #Merge aşamasında, iki sıralı alt listeyi birleştirip tek parça haline getiriyorum.
    #Her eklemede listeyi dönüyorum ki animasyonda kısmi sıralamayı görebilelim.
    left = arr[start:mid + 1]
    right = arr[mid + 1:end + 1]
    i, j = 0, 0
    k = start
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            arr[k] = left[i]
            i += 1
        else:
            arr[k] = right[j]
            j += 1
        k += 1
        yield arr, (k - 1,)

    while i < len(left):
        arr[k] = left[i]
        i += 1
        k += 1
        yield arr, (k - 1,)

    while j < len(right):
        arr[k] = right[j]
        j += 1
        k += 1
        yield arr, (k - 1,)
def heap_sort(data):
    #Heap Sort: Diziyi önce bir max-heap yapısına dönüştürüyorum. Sonra en büyük elemanı sona
    #atıyorum ve kalan kısmı tekrar heapify yapıyorum. Her swap adımından sonra listeyi dönüyorum.
    arr = data.copy()
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        yield from heapify(arr, n, i)

    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        yield arr, (0, i)
        yield from heapify(arr, i, 0)
    yield arr, None
def heapify(arr, n, i):
    #heapify: Alt ağaçların da 'heap' özelliğini korumasını sağlıyorum.
    #Bunu yaparken gerekli olduğunda swap edip, alt düğümlerde de devam ediyorum.
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2
    if left < n and arr[left] > arr[largest]:
        largest = left
    if right < n and arr[right] > arr[largest]:
        largest = right
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        yield arr, (i, largest)
        yield from heapify(arr, n, largest)
def counting_sort_for_radix(arr, exp):
    #Radix Sort içindeki yardımcı Counting Sort fonksiyonu.
    #Belirli bir digit (exp) üzerinden diziyi sıralıyor.
    n = len(arr)
    output = [0] * n
    count = [0] * 10
    for i in range(n):
        index = arr[i] // exp
        count[index % 10] += 1
    for i in range(1, 10):
        count[i] += count[i - 1]
    i = n - 1
    while i >= 0:
        index = arr[i] // exp
        output[count[index % 10] - 1] = arr[i]
        count[index % 10] -= 1
        i -= 1
    for i in range(n):
        arr[i] = output[i]
def radix_sort(data):
    #Radix Sort: Diziyi en küçük basamaktan başlayarak sırayla sıralıyorum her basamak sıralandıktan sonra 'yield' ile o anki halini gösteriyorum.
    arr = data.copy()
    max_val = max(arr)
    exp = 1
    while max_val // exp > 0:
        counting_sort_for_radix(arr, exp)
        yield arr, None
        exp *= 10
def visualize_sort(data, sort_func):
    #Seçilen sıralama fonksiyonunun 'yield' ettiği her adım içinmatplotlib'te kolonları yeniliyorum. Böylece sıralama süreciniadım adım izlemek mümkün oluyor.
    fig, ax = plt.subplots()
    plt.title(f"{sort_func.__name__} Visualization")
    # Sort fonksiyonundan (arr, highlight) şeklinde gelecek adımları tutan bir generator
    generator = sort_func(data)

    def update(frame):
        time.sleep(2)
        arr, highlight = frame
        ax.clear()

        if highlight:
            draw_bars(arr, highlight)
        else:
            draw_bars(arr)
        ax.set_ylim(0, max(data) + 1)
        ax.set_xticks([])

    ani = animation.FuncAnimation(
        fig,
        update,
        frames=generator,
        interval=500,
        repeat=False
    )
    plt.show()
def main():
    print("Hangi sıralama algoritmasını izlemek istersin?")
    print("1) Bubble Sort")
    print("2) Selection Sort")
    print("3) Insertion Sort")
    print("4) Merge Sort")
    print("5) Heap Sort")
    print("6) Radix Sort")
    choice = input("Seçim: ")
    # Rastgele bir liste oluşturuyorum
    data_size = 10
    data = [random.randint(1, 100) for _ in range(data_size)]
    print("Sıralanacak liste:", data)
    if choice == '1':
        visualize_sort(data, bubble_sort)
    elif choice == '2':
        visualize_sort(data, selection_sort)
    elif choice == '3':
        visualize_sort(data, insertion_sort)
    elif choice == '4':
        visualize_sort(data, merge_sort)
    elif choice == '5':
        visualize_sort(data, heap_sort)
    elif choice == '6':
        visualize_sort(data, radix_sort)
    else:
        print("Geçerli bir seçenek girmedin...")
while True:
    if __name__ == "__main__":
        main()